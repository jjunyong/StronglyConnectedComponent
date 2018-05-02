
SCC:scc.o
	gcc -o SCC scc.o
scc.o: scc.c
	gcc -std=c99 -c scc.c
clean:
	rm SCC *.o
