; 2Test.t
;
; Simple buffering with updates but no replacements.
;
; Buffer pool configuration:
buffer	16	4
;
; Load up the buffer pool:
show	3
show	4
show	5
show	9
debug	
;
; Update a resident record:
update	4	ABCDEF	1	1
; Check the buffer pool:
debug	
; Look it up again and see if it changed:
show	4
debug	
;
; Update a few more w/o replacements:
update	3	GHIJKL	2	2
update	4	MNOPQR	3	3
update	5	STUVWX	4	4
update	9	YZABCD	5	5
; Check the buffer pool:
debug	
; Look 'em up again:
show	3
show	4
show	5
show	9
;
exit	
; Note: there should be writebacks at this point.
