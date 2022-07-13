.text

# // part 1 p1.s
# unsigned char find_payment(TreeNode* trav) { 
# 	// Base case
# 	if (trav == NULL) {
# 		return 0;
# 	}
# 	// Recurse once for each child
# 	unsigned char payment_left = find_payment(trav->left);
# 	unsigned char payment_center = find_payment(trav->center);
# 	unsigned char payment_right = find_payment(trav->right);
# 	unsigned char value = payment_left + payment_center + payment_right + trav->value;
# 	return value / 2;
# }

.globl find_payment
find_payment:
	li   $t0, 0
	bne  $a0, $t0, recurse_
	move $v0, $0
	jr   $ra
recurse_:
	sub $sp, $sp, 12 
	sw  $ra, 0($sp)
	sw  $s0, 4($sp)     # allocate for trav
	sw  $s1, 8($sp) 	# allocate for return values

	move $s0, $a0 		# save a0
	lw  $a0, 0($s0) 	# deref a0

	li 	 $s1, 0
	lw 	 $a0, 0($s0) 	# load left
	jal  find_payment 	# jump to function
	add  $s1, $s1, $v0	# add to result

	lw  $a0, 4($s0) 	# deref a0 to be center
	jal  find_payment 	# jump to function
	add  $s1, $s1, $v0	# add to result

	lw  $a0, 8($s0) 	# deref a0 to be right
	jal  find_payment 	# jump to function
	add  $s1, $s1, $v0	# add to result

	lb  $a0, 12($s0) 	# deref a0
	add  $s1, $s1, $a0  # add final result

	div  $s1, $s1, 2
	move $v0, $s1

	lw  $ra, 0($sp)
	lw  $s0, 4($sp)     # allocate for trav
	lw  $s1, 8($sp) 	# allocate for return values
	add $sp, $sp, 12 

	jr $ra