trie: main.o trie.o
	gcc main.o trie.o -o trie
	
main.o: main.c trie.h
	gcc -c main.c
	
trie.o: trie.c trie.h
	gcc -c trie.c

clean:
	rm *.o trie
