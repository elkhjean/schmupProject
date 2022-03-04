  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
	.global time2string, delay, hexasc
	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
HOUR: .ascii "HOUR\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall 
	nop
	# wait a little
	li	$a0,1000
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

# hexasc function from assignment 2
hexasc:
	andi $a0, $a0, 0xf
	slti $t0, $a0, 10
	bne $t0, $zero, lessThenTen
	nop
	addi $v0, $a0, 55
	jr $ra
	nop
lessThenTen:
	addi $v0, $a0, 48
	jr $ra
	nop
	
#delay function	
delay:
      while1:
      slti $t0,$a0, 1 
      bne $t0, $zero, exit
      nop
      addi $a0, $a0, -1
      addi $t1, $zero, 0 # int i = 0
      for:
      addi $t1, $t1, 1
      slti $t2, $t1, 6800
      bne $t2, $zero, for
      nop
      j while1
      nop  
exit:    
     jr $ra    
     nop     
 	
#time2string function $a0 holds memory address and $a1 holds word
time2string:
 	PUSH $a1
	andi $a1, $a1, 0xff 
	POP $a1
 	PUSH $ra				#save the return address in stack
 	PUSH $a1				#not needed in this case but maybe good practice to reset after done
 	PUSH $a0				#not needed in this case but maybe good practice to reset after done
 	#adds null to end of the string
 	addi $t1, $zero, 0x00
 	sb $t1, 5($a0)
#loop to build string
while:
 	bge $t4, 4, done			#while i<=5
 	nop
 	PUSH $a0				#push to save address to the stack
 	nop
	andi $a0, $a1, 0xf		#mask all except 4 least significant bits
	srl  $a1, $a1, 4			#shifts to next nibble for next iteration
	jal hexasc				#hexasc function to convert to char
	nop
continue:					#continue from here in case of $t4 = 2
	POP $a0					#Restore address from stack
	addi $a0, $a0, -1		#decrement address by one byte in this case
 	sb $v0, 5($a0)			#offset byte of address by 5 
	addi $t4, $t4, 1			#i++
 	j while					#loop around
 	nop
done:						#when done
	addi $t4, $zero, 0		#reset $t4 (i = 0)
	POP $a0 				#not needed in this case but maybe good practice to reset after done
	POP $a1 				#not needed in this case but maybe good practice to reset after done
 	POP $ra					#restore return address from stack
 	jr $ra					#return to main
 	nop

