#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef enum{
	AVENTURA = 0,
	COMEDIA,
	DRAMA,
	TERROR,
	ACAO,
	ROMANCE,
}Genero;

typedef enum{
	LIVRE = 0,
	MAIS_10,
	MAIS_12,
	MAIS_14,
	MAIS_16,
	MAIS_18,
}Classificacao;

typedef enum{
	PLANO_B = 0,
	PLANO_P,
}Tipo_Plano;

typedef struct{
	int codigo_filme;
	char nome_filme[50];
	Genero genero_filme;
	Classificacao classificacao_filme; 
}Filme;

typedef struct{
	int qntd_filmes_b;
	float valor_base_b;
	float valor_excedente_b;
}Plano_B;

typedef struct{
	float valor_base_p;
}Plano_P;

typedef union{
	Plano_B PLANO_B;
	Plano_P PLANO_P;
}PLANOS;

typedef struct{
	int numero_agencia;
	int numero_conta;
}Debito;

typedef struct{ 
	int numero_cartao_c;
}Credito;

typedef enum{
	ATIVO = 1,
	INATIVO = 0,
}Status;

typedef struct{
	int cpf_cliente;
	char nome_cliente[50];
	char email_cliente[50];
	char telefone_cliente[15];
	Status status;
}Cliente;

typedef struct {
	Cliente clientes; //para o cpf
	Tipo_Plano tipo_plano;
	int data_contrato;
	int data_cancelamento;
	int qntd_filmes;
	Status status;
	Credito credito;
	Debito debito;
}Contrato;

typedef struct{
	int gera_fatura;	
}Gera_fatura;

typedef struct{
	char nome_filme[50];
	int cod_genero;
	int cod_classificacao;
	int data_assistiu;
	int mes_assistiu;
	int cod_filme;
	Gera_fatura gera_fatura;	
	Filme filmes;
}Historico;


int cadastra_cliente(Cliente* clientes, int tam); 
int cadastra_filme(Filme* filmes, int tam); 
int cadastra_plano_b(PLANOS* planos);
int cadastra_plano_p(PLANOS* planos);
int cadastra_contrato(Contrato* contratos, Cliente* clientes, int tam_contrato, int tam_clientes); //maximo de 10 cadastrados (1 por cliente)
int carrega_filme(Contrato* contratos, Filme* filmes, Cliente* clientes, PLANOS* plano_b, PLANOS* planos_p, Historico historico_mensal[][30], int tam_x, int tam_y, int tam_contrato, int tam_filmes, int tam_clientes, Gera_fatura* mes_fatura, int tam_mes, int tipo_plano_b);
int cancela_contrato(Cliente* clientes, int tam_clientes, Contrato* contratos, int tam_contrato, PLANOS* plano_b, PLANOS* plano_p);
int gera_fatura(Contrato* contratos, int tam_contrato, Historico historico_mensal[][30], int tam_x, int tam_y, Cliente* clientes, int tam_cliente, int tipo_plano_b, PLANOS* planos_b, PLANOS* planos_p, Gera_fatura* mes_fatura, int *tam_mes);
int listar_dados_cliente(Contrato* contratos, Cliente* clientes, int tam_contrato, int tam_clientes);
int lista_historico_cliente(Contrato* contratos, int tam_contrato, Cliente* clientes, int tam_cliente, Filme* filmes, int tam_filmes, Historico historico_mensal[][30], int tam_x, int tam_y);
int lista_clientes_exc_cota_mensal(Contrato* contratos, int tam_contrato, Historico historico_mensal[][30], int tam_x, int tam_y, int tipo_plano_b, PLANOS* plano_b);
int frequencia_filme(Filme* filmes, int tam_filmes, Historico historico_mensal[][30], int tam_x, int tam_y, int qntd_filmes_total); //arrumar ainda
int recomenda_filme(Cliente* clientes, int tam_clientes, Contrato* contratos, int tam_contrato, Historico historico_mensal[][30], int tam_x, int tam_y, Filme* filmes, int tam_filmes);

int main (){
	Cliente vet_cliente[10];
	Filme vet_filme[10];
	Gera_fatura mes_fatura[1];
	PLANOS plano_b;
	PLANOS plano_p;
	int plano_basico=0;
	Contrato contratos[10];
	Historico matriz_historico[10][30];
	int opcao, cont_cliente=0, cont_filme=0, cont_contrato=0, conta_mes=1;
	int filme_carregado=0;
	
	int i, k;
	for (i = 0; i < 10; i++) {
		for (k = 0; k < 30; k++) {
			matriz_historico[i][k].data_assistiu = -1;
		}
	}
	do{
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				if(cadastra_cliente(vet_cliente, cont_cliente) == 0){
					cont_cliente++;
					printf("Cliente cadastrado com sucesso\n");
				}
				break;
			case 2:
				if(cadastra_filme(vet_filme, cont_filme) == 0){
					cont_filme++;
					printf("Filme cadastrado com sucesso\n");
				}
				break;
			case 3:
				if(cadastra_plano_b(&plano_b) == 0){
					printf("Plano Basico cadastrado com sucesso\n");
				}
				break;
			case 4:
				if(cadastra_plano_p(&plano_p) == 0){
					printf("Plano Premium cadastrado com sucesso\n");
				}
				break;
			case 5:
				if(cadastra_contrato(contratos, vet_cliente, cont_contrato, cont_cliente) == 0){
					cont_contrato++;
					printf("Contrato cadastrado com sucesso\n");
				}
				break;
			case 6:
				if(carrega_filme(contratos, vet_filme, vet_cliente, &plano_b, &plano_p, matriz_historico, 10, 30, cont_contrato, cont_filme, cont_cliente, mes_fatura, conta_mes, plano_basico) == 0){ 
						printf("Filme carregado com sucesso\n");
						filme_carregado++;
				}
				break;
			case 7:
				cancela_contrato(vet_cliente, cont_cliente, contratos, cont_contrato, &plano_b, &plano_p);
				break;
			case 8:
				gera_fatura(contratos, cont_contrato, matriz_historico, 10, 30, vet_cliente, cont_cliente, plano_basico, &plano_b, &plano_p, mes_fatura, &conta_mes);
				break;
			case 9:
				listar_dados_cliente(contratos, vet_cliente, cont_contrato, cont_cliente);
				break;
			case 10:
				lista_historico_cliente(contratos, cont_contrato, vet_cliente, cont_cliente, vet_filme, cont_filme, matriz_historico, 10, 30);
				break;
			case 11:
				lista_clientes_exc_cota_mensal(contratos, cont_contrato, matriz_historico, 10, 30, plano_basico, &plano_b);
				break;
			case 12:
				frequencia_filme(vet_filme, cont_filme, matriz_historico, 10, 30, filme_carregado);
				break;
			case 13:
				recomenda_filme(vet_cliente, cont_cliente, contratos, cont_contrato, matriz_historico, 10, 30, vet_filme, cont_filme);
				break;
			case 0:
				printf("Finalizando programa...");
				break;
			default:
				printf("ERRO: Opcao invalida\n");
				break;
		}
	}while(opcao != 0);

	return 0;
}

int cadastra_cliente(Cliente* clientes, int tam){ //1
	const int max = 10;
	int i; 
	
	if(tam == max){
		printf("ERRO: Numero maximo de clientes no sistema atingido\n");
		return 1;
	}
	
	int cpf_do_cliente;
	scanf("%d", &cpf_do_cliente);
	
	for(i=0; i<tam; i++){
		if(cpf_do_cliente == clientes[i].cpf_cliente){
				printf("ERRO: CPF do cliente ja cadastrado\n");
			return 1;
		}
	}
	
	clientes[tam].cpf_cliente = cpf_do_cliente;
	scanf(" %[^\n]%*c", clientes[tam].nome_cliente);
	scanf(" %[^\n]%*c", clientes[tam].email_cliente);
	scanf(" %[^\n]%*c", clientes[tam].telefone_cliente);
	clientes[tam].status = INATIVO;
	
	return 0;
}

int cadastra_filme(Filme* filmes, int tam){ //2
	const int max = 10;
	
	if(max == tam){
		printf("ERRO: Numero maximo de filmes no sistema atingido\n");
		return 1;
	}
	
	scanf(" %[^\n]%*c", filmes[tam].nome_filme);
	
	int genero, validacao_f=1;
	do{
		//printf("Digite o genero: ");
		scanf("%d", &genero);
		if(genero >= 0 && genero <= 5){
			validacao_f = 0;
		}else{
		printf("ERRO: Genero invalido\n"); }
		
	}while(validacao_f);
	
	int classificacao, validacao_c=1;
	do{
		//printf("Digite a classificacao: ");
		scanf("%d", &classificacao);
		if(classificacao >= 0 && classificacao <= 5){
			validacao_c = 0;
		}else{
		printf("ERRO: Classificacao invalida\n");}
		
	}while(validacao_c);
	
	switch(genero){
		case 0: 
			filmes[tam].genero_filme = AVENTURA;	
		break;
		case 1: 
			filmes[tam].genero_filme = COMEDIA;
		break;
		case 2: 
			filmes[tam].genero_filme = DRAMA;
		break;
		case 3: 
			filmes[tam].genero_filme = TERROR;
		break;
		case 4: 
			filmes[tam].genero_filme = ACAO;
		break;
		case 5: 
			filmes[tam].genero_filme = ROMANCE;
		break;
	}
	
	switch(classificacao){
		case 0: 
			filmes[tam].classificacao_filme = LIVRE;	
		break;
		case 1: 
			filmes[tam].classificacao_filme = MAIS_10;
		break;
		case 2: 
			filmes[tam].classificacao_filme = MAIS_12;
		break;
		case 3: 
			filmes[tam].classificacao_filme = MAIS_14;
		break;
		case 4: 
			filmes[tam].classificacao_filme = MAIS_16;
		break;
		case 5: 
			filmes[tam].classificacao_filme = MAIS_18;
		break;
	}
	
	filmes[tam].codigo_filme = 1001 + tam;
	return 0;	
}

int cadastra_plano_b(PLANOS* planos){ //3
	int qntd;
	
	scanf("%d", &qntd);
	planos->PLANO_B.qntd_filmes_b = qntd;
	
	float valor_base;
	scanf("%f", &valor_base);
	planos->PLANO_B.valor_base_b = valor_base;
	
	float valor_exc;
	scanf("%f", &valor_exc);
	planos->PLANO_B.valor_excedente_b = valor_exc;
	
	return 0;
}

int cadastra_plano_p(PLANOS* planos){ //4
	float valor_base;
	
	scanf("%f", &valor_base);
	planos->PLANO_P.valor_base_p = valor_base;
	
	
	return 0;
}

int cadastra_contrato(Contrato* contratos, Cliente* clientes, int tam_contrato, int tam_clientes){ //5
	const int max = 10;
	if(max == tam_contrato){
		printf("ERRO: Numero maximo de contratos no sistema atingido\n"); 
		return 1;
	}
	
	if(tam_clientes == 0){
		printf("ERRO: Nenhum cliente cadastrado no sistema\n"); //ve se tem algum cliente cadastrado >>no sistema<<
		return 1;
	}
	
	int cpf_cliente, i, k, validacao_cpf=1;
	do{
	//	printf("cpf: \n");
		scanf("%d", &cpf_cliente);
		for(k = 0; k < tam_contrato; k++){
			if(contratos[k].clientes.cpf_cliente == cpf_cliente){
				printf("ERRO: Cliente com contrato existente\n");
				return 1;
			}
		}
		for(i = 0; i < tam_clientes; i++){
				if(clientes[i].cpf_cliente == cpf_cliente){ //verifica se o cpf dado bate com algum cliente já cadastrado
					contratos[tam_contrato].clientes.cpf_cliente = cpf_cliente; //se existir o cpf no vetor de cadastrdo vai receber o cpf existente.
					strcpy(contratos[tam_contrato].clientes.nome_cliente, clientes[i].nome_cliente);
					clientes[i].status = ATIVO;
					validacao_cpf = 0;	
				}
		}
		if(validacao_cpf == 1){ 
				printf("ERRO: Cliente nao cadastrado\n");
				return 1; 
		}
	}while(validacao_cpf);
	
	int plano, validacao_plano=1;
	do{
	//	printf("plano: \n");
		scanf("%d", &plano);
		if(plano >= 0 && plano <= 1){
			validacao_plano = 0;
		}else {
			printf("ERRO: Tipo de plano invalido\n");
		}
	}while(validacao_plano);
	
	if(plano == 0){
		contratos[tam_contrato].tipo_plano = PLANO_B;
		contratos[tam_contrato].qntd_filmes = 0;
	}else{
		contratos[tam_contrato].tipo_plano = PLANO_P;
	}
	
	int pagamento, validacao_pag=1;
	do{
	//	printf("pag: \n");
		scanf("%d", &pagamento);
		if(pagamento >= 0 && pagamento <= 1){
			validacao_pag = 0;
		}else{
			printf("ERRO: Tipo de pagamento invalido\n");
		}
	}while(validacao_pag);
	
	int agencia, conta, cartao_credito;
	if(pagamento == 0){
	//	printf("ag\n");
		scanf("%d", &agencia);
		contratos[tam_contrato].debito.numero_agencia = agencia;
	//	printf("conta: \n");
		scanf("%d", &conta);
		contratos[tam_contrato].debito.numero_conta = conta;
	}else{
	//	printf("cartao\n");
		scanf("%d", &cartao_credito);
		contratos[tam_contrato].credito.numero_cartao_c = cartao_credito;
	}
	
	int dia, validacao_dia=1;
	do{
	//	printf("dia\n");
		scanf("%d", &dia);
		if(dia >= 1 && dia <= 31){
			contratos[tam_contrato].data_contrato = dia;
			validacao_dia = 0;
		}else{
			printf("ERRO: Dia invalido\n");
		}
	}while(validacao_dia);
	
	contratos[tam_contrato].status = ATIVO;
	
	contratos[tam_contrato].data_cancelamento = 0;
	
	contratos[tam_contrato].qntd_filmes = 0;
	
	return 0;
}

int carrega_filme(Contrato* contratos, Filme* filmes, Cliente* clientes, PLANOS* plano_b, PLANOS* planos_p, Historico historico_mensal[][30], int tam_x, int tam_y, int tam_contrato, int tam_filmes, int tam_clientes, Gera_fatura* mes_fatura, int tam_mes, int tipo_plano_b){ //6
	
	if(tam_clientes == 0){
		printf("ERRO: Nenhum cliente cadastrado no sistema\n");
		return 1;
	}
	
	int i, k, aux=0, cpf, validacao_cpf=1;
	do{
		scanf("%d", &cpf);
		for(i = 0; i < tam_clientes; i++){ 
			if(clientes[i].cpf_cliente == cpf){ 
				for(k = 0; k < tam_contrato; k++){ 
					if(contratos[k].clientes.cpf_cliente == cpf){
					aux = k;
					validacao_cpf = 0;
					}
				}
				if(validacao_cpf == 1){
					printf("ERRO: Cliente nao ativo\n");
					return 1;
				}
			}
		}
		if(validacao_cpf == 1){
			printf("ERRO: Cliente nao cadastrado\n");
			return 1;
		}
	}while(validacao_cpf);
	
	
	int dia, validacao_dia=1;
	do{
	//	printf("Data:\n");
		scanf("%d", &dia);
			if(dia >= 1 && dia <= 31){
				validacao_dia = 0;
			}else{
				printf("ERRO: Dia invalido\n");
			}
	}while(validacao_dia);
	
	
	int resposta, validacao_r=1;
	do{
	//	printf("genero(0) ou classificacao(1))\n");
		scanf("%d", &resposta);
		if(resposta >= 0 && resposta <= 1){
			validacao_r = 0;
		}else{
			printf("ERRO: Escolha invalida\n");
		}	
	}while(validacao_r);
	
	
	
	int numero, validacao_num=1;
	do{
	//	printf("numero:\n");
		scanf("%d", &numero);
		if(numero >= 0 && numero <= 5){
			validacao_num = 0;
		}else{
			printf("ERRO: Escolha invalida\n");
		}
	}while(validacao_num);
	
	//para a função 13//
	/*int num_genero=0, num_classificacao=0;
	if(resposta == 0){
		num_genero = numero;
	}
	if(resposta == 1){
		num_classificacao = numero;
	}*/
	
	
	int z;
	if(resposta == 0){
		for(z = 0; z < tam_filmes; z++){
			if(filmes[z].genero_filme == numero){
				printf("Codigo: %d\n", filmes[z].codigo_filme);
				printf("Nome: %s\n", filmes[z].nome_filme);
			}
		}
	}
	if(resposta == 1){
		for(z = 0; z < tam_filmes; z++){
			if(filmes[z].classificacao_filme == numero){
				printf("Codigo: %d\n", filmes[z].codigo_filme);
				printf("Nome: %s\n", filmes[z].nome_filme);
			}
		}
	}
	

	int taxa_adicional, valida_b=1, valida_cod=1, y, cod_escolhido;
	scanf("%d", &cod_escolhido);
	for(y = 0; y < tam_filmes; y++){
		if(filmes[y].codigo_filme == cod_escolhido){
			if(contratos[aux].tipo_plano == tipo_plano_b){
				if(contratos[aux].qntd_filmes >= plano_b->PLANO_B.qntd_filmes_b){
					do{
						scanf("%d", &taxa_adicional);
							if(taxa_adicional == 0){
								printf("ERRO: Taxa adicional negada\n");
								return 1;
							}
							if(taxa_adicional != 1){
								printf("ERRO: Escolha invalida\n");
							}
							if(taxa_adicional == 1){
								valida_b = 0;
							}
					}while(valida_b);	
				}
			}
			valida_cod = 0;
		}
	}
	if(valida_cod == 1){
		printf("ERRO: Filme nao encontrado\n");
		return 1;
	}
	
	int aux1;
	for(i = 0; i <tam_filmes; i++){
		if(filmes[i].codigo_filme == cod_escolhido){
			aux1 = i;
		}
	}

	
	int m;
	for (i = 0; i < 30; i++){
		if (historico_mensal[aux][i].data_assistiu == -1) {
			historico_mensal[aux][i].data_assistiu = dia;
			historico_mensal[aux][i].mes_assistiu = tam_mes;
			historico_mensal[aux][i].cod_filme = cod_escolhido;
				for(m = 0; m < tam_filmes; m++){
					if(filmes[m].codigo_filme == cod_escolhido){
						strcpy(historico_mensal[aux][i].nome_filme, filmes[m].nome_filme);
					}
				}
			historico_mensal[aux][i].cod_genero = filmes[aux1].genero_filme;
			historico_mensal[aux][i].cod_classificacao = filmes[aux1].classificacao_filme;
			break;
		}
	}
	
	contratos[aux].qntd_filmes = contratos[aux].qntd_filmes + 1;

	return 0; 
}

int cancela_contrato(Cliente* clientes, int tam_cliente, Contrato* contratos, int tam_contrato, PLANOS* plano_b, PLANOS* plano_p){ //7

	if(tam_contrato == 0){
		printf("ERRO: Nenhum contrato cadastrado no sistema\n");
		return 1;
	}
	
	int i, k, aux=0, cpf, validacao_cpf=1;
	do{
		scanf("%d", &cpf);
		for(i = 0; i < tam_cliente; i++){ 
			if(clientes[i].cpf_cliente == cpf){ 
				for(k = 0; k < tam_contrato; k++){ 
					if(contratos[k].clientes.cpf_cliente == cpf){
					aux = k;
					validacao_cpf = 0;
					}
				}
				if(validacao_cpf == 1){
					printf("ERRO: Cliente inativo\n");
					return 1;
				}
			}
		}
		if(validacao_cpf == 1){
			printf("ERRO: Cliente nao cadastrado\n");
			return 1;
		}
	}while(validacao_cpf);
	
	int data, valida_data=1;
	do{
		scanf("%d", &data);
		if(data >= 1 && data <= 31){
			valida_data = 0;
		}
		if(valida_data == 1){
			printf("ERRO: Dia invalido\n");
		}
	}while(valida_data);
	
	if(contratos[aux].data_contrato > data){
		printf("ERRO: Data de cancelamente anteiror a data de contratacao\n");
		return 1;
	}else{
		if(contratos[aux].tipo_plano == 0){
			
			printf("Valor devido: %.2f\n", plano_b->PLANO_B.valor_base_b + ((contratos[aux].qntd_filmes - plano_b->PLANO_B.qntd_filmes_b) * plano_b->PLANO_B.valor_excedente_b));
			printf("Cancelamento feito com sucesso\n");
				contratos[aux].data_cancelamento = data;
				contratos[aux].clientes.cpf_cliente = -1;
			//	contratos[aux].clientes.email_cliente = -1;
			//	contratos[aux].clientes.nome_cliente = NULL;
			//	contratos[aux].clientes.telefone_cliente = NULL;
				contratos[aux].credito.numero_cartao_c = -1;
				contratos[aux].debito.numero_agencia = -1;
				contratos[aux].debito.numero_conta = -1;
				contratos[aux].qntd_filmes = -1;
				contratos[aux].tipo_plano = -1;
				contratos[aux].status = 0;
		}
		if(contratos[aux].tipo_plano == 1){
			printf("Valor devido: %.2f\n", plano_p->PLANO_P.valor_base_p);
			printf("Cancelamento feito com sucesso\n");
				contratos[aux].data_cancelamento = data;
				contratos[aux].clientes.cpf_cliente = -1;
			//	contratos[aux].clientes.email_cliente = -1;
			//	contratos[aux].clientes.nome_cliente = NULL;
			//	contratos[aux].clientes.telefone_cliente = NULL;
				contratos[aux].credito.numero_cartao_c = -1;
				contratos[aux].debito.numero_agencia = -1;
				contratos[aux].debito.numero_conta = -1;
				contratos[aux].qntd_filmes = -1;
				contratos[aux].tipo_plano = -1;
				contratos[aux].status = 0;
		}
	}

	return 0;
}

int gera_fatura(Contrato* contratos, int tam_contrato, Historico historico_mensal[][30], int tam_x, int tam_y, Cliente* clientes, int tam_cliente, int tipo_plano_b, PLANOS* planos_b, PLANOS* planos_p, Gera_fatura* mes_fatura, int *tam_mes){ //8
	int i, j, m, escolha, cpf, valida_cpf=1, valida_r=1;
	do{
		scanf("%d", &escolha);
			if(escolha == 0){
				if(tam_contrato == 0){
				printf("ERRO: Nenhum cliente cadastrado no sistema\n");
				return 1;
				}
				valida_r=0;
			}
			if(escolha == 1){
				valida_r=0;
			}
			if(valida_r == 1){
				printf("ERRO: Escolha invalida\n");
			}
	}while(valida_r);
	
	//fatura especifica
	if(escolha == 0){
		do{
			scanf("%d", &cpf);
				for(i = 0; i < tam_cliente; i++){
					if(clientes[i].cpf_cliente == cpf){
						for(j = 0; j < tam_contrato; j++){
							if(clientes[i].cpf_cliente == contratos[j].clientes.cpf_cliente){
								for(m = 0; m < contratos[j].qntd_filmes; m++){
									printf("Nome: %s\n", historico_mensal[j][m].nome_filme); //nome do filme
									printf("Data: %d/%d\n", historico_mensal[j][m].data_assistiu, historico_mensal[j][m].mes_assistiu); //data do carregamento
									valida_cpf=0;
									}	
										if(contratos[j].tipo_plano == tipo_plano_b){
											printf("Valor devido: %.2f\n", planos_b->PLANO_B.valor_base_b + (planos_b->PLANO_B.valor_excedente_b * (contratos[j].qntd_filmes - planos_b->PLANO_B.qntd_filmes_b)));
										}else{
											printf("Valor devido: %.2f\n", planos_p->PLANO_P.valor_base_p);
										}				
							}
							
						}
					if(valida_cpf == 1){
						printf("ERRO: Cliente nao possui contrato\n");
						return 1;
					}
					}
				}
				if(valida_cpf==1){
					printf("ERRO: Cliente nao cadastrado\n");
					return 1;
				}
		}while(valida_cpf);
	}
	
	//fatura de todos os clientes
	if(escolha == 1){
		for(i = 0; i < tam_contrato; i++){
			if(contratos[i].clientes.cpf_cliente != -1){
					printf("CPF: %d\n", contratos[i].clientes.cpf_cliente);
					printf("Nome: %s\n", contratos[i].clientes.nome_cliente); //nome do cliente
					if(contratos[i].tipo_plano == tipo_plano_b){
						printf("Valor devido: %.2f\n", planos_b->PLANO_B.valor_base_b + (planos_b->PLANO_B.valor_excedente_b * (contratos[j].qntd_filmes - planos_b->PLANO_B.qntd_filmes_b)));
					} else{
						printf("Valor devido: %.2f\n", planos_p->PLANO_P.valor_base_p);
					}
			}
		}
		*tam_mes += 1;
		printf("Mes vigente apos a fatura: %d\n", *tam_mes);
	}
	
	
	return 0;
}

int listar_dados_cliente(Contrato* contratos, Cliente* clientes, int tam_contrato, int tam_clientes){ //9
	if(tam_clientes == 0){
		printf("ERRO: Nenhum cliente cadastrado no sistema\n");
		return 1;
	}
	
	int i, validacao_cpf=1, cpf_cliente;
	do{
		scanf("%d", &cpf_cliente);
		for(i = 0; i < tam_clientes; i++){ 
			if(clientes[i].cpf_cliente == cpf_cliente){
				printf("Nome: %s\n", clientes[i].nome_cliente);
				printf("Email: %s\n", clientes[i].email_cliente);
				printf("Telefone: %s\n", clientes[i].telefone_cliente);
				printf("Status: %d\n", clientes[i].status);
				validacao_cpf = 0; 
			}
		}
		if(validacao_cpf == 1){
				printf("ERRO: Cliente nao cadastrado\n");
				return 1;
		}
	}while(validacao_cpf);
			
	return 0;
}

int lista_historico_cliente(Contrato* contratos, int tam_contrato, Cliente* clientes, int tam_cliente, Filme* filmes, int tam_filmes, Historico historico_mensal[][30], int tam_x, int tam_y){ //10
	 if(tam_cliente == 0){
	 	printf("ERRO: Nenhum cliente cadastrado no sistema\n");
	 	return 1;
	 }
	 
	 int i, k, aux=0, cpf, valida_cpf=1;
	 scanf("%d", &cpf);
	 do{
		 for(i = 0; i < tam_cliente; i++){
		 	if(clientes[i].cpf_cliente == cpf){
		 		for(k = 0; k < tam_contrato; k++){
		 			if(contratos[k].clientes.cpf_cliente == cpf){
						 aux = k;
		 				valida_cpf = 0;
					 }
				 }
				if(valida_cpf == 1){
				 	printf("Estado: Inativo\n");
					printf("ERRO: Nenhum filme assistido\n");
					return 1;
				}	 
			 }
		}
		 if(valida_cpf == 1){
		 	printf("ERRO: Cliente nao cadastrado\n");
		 	return 1;
		 }
	}while(valida_cpf);
	
	if(contratos[aux].qntd_filmes == 0){
		printf("Estado: Ativo\n");
		printf("ERRO: Nenhum filme assistido\n");
		return 1;
	}
	int j, p;
	if(contratos[aux].qntd_filmes > 0){
		printf("Estado: Ativo\n");
				for(j = 0; j < contratos[aux].qntd_filmes; j++){
					printf("Codigo: %d\n", historico_mensal[aux][j].cod_filme); 
						for(p = 0; p < tam_filmes; p++){
							if(historico_mensal[aux][j].cod_filme == filmes[p].codigo_filme){
								printf("Nome: %s\n", filmes[p].nome_filme);
									switch(filmes[p].genero_filme){
										case 0: 
											printf("Genero: aventura\n");
										break;
										case 1: 
											printf("Genero: comedia\n");
										break;
										case 2: 
											printf("Genero: drama\n");
										break;
										case 3: 
											printf("Genero: terror\n");
										break;
										case 4: 
											printf("Genero: acao\n");
										break;
										case 5: 
											printf("Genero: romance\n");
										break;
									}
									switch(filmes[p].classificacao_filme){
										case 0: 
											printf("Classificacao: livre\n");
										break;
										case 1: 
											printf("Classificacao: +10\n");
										break;
										case 2: 
											printf("Classificacao: +12\n");
										break;
										case 3: 
											printf("Classificacao: +14\n");
										break;
										case 4: 
											printf("Classificacao: +16\n");
										break;
										case 5: 
											printf("Classificacao: +18\n");
										break;
									}
						}
					}
				printf("Data do carregamento: %d/%d\n\n", historico_mensal[aux][j].data_assistiu, historico_mensal[aux][j].mes_assistiu);
			}
	}
	 return 0;
}

int lista_clientes_exc_cota_mensal(Contrato* contratos, int tam_contrato, Historico historico_mensal[][30], int tam_x, int tam_y, int tipo_plano_b, PLANOS* plano_b){ //11/
	int i, valida=1;
		for(i = 0; i < tam_contrato; i++){
			if(contratos[i].tipo_plano == tipo_plano_b){
				if(contratos[i].qntd_filmes > plano_b->PLANO_B.qntd_filmes_b){
					printf("CPF: %d\n", contratos[i].clientes.cpf_cliente);
					printf("Nome: %s\n", contratos[i].clientes.nome_cliente);
					printf("Valor excedente: %.2f\n\n", (contratos[i].qntd_filmes - plano_b->PLANO_B.qntd_filmes_b) * plano_b->PLANO_B.valor_excedente_b);
					valida = 0;		
				}
			}
		}
		if(valida == 1){
			printf("ERRO: Nenhum cliente excedente\n");
			return 1;
		}
		return 0;
}

int frequencia_filme(Filme* filmes, int tam_filmes, Historico historico_mensal[][30], int tam_x, int tam_y, int qntd_filmes_total){ //12 
	if(tam_filmes == 0){
		printf("ERRO: Nenhum filme cadastrado no sistema\n");
		return 1;
	}
	
	int cod_filme, i, validacao_cod=1;
	do{
		scanf("%d", &cod_filme);
		for(i = 0; i < tam_filmes; i++){
			if(filmes[i].codigo_filme == cod_filme){
				validacao_cod = 0;
			}
		}
		if(validacao_cod == 1){
			printf("ERRO: Codigo invalido\n");
			return 1;
		}
	}while(validacao_cod);
	
	int j, k; 
	float qntd_filme_exibido=0;
	for(j = 0; j < tam_x; j++){
		for(k = 0; k < tam_y; k++){
			if(historico_mensal[j][k].cod_filme == cod_filme){
				qntd_filme_exibido++;
			}
		}
	}
	
	if(qntd_filme_exibido == 0){
		printf("ERRO: Nenhum filme assistido\n");
	}else{
	printf("Frequencia: %.2f%%\n", qntd_filme_exibido/qntd_filmes_total * 100);
	}
	
	return 0;
}

int recomenda_filme(Cliente* clientes, int tam_clientes, Contrato* contratos, int tam_contrato, Historico historico_mensal[][30], int tam_x, int tam_y, Filme* filmes, int tam_filmes){ //13
	if(tam_clientes == 0){
		printf("ERRO: Nenhum cliente cadastrado no sistema\n");
		return 1;
	}
	
	int i, j, aux=0, cpf, valida_cpf=1;
	scanf("%d", &cpf);
	do{
		for(i = 0; i < tam_clientes; i++){
			if(clientes[i].cpf_cliente == cpf){
				for(j = 0; j < tam_contrato; j++){
					if(contratos[j].clientes.cpf_cliente == cpf){
						aux = j;
						valida_cpf = 0;
					}
				}
					if(valida_cpf == 1){
						printf("ERRO: Cliente nao ativo\n");
						return 1;
					}
				}
		}
		if(valida_cpf == 1){
			printf("ERRO: Cliente nao cadastrado\n");
			return 1;
		}	
	} while(valida_cpf);
	
	if(contratos[aux].qntd_filmes == 0){
		printf("ERRO: Nenhum filme assistido\n");
		return 1;
	}
	
	int vet_qntd[6], qntd0=0, qntd1=0, qntd2=0, qntd3=0, qntd4=0, qntd5=0;
	for(i = 0; i < contratos[aux].qntd_filmes; i++){
		switch(historico_mensal[aux][i].cod_genero){
			case 1:
				qntd1++;
				break;
			case 2:
				qntd2++;
				break;
			case 3:
				qntd3++;
				break;
			case 4:
				qntd4++;
				break;
			case 5:
				qntd5++;
				break;
			case 0:
				qntd0++;
				break;
		}
	}
	//////vetores de cada genero com a quantidade///////
	vet_qntd[0] = qntd0;
	vet_qntd[1] = qntd1;
	vet_qntd[2] = qntd2;
	vet_qntd[3] = qntd3;
	vet_qntd[4] = qntd4;
	vet_qntd[5] = qntd5;
	
	int mais_assistido=0, aux1=0, aux2=0;
	for(i = 0; i < 6; i++){
		if(vet_qntd[i] > mais_assistido){
			mais_assistido = vet_qntd[i];
			aux1 = i; // indice do cod genero mais assistido do cliente
		}
	}
	for(i = 0; i < 6; i ++){
		if(vet_qntd[aux1] == vet_qntd[i]){
			aux2 = i; 
		}
	}
	
	
	int z, valida_filme = 0;
	for(i = 0; i < contratos[aux].qntd_filmes; i++){
		if(historico_mensal[aux][i].cod_genero == aux1){
			for(z = 0; z < tam_filmes; z++){
				if(filmes[z].genero_filme == aux1){
					if(historico_mensal[aux][i].cod_filme != filmes[z].codigo_filme){
						printf("Codigo: %d\n", filmes[z].codigo_filme);
						printf("Nome: %s\n", filmes[z].nome_filme);
							switch(filmes[z].genero_filme){
								case 0:
									printf("Genero: aventura\n");
									break;
								case 1:
									printf("Genero: comedia\n");
									break;
								case 2:
									printf("Genero: drama\n");
									break;
								case 3:
									printf("Genero: terror\n");
									break;
								case 4:
									printf("Genero: acao\n");
									break;
								case 5:
									printf("Genero: romance\n");
									break;
							}
							switch(filmes[z].classificacao_filme){
								case 0:
									printf("Classificacao: livre\n");
									break;
								case 1:
									printf("Classificacao: +10\n");
									break;
								case 2:
									printf("Classificacao: +12\n");
									break;
								case 3:
									printf("Classificacao: +14\n");
									break;
								case 4:
									printf("Classificacao: +16\n");
									break;
								case 5:
									printf("Classificacao: +18\n");
									break;
									valida_filme=0;
							}
					}
				}
			}
		}
	}
	int p, q;
	for(p = 0; p < contratos[aux].qntd_filmes; p++){
		if(historico_mensal[aux][p].cod_genero == aux2){
			for(q = 0; q < tam_filmes; q++){
				if(filmes[q].genero_filme == aux2){
					if(historico_mensal[aux][p].cod_filme != filmes[q].codigo_filme){
						printf("Codigo: %d\n", filmes[q].codigo_filme);
						printf("Nome: %s\n", filmes[q].nome_filme);
							switch(filmes[q].genero_filme){
								case 0:
									printf("Genero: aventura\n");
									break;
								case 1:
									printf("Genero: comedia\n");
									break;
								case 2:
									printf("Genero: drama\n");
									break;
								case 3:
									printf("Genero: terror\n");
									break;
								case 4:
									printf("Genero: acao\n");
									break;
								case 5:
									printf("Genero: romance\n");
									break;
							}
							switch(filmes[q].classificacao_filme){
								case 0:
									printf("Classificacao: livre\n");
									break;
								case 1:
									printf("Classificacao: +10\n");
									break;
								case 2:
									printf("Classificacao: +12\n");
									break;
								case 3:
									printf("Classificacao: +14\n");
									break;
								case 4:
									printf("Classificacao: +16\n");
									break;
								case 5:
									printf("Classificacao: +18\n");
									break;
									valida_filme=0;
							}
					}
				}
			}
		}
	}
	
		if(valida_filme == 1){
			printf("ERRO: Todos os filmes do(s) genero(s) foram assistidos\n");
			return 1;
		}
	
	
	return 0;
}

