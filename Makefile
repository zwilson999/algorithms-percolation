build:
	gcc -o ./bin/main main.c ./src/wquf.c ./src/percolation.c ./src/percolation_stats.c ./src/stats.c ./src/uniform_random.c -lm -I include/
run:
	./bin/main $(SIZE) $(TRIALS)
test:
	gcc -o ./bin/test_main -Iinclude/ ./src/test_main.c ./src/wquf.c ./src/percolation.c && ./bin/test_main 2
clean:
	rm -f ./bin/test_main ./bin/main
