#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

#define TAM 10000

int main(){
	int op, i;
	node *raiz;
	char aux, sel,*palavra;
	
	raiz = Trie();
	
	while((scanf("%c", &sel)) == 1){
		if ((sel == 'b') || (sel == 'i') || (sel == 'r')){
			scanf("%c", &aux);

			if (!(palavra = malloc(sizeof(char)*TAM))){
				printf("Falha a alocar memória.\n");
				exit(1);
			}
			
			scanf("%c", &aux);
			i = 0;
			while((aux != '\n')){
				palavra[i] = aux;
				i++;
				scanf("%c", &aux);
			}
			
			palavra[i] = '\0';

			op = 0;
			
			switch(sel){
				case 'b': op = find(raiz, palavra);
					break;
				case 'i': op = insert(raiz, palavra);
					break;
				case 'r': op = delete(raiz, palavra);
					break;
			}
			
			free(palavra);
			
			if (op){
				printf("v");
			} else {
				printf("f");
			}
			
			printf("\n");
		}
	}
	
	return 0;
}
