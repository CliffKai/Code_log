#!/usr/bin/env python3
import csv, json, time, urllib.parse, urllib.request
from datetime import datetime, timezone, timedelta
from pathlib import Path

TARGET='2026-07-21'; BEG='2025-12-01'
SERIES=[
('上证指数','000001.SH','1.000001','东方财富指数日K，不复权'),
('科创50','000688.SH','1.000688','东方财富指数日K，不复权'),
('创业板指','399006.SZ','0.399006','东方财富指数日K，不复权'),
('CPO概念','BK1128','90.BK1128','东方财富概念板块日K，不复权'),
('PCB','BK0877','90.BK0877','东方财富概念板块日K，不复权'),
('存储芯片','BK1137','90.BK1137','东方财富概念板块日K，不复权'),
('半导体设备','BK1326','90.BK1326','东方财富概念板块日K，不复权'),
('半导体材料','BK1325','90.BK1325','东方财富概念板块日K，不复权')]
FIELDS=['date','open','close','high','low','volume','amount','amplitude','supplier_pct','supplier_change','turnover']
OUT=Path('a_share_output'); RAW=OUT/'raw_json'; RAW.mkdir(parents=True,exist_ok=True)
HEADERS={'User-Agent':'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 Chrome/126 Safari/537.36','Referer':'https://quote.eastmoney.com/','Accept':'application/json,text/plain,*/*'}
FETCH_LOG=[]

def decode_payload(raw):
    text=raw.decode('utf-8','replace').strip()
    try: return json.loads(text)
    except json.JSONDecodeError:
        start=text.find('{'); end=text.rfind('}')
        if start>=0 and end>start: return json.loads(text[start:end+1])
        raise

def fetch(secid):
    q=urllib.parse.urlencode({'secid':secid,'klt':'101','fqt':'0','fields1':'f1,f2,f3,f4,f5,f6','fields2':'f51,f52,f53,f54,f55,f56,f57,f58,f59,f60,f61','lmt':'100000','beg':BEG.replace('-',''),'end':TARGET.replace('-','')})
    hosts=['push2his.eastmoney.com','1.push2his.eastmoney.com','8.push2his.eastmoney.com','33.push2his.eastmoney.com']
    candidates=[]
    for host in hosts:
        direct=f'https://{host}/api/qt/stock/kline/get?{q}'
        candidates.append(('direct',direct,direct))
    canonical=f'https://push2his.eastmoney.com/api/qt/stock/kline/get?{q}'
    candidates.append(('r.jina.ai',f'https://r.jina.ai/{canonical}',canonical))
    errors=[]
    for mode,url,canonical_url in candidates:
        for attempt in range(2):
            try:
                req=urllib.request.Request(url,headers=HEADERS)
                with urllib.request.urlopen(req,timeout=8 if mode=='direct' else 30) as resp:
                    payload=decode_payload(resp.read())
                if payload.get('rc')==0 and payload.get('data',{}).get('klines'):
                    FETCH_LOG.append({'secid':secid,'mode':mode,'request_url':url,'canonical_url':canonical_url,'attempt':attempt+1,'status':'success'})
                    return payload,url,canonical_url,mode
                errors.append(f'{mode} invalid payload')
            except Exception as exc:
                errors.append(f'{mode} {type(exc).__name__}: {exc}')
                time.sleep(.5*(attempt+1))
    FETCH_LOG.append({'secid':secid,'status':'failed','errors':errors[-8:]})
    raise RuntimeError(f'{secid} all transports failed: '+' | '.join(errors[-8:]))

def parse(payload):
    rows=[]
    for raw in payload['data']['klines']:
        vals=raw.split(',')
        if len(vals)!=11: raise ValueError(f'K线字段数异常: {raw}')
        row={'date':vals[0]}
        for key,val in zip(FIELDS[1:],vals[1:]): row[key]=float(val)
        rows.append(row)
    rows.sort(key=lambda x:x['date'])
    return rows

fetched_at=datetime.now(timezone(timedelta(hours=8))).isoformat(timespec='seconds')
results=[]; validations=[]; calendars={}
for name,code,secid,scope in SERIES:
    payload,transport_url,canonical_url,mode=fetch(secid)
    raw_path=RAW/f"{secid.replace('.','_')}.json"
    raw_path.write_text(json.dumps(payload,ensure_ascii=False,indent=2),encoding='utf-8')
    rows=parse(payload); by={r['date']:r for r in rows}; cur=by.get(TARGET)
    if cur is None: raise RuntimeError(f'{name} 缺少目标日期 {TARGET}; last={rows[-1]["date"]}')
    prevs=[r for r in rows if r['date']<TARGET]; yends=[r for r in rows if r['date']<'2026-01-01']
    if not prevs or not yends: raise RuntimeError(f'{name} 缺少前收或年末基准')
    prev=prevs[-1]; yend=yends[-1]
    rec_chg=cur['close']-prev['close']; rec_pct=(cur['close']/prev['close']-1)*100
    diff_bp=(cur['supplier_pct']-rec_pct)*100; ytd=(cur['close']/yend['close']-1)*100
    ohlc=cur['low']<=min(cur['open'],cur['close']) and cur['high']>=max(cur['open'],cur['close']) and cur['low']<=cur['high']
    calendars[name]={r['date'] for r in rows if r['date']>='2026-01-01'}
    results.append({'名称':name,'代码':code,'secid':secid,'口径':scope,'日期':cur['date'],'开盘':cur['open'],'最高':cur['high'],'最低':cur['low'],'收盘':cur['close'],'供应商涨跌额':cur['supplier_change'],'供应商涨跌幅':cur['supplier_pct'],'复算涨跌额':round(rec_chg,6),'复算涨跌幅':round(rec_pct,6),'供应商涨跌幅与复算涨跌幅差异_bp':round(diff_bp,6),'年初至今涨跌幅':round(ytd,6),'成交量':cur['volume'],'成交额':cur['amount'],'振幅':cur['amplitude'],'换手率':cur['turnover'],'前一交易日':prev['date'],'前一交易日收盘':prev['close'],'年末基准日':yend['date'],'年末基准收盘':yend['close'],'规范数据源':canonical_url,'实际传输路径':transport_url,'传输方式':mode,'抓取时间':fetched_at})
    validations.append({'name':name,'secid':secid,'response_name':payload['data'].get('name'),'records_fetched':len(rows),'first_date':rows[0]['date'],'last_date':rows[-1]['date'],'target_present':True,'previous_trading_date':prev['date'],'year_end_base_date':yend['date'],'duplicate_dates':len(rows)-len(by),'strictly_increasing':all(rows[i]['date']<rows[i+1]['date'] for i in range(len(rows)-1)),'ohlc_valid':ohlc,'supplier_vs_recalc_diff_bp':round(diff_bp,6),'supplier_change_vs_recalc_abs_diff':round(abs(cur['supplier_change']-rec_chg),6),'raw_file':str(raw_path),'canonical_url':canonical_url,'transport_url':transport_url,'transport_mode':mode})
    time.sleep(.2)

ref=calendars['上证指数']; checks={n:{'missing_vs_reference':sorted(ref-d),'extra_vs_reference':sorted(d-ref)} for n,d in calendars.items()}
summary={'target_date':TARGET,'fetched_at':fetched_at,'series_expected':8,'series_succeeded':len(results),'all_target_rows_present':len(results)==8,'all_ohlc_valid':all(v['ohlc_valid'] for v in validations),'all_no_duplicates':all(v['duplicate_dates']==0 for v in validations),'all_strictly_increasing':all(v['strictly_increasing'] for v in validations),'all_calendars_aligned':all(not x['missing_vs_reference'] and not x['extra_vs_reference'] for x in checks.values()),'series':validations,'calendar_checks':checks,'fetch_log':FETCH_LOG}
cols=list(results[0].keys())
with (OUT/'target_day_20260721.csv').open('w',encoding='utf-8-sig',newline='') as f:
    w=csv.DictWriter(f,fieldnames=cols); w.writeheader(); w.writerows(results)
(OUT/'validation.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),encoding='utf-8')
(OUT/'results.json').write_text(json.dumps(results,ensure_ascii=False,indent=2),encoding='utf-8')
(OUT/'fetch_log.json').write_text(json.dumps(FETCH_LOG,ensure_ascii=False,indent=2),encoding='utf-8')
lines=['# 2026-07-21 A股 8 序列数据','',f'- 抓取时间：{fetched_at}',f'- 成功序列：{len(results)}/8',f"- 交易日历一致：{summary['all_calendars_aligned']}",f"- 无重复日期：{summary['all_no_duplicates']}",f"- OHLC 全部合理：{summary['all_ohlc_valid']}",'','| 名称 | 收盘 | 涨跌幅(%) | 复算涨跌幅(%) | 差异(bp) | YTD(%) | 前一交易日 | 年末基准日 |','|---|---:|---:|---:|---:|---:|---|---|']
for r in results: lines.append(f"| {r['名称']} | {r['收盘']:.2f} | {r['供应商涨跌幅']:.2f} | {r['复算涨跌幅']:.6f} | {r['供应商涨跌幅与复算涨跌幅差异_bp']:.4f} | {r['年初至今涨跌幅']:.6f} | {r['前一交易日']} | {r['年末基准日']} |")
(OUT/'report.md').write_text('\n'.join(lines)+'\n',encoding='utf-8')
print(json.dumps(summary,ensure_ascii=False,indent=2))
