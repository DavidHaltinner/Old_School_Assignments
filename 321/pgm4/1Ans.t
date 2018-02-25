Assignment: buffer pool ; LRU Replacement
Written by: Andrew Perrie

database file:	Records01.bin
command file:	1Test.t
log file:	1Log.t

buffer	16  4

show	17
     buffer pool: insert page into frame 0
     17  guyudm  2847  9930

debug

show	23
     buffer pool: insert page into frame 1
     23  zggzfy  2424  3074

debug

show	18
     buffer pool: insert page into frame 2
     18  bmhxvj  23447  18771

debug

show	23
     buffer pool: record found in frame 1
     buffer pool: record now in frame 2
     23  zggzfy  2424  3074

debug

show	22
     buffer pool: insert page into frame 3
     22  lzgukf  1991  4593

debug

show	23
     buffer pool: record found in frame 2
     buffer pool: record now in frame 3
     23  zggzfy  2424  3074

debug

show	18
     buffer pool: record found in frame 1
     buffer pool: record now in frame 3
     18  bmhxvj  23447  18771

debug

show	17
     buffer pool: record found in frame 0
     buffer pool: record now in frame 3
     17  guyudm  2847  9930

debug

show	0
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 3
     0  hapjia  175  400

debug

show	99
     buffer pool: removing block in frame 0
     buffer pool: insert page into frame 3
     99  asiuqb  30818  9448

debug

exit

Statistics
     hits:              4
     misses:            6
     write backs:       0
