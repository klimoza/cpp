all: obj obj/bmp.o obj/stego.o obj/main.o hw_01
obj:
	mkdir -p obj
obj/bmp.o: src/bmp.c include/bmp.h
	gcc -c -Wall -Wextra -Werror src/bmp.c -o obj/bmp.o -I include
obj/stego.o: src/stego.c include/stego.h
	gcc -c -Wall -Wextra -Werror src/stego.c -o obj/stego.o -I include
obj/main.o: src/main.c include/stego.h
	gcc -c -Wall -Wextra -Werror src/main.c -o obj/main.o -I include
hw_01: obj/bmp.o obj/stego.o obj/main.o
	gcc obj/bmp.o obj/stego.o obj/main.o -o hw_01
clean:
	rm -rf obj hw_01
