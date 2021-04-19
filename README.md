# C-Mini-Compiler

HOW TO RUN THE CODE

=> Download Flex on your system

=> For Compiling Yacc File
	Use the Command **yacc -d Yacc.y** 

=> For Compiling Lex File
	Use the Command **lex lex.l**

=> Then Construct the Compiler using
    **gcc  lex.yy.c Yacc.tab.c -w **

=> Run executable file
    **a  < input.c (windows) 
    or 
    ./a.out < input.c (Unix Based machine)**

=> Generate Optimized ICG Using Python3
	**python3 optimize.py input.txt (ICG code generated by compiler)**
