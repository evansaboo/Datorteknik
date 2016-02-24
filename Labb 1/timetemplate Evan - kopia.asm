  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "time\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,100
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #
  hexasc:
	andi 	$a0,$a0, 0x000F
	addi	$v0, $a0, 0x30
	jr	$ra
	nop

delay:
	PUSH($ra)
	addi	$t0,$0,0
	addi	$t1,$0,4711

delaywhileloop:
	ble	$a0,$0,delayfinished
	addi	$a0,$a0,-1
delayforloop:
	ble	$t1,$t0,delaywhileloop
	addi	$t0,$t0,1
	j	delayforloop
	nop
delayforloopfinished:
	j	delaywhileloop
	nop

delayfinished:	
	POP($ra)
	jr	$ra
	nop

time2string:
	PUSH($ra)		
	addi 	$t3,$0,6
	addi 	$t4,$0,12
	addi	$t5,$0,3
	move	$a0,$0
	j	last
	nop
finished:
	POP($ra)
	jr	$ra
	nop
timeloop:
	beq 	$t3,$0, finished
	nop
	beq	$t3,$t5,colon
	nop
	srlv	$a0, $a1,$t4
	addi	$t4,$t4,-4
	jal	hexasc
	nop
	move	$a0, $v0	
last:
	nop
	li	$v0, 11
	syscall
	nop
	addi	$t3,$t3,-1
	j	timeloop
	nop
colon:
	addi	$a0,$0,0x3a
	j	last
	nop
