all: 
	gcc -DDEBUG -o joe -lreadline joe.c
	gcc -DDEBUG -o jmvm_test jmvm_test.c
	gcc -DDEBUG -o jmvm_dbg jmvm_dbg.c
