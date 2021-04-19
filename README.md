# C-Mini-Compiler

**HOW TO RUN THE CODE**

=> Download Flex on your system

=> For Compiling Yacc File
	Use the Command _yacc -d Yacc.y_

=> For Compiling Lex File
	Use the Command _lex lex.l_

=> Then Construct the Compiler using
    _gcc  lex.yy.c Yacc.tab.c -w_

=> Run executable file
   	_a  < input.c (windows) 
    			or 
    	./a.out < input.c (Unix Based machine)_

=> Generate Optimized ICG Using Python3
	_python3 optimize.py input.txt_ (ICG code generated by compiler)
