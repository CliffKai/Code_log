#!/usr/bin/env python3
import csv, json, time, urllib.parse, urllib.request
from datetime import datetime, timezone, timedelta
from pathlib import Path

TARGET='2026-07-20'; BEG='2025-12-01'
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

def decode_payload(raw: bytes):
    text=raw.decode('utf-8','replace').strip()
    # r.jina.ai may prepend a small text wrapper; locate the JSON object.
    start=text.find('{'); end=text.rfind('}')
    if start < 0 or end < start: raise ValueError('response has no JSON object')
    return json.loads(text[start:end+1])

def fetch(secid):
    q=urllib.parse.urlencode({'secid':secid,'klt':'101','fqt':'0','fields1':'f1,f2,f3,f4,f5,f6','fields2':'f51,f52,f53,f54,f55,f56,f57,f58,f59,f60,f61','lmt':'100000','beg':BEG.replace('-',''),'end':TARGET.replace('-','')})
    direct=[]
    for host in ['push2his.eastmoney.com','1.push2his.eastmoney.com','7.push2his.eastmoney.com','18.push2his.eastmoney.com','31.push2his.eastmoney.com','55.push2his.eastmoney.com','88.push2his.eastmoney.com']:
        direct += [f'https://{host}/api/qt/stock/kline/get?{q}', f'http://{host}/api/qt/stock/kline/get?{q}']
    candidates=direct + [f'https://r.jina.ai/http://{u}' for u in direct[:2]] + [f'https://r.jina.ai/https://push2his.eastmoney.com/api/qt/stock/kline/get?{q}']
    errors=[]
    for url in candidates:
        try:
            req=urllib.request.Request(url,headers=HEADERS)
            with urllib.request.urlopen(req,timeout=12) as r: payload=decode_payload(r.read())
            if payload.get('rc')==0 and payload.get('data',{}).get('klines'):
                print(f'OK {secid} via {url.split("?")[0]}',flush=True)
                return payload,url
            errors.append(f'{url}: invalid payload')
        except Exception as exc:
            errors.append(f'{url}: {type(exc).__name__}: {exc}')
    raise RuntimeError('all fast candidates failed: '+' | '.join(errors[-8:]))

def parse(payload):
    rows=[]
    for raw in payload['data']['klines']:
        vals=raw.split(',')
        if len(vals)!=11: raise ValueError(raw)
        row={'date':vals[0]}
        for k,v in zip(FIELDS[1:],vals[1:]): row[k]=float(v)
        rows.append(row)
    return sorted(rows,key=lambda x:x['date'])

fetched_at=datetime.now(timezone(timedelta(hours=8))).isoformat(timespec='seconds')
results=[]; validations=[]; calendars={}
for name,code,secid,scope in SERIES:
    print(f'FETCH {name} {secid}',flush=True)
    payload,url=fetch(secid)
    (RAW/f"{secid.replace('.','_')}.json").write_text(json.dumps(payload,ensure_ascii=False,indent=2),encoding='utf-8')
    rows=parse(payload); by={r['date']:r for r in rows}; cur=by.get(TARGET)
    prevs=[r for r in rows if r['date']<TARGET]; yends=[r for r in rows if r['date']<'2026-01-01']
    if cur is None or not prevs or not yends: raise RuntimeError(f'{name} missing target/previous/year-end base')
    prev=prevs[-1]; yend=yends[-1]
    rec_chg=cur['close']-prev['close']; rec_pct=(cur['close']/prev['close']-1)*100
    diff_bp=(cur['supplier_pct']-rec_pct)*100; ytd=(cur['close']/yend['close']-1)*100
    ohlc=cur['low']<=min(cur['open'],cur['close']) and cur['high']>=max(cur['open'],cur['close']) and cur['low']<=cur['high']
    calendars[name]={r['date'] for r in rows if r['date']>='2026-01-01'}
    results.append({'名称':name,'代码':code,'secid':secid,'口径':scope,'日期':cur['date'],'开盘':cur['open'],'最高':cur['high'],'最低':cur['low'],'收盘':cur['close'],'供应商涨跌额':cur['supplier_change'],'供应商涨跌幅':cur['supplier_pct'],'复算涨跌额':round(rec_chg,6),'复算涨跌幅':round(rec_pct,6),'供应商涨跌幅与复算涨跌幅差异_bp':round(diff_bp,6),'年初至今涨跌幅':round(ytd,6),'成交量':cur['volume'],'成交额':cur['amount'],'振幅':cur['amplitude'],'换手率':cur['turnover'],'前一交易日':prev['date'],'前一交易日收盘':prev['close'],'年末基准日':yend['date'],'年末基准收盘':yend['close'],'数据源':url,'抓取时间':fetched_at})
    validations.append({'name':name,'secid':secid,'response_name':payload['data'].get('name'),'records_fetched':len(rows),'first_date':rows[0]['date'],'last_date':rows[-1]['date'],'target_present':True,'previous_trading_date':prev['date'],'year_end_base_date':yend['date'],'duplicate_dates':len(rows)-len(by),'strictly_increasing':all(rows[i]['date']<rows[i+1]['date'] for i in range(len(rows)-1)),'ohlc_valid':ohlc,'supplier_vs_recalc_diff_bp':round(diff_bp,6),'supplier_change_vs_recalc_abs_diff':round(abs(cur['supplier_change']-rec_chg),6),'source_url':url})

ref=calendars['上证指数']; checks={n:{'missing_vs_reference':sorted(ref-d),'extra_vs_reference':sorted(d-ref)} for n,d in calendars.items()}
summary={'target_date':TARGET,'fetched_at':fetched_at,'series_expected':8,'series_succeeded':len(results),'all_target_rows_present':len(results)==8,'all_ohlc_valid':all(v['ohlc_valid'] for v in validations),'all_no_duplicates':all(v['duplicate_dates']==0 for v in validations),'all_calendars_aligned':all(not x['missing_vs_reference'] and not x['extra_vs_reference'] for x in checks.values()),'series':validations,'calendar_checks':checks}
cols=list(results[0].keys())
with (OUT/'target_day_20260720.csv').open('w',encoding='utf-8-sig',newline='') as f:
    w=csv.DictWriter(f,fieldnames=cols); w.writeheader(); w.writerows(results)
(OUT/'validation.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),encoding='utf-8')
(OUT/'results.json').write_text(json.dumps(results,ensure_ascii=False,indent=2),encoding='utf-8')
lines=['# 2026-07-20 A股 8 序列数据','',f'- 抓取时间：{fetched_at}',f"- 成功序列：{len(results)}/8",f"- 交易日历一致：{summary['all_calendars_aligned']}",f"- 无重复日期：{summary['all_no_duplicates']}",f"- OHLC 全部合理：{summary['all_ohlc_valid']}",'','| 名称 | 收盘 | 涨跌幅(%) | 复算涨跌幅(%) | 差异(bp) | YTD(%) | 前一交易日 | 年末基准日 |','|---|---:|---:|---:|---:|---:|---|---|']
for r in results: lines.append(f"| {r['名称']} | {r['收盘']:.2f} | {r['供应商涨跌幅']:.2f} | {r['复算涨跌幅']:.6f} | {r['供应商涨跌幅与复算涨跌幅差异_bp']:.4f} | {r['年初至今涨跌幅']:.6f} | {r['前一交易日']} | {r['年末基准日']} |")
(OUT/'report.md').write_text('\n'.join(lines)+'\n',encoding='utf-8')
print(json.dumps(summary,ensure_ascii=False,indent=2),flush=True)
