.text

# void toggle_light(int row, int col, LightsOut* puzzle, int action_num){
#     int num_rows = puzzle->num_rows;
#     int num_cols = puzzle->num_cols;
#     int num_colors = puzzle->num_colors;
#     unsigned char* board = (puzzle-> board);
#     board[row*num_cols + col] = (board[row*num_cols + col] + action_num) % num_colors;
#     if (row > 0){
#         board[(row-1)*num_cols + col] = (board[(row-1)*num_cols + col] + action_num) % num_colors;
#     }
#     if (col > 0){
#         board[(row)*num_cols + col-1] = (board[(row)*num_cols + col-1] + action_num) % num_colors;
#     }
#     
#     if (row < num_rows - 1){
#         board[(row+1)*num_cols + col] = (board[(row+1)*num_cols + col] + action_num) % num_colors;
#     }
# 
#     if (col < num_cols - 1){
#         board[(row)*num_cols + col+1] = (board[(row)*num_cols + col+1] + action_num) % num_colors;
#     }
# }
# $a0 row
# $a1 col
# $a2 puzzle
# $a3 action_num

.globl toggle_light
toggle_light:
	sub $sp, $sp, 4   # allocate stack
	sw  $ra, 0($sp)   # store ra on stack

	lw  $t0, 0($a2)   # t0 = num_rows
	lw  $t1, 4($a2)   # t1 = num_cols
	lw  $t2, 8($a2)   # t2 = num_colors
	add $t3, $a2, 12  # t3 = board

	mul $t4, $a0, $t1 # t4 = row * num_col
	add $t4, $t4, $a1 # t4 = row * num_col + col
	# sll $t4, $t4, 1
	add $t4, $t3, $t4 # point to board[row * num_col + col]

	lb $t5, 0($t4)    # load board[row * num_col + col]
	add $t5, $t5, $a3 # board[(row)*num_cols + col] + action_num
	rem $t5, $t5, $t2 # (board[row*num_cols + col] + action_num) % num_colors
	sb  $t5, 0($t4)   # board[row*num_cols + col] = (board[row*num_cols + col] + action_num) % num_colors;

if1: 
	ble $a0, $0, if2

	sub $t4, $a0, 1   # t4 = row - 1
	mul $t4, $t4, $t1 # t4 = (row - 1) * num_col
	add $t4, $t4, $a1 # t4 = (row - 1) * num_col + col
	add $t4, $t3, $t4 # point to board[(row - 1) * num_col + col]

	lb $t5, 0($t4)     # load board[(row - 1) * num_col + col]
	add $t5, $t5, $a3 # board[(row-1)*num_cols + col] + action_num
	rem $t5, $t5, $t2 # (board[row*num_cols + col] + action_num) % num_colors
	sb  $t5, 0($t4)   # board[row*num_cols + col] = (board[row*num_cols + col] + action_num) % num_colors;

if2: 
	ble $a1, $0, if3

	mul $t4, $a0, $t1 # t4 = row * num_col
	add $t4, $t4, $a1 # t4 = row * num_col + col
	sub $t4, $t4, 1   # t4 = (row) * num_col + col - 1
	add $t4, $t3, $t4 # point to board[row * num_col + col - 1]

	lb $t5, 0($t4)     # load board[row * num_col + col - 1 ]
	add $t5, $t5, $a3 # board[(row)*num_cols + col - 1 ] + action_num
	rem $t5, $t5, $t2 # (board[row*num_cols + col - 1 ] + action_num) % num_colors
	sb  $t5, 0($t4)   # board[row*num_cols + col - 1 ] = (board[row*num_cols + col - 1 ] + action_num) % num_colors;
if3: 
	sub $t6, $t0, 1
	bge $a0, $t6, if4

	add $t4, $a0, 1   # t4 = row + 1
	mul $t4, $t4, $t1 # t4 = (row + 1) * num_col
	add $t4, $t4, $a1 # t4 = (row + 1) * num_col + col
	add $t4, $t3, $t4 # point to board[(row + 1) * num_col + col]

	lb $t5, 0($t4)     # load board[(row + 1) * num_col + col]
	add $t5, $t5, $a3 # board[(row + 1)*num_cols + col] + action_num
	rem $t5, $t5, $t2 # (board[(row + 1)*num_cols + col] + action_num) % num_colors
	sb  $t5, 0($t4)   # board[(row + 1)num_cols + col] = (board[(row + 1)*num_cols + col] + action_num) % num_colors;
if4: 
	sub $t6, $t1, 1
	bge $a1, $t6, end_function

	mul $t4, $a0, $t1 # t4 = row * num_col
	add $t4, $t4, $a1 # t4 = row * num_col + col
	add $t4, $t4, 1   # t4 = (row) * num_col + col - 1
	add $t4, $t3, $t4 # point to board[row * num_col + col - 1]

	lb $t5, 0($t4)     # load board[row * num_col + col - 1 ]
	add $t5, $t5, $a3 # board[(row)*num_cols + col - 1 ] + action_num
	rem $t5, $t5, $t2 # (board[row*num_cols + col - 1 ] + action_num) % num_colors
	sb  $t5, 0($t4)   # board[row*num_cols + col - 1 ] = (board[row*num_cols + col - 1 ] + action_num) % num_colors;

end_function:
	
	lw  $ra, 0($sp)   # load ra on stack
	add $sp, $sp, 4   # allocate stack	
	jr	$ra



# bool solve(LightsOut* puzzle, unsigned char* solution, int row, int col){
#     int num_rows = puzzle->num_rows; 
#     int num_cols = puzzle->num_cols;
#     int num_colors = puzzle->num_colors;
#     int next_row = ((col == num_cols-1) ? row + 1 : row);
#     if (row >= num_rows || col >= num_cols) {
#          return board_done(num_rows,num_cols,puzzle->board);
#     }
#
#     if (puzzle->clue[row*num_cols + col]) {
#          return solve(puzzle,solution, next_row, (col+1) % num_cols);
#     }
# 
#     for(char actions = 0; actions < num_colors; actions++) {
#         solution[row*num_cols + col] = actions;
#         toggle_light(row, col, puzzle, actions);
#         if (solve(puzzle,solution, next_row, (col + 1) % num_cols)) {
#             return true;
#         }
#         toggle_light(row, col, puzzle, num_colors - actions); 
#         solution[row*num_cols + col] = 0;
#     }
#     return false;
# }
# $a0 puzzle
# $a1 solution
# $a2 row
# $a3 col

.globl solve
solve:
	sub $sp, $sp, 36   # allocate stack
	sw  $ra, 0($sp)   # store ra on stack
	sw  $s0, 4($sp)   
	sw  $s1, 8($sp)
	sw  $s2, 12($sp)
	sw  $s3, 16($sp)

	sw  $s4, 20($sp)
	sw  $s5, 24($sp)
	sw  $s6, 28($sp)
	sw  $s7, 32($sp)

	move $s4, $a0     # puzzle = s4
	move $s5, $a1     # solution = s5
	move $s6, $a2     # row = s6
	move $s7, $a3     # col = s7

	lw  $s1, 4($s4)   # s1 = num_cols
	lw  $s2, 8($s4)   # s2 = num_colors
	
	li 	$s3, 0        # intialize next_row = 0
	li  $s0, 0        # intialize action to be 0

if_next_row:
	sub $t0, $s1, 1   # t0 = num_cols - 1
	bne $s7, $t0, n_eq 
	add $s3, $s6, 1   # next_row = row + 1
	j   if_row_col
n_eq: 
	move $s3, $s6     # next_row = row 

if_row_col: 
	lw  $t4, 0($s4)   # t4 = num_rows
	bge  $s6, $t4, if_body
	bge  $s7, $s1, if_body
	j 	 next_if

if_body:
	lw   $a0, 0($s4)
	lw   $a1, 4($s4)
	add  $a2, $s4, 12
	jal solver_board_done
	j end_of_function



next_if: 
	add $t1, $s4, 268	# find the correct position of the boolean array pointer
	mul $t2, $s6, $s1   # row*num_cols
	add $t2, $t2, $s7   # t2 = row*num_cols + col
	add $t1, $t1, $t2
	lbu  $t2, 0($t1)     # t2 = value of (puzzle->clue[row*num_cols + col])
	li  $t3, 0			# temp var for boolean comparison
	beq $t2, $t3, for_loop
	move $a0, $s4		# assign each input value 
	move $a1, $s5
	move $a2, $s3 
	add  $t1, $s7, 1 
	rem  $a3, $t1, $s1  # col + 1 % num_cols
	jal  solve
	j    end_of_function

for_loop:
	bge  $s0, $s2, return_false
	mul  $t4, $s6, $s1  # row*num_cols 
	add  $t4, $t4, $s7  # row*num_cols + col 
	add  $t4, $t4, $s5  # solution[row*num_cols + col]
	sb   $s0, 0($t4)    # solution[row*num_cols + col] = action
	
	move $a0, $s6       # deal with inputs for toggle_light()
	move $a1, $s7 
	move $a2, $s4
	move $a3, $s0

	jal  toggle_light

	if_in_for:
		add  $t1, $s7, 1 
		rem  $t1, $t1, $s1  # col + 1 % num_cols

		move $a0, $s4
		move $a1, $s5
		move $a2, $s3
		move $a3, $t1       # inputs for solve()

		jal solve

		li $t0, 1
		beq $v0, $t0, return_true
	
		sub $t3, $s2, $s0   # num colors - actions

		move $a0, $s6       # deal with inputs for toggle_light()
		move $a1, $s7 
		move $a2, $s4
		move $a3, $t3

		jal  toggle_light

		mul  $t4, $s6, $s1  # row*num_cols 
		add  $t4, $t4, $s7  # row*num_cols + col 
		add  $t4, $t4, $s5  # solution[row*num_cols + col]
		sb   $0, 0($t4)    # solution[row*num_cols + col] = 0
		add $s0, $s0, 1
		j   for_loop
	
return_true:
	li  $v0, 1
	j   end_of_function

return_false:
	li   $v0, 0
	j 	 end_of_function



end_of_function:
	lw  $ra, 0($sp)   # store ra on stack
	lw  $s0, 4($sp)
	lw  $s1, 8($sp)
	lw  $s2, 12($sp)
	lw  $s3, 16($sp)

	lw  $s4, 20($sp)
	lw  $s5, 24($sp)
	lw  $s6, 28($sp)
	lw  $s7, 32($sp)

	move $a0, $s4    # puzzle = s4
	move $a1, $s5      # solution = s5
	move $a2, $s6      # row = s6
	move $a3, $s7      # col = s7

	add $sp, $sp, 36   # allocate stack

	jr $ra
