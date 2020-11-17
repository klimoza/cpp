all: make_bin obj/str.o obj/test_str.o obj/test.o lab_02 clean
make_bin:
	mkdir obj
obj/str.o: src/str.c
	gcc -c src/str.c -o obj/str.o -I include
obj/test_str.o: src/test_str.c include/str.h
	gcc -c src/test_str.c -o obj/test_str.o -I include
obj/test.o: src/test.c include/test_str.h
	gcc -c src/test.c -o obj/test.o -I include
lab_02: obj/str.o obj/test_str.o obj/test.o
	gcc obj/str.o obj/test_str.o obj/test.o -o lab_02
run:
	./lab_02
clean:
	rm -R obj