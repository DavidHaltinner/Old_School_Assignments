; 3Test.t
;
; Simple buffering with updates, replacements and internal writebacks.
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
; Update some resident records:
update	4	ABCDEF	1	1
update	3	GHIJKL	2	2
update	5	MNOPQR	3	3
update	9	STUVWX	4	4
;
; Check the buffer pool:
debug	
;
; Update some more, triggering replacements but not writebacks:
update	5	000001	6	6
update	9	000002	7	7
debug	
;
; Now force some writebacks:
update	2	000003	8	8
update	8	000004	9	9
debug	
;
; Re-load earlier writeback and verify contents:
show	4
debug	
;
; Update another resident record, no writeback:
update	2	000005	10	10
debug	
;
exit	
; Note: there should be writebacks at this point.
