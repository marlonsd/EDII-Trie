#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

#define TAM 35000

int main(){
	unsigned long int i;
	node *raiz;
	char aux, op, sel,*palavra;
	int j;
	
	raiz = Trie();
	
	scanf("%c", &sel);
	j = 0;
	while(sel != '@'){
		if ((sel == 'b') || (sel == 'i') || (sel == 'r')){
			scanf("%c", &aux);

			if (!(palavra = malloc(sizeof(char)*(TAM + 1)))){
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

			op = 1;
			
			switch(sel){
				case 'b': op = find(raiz, palavra);
					break;
				case 'i'://printf("%d\n", j);
				op = insert(raiz, palavra);
					break;
				case 'r': op = delete(raiz, palavra);
					break;
			}
			
			free(palavra);
//			printf("%d ", j);
			if (op){
				printf("v");
			} else {
				printf("f");
			}
			
			printf("\n");
		}
		j++;
		scanf("%c", &sel);
	}
	
	return 0;
}
