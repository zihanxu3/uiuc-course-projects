.text

# // Ignore integer overflow for addition
# int update_alert_level(unsigned int* stockpiles, unsigned int cutoff,
#   unsigned int alert_level) {
#     int total_monster = 0;
#     for (int i = 0; i < 10; i++) {
#         total_monster += stockpiles[i];
#     }
#     if (total_monster < cutoff) {
#         return alert_level + 1;
#     } else if (total_monster == cutoff) {
#         return alert_level;
#     } else {
#         return alert_level - 1;
#     }
# }
# // a0: unsigned int *stockpiles
# // a1: unsigned int cutoff
# // a2: unsigned int alert_level

.globl update_alert_level
update_alert_level:
	addi $sp, $sp, -16
	sw $ra, 0($sp)
	sw $a0, 4($sp)
	sw $a1, 8($sp)
	sw $a2, 12($sp)

	li $t0, 0		# total_monster = 0;
	li $t1, 0  	    # i = 0

	li $t2, 10	 	# temporary register storing 10 for i < 10 condition
loop:
	bge $t1, $t2, done_loop		# i < 10 condition of the for loop
	sll $t3, $t1, 2	        # i x 4 to get the pointer position of stockpiles
	addu $t4, $a0, $t3		# moving pointer to correct position of stockpiles
	lw 	$t5, 0($t4)         # t5 = stockpiles[i]
	addu $t0, $t0, $t5      # total_monster += stockpiles[i];
	addi $t1, $t1, 1  		# i++
	j  loop


done_loop:
	if:
		bge $t0, $a1, else_if   # total_monster < cutoff 
		addiu $v0, $a2, 1  		# return alert_level + 1
		j end_of_function
	else_if:
		bne $t0, $a1, else
		move $v0, $a2; 			# return alert_level 
		j end_of_function
	else: 
		addi $v0, $a2, -1		# return alert_level - 1
		j end_of_function

end_of_function:
	lw $ra, 0($sp)
	lw $a0, 4($sp)
	lw $a1, 8($sp)
	lw $a2, 12($sp)
	addi $sp, $sp, 16
	jr	$ra