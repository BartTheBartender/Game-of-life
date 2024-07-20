correct: correct.c
	gcc correct.c -o correct

main.o: main.s
	as -g -arch arm64 -o main.o main.s

main: main.o
	ld -lSystem -syslibroot `xcrun -sdk macosx --show-sdk-path` -e _start -arch arm64 -o main main.o

clean: correct main main.o
	rm corect main main.o
