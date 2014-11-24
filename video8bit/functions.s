	
.section .data
.align 1
foreColor:
.hword 0xFFFF

.align 2
graphicsAddress:
.int 0


.section .text
.globl SetForeColor
SetForeColor:
cmp r0,#0x10000
movhs pc,lr
ldr r1,=foreColor
strh r0,[r1]
mov pc,lr

.globl SetGraphicsAddress
SetGraphicsAddress:
ldr r1,=graphicsAddress
str r0,[r1]
mov pc,lr

.globl DrawPixel
DrawPixel:
	px .req r0
	py .req r1
	addr .req r2
	ldr addr,=graphicsAddress
	ldr addr,[addr]
	height .req r3
	ldr height,[addr,#4]
	sub height,#1
	cmp py,height
	movhi pc,lr
	.unreq height

	width .req r3
	ldr width,[addr,#0]
	sub width,#1
	cmp px,width
	movhi pc,lr
	ldr addr,[addr,#32]
	add width,#1
	mla px,py,width,px
	.unreq width
	.unreq py
	add addr, px,lsl #1
	.unreq px
	fore .req r3
	ldr fore,=foreColor
	ldrh fore,[fore]
	strh fore,[addr]
	.unreq fore
	.unreq addr
	mov pc,lr

.globl Random	@r0 last random #
Random:
	xnm .req r0
	a .req r1
	ldr a,=0xef35
	mul a,xnm
	mul a,xnm
	add a, xnm
	.unreq xnm
	add r0,a,#73
	.unreq a
	mov pc,lr
	


.globl clrScreen
clrScreen:
	push {r4,r5,r6,r7,r8,r9,r10,lr}
	push {r1}
	mov r3,r0
	color .req r3
	color2 .req r4
	color3 .req r5
	color4 .req r6
	color5 .req r7
	color6 .req r8
	color7 .req r9
	color8 .req r10
	j .req r0
	mov r1,color
	lsl r1,#16
	orr color,r1
	mov color2,color
	mov color3,color
	mov color4,color
	mov color5,color
	mov color6,color
	mov color7,color
	mov color8,color
	ldr r2,=0x40040020
	ldr r1,[r2]
	address .req r1
	pop {r2}
	cmp r2,#0
	ldrhi r2,=614400
	addhi address, r2
	
	ldr j,=2400
	jloop$:
		
			
			stmia address!, {color,color2,color3,color4,color5,color6,color7,color8}
			stmia address!, {color,color2,color3,color4,color5,color6,color7,color8}
			stmia address!, {color,color2,color3,color4,color5,color6,color7,color8}
			stmia address!, {color,color2,color3,color4,color5,color6,color7,color8}
			stmia address!, {color,color2,color3,color4,color5,color6,color7,color8}
			stmia address!, {color,color2,color3,color4,color5,color6,color7,color8}
			stmia address!, {color,color2,color3,color4,color5,color6,color7,color8}
			stmia address!, {color,color2,color3,color4,color5,color6,color7,color8}
			
			
			
		subs j,#1
		bne jloop$
	.unreq color
	.unreq color2
	.unreq color3
	.unreq color4
	.unreq color5
	.unreq color6
	.unreq color7
	.unreq color8
	.unreq j
	pop {r4,r5,r6,r7,r8,r9,r10,pc}
