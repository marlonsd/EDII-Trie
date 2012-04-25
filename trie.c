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
	
	/*aux = Trie();
	
	if (!(aux)){
		return 0;
	}
	
	aux->father = pointer;
	pointer->key[26] = aux;
	pointer->kids++;*/
	//printf("%x %x ", pointer->key[26], pointer->key[26]->father);
	
	pointer->key[26] = (node *) 1;
	pointer->kids++;

	//printf("\n%x - %x\n", pointer, pointer->key[26]);
	//printf("T Kids: %d - Pointer Kids: %d\n", T->kids, pointer->kids);
	//printf("%d %d", T->kids, T->key[0]->kids);
	return 1;
	
}
/* Função auxiliar
 * Acha o final da palavram
 * É útil tanto para a função find e para a função delete */
node *get(node *T, char *word){
	int i, pos;
	node *pointer;
	
	i = 0;

//	printf("%s\n\n", aux);
	pointer = T;
	if (word[0] == '\0'){
		return NULL;
	} else {
		while((word[i] != '\0') && (pointer)){
			pos = word[i] - 'a';
//			printf("%d\n", pos);
//			printf("Pointer: %x - Pointer->key[%c]: %x\n",pointer, pos+'a', pointer->key[pos] );
			pointer = pointer->key[pos];
			//printf("%x ", pointer);
			i++;
		}
	}
	
	/*if (pointer) {
		return pointer->key[26];
	} 
	
	return NULL;*/
	
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

	//size = lenght(word);
	//printf("%x %d\n\n", aux, aux->kids);
	/* Enquanto não chegar na raiz, onde o pai é nulo */
	if (aux){
		//printf("%x %d\n", aux, aux->kids);
//		printf("%x %x %x\n", aux, aux->father->key[26], aux->father);
		aux->key[26] = NULL;
		aux->kids--;
		if (!aux->kids){
			father = aux->father;
			father->kids--;
			free(aux);
			//printf("Here\n");
			while(father){
				aux = father;
				father = aux->father;
				if ((aux->father) && (!father->kids)){
					//printf("Here\n");
/*					father->kids--;
						
					if (!aux->kids){
						i = 0;
						while((father->key[i] != aux) && (i < 26)){
							i++;
						}
						
						if (father->key[i] == aux){
							father->key[i] = NULL;
						} else {
							return 0;
						}
						
						free(aux);
					}*/
					aux = father;
					father = father->father;
					
					if (!aux->kids){
						i = 0;
						while((father->key[i] != aux) && (i < 26)){
							i++;
						}
						
						if (father->key[i] == aux){
							father->key[i] = NULL;
						} else {
							return 0;
						}
						
						free(aux);
						father->kids--;
					}
				}
			}
		}
	} else {
		return 0;
	}
	
	//printf("\n%x\n", aux->key[0]);
	
	return 1;
}

int lenght(char *word){
	int size;
	
	for (size = 0; word[size] != '\0'; size++);
	
	return size;
}
