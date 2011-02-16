CC=g++

.SUFFIXES: .cc .o

.cc.o:
	$(CC) -g -c $*.cc

all: jc jvm ejvm

jc: jc.o stack.o jcmain.o
	$(CC) -o jc jc.o stack.o jcmain.o

jvm: jvm.o stack.o jvmmain.o 
	$(CC) -o jvm jvm.o stack.o jvmmain.o jc.o 

ejvm: ejvm.o stack.o ejvmmain.o jvm.o
	$(CC) -o ejvm ejvm.o stack.o ejvmmain.o jvm.o jc.o
clean : 
	rm -f *.o jc jvm ejvm

stack.o: stack.cc

jc.o: jc.cc 
jcmain.o: jcmain.cc
jvm.o: jvm.cc jc.o 
jvmmain.o: jvmmain.cc
ejvm.o: ejvm.cc jvm.o jc.o 
ejvmmain.o: ejvmmain.cc
