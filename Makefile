build:
	gcc -Wall -Wextra -pedantic -lpthread utilities/string_utils.c utilities/proc_utils.c lsh.c -o lsh -g

clean:
	rm lsh

fresh: clean build

hot:
	make fresh
	./lsh

runtest:
	gcc -o test tester.c
	./test
