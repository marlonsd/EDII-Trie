/* Marlon da Silva Dias - Ciência da Computação
 * Sinal indicador de fim de palavra: $ 
 * Tamanho de palavra aleatório até 30k: OK (Sem erros)
 * 0 = FALSE
 * 1 = TRUE */
 
/* Problem:
i n
i ap
r n
r ap
r n
 *  */

#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

/* Cria o nodo raiz;
 * Inicializa suas variáveis;
 * Poem o sinal indicar de fim de palavra em todas as letras do vetor. */

node *Trie(){
	node *T;
	int i;
	
	if (!(T = malloc(sizeof(node)))){
		printf("Faltou memória.\n");
		exit(1);
	}
	
	T->father = NULL;
	
	for (i = 0; i < 27; i++){
		T->key[i] = NULL;
	}
	
	T->kids = 0;
	
	return T;
}

int insert(node *T, char *word){
	int i, size, pos;
	node *aux, *pointer;
	
	pointer = T;

	for (i = 0; word[i] != '\0'; i++){
		pos = word[i] - 'a';
		if (pointer->key[pos]){
			pointer = pointer->key[pos];
		} else {
			aux = Trie();
			if (!aux) {
				printf("Faltou memória.\n");
				exit(1);
			}
			pointer->key[pos] = aux;
			aux->father = pointer;
			pointer->kids++;
			pointer = aux;
		}
	}
	
	if (!pointer->key[26]){
		pointer->key[26] = (node *) 1;
		pointer->kids++;
	}
	
	return 1;
	
}
/* Função auxiliar
 * Acha o final da palavram
 * É útil tanto para a função find e para a função delete */
node *get(node *T, char *word){
	int i, pos;
	node *pointer;
	
	i = 0;

	pointer = T;
	if (word[i] == '\0'){
		return NULL;
	} else {
		while((word[i] != '\0') && (pointer)){
			pos = word[i] - 'a';
			pointer = pointer->key[pos];
			i++;
		}
	}
	
	return pointer;
}


int find(node *T, char *word){
	node *aux;
	
	aux = get(T, word);
	
	if ((aux) && (aux->key[26])){
		return 1;
	}
	
	return 0;
}

int delete(node *T, char *word){
	int i, control;
	node *aux, *father;
	
	aux = get(T, word);

	if (aux && aux->key[26]){
		aux->key[26] = NULL;
		aux->kids--;
			
		while (aux && (!aux->kids)){
			father = aux->father;
			i = 0;
			
			while((father->key[i] != aux) && (i < 26)){
				i++;
			}
			
			father->key[i] = NULL;
			
			if (aux->father){
				free(aux);
			}
			
			aux = father;
		}
	
	} else {
		return 0;
	}
	return 1;
}
