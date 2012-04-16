/* Marlon da Silva Dias - Ciência da Computação
 * Sinal indicador de fim de palavra: $ 
 * 
 * 0 = FALSE
 * 1 = TRUE */

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
		return NULL;
	}
	
	T->father = NULL;
	
	for (i = 0; i < 27; i++){
		T->key[i] = NULL;
	}
	
	T->kids = 0;
	
	return T;
}

int insert(node *T, char *word){
	int i, size;
	node *aux, *pointer;
	
	for (size = 1; word[size] != '\0'; size++);
	
	pointer = T;
	
	for (i = 0; i < size; i++){
		aux = Trie();
		if (!aux) {
			return 0;
			printf("Cai aqui\n");
		}
		pointer->key[word[i]] = aux;
		aux->father = pointer->key[word[i]];
		aux->kids++;
		pointer = aux;
	}
	
	pointer->key[26] = malloc(sizeof(node));
	
	T->kids++;
	
	return 1;
	
}
/* Função auxiliar
 * Acha o final da palavram
 * É útil tanto para a função find e para a função delete */
node *get(node *T, char *word){
	int i, pos;
	node *pointer;
	char *aux;
	
	i = 0;
	
	aux = word;
	
	pointer = T;
	
	while(aux[i] != '\0'){
		pos = *aux - 'a';
		pointer = pointer->key[pos];
		i++;
	}
	
	return pointer;
}


int find(node *T, char *word){
	node *aux;
	
	aux = get(T, word);
	
	if (!aux){
		return 1;
	} else {
		return 0;
	}
}

int delete(node *T, char *word){
	node *aux, *pointer;
	
	aux = get(T, word);
	
	/* Enquanto não chegar na raiz, onde o pai é nulo */
	while(aux->father){
		if (!aux->kids){ // Se não tem filhos
			pointer = aux->father;
			free(aux);
			aux = pointer;
		} else {
			return 0;
		}
	}
	
	return 1;
}
