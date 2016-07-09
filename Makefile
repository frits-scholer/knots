objects = utils.o phpk.o testphpk.o
testphpk: $(objects)
	cc -o testphpk $(objects)

testphpk.o : phpk.h


phpk.o : utils.h


utils.o : utils.c

.PHONY : clean
clean :
	rm testphpk testphpk.o
