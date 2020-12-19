all: obj obj/bmp.o obj/main.o hw_01
obj:
	mkdir -p obj	
obj/bmp.o: src/bmp.c include/bmp.h
	gcc -c -Wall -Wextra -Werror src/bmp.c -o obj/bmp.o -I include
obj/main.o: src/main.c include/bmp.h
	gcc -c -Wall -Wextra -Werror src/main.c -o obj/main.o -I include
hw_01: obj/bmp.o obj/main.o
	gcc obj/bmp.o obj/main.o -o hw_01
clean:
	rm -r obj hw_01
run:
	valgrind --leak-check=full ./hw_01 crop-rotate samples/small-one.bmp test.bmp 0 0 2 2
run2:
	valgrind --leak-check=full ./hw_01 crop-rotate samples/lena_512.bmp test.bmp 200 200 200 200
run3:
	./hw_01 crop-rotate samples/small-one.bmp test.bmp 0 0 3 2
