#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PALAVRA 15000
#define TOTAL_PALAVRAS 10000

void inserir(char *word[], int *count);
void buscar(char *word[], int count);
void remover(char **word, int count);
void gerarPalavra(int tamanho, char *palavra);

FILE *fin, *fout;

int main(){
	char *palavras[40000];
	int count_palavras, numero, i;
		
	if((fin = fopen( "in.txt", "w")) == NULL ) {
		printf("nao foi possivel criar o arquivo\n");
		exit(1);
	}
	
	if((fout = fopen( "out.txt", "w")) == NULL ) {
		printf("nao foi possivel criar o arquivo\n");
		exit(1);
	}
	
	srand(time(NULL));
	count_palavras = 0;
	
	for (i = 0; i < TOTAL_PALAVRAS; i++){
		numero = rand() % 3;
		printf("passei aqui %d\n", numero);
		switch(numero){

			case 0: inserir(palavras, &count_palavras);
				break;
			case 1: buscar(palavras, count_palavras);
				break;
			case 2: remover(palavras, count_palavras);
				break;
		}
	}
	
	fclose(fout);
	fclose(fin);
	
	return 0;
}

void inserir(char *word[], int *count) {
	int tam;
	
	tam = rand() % MAX_PALAVRA;
	
	while(tam == 0){
		tam = rand() % MAX_PALAVRA;
	}
	
	if (!(word[*count] = malloc((tam + 1)*sizeof(char)))){
		printf("Nao consegui alocar o vetor.\n");
		exit(1);
	}
	
		
	gerarPalavra(tam, word[*count]);
	
	fprintf(fin,"i %s\n", word[*count]);
	fprintf(fout,"v\n");
	
	(*count)++;
}

void buscar(char *word[], int count){
	int chance, i, j, tam, teste;
	char *aux, *comp;
	
	i = 0;
	
	teste = 0;
	aux = word[i];
	printf("Passei %d %d\n", i, count);
	while (!teste && (i < count)){
		if (aux[0] != '\0'){
			teste = 1;
		}
		aux = word[i];
		i++;
		printf("PRESO\n");
	}
	
	if (teste){
		chance = rand() % 2;
	} else {
		chance = 0;
	}
	
	if (chance){
		chance = rand() % count;
		aux = word[chance];
		
		while (aux[0] == '\0'){
			chance = rand() % count;
			aux = word[chance];
			printf("preseo\n");
		}
		
		fprintf(fin,"b %s\n", aux);
		fprintf(fout, "v\n");
	} else {
		tam = rand() % MAX_PALAVRA;
		
		while(tam == 0){
			tam = rand() % MAX_PALAVRA;
		}
		
		aux = malloc(sizeof(char)*(tam+1));

		gerarPalavra(tam, aux);
		/* */
		if (count > 0){
			teste = 0;
			while (!teste){
				i = 0;
				while (!teste && (i < count)){
					comp = word[i];
					j = 0;
					while ((aux[j] != '\0') && (comp[j] != '\0') && !teste){
						if (aux[j] == comp[j]){
							printf("%c %c\n", aux[j], comp[j]);
							j++;
						} else {
							printf("Oi 1\n");
							teste = 1;
						}
					}
					i++;
					printf("Here 1\n");
				}
				if (!teste){
					gerarPalavra(tam, aux);
				}
			}
		}
		/*  */
		
		fprintf(fin,"b %s\n", aux);
		fprintf(fout, "f\n");
	}
}

void remover(char *word[], int count){
	int chance, i, tam, teste, j;
	char *aux, *comp;
	
	i = 0;
	
	teste = 0;
	
	aux = word[i];
	while(!teste && (i < count)){
		if (aux[0] != '\0'){
			teste = 1;
		}
		aux = word[i];
		i++;
		printf("PRESO\n");
	}
	
	if (teste){
		chance = rand() % 2;
	} else {
		chance = 0;
	}
	
	if (chance){
		chance = rand() % count;
		aux = word[chance];
		
		while (aux[0] == '\0'){
			chance = rand() % count;
			aux = word[chance];
			printf("preseo\n");
		}
		
		fprintf(fin,"r %s\n", aux);
		fprintf(fout, "v\n");
		
		aux[0] = '\0';
	} else {
		tam = rand() % MAX_PALAVRA;
		
		while(tam == 0){
			tam = rand() % MAX_PALAVRA;
		}
		
		aux = malloc(sizeof(char)*(tam+1));
		
		gerarPalavra(tam, aux);
		
		/* */
		teste = 0;
		if (count > 0){
			while (!teste){
				i = 0;
				while (!teste && (i < count)){
					comp = word[i];
					j = 0;
					while ((aux[j] != '\0') && (comp[j] != '\0') && !teste){
						if (aux[j] == comp[j]){
							printf("%c %c\n", aux[j], comp[j]);
							j++;
						} else {
							printf("Oi 2\n");
							teste = 1;
						}
					}
					i++;
					printf("Here 2 %d\n", i);
				}
				if (!teste){
					gerarPalavra(tam, aux);
				}
			}
		}
		/*  */
		
		fprintf(fin,"r %s\n", aux);
		fprintf(fout, "f\n");
	}
}

void gerarPalavra(int tamanho, char *palavra){
	int i;
	char aux;
	
	for (i = 0; i < tamanho; i++){
		aux = rand() % 26;
		palavra[i] = aux + 'a';
	}
	
	palavra[tamanho] = '\0';
}
