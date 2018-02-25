; 1Test.t
;
; Simple buffering with no updates or writebacks.
;
; Buffer pool configuration:
buffer	16	4
;
; Display a few data records and check the buffer pool:
show	17
debug	
show	23
debug	
show	18
debug	
;
; Display one that should already be loaded:
show	23
debug	
;
; Load a bunch of blocks to fill the buffer pool:
show	22
debug	
;
; None of these should force replacements:
show	23
debug	
show	18
debug	
show	17
debug	
;
; Check the boundaries of the file:
show	0
debug	
show	99
;
debug	
;
exit	
