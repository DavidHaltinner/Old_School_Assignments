; 4Test.t
;
; Multi-record buffering with updates, replacements and internal writebacks.
;
; Buffer pool configuration:
buffer	64	5
;
; Load up the buffer pool:
show	17
show	23
show	22
show	21
show	31
show	3
show	4
show	5
show	13
show	9
debug	
;
; Update some resident records:
update	4	ABCDEF	1	1
update	13	GHIJKL	2	2
update	18	MNOPQR	3	3
update	31	STUVWX	4	4
update	22	YZABCD	5	5
; Check the buffer pool:
debug	
; Update some more:
update	50	000001	6	6
update	60	000002	7	7
debug	
show	50
;
update	30	000003	8	8
update	40	000004	9	9
debug	
;
; Re-load earlier writeback and verify contents:
show	18
debug	
; Update another non-resident record, with writeback:
update	9	000005	10	10
debug	
;
; Stop:
exit	
; Note: there should be writebacks at this point.
