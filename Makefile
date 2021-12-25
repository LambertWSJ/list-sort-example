CC = gcc
FLAGS = -o3 -std=c99 -D_POSIX_SOURCE -D_GNU_SOURCE -fsplit-stack -g

TRG = bench_mark

build:
	@$(CC) main.c $(FLAGS) -o bench_mark
run: build
	@./$(TRG)
	@gnuplot plot.gp
example: 
	@$(CC) example.c $(FLAGS) -o example
	./example
clean:
	@rm -rf $(TRG) *.png *.txt example
debug: build
	gdb ./$(TRG)