//push argument 1
@1
D=A
@ARG
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1
//pop pointer 1
@SP
M=M-1
A=M
D=M
@R13
M=D
@THAT
M=D
//push constant 0
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
//pop that 0
@SP
M=M-1
A=M
D=M
@R13
M=D
@THAT
D=M
@0
D=D+A
@R14
M=D
@R13
D=M
@R14
A=M
M=D
//push constant 1
@1
D=A
@SP
A=M
M=D
@SP
M=M+1
//pop that 1
@SP
M=M-1
A=M
D=M
@R13
M=D
@THAT
D=M
@1
D=D+A
@R14
M=D
@R13
D=M
@R14
A=M
M=D
//push argument 0
@0
D=A
@ARG
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1
//push constant 2
@2
D=A
@SP
A=M
M=D
@SP
M=M+1
//start operation
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M-D
@SP
M=M+1
//pop argument 0
@SP
M=M-1
A=M
D=M
@R13
M=D
@ARG
D=M
@0
D=D+A
@R14
M=D
@R13
D=M
@R14
A=M
M=D
(MAIN_LOOP_START)
//push argument 0
@0
D=A
@ARG
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
AM=M-1
D=M
A=A-1
@COMPUTE_ELEMENT
D;JNE
@END_PROGRAM
0;JMP
(COMPUTE_ELEMENT)
//push that 0
@0
D=A
@THAT
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1
//push that 1
@1
D=A
@THAT
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1
//start operation
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=D+M
@SP
M=M+1
//pop that 2
@SP
M=M-1
A=M
D=M
@R13
M=D
@THAT
D=M
@2
D=D+A
@R14
M=D
@R13
D=M
@R14
A=M
M=D
//push pointer 1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
//push constant 1
@1
D=A
@SP
A=M
M=D
@SP
M=M+1
//start operation
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=D+M
@SP
M=M+1
//pop pointer 1
@SP
M=M-1
A=M
D=M
@R13
M=D
@THAT
M=D
//push argument 0
@0
D=A
@ARG
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1
//push constant 1
@1
D=A
@SP
A=M
M=D
@SP
M=M+1
//start operation
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M-D
@SP
M=M+1
//pop argument 0
@SP
M=M-1
A=M
D=M
@R13
M=D
@ARG
D=M
@0
D=D+A
@R14
M=D
@R13
D=M
@R14
A=M
M=D
@MAIN_LOOP_START
0;JMP
(END_PROGRAM)
