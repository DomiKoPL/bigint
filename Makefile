all:
	gcc -Wall -O3 -lm src/main.c src/bigint.c src/bigintc.c src/biginto.c src/fft.c src/parser.c -o app

clean:
	rm app