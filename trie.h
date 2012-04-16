/* Marlon da Silva Dias - Ciência da Computação
 * Sinal indicador de fim de palavra: $ 
 * 
 * 0 = FALSE
 * 1 = TRUE */


#ifndef TRIE_H_
#define TRIE_H_

struct no {
	struct no *key[27]; 
	struct no *father;
	int kids;
};

typedef struct no node;

/* Inicialização */
node *Trie();

/* Tratar a árvore */
// 0 = false; 1 = true;
int insert(node *T, char *word);
int find(node *T, char *word);
int delete(node *T, char *word);
node *get(node *T, char *word);

#endif
