#include <stdio.h>
#include <stdlib.h>

/*Menu de op��es
 1. Cadastrar um dos tr�s tipos de obras
 2. Consultar um dos tr�s tipos de obras
 3. Finalizar o programa*/

typedef enum {
	MESTRADO = 1,
	DOUTORADO
}Modalidade;

typedef enum{
	LIVRO = 1,
	TESE,
	PERIODICO 
}Tipo;

typedef struct {
	char autor[30];
	char titulo[30];
	int ano;
	char editora[30];
	char cidade[30];
	Tipo tipo;
}Livros;

typedef struct {
	char autor[30];
	char titulo[30];
	int mes;
	int ano;
	char universidade[30];
	char p_pos_grad[30];
	char orientador[30];
	Modalidade modalidade;
	Tipo tipo;
}Teses;

typedef struct {
	char titulo[30];
	int volume;
	int mes;
	int ano;
	char editora[30];
	char cidade[30];
	int num_paginas;
	Tipo tipo;
}Periodicos;

typedef union {
	Periodicos periodicos;
	Teses teses;
	Livros livros;
}Obras;

int cadastrar(Obras* obras, int posicao);
void consultar(Obras* obras, int tam);

int main()
{
	const int tam = 1;
	Obras vet_obras[tam];
	int opcao, cont=0;
	
	do{
		printf("1)Cadastrar um dos tres tipos de obras\n2)Consultar um dos tres tipos de obras\n3)Finalizar o programa\nDigite a opcao desejado: ");
		scanf("%d", &opcao);
		switch(opcao)
		{
			case 1: 
			 	if(cadastrar(vet_obras, cont) == 0){
			 	cont++;
			 }
			break;
			case 2:
				consultar(vet_obras, cont);
			break;
			case 3:
				printf("Fim de execucao\n");
			break;
		}
		fflush(stdin);
	}while(opcao != 3);
	
	return 0;
}

int cadastrar(Obras* obras, int posicao){
	const int max = 1;
	int opcao; 
	
	if(posicao == max){
		printf("Limite de cadastros excedido!\n");
		return 1;
	}
	
	printf("\n\n------CADASTRO-------\n1)Livro\n2)Tese\n3)Periodicos\nDigite a opcao desejada: ");
	scanf("%d", &opcao);
	
	switch(opcao)
	{
		case 1: 
			obras[posicao].livros.tipo = 1;
			printf("Nome do autor: ");
			scanf(" %[^\n]%*c", obras[posicao].livros.autor);
			printf("Titulo do livro: ");
			scanf(" %[^\n]%*c", obras[posicao].livros.titulo);
			printf("Ano de lancamento: ");
			scanf("%d", &obras[posicao].livros.ano);
			printf("Editora: ");
			scanf(" %[^\n]%*c", obras[posicao].livros.editora);
			printf("Cidade: ");
			scanf(" %[^\n]%*c", obras[posicao].livros.cidade);
			printf("-----Livro Cadastrado!-----\n");
			return 0;
		break;
		case 2: 
			obras[posicao].teses.tipo = 2;
			printf("Nome do autor: ");
			scanf(" %[^\n]%*c", obras[posicao].teses.autor);
			printf("Titulo da tese: ");
			scanf(" %[^\n]%*c", obras[posicao].teses.titulo);
			printf("Mes de lancamento: ");
			scanf("%d", &obras[posicao].teses.mes);
			printf("Ano de lancamento: ");
			scanf("%d", &obras[posicao].teses.ano);
			printf("Universidade: ");
			scanf(" %[^\n]%*c", obras[posicao].teses.universidade);
			printf("Programa: ");
			scanf(" %[^\n]%*c", obras[posicao].teses.p_pos_grad);
			printf("Orientador: ");
			scanf(" %[^\n]%*c", obras[posicao].teses.orientador);
			int aux;
			scanf("%d", &aux);
			obras[posicao].teses.modalidade = aux;
			printf("-----Tese Cadastrada!-----\n");
			return 0;
		break;
		case 3:
			obras[posicao].periodicos.tipo = 3;
			printf("Titulo do periodico: ");
			scanf(" %[^\n]%*c", obras[posicao].periodicos.titulo);
			printf("Volume: ");
			scanf("%d", &obras[posicao].periodicos.volume);
			printf("Mes: ");
			scanf("%d", &obras[posicao].periodicos.mes);
			printf("Ano: ");
			scanf("%d", &obras[posicao].periodicos.ano);
			printf("Editora: ");
			scanf(" %[^\n]%*c", obras[posicao].periodicos.editora);
			printf("Cidade: ");
			scanf(" %[^\n]%*c", obras[posicao].periodicos.cidade);	
			printf("Numero de paginas: ");
			scanf("%d", &obras[posicao].periodicos.num_paginas);
			printf("-----Periodico Cadastrado!-----\n");
			return 0;
		break;
	}
	
	return 1;
}

void consultar(Obras* obras, int tam){
	int opcao, i;
	
	scanf("%d", &opcao);
	
	switch(opcao)
	{
		case 1:
			for(i = 0; i < tam; i++){
				if(obras[i].livros.tipo == 1){
				printf("Autor: %s\n", obras[i].livros.autor);
				printf("Titulo: %s\n", obras[i].livros.titulo);
				printf("Ano: %d\n", obras[i].livros.ano);
				printf("Editora: %s\n", obras[i].livros.editora);
				printf("Cidade: %s\n", obras[i].livros.cidade);
				printf("tipo: %d", obras[i].livros.tipo);
				printf("-----------------\n");;
				}
		    }
		break;
		case 2:
			for(i = 0; i < tam; i++){
				if(obras[i].teses.tipo == 2){
				printf("Autor: %s\n", obras[i].teses.autor);
				printf("Titulo: %s\n", obras[i].teses.titulo);
				printf("Mes: %d\n", obras[i].teses.mes);
				printf("Ano: %d\n", obras[i].teses.ano);
				printf("Universidade: %s\n", obras[i].teses.universidade);
				printf("Programa: %s\n", obras[i].teses.p_pos_grad);
				printf("Orientador: %s\n", obras[i].teses.orientador);
				printf("Graduacao: %d\n", obras[i].teses.modalidade);
				printf("-----------------\n");
				}
		    }
		break;
		case 3:
			for(i = 0; i < tam; i++){
				if(obras[i].periodicos.tipo == 3){
				printf("Titulo: %s\n", obras[i].periodicos.titulo);
				printf("Volume: %d\n", obras[i].periodicos.volume);
				printf("Mes: %d\n", obras[i].periodicos.mes);
				printf("Ano: %d\n", obras[i].periodicos.ano);
				printf("Editora: %s\n", obras[i].periodicos.editora);
				printf("Cidade: %s\n", obras[i].periodicos.cidade);
				printf("Numero de paginas: %d\n", obras[i].periodicos.num_paginas);
				printf("-----------------\n");
				}
		    }
		break;
	}
}

