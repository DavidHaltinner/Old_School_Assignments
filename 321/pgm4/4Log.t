Assignment: buffer pool ; LRU Replacement
Written by: David Haltinner

database file:	Records01.bin
command file:	4Test.t
log file:	4Log.t

buffer	64  5

show	17
     buffer pool: insert page into frame 0
     16  dpyovi  13122  29585

show	23
     buffer pool: insert page into frame 1
     20  jokete  19345  9907

show	22
     buffer pool: insert page into frame 2
     20  jokete  19345  9907

show	21
     buffer pool: record found in frame 1
     buffer pool: record now in frame 2
     20  jokete  19345  9907

show	31
     buffer pool: insert page into frame 3
     28  dawzqs  3935  21030

show	3
     buffer pool: insert page into frame 4
     0  hapjia  175  400

show	4
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4
     4  czbmdd  28888  17445

show	5
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4
     4  czbmdd  28888  17445

show	13
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4
     12  gmcyvd  28793  27166

show	9
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4
     8  tpffms  9102  2386

debug

update	4	ABCDEF	1	1
     buffer pool: record found in frame 1
     buffer pool: updating record in frame 1
     buffer pool: record now in frame 4

update	13	GHIJKL	2	2
     buffer pool: record found in frame 2
     buffer pool: updating record in frame 2
     buffer pool: record now in frame 4

update	18	MNOPQR	3	3
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4

update	31	STUVWX	4	4
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4

update	22	YZABCD	5	5
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4

debug

update	50	000001	6	6
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4

update	60	000002	7	7
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4

debug

show	50
     buffer pool: record found in frame 3
     buffer pool: record now in frame 4
     1         16  -1073751920

update	30	000003	8	8
     buffer pool: record found in frame 1
     buffer pool: updating record in frame 1
     buffer pool: record now in frame 4

update	40	000004	9	9
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4

debug

show	18
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4
     1         16  -1073751920

debug

update	9	000005	10	10
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4

debug

exit
     buffer pool flush: frame 4
     buffer pool flush: frame 3
     buffer pool flush: frame 2
     buffer pool flush: frame 1
     buffer pool flush: frame 0

Statistics
     hits:              5
     misses:           17
     write backs:      11
