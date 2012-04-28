// ------------------------------------------------------------
//  Trabalho Estrutura de Dados II
//		Ciênia da Computação
//
//	Aluno: Marlon da Silva Dias
//	GitHub: https://github.com/marlonsd/EDII-Trie
//	main.c
//
//	A condição de parada da leitura é quando ler um '@'
//	O programa interpreta três opções:
//		'i' - Inserir
//		'b' - Buscar
//		'r' - Remover
// ------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "trie.h"	// Implementação das funções da trie

#define TAM 35000

int main(){
	unsigned long int i;
	node *raiz;
	char aux, op, sel, *palavra;
	
	raiz = Trie();
	
	scanf("%c", &sel);

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
		
		scanf("%c", &sel);
	}
	
	return 0;
}
