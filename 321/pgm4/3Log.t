Assignment: buffer pool ; LRU Replacement
Written by: David Haltinner

database file:	Records01.bin
command file:	3Test.t
log file:	3Log.t

buffer	16  4

show	3
     buffer pool: insert page into frame 0
     3  shnxwj  9190  7040

show	4
     buffer pool: insert page into frame 1
     4  czbmdd  28888  17445

show	5
     buffer pool: insert page into frame 2
     5  romtvt  27469  29923

show	9
     buffer pool: insert page into frame 3
     9  rdftod  16625  23767

debug

update	4	ABCDEF	1	1
     buffer pool: record found in frame 1
     buffer pool: updating record in frame 1
     buffer pool: record now in frame 3

update	3	GHIJKL	2	2
     buffer pool: record found in frame 0
     buffer pool: updating record in frame 0
     buffer pool: record now in frame 3

update	5	MNOPQR	3	3
     buffer pool: record found in frame 0
     buffer pool: updating record in frame 0
     buffer pool: record now in frame 3

update	9	STUVWX	4	4
     buffer pool: record found in frame 0
     buffer pool: updating record in frame 0
     buffer pool: record now in frame 3

debug

update	5	000001	6	6
     buffer pool: record found in frame 2
     buffer pool: updating record in frame 2
     buffer pool: record now in frame 3

update	9	000002	7	7
     buffer pool: record found in frame 2
     buffer pool: updating record in frame 2
     buffer pool: record now in frame 3

debug

update	2	000003	8	8
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 3

update	8	000004	9	9
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 3

debug

show	4
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 3
     1  czbmdd  28888  -1073752048

debug

update	2	000005	10	10
     buffer pool: record found in frame 1
     buffer pool: updating record in frame 1
     buffer pool: record now in frame 3

debug

exit
     buffer pool flush: frame 3
     buffer pool flush: frame 2
     buffer pool flush: frame 1
     buffer pool flush: frame 0

Statistics
     hits:              7
     misses:            7
     write backs:       3
