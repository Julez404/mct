;
; Assembler Test.asm
;
; Created: 20.10.2018 08:26:46
; Author : julian
;


; Replace with your application code

#define regX r16 
#define regY r17 

rcall sub1

loop:	
	rjmp loop

sub1:
	rcall sub2
	ret

sub2:
	ret
