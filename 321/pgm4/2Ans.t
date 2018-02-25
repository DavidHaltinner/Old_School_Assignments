Assignment: buffer pool ; LRU Replacement
Written by: Andrew Perrie

database file:	Records01.bin
command file:	2Test.t
log file:	2Log.t

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

debug

show	4
     buffer pool: record found in frame 3
     buffer pool: record now in frame 3
     4  ABCDEF  1  1

debug

update	3	GHIJKL	2	2
     buffer pool: record found in frame 0
     buffer pool: updating record in frame 0
     buffer pool: record now in frame 3

update	4	MNOPQR	3	3
     buffer pool: record found in frame 2
     buffer pool: updating record in frame 2
     buffer pool: record now in frame 3

update	5	STUVWX	4	4
     buffer pool: record found in frame 0
     buffer pool: updating record in frame 0
     buffer pool: record now in frame 3

update	9	YZABCD	5	5
     buffer pool: record found in frame 0
     buffer pool: updating record in frame 0
     buffer pool: record now in frame 3

debug

show	3
     buffer pool: record found in frame 0
     buffer pool: record now in frame 3
     3  GHIJKL  2  2

show	4
     buffer pool: record found in frame 0
     buffer pool: record now in frame 3
     4  MNOPQR  3  3

show	5
     buffer pool: record found in frame 0
     buffer pool: record now in frame 3
     5  STUVWX  4  4

show	9
     buffer pool: record found in frame 0
     buffer pool: record now in frame 3
     9  YZABCD  5  5

exit
     buffer pool flush: frame 3
     buffer pool flush: frame 2
     buffer pool flush: frame 1
     buffer pool flush: frame 0

Statistics
     hits:             10
     misses:            4
     write backs:       4
