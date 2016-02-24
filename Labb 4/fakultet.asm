
.text

	addi $a0,$0,8     # set $a0 to 4
	beq  $a0,$0,zero
	add  $v0, $0, $a0
	addi  $a0, $a0, -1
loop:	beq  $a0,$0,done # test, jump to done.
	mul  $v0,$v0,$a0
	addi $a0, $a0, -1
	beq  $0,$0,loop
zero:	addi $v0,$0, 1
done:	add  $0,$0,$0	  # NOP
	