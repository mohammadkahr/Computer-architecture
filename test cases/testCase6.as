	or	3,2,7		#duplicated symbol
	nand	4,3,6
	addi	4,6,5
	slti	8,7,6
	add	0,1,2
	sub	1,2,3
	slt	2,3,4
lbl1	or	3,4,5
	sub	1,2,3
	nand	4,5,6
lbl1	addi	5,6,7
	slti	6,7,8
	slt	1,2,12
	ori	7,8,9
	lui	10,11
	lw	12,13,lbl1
	beq	13,14,13
	jalr	14,15
	j	lbl1
	add	1,2,3