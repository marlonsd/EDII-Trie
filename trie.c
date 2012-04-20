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
	int i, size, pos;
	node *aux, *pointer;
	
	size = lenght(word); //for (size = 1; word[size] != '\0'; size++);
	
	pointer = T;
//	printf("Pointer: %x\n", pointer);
	for (i = 0; i < size; i++){
		pos = word[i] - 'a';
//		printf("%d ",pos);
		if (pointer->key[pos]){
			pointer = pointer->key[pos];
			pointer->kids++;
		} else {
			aux = Trie();
			if (!aux) {
				return 0;
			}
			pointer->key[pos] = aux;
			aux->father = pointer;
			pointer->kids++;
//			printf("%x %x\n", pointer, aux->father);
			//printf("Father: %x - Pointer: %x - Aux: %x - Pointer->key[%c]: %x\n", pointer->father,pointer, aux,(pos + 'a'), pointer->key[pos]);
			//printf("%d %d", )
			pointer = aux;
		}
	}
	
	pointer->key[26] = (node*) 1;

	//printf("\n%x - %x\n", pointer, pointer->key[26]);
	//printf("T Kids: %d - Pointer Kids: %d\n", T->kids, pointer->kids);
	
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
//	printf("%s\n\n", aux);
	pointer = T;
	if (aux == '\0'){
		return NULL;
	} else {
		while((aux[i] != '\0') && (pointer)){
			pos = aux[i] - 'a';
//			printf("%d\n", pos);
//			printf("Pointer: %x - Pointer->key[%c]: %x\n",pointer, pos+'a', pointer->key[pos] );
			pointer = pointer->key[pos];
			//printf("%x ", pointer);
			i++;
		}
	}
	
	return pointer;
	
}


int find(node *T, char *word){
	node *aux;
	
	aux = get(T, word);
	
	if (aux){
		if (aux->key[26]){
			return 1;
		}
	}
	
	return 0;
}

int delete(node *T, char *word){
	int size, control;
	node *aux, *pointer;
	
	aux = get(T, word);

	size = lenght(word);
	//printf("%x %d\n\n", aux, aux->kids);
	/* Enquanto não chegar na raiz, onde o pai é nulo */
	if (aux){
		//printf("%x %d\n", aux, aux->kids);
		while(aux->father){
			//aux->key[26] = NULL;
			//pointer = aux->father;
			//printf("%d ", pointer->kids);
			if (aux->kids < 1){ // Se não tem filhos
				//printf("%d\n", size);
				aux->key[26] = NULL;
				pointer = aux->father;
				size--;
				//printf("Pointer: %x - Pointer->key[%c]: %x - Aux: %x\n", pointer, word[size], pointer->key[word[size] - 'a'], aux);
				//printf("-- Kids: %d %d\n", pointer->kids, aux->kids);
				pointer->key[word[size] - 'a'] = NULL;
				pointer->kids--;
				//printf("%x %d\n", aux->key[size], size);
				free(aux);
				aux = pointer;
			} else {
				aux = aux->father;
			}
			//printf("%x %d\n", aux, aux->kids);
		} 
	} else {
		return 0;
	}
	
	//printf("\n%x\n", aux->key[0]);
	
	return 1;
}

int lenght(char *word){
	int size;
	
	for (size = 1; word[size] != '\0'; size++);
	
	return size;
}
