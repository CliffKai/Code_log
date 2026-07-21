#!/usr/bin/env python3
import json, urllib.parse, urllib.request
from pathlib import Path

TARGET='2026-07-21'; BEG='2025-12-01'
SERIES=[('上证指数','1.000001'),('科创50','1.000688'),('创业板指','0.399006'),('CPO概念','90.BK1128'),('PCB','90.BK0877'),('存储芯片','90.BK1137'),('半导体设备','90.BK1326'),('半导体材料','90.BK1325')]
OUT=Path('a_share_output'); OUT.mkdir(exist_ok=True); (OUT/'raw_history').mkdir(exist_ok=True); (OUT/'raw_quote').mkdir(exist_ok=True)
HEADERS={'User-Agent':'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 Chrome/126 Safari/537.36','Referer':'https://quote.eastmoney.com/','Accept':'application/json,text/plain,*/*'}

def decode(raw):
    text=raw.decode('utf-8','replace').strip(); a=text.find('{'); b=text.rfind('}')
    if a<0 or b<a: raise ValueError(text[:300])
    return json.loads(text[a:b+1])

def get_json(canonical):
    direct=[canonical]
    if canonical.startswith('https://push2his.eastmoney.com'):
        direct += [canonical.replace('https://push2his','http://push2his'),canonical.replace('push2his.eastmoney.com','1.push2his.eastmoney.com')]
    if canonical.startswith('https://push2.eastmoney.com'):
        direct += [canonical.replace('https://push2','http://push2'),canonical.replace('push2.eastmoney.com','1.push2.eastmoney.com')]
    candidates=direct+[f'https://r.jina.ai/http://{u}' for u in direct[:2]]+[f'https://r.jina.ai/{canonical}']
    errors=[]
    for url in candidates:
        try:
            req=urllib.request.Request(url,headers=HEADERS)
            with urllib.request.urlopen(req,timeout=15) as r: payload=decode(r.read())
            if payload.get('rc')==0 and payload.get('data'):
                return payload,url
            errors.append(f'{url} invalid')
        except Exception as e: errors.append(f'{url} {type(e).__name__}: {e}')
    raise RuntimeError(' | '.join(errors[-6:]))

report=[]
for name,secid in SERIES:
    hq=urllib.parse.urlencode({'secid':secid,'klt':'101','fqt':'0','fields1':'f1,f2,f3,f4,f5,f6','fields2':'f51,f52,f53,f54,f55,f56,f57,f58,f59,f60,f61','lmt':'100000','beg':BEG.replace('-',''),'end':TARGET.replace('-','')})
    history_url=f'https://push2his.eastmoney.com/api/qt/stock/kline/get?{hq}'
    qq=urllib.parse.urlencode({'secid':secid,'fields':'f43,f44,f45,f46,f47,f48,f57,f58,f59,f60,f86,f168,f169,f170,f171'})
    quote_url=f'https://push2.eastmoney.com/api/qt/stock/get?{qq}'
    item={'name':name,'secid':secid}
    try:
        hp,hu=get_json(history_url); (OUT/'raw_history'/f"{secid.replace('.','_')}.json").write_text(json.dumps(hp,ensure_ascii=False,indent=2),encoding='utf-8')
        ks=hp['data'].get('klines') or []; item['history_transport']=hu; item['history_last']=ks[-1] if ks else None; item['history_count']=len(ks)
    except Exception as e: item['history_error']=repr(e)
    try:
        qp,qu=get_json(quote_url); (OUT/'raw_quote'/f"{secid.replace('.','_')}.json").write_text(json.dumps(qp,ensure_ascii=False,indent=2),encoding='utf-8')
        item['quote_transport']=qu; item['quote_data']=qp.get('data')
    except Exception as e: item['quote_error']=repr(e)
    report.append(item)
    print(json.dumps(item,ensure_ascii=False),flush=True)
(OUT/'diagnostics.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
