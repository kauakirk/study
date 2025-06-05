add x2, x0, x1
sll x1, x2, x2
and x2, x2, x1
ori x2, x1, 16
lb x4, 0(x5)
sb x6, 4(x7)
bne x8, x9, 8
