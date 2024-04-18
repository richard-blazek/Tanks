tanks: main.c main.c libs/fighters.c libs/io.c libs/play.c libs/shoot.c
	gcc -o tanks main.c libs/fighters.c libs/io.c libs/play.c libs/shoot.c -lm  -I/usr/include -D_REENTRANT -lSDL2 -lSDL2_ttf

clean:
	rm tanks
