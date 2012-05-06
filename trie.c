// ------------------------------------------------------------
//  Trabalho Estrutura de Dados II - Árvore Trie
//		Ciênia da Computação
//
//	Aluno: Marlon da Silva Dias
//	GitHub: https://github.com/marlonsd/EDII-Trie
//	trie.c
//
// 0 = false; 1 = true;
// ------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

/* Cria um novo nodo;
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

/* Insere um novo elemento na árvore */
int insert(node *T, char *word){
	int i, pos;
	node *aux, *pointer;
	
	pointer = T;

	for (i = 0; word[i] != '\0'; i++){
		pos = word[i] - 'a';
		if (pointer->key[pos]){
			pointer = pointer->key[pos];
		} else {
			aux = Trie();
			if (!aux) {
				return 0;
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
 * É utilizada tanto para a função find como para a função delete */
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

/* Localiza um elemento na árvore */
int find(node *T, char *word){
	node *aux;
	
	aux = get(T, word);
	
	if ((aux) && (aux->key[26])){
		return 1;
	}
	
	return 0;
}

/* Remove um elemento da árvore */
int delete(node *T, char *word){
	int i;
	node *aux, *father;
	
	aux = get(T, word);

	if (aux && aux->key[26]){
		aux->key[26] = NULL;
		aux->kids--;
			
		while (aux->father && (!aux->kids)){
			father = aux->father;
			i = 0;
			
			while((father->key[i] != aux) && (i < 26)){
				i++;
			}
			
			father->key[i] = NULL;
			father->kids--;
			
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
