default: radix

main.o: main.c
	gcc -c $^ -o $@

radix.o: radix.c
	gcc -c $^ -o $@

print_bytes.o: print_bytes.c
	gcc -c $^ -o $@

radix: main.o radix.o print_bytes.o
	gcc $^ -o $@
	rm main.o radix.o print_bytes.o

clean:
	rm radix
