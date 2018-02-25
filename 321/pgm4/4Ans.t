Assignment: buffer pool ; LRU Replacement
Written by: Andrew Perrie

database file:	Records01.bin
command file:	4Test.t
log file:	4Log.t

buffer	64  5

show	17
     buffer pool: insert page into frame 0
     17  guyudm  2847  9930

show	23
     buffer pool: insert page into frame 1
     23  zggzfy  2424  3074

show	22
     buffer pool: record found in frame 1
     buffer pool: record now in frame 1
     22  lzgukf  1991  4593

show	21
     buffer pool: record found in frame 1
     buffer pool: record now in frame 1
     21  ezfsli  7417  28890

show	31
     buffer pool: insert page into frame 2
     31  pkeqjr  26757  7961

show	3
     buffer pool: insert page into frame 3
     3  shnxwj  9190  7040

show	4
     buffer pool: insert page into frame 4
     4  czbmdd  28888  17445

show	5
     buffer pool: record found in frame 4
     buffer pool: record now in frame 4
     5  romtvt  27469  29923

show	13
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4
     13  tsxrlb  18260  17612

show	9
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4
     9  rdftod  16625  23767

debug

update	4	ABCDEF	1	1
     buffer pool: record found in frame 2
     buffer pool: updating record in frame 2
     buffer pool: record now in frame 4

update	13	GHIJKL	2	2
     buffer pool: record found in frame 2
     buffer pool: updating record in frame 2
     buffer pool: record now in frame 4

update	18	MNOPQR	3	3
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4
     buffer pool: updating record in frame 4
     buffer pool: record now in frame 4

update	31	STUVWX	4	4
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4
     buffer pool: updating record in frame 4
     buffer pool: record now in frame 4

update	22	YZABCD	5	5
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4
     buffer pool: updating record in frame 4
     buffer pool: record now in frame 4

debug

update	50	000001	6	6
     buffer pool: write back frame 0
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4
     buffer pool: updating record in frame 4
     buffer pool: record now in frame 4

update	60	000002	7	7
     buffer pool: write back frame 0
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4
     buffer pool: updating record in frame 4
     buffer pool: record now in frame 4

debug

show	50
     buffer pool: record found in frame 3
     buffer pool: record now in frame 4
     50  000001  6  6

update	30	000003	8	8
     buffer pool: record found in frame 1
     buffer pool: updating record in frame 1
     buffer pool: record now in frame 4

update	40	000004	9	9
     buffer pool: write back frame 0
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4
     buffer pool: updating record in frame 4
     buffer pool: record now in frame 4

debug

show	18
     buffer pool: write back frame 0
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4
     18  MNOPQR  3  3

debug

update	9	000005	10	10
     buffer pool: write back frame 0
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 4
     buffer pool: updating record in frame 4
     buffer pool: record now in frame 4

debug

exit
     buffer pool flush: frame 4
     buffer pool flush: frame 2
     buffer pool flush: frame 1
     buffer pool flush: frame 0

Statistics
     hits:              7
     misses:           15
     write backs:       9
