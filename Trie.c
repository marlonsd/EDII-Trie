/* Marlon da Silva Dias - Ciência da Computação
 * Sinal indicador de fim de palavra: $ 
 * 
 * 0 = FALSE
 * 1 = TRUE */

#include <stdio.h>
#include <stdlib.h>
#include "Trie.h"

/* Cria o nodo raiz;
 * Inicializa suas variáveis;
 * Poem o sinal indicar de fim de palavra em todas as letras do vetor. */

node Trie(){
	node *T;
	int i;
	
	if (!(T = malloc(sizeof(trie)))){
		return NULL;
	}
	
	father = NULL;
	
	for (i = 0; i < 27; i++){
		T[i] = '$';
	}
	
	T->kids = 0;
	
	return T;
}

int insert(node *T, char *word){
	int i, size;
	node *aux, *pointer;
	
	for (size = 0; word[size] != '\0'; size++);
	
	T = root;
	
	pointer = T->nodo;
	for (i = 0; i < size; i++){
		aux = Trie();
		if (!aux) {
			return 0;
		}
		aux->kids++;
		pointer[word[i]] = aux;
		aux->father = pointer[word[i]];
		pointer = aux;
	}
	
	pointer[26] = 1;
	
	T->kids++;
	
	return 1;
	
}
/* Função auxiliar
 * Acha o final da palavram
 * É útil tanto para a função find e para a função delete */
int get(node *T, char *word){
	int i, pos;
	node *pointer;
	char *aux;
	
	i = 0;
	aux = word[i];
	pointer = T->nodo;
	
	while(aux != '\0'){
		pos = *aux - 'a';
		pointer = pointer[pos];
		i++;
		aux = word[i];
	}
	
	return pointer;
}


int find(node *T, char *word){
	node *aux;
	
	aux = get(T, word);
	
	if (aux[25]){
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
			pointer = aux-father;
			free(aux);
			aux = pointer;
		} else {
			return 0;
		}
	}
	
	return 1;
}
