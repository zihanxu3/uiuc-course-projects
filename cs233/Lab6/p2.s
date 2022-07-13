.text

# void matrix_mult(int *matr_a, int *matr_b, int *output, unsigned int width) {
#     for (int i = 0; i < width; i++) {
#         for (int j = 0; j < width; j++) {
#             output[i*width + j] = 0;
#             for (int k = 0; k < width; k++) {
#                 output[i*width + j] += matr_a[i*width + k] * matr_b[k*width + j];
#             }
#         }
#     }
# }
#
# // a0: int *matr_a
# // a1: int *matr_b
# // a2: int *output
# // a3: unsigned int width

.globl matrix_mult
matrix_mult:
	addi $sp, $sp, -20;		# allocate stack
	sw 	$ra, 0($sp)
	sw 	$a0, 4($sp)
	sw  $a1, 8($sp)
	sw 	$a2, 12($sp) 
	sw 	$a3, 16($sp) 		# store input variable in stack

	li $t0, 0;				# i = 0


for1: 
	beq $t0, $a3, done_for1 		# i < width
	li $t1, 0;				# j = 0
	for2: 
		beq $t1, $a3, done_for2  	# j < width
		mul  $t3, $t0, $a3          # t3 = i * width
		add  $t3, $t3, $t1   		# t3 = i * width + j
		sll  $t3, $t3, 2			# t3 = right address
		add  $t3, $t3, $a2			# t3 = output[t3]
		sw 	 $0, 0($t3) 			# t3 = 0;

		li $t2, 0;				# k = 0
		for3: 
			beq $t2, $a3, done_for3     # k < width
			mul  $t4, $t0, $a3          # t4 = i * width
			add  $t5, $t4, $t2			# t5 = i * width + k
			sll  $t5, $t5, 2			# t5 = right address
			add  $t5, $t5, $a0  		# t5 = ma[t5]
			lw 	 $t5, 0($t5) 			# extract value mata i * width + k
			add  $t4, $t4, $t1   		# t4 = i * width + j
			sll  $t4, $t4, 2			# t4 = right address
			add  $t4, $t4, $a2			# t4 = output[t4]
			lw   $t8, 0($t4)

			mul  $t6, $t2, $a3          # t6 = k * width
			add  $t6, $t6, $t1          # t6 = k * width + j 
			sll  $t6, $t6, 2			# t6 = right address
			add  $t6, $t6, $a1  		# t6 = mb[t6]
			lw 	 $t6, 0($t6) 			# extract value

			mul  $t7, $t5, $t6 			# matr_a[i*width + k] * matr_b[k*width + j]
			add  $t7, $t7, $t8			# matr_a[i*width + k] * matr_b[k*width + j] + output[i*width + j]

			sw 	 $t7, 0($t4)			# output[i*width + j] += matr_a[i*width + k] * matr_b[k*width + j]
			addi $t2, $t2, 1			# k++
			j    for3

		done_for3:
			addi $t1, $t1, 1			# j++
			j    for2					# to for2
	done_for2:
		addi $t0, $t0, 1			# i++
		j 	 for1 					# to for1
done_for1:

	lw 	$ra, 0($sp)
	lw 	$a0, 4($sp)
	lw  $a1, 8($sp)
	lw 	$a2, 12($sp) 
	lw 	$a3, 16($sp) 		# store input variable in stack
	addi $sp, $sp, 20;		# allocate stack
	jr	$ra



# #define MAX_WIDTH 100
# int working_matrix[MAX_WIDTH*MAX_WIDTH];

# void markov_chain(int *state, int *transitions, unsigned int width, int times) {
#     for (int i = 0; i < times; i++) {
#         matrix_mult(state, transitions, working_matrix, width);
#         copy(state, working_matrix);
#     }
# }
#
# // a0: int *state
# // a1: int *transitions
# // a2: unsigned int width
# // a3: int times

.globl markov_chain
markov_chain:
	# Can access working_matrix from p2_main.s

	sub $sp, $sp, 28		# allocate stack
	sw 	$ra, 0($sp)
	sw 	$s0, 4($sp)
	sw  $s1, 8($sp)
	sw 	$s2, 12($sp) 
	sw 	$s3, 16($sp) 		
	sw  $s4, 20($sp)		# store input variable in stack
	sw  $s5, 24($sp)

	move $s0, $a0
	move $s1, $a1
	move $s2, $a2 
	move $s3, $a3 		# store input variable in stack 
	li  $s4, 0
	la  $s5, working_matrix

	for:
		bge $s4, $s3, out
		move $a0, $s0
		move $a1, $s1
		move $a2, $s5
		move $a3, $s2

		jal matrix_mult

		move $a0, $s0
		move $a1, $s5
		move $a2, $s2
		jal copy

		addi $s4, $s4, 1
		j for

	out:
		lw 	$ra, 0($sp)
		lw 	$a0, 4($sp)
		lw  $a1, 8($sp)
		lw 	$a2, 12($sp) 
		lw 	$a3, 16($sp) 		# store input variable in stack
		lw  $s4, 20($sp)		# store input variable in stack
		lw  $s5, 24($sp)

		addi $sp, $sp, 28		# allocate stack

		jr	$ra
		