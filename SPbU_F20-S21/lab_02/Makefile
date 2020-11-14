all: bin/str.o bin/test_str.o bin/test.o lab_02 clean
bin/str.o: src/str.c
	gcc -c src/str.c -o bin/str.o -I include
bin/test_str.o: src/test_str.c include/str.h
	gcc -c src/test_str.c -o bin/test_str.o -I include
bin/test.o: src/test.c include/test_str.h
	gcc -c src/test.c -o bin/test.o -I include
lab_02: bin/str.o bin/test_str.o bin/test.o
	gcc bin/str.o bin/test_str.o bin/test.o -o lab_02
run:
	./lab_02
clean:
	rm bin/*.o