  # labwork.S
  # Written 2015 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1 2015-2016.
  # The macros PUSH and POP are in the public domain.

.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm

  # You can add your own code here
  #

	.global time2string
	.global delay
	.global hexasc

hexasc:
	andi 	$a0,$a0, 0x000F
	addi 	$t1, $0, 9
	ble	$a0, $t1, number
	addi	$v0, $a0, 0x37
	jr	$ra
	nop
number:
	addi	$v0, $a0, 0x30
	jr	$ra
	nop

delay:
	addi	$t1,$0,4711

delaywhileloop:
	blez	$a0,delayfinished
	nop
	addi	$a0,$a0,-1
	addi	$t0,$0,0
delayforloop:
	ble	$t1,$t0,delaywhileloop
	nop
	addi	$t0,$t0,1
	j	delayforloop
	nop
delayfinished:	
	jr	$ra
	nop
time2string:
	PUSH 	$ra
	PUSH 	$a0
	PUSH	$a1
	
	srl 	$a0, $a1, 12
	jal 	hexasc
	nop
	POP	$a1
	POP 	$a0
	sb	$v0, 0($a0)
	
	PUSH	$a0
	PUSH	$a1
	srl	$a0, $a1, 8
	jal 	hexasc
	nop
	POP	$a1
	POP 	$a0
	sb	$v0, 1($a0)
	
	addi 	$v0, $0, 0x3a
	sb	$v0, 2($a0)
	
	PUSH 	$a0
	PUSH	$a1
	srl	$a0, $a1, 4
	jal 	hexasc
	nop
	POP	$a1
	POP 	$a0
	sb 	$v0, 3($a0)
	
	PUSH 	$a0
	PUSH	$a1
	move 	$a0, $a1
	jal 	hexasc
	nop
	POP	$a1
	POP 	$a0
	sb 	$v0, 4($a0)
	sb	$0, 5($a0)
	
	POP	$ra
	jr 	$ra
	nop
