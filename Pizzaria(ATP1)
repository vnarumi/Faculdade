#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

typedef struct {
	char rua[50];
	int numero;
	char bairro[50];
}Endereco;

typedef struct {
	char telefone[15];
	char nome[50];
	Endereco endereco;
}Pessoa;

typedef struct {
	Pessoa pessoa;
}Cliente;

typedef struct {
	Pessoa pessoa;
	int cod_motoqueiro;
}Motoqueiro;

typedef struct {
	int cod_pizza;
	char nome_pizza[50];
	float preco;
}Pizza;

typedef struct {
	int cod_pedido;
	char telefone_cliente[50];
	int cod_pizza;
	int cod_motoqueiro;
	int situacao;
}Pedido;

int cadastro_cliente(Cliente* vetor_cliente, int tam);
int cadastro_motoqueiro(Motoqueiro* vetor_motoqueiro, int tam);
int cadastro_pizza(Pizza* vetor_pizza, int tam);
int cadastro_pedido(Pedido* vetor_pedido, Cliente* vetor_clientes, Pizza* vetor_pizza, int tam, int tam_cliente, int tam_pizza);
int despacho_pizza(Pedido* pedido, Motoqueiro* vetor_motoqueiro, int tam_pedido, int tam_motoqueiro);
int recebe_pizza(Pedido* vetor_pedido, int tam);
int situacao_pedido(Pedido* vet_pedido, int tam);
int pedidos_clientes(Pedido* vet_pedido, Cliente* vet_cliente, int tam, int tam_cliente);
int pedidos_motoqueiros(Pedido* vet_pedido, Motoqueiro* vet_motoqueiro, int tam, int tam_motoqueiro);

int main(){
	int opcao = 1, qnt_clientes = 0, qnt_motoqueiro = 0, qnt_pizza = 0, qnt_pedido = 0;
	Cliente clientes[5];
	Motoqueiro motoqueiros[2];
	Pizza pizzas[3];
	Pedido pedidos[6];
	
	printf("1)Cadastra Cliente\n");
	printf("2)Cadastra Motoboy\n");
	printf("3)Cadastra pizza\n");
	printf("4)Cadastra pedido\n");
	printf("5)Despacha pizza\n");
	printf("6)Recebe pizza\n");
	printf("7)Pedidos por situacao\n");
	printf("8)Pedidos por cliente\n");
	printf("9)Motoqueiros entregas\n");
	printf("0)Sair\n");
	printf("Digite um numero do menu: ");
	
	while(opcao != 0){
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				if(cadastro_cliente(clientes, qnt_clientes) == 0){
					qnt_clientes++;
					printf("Cliente cadastrado com sucesso\n");
				}
				break;
			case 2:
				if(cadastro_motoqueiro(motoqueiros, qnt_motoqueiro) == 0){
					qnt_motoqueiro++;
					printf("Motoqueiro cadastrado com sucesso\n");
				} 
				break;
			case 3:
				if(cadastro_pizza(pizzas, qnt_pizza) == 0){
					qnt_pizza++;
					printf("Pizza cadastrada com sucesso\n");
				}
				break;
			case 4:
				if(cadastro_pedido(pedidos, clientes, pizzas, qnt_pedido, qnt_clientes, qnt_pizza) == 0){
					qnt_pedido++;
					printf("Pedido cadastrado\n");
				}
				break;
			case 5:
				despacho_pizza(pedidos, motoqueiros, qnt_pedido, qnt_motoqueiro);
				break;
			case 6:
				recebe_pizza(pedidos, qnt_pedido);
				break;
			case 7:
				situacao_pedido(pedidos, qnt_pedido);
				break;
			case 8:
				pedidos_clientes(pedidos, clientes, qnt_pedido, qnt_clientes);
				break;
			case 9:
				pedidos_motoqueiros(pedidos, motoqueiros, qnt_pedido, qnt_motoqueiro);
				break;
			case 0:
				printf("Encerrando sistema");
				break;
			default:
				printf("Opcao invalida\n");
				break;
		}
		fflush(stdin);
	}
	return 0;
}

int cadastro_cliente(Cliente* vetor_cliente, int tam){
	int max = 5;
	if(tam == max){
		printf("Numero maximo de clientes cadastrados\n");
		return 1;
	}
	
	char telefone_cliente[50];
	scanf(" %[^\n]%*c", telefone_cliente);
	
	int i;
	for(i=0; i<tam; i++){
		if(strcmp(telefone_cliente, vetor_cliente[i].pessoa.telefone) == 0){
			printf("Cliente ja cadastrado\n");
			return 1;
		}
	}
	
	strcpy(vetor_cliente[tam].pessoa.telefone, telefone_cliente);
	
	scanf(" %[^\n]%*c", vetor_cliente[tam].pessoa.nome);
	scanf(" %[^\n]%*c", vetor_cliente[tam].pessoa.endereco.rua);
	scanf(" %d", &vetor_cliente[tam].pessoa.endereco.numero);
	scanf(" %[^\n]%*c", vetor_cliente[tam].pessoa.endereco.bairro);
	
	return 0;
}

int cadastro_motoqueiro(Motoqueiro* vetor_motoqueiro, int tam){
	int max = 2;
	if(tam == max){
		printf("Numero maximo de motoqueiros cadastrados\n");
		return 1;
	}
	
	int cod_motoqueiro;
	scanf(" %d", &cod_motoqueiro);
	
	int i;
	for(i = 0; i < tam; i++){
		if(cod_motoqueiro == vetor_motoqueiro[i].cod_motoqueiro){
			printf("Motoqueiro ja cadastrado\n");
			return 1;
		}
	}
	
	vetor_motoqueiro[tam].cod_motoqueiro = cod_motoqueiro;
		
	scanf(" %[^\n]%*c", vetor_motoqueiro[tam].pessoa.telefone);
	scanf(" %[^\n]%*c", vetor_motoqueiro[tam].pessoa.nome);
	scanf(" %[^\n]%*c", vetor_motoqueiro[tam].pessoa.endereco.rua);
	scanf(" %d", &vetor_motoqueiro[tam].pessoa.endereco.numero);
	scanf(" %[^\n]%*c", vetor_motoqueiro[tam].pessoa.endereco.bairro);
	
	return 0;
}

int cadastro_pizza(Pizza* vetor_pizza, int tam){
	int max = 3;
	
	if(tam == max){
		printf("Numero maximo de pizzas cadastrados\n");
		return 1;
	}
	
	int cod_pizza;
	scanf("%d", &cod_pizza);
	
	int i;
	for(i=0; i<tam; i++){
		if(vetor_pizza[i].cod_pizza == cod_pizza){
			printf("Pizza ja cadastrada\n");
			return 1;
		}
    }
    
	vetor_pizza[tam].cod_pizza = cod_pizza;
	
	scanf(" %[^\n]%*c", vetor_pizza[tam].nome_pizza);
	scanf("%f", &vetor_pizza[tam].preco);
	return 0;
}

int cadastro_pedido(Pedido* vetor_pedido, Cliente* vetor_clientes, Pizza* vetor_pizza, int tam, int tam_cliente, int tam_pizza){
	int max = 6;
	
	if(tam == max){
		printf("Numero maximo de pedidos realizados\n");
		return 1;
	}
	
	int i, aux = 1, cod_pizza;
	char telefone_cliente[50];
	
	scanf(" %[^\n]%*c", telefone_cliente);

	for(i = 0; i < tam_cliente; i++) {
		if(strcmp(vetor_clientes[i].pessoa.telefone, telefone_cliente)  == 0){
			aux = 0;
		}
	}
	
	if(aux == 1){
		printf("Cliente nao encontrado\n");
		return 1;
	}
	
	strcpy(vetor_pedido[tam].telefone_cliente, telefone_cliente);
	
	aux = 1;
	scanf(" %d", &cod_pizza);
	for(i = 0; i < tam_pizza; i++) {
		if(vetor_pizza[i].cod_pizza  == cod_pizza){
			aux = 0;
		}
	}
	
	if(aux == 1){
		printf("Pizza nao cadastrada\n");
		return 1;
	}
	
	vetor_pedido[tam].cod_pizza = cod_pizza;
	
	vetor_pedido[tam].situacao = 1;
	vetor_pedido[tam].cod_motoqueiro = 0;
	vetor_pedido[tam].cod_pedido = tam;
	return 0;
	
}

int despacho_pizza(Pedido* pedido, Motoqueiro* vetor_motoqueiro, int tam_pedido, int tam_motoqueiro){

	int cod_pedido, aux = 1, i;
	scanf("%d", &cod_pedido);
	
	for(i = 0; i < tam_pedido; i++){
		if(pedido[i].cod_pedido == cod_pedido){
			aux = 0;
		}
	}
	
	if(aux == 1){
		printf("Pedido nao encontrado\n");
		return 1;
	} 
	
	if(pedido[cod_pedido].situacao == 1){
		int cod_motoquerio;
		scanf("%d", &cod_motoquerio);
		aux = 1;
		for(i = 0; i < tam_motoqueiro; i++){
			if(vetor_motoqueiro[i].cod_motoqueiro == cod_motoquerio){
				aux = 0;
			}
		}
		
		if(aux == 1){
			printf("Motoqueiro nao encontrado\n");
			return 1;
		}
		
		pedido[cod_pedido].situacao = 2;
		pedido[cod_pedido].cod_motoqueiro = cod_motoquerio;
		printf("Despachando pedido\n");
	} else if(pedido[cod_pedido].situacao == 2){
		printf("Pedido ja despachado\n");
		return 1;
	} else if(pedido[cod_pedido].situacao == 3){
		printf("Pedido ja entregue\n");
		return 1;
	}
	return 0;
}

int recebe_pizza(Pedido* vetor_pedido, int tam) {
	int codigo_pedido, i, aux = 1;
	
	scanf("%d", &codigo_pedido);
	
	for(i = 0; i < tam; i++){
		if(vetor_pedido[i].cod_pedido == codigo_pedido){
			aux = 0;
		}
	}
	
	if(aux == 1){
		printf("Pedido nao encontrado\n");
		return 1;
	}
	
	if(vetor_pedido[codigo_pedido].situacao == 3){
		printf("Entrega ja realizada\n");
		return 1;
	}
	
	vetor_pedido[codigo_pedido].situacao = 3;
	printf("Pedido entregue\n");
	return 0;
}

int situacao_pedido(Pedido* vet_pedido, int tam){
	int cod_situacao, i, aux = 1;
	scanf("%d", &cod_situacao);
	
	if(cod_situacao != 1 && cod_situacao != 2 && cod_situacao != 3){
		printf("Opcao invalida\n");
		return 1;
	}
	
	for(i = 0; i < tam; i++){
		if(vet_pedido[i].situacao == cod_situacao){
			printf("Pedido: %d\n", vet_pedido[i].cod_pedido);
			printf("Cliente: %s\n", vet_pedido[i].telefone_cliente);
			printf("Pizza: %d\n", vet_pedido[i].cod_pizza);
			printf("Motoq: %d\n", vet_pedido[i].cod_motoqueiro);
			aux = 0;
		}
	}
	
	if(aux == 1){
		printf("Sem itens nessa situacao\n");
		return 1;
	}
	
	return 0;
}

int pedidos_clientes(Pedido* vet_pedido, Cliente* vet_cliente, int tam, int tam_cliente){
	int i, aux = 1;
	char telefone[50];
	scanf(" %[^\n]%*c", telefone);
	
	for(i = 0; i < tam_cliente; i++){
		if(strcmp(vet_cliente[i].pessoa.telefone, telefone) == 0) {
			aux = 0;
		}
	}
		
	if(aux == 1){
		printf("Cliente nao encontrado\n");
		return 1;
	}
	
	aux = 1;
	for(i = 0; i < tam; i++){
		if(strcmp(vet_pedido[i].telefone_cliente, telefone) == 0){
			printf("Pedido: %d\n", vet_pedido[i].cod_pedido);
			printf("Situacao: %d\n", vet_pedido[i].situacao);
			printf("Pizza: %d\n", vet_pedido[i].cod_pizza);
			printf("Motoq: %d\n", vet_pedido[i].cod_motoqueiro);
			aux = 0;
		}
	}
	
	if(aux == 1){
		printf("Cliente sem pedidos\n");
		return 1;
	}
	
	return 0;
}

int pedidos_motoqueiros(Pedido* vet_pedido, Motoqueiro* vet_motoqueiro, int tam, int tam_motoqueiro){
	int cod_motoqueiro, i, aux = 1;
	
	scanf("%d", &cod_motoqueiro);
	
	for(i = 0; i < tam_motoqueiro; i++){
		if(vet_motoqueiro[i].cod_motoqueiro == cod_motoqueiro) {
			aux = 0;
		}
	}
		
	if(aux == 1){
		printf("Motoqueiro nao encontrado\n");
		return 1;
	}
	
	aux = 1;
	for(i = 0; i < tam; i++){
		if(vet_pedido[i].cod_motoqueiro == cod_motoqueiro){
			printf("Pedido: %d\n", vet_pedido[i].cod_pedido);
			printf("Situacao: %d\n", vet_pedido[i].situacao);
			aux = 0;
		}
	}
	
	if(aux == 1){
		printf("Motoqueiro sem pedidos\n");
		return 1;
	}
	
	return 0;
}
