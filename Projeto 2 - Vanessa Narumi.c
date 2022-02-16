#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[50];
    float v_d_compra;
    float v_d_venda;
    int qntd_estoque;
    int qntd_vendida;
}Info;

typedef struct{
    char nome[50];
    int ativo;
}Ch_primaria;

void cadastra_produto(Info informacoes, Ch_primaria key);
int vender_produto(Info informacoes, Ch_primaria key);
int deleta_produto(Info informacoes, Ch_primaria key);
void calcula_lucro(Info informacoes, Ch_primaria key);
void calcula_valor_estoque(Info informacoes, Ch_primaria key);
void repor_estoque(Info informacoes, Ch_primaria key); 

FILE *arqOut;
FILE *arqIn;
FILE *chave_bin;
FILE *chave_bin_out;

int main() {
    int opcao;
    Info info;
    Ch_primaria chave;

	arqOut = fopen("sistema_venda.txt", "a+b"); //usando a flag a+b(vamos abrir um arq, se ele ja existir nos vamos escrever no final dele se n ele vai ser criado). vamos escrever em binario
	if (arqOut == NULL) { //verificar se o arquivo foi criado/aberto com sucesso
		printf("Nao foi possivel abrir o arquivo!");
		return 0;
	}

    chave_bin = fopen("chave_bin.txt", "a+b");
    if (chave_bin == NULL) { 
		printf("Nao foi possivel abrir o arquivo!");
		return 0;
	}
	
    do{
        printf("\nMENU\n1- Vender\n2- Cadastrar novo produto\n3- Remover produto do estoque\n4- Consultar estoque\n5- Consultar lucro\n6- Repor estoque\n0- Sair\n");
        printf("Digite a opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                vender_produto(info, chave);
            break;

            case 2:
                cadastra_produto(info, chave);
            break;

            case 3:
                deleta_produto(info, chave);
            break;

            case 4: 
                calcula_valor_estoque(info, chave);
            break;

            case 5:
                calcula_lucro(info, chave);
            break;

            case 6:
                repor_estoque(info,chave); 
            break;
        }
    }while(opcao != 0);

	fclose(arqOut);
    fclose(chave_bin);
    
	return 0;
}

void cadastra_produto(Info informacoes, Ch_primaria key){
    arqOut = fopen("sistema_venda.txt", "a+b"); 
	if (arqOut == NULL) { 
		printf("Nao foi possivel abrir o arquivo!");
		return 0;
	}

    chave_bin = fopen("chave_bin.txt", "a+b");
    if (chave_bin == NULL) { 
		printf("Nao foi possivel abrir o arquivo!");
		return 0;
	}

    char nome[50];
	int qntd_vend, qntd_est;
	float v_venda, v_compra;
    int ativo=1;

    printf("\nNome: ");
    scanf(" %[^\n]", nome);
    getchar();
    strcpy(informacoes.nome, nome);
    strcpy(key.nome, nome);
    key.ativo = ativo;
    fwrite(&key, sizeof(key), 1, chave_bin);

    fflush(stdin);
    printf("Valor de compra: ");
    scanf("%f", &v_compra);
    fflush(stdin);
    informacoes.v_d_compra = v_compra;

    printf("Valor de venda: ");
    scanf("%f", &v_venda);
    fflush(stdin);
    informacoes.v_d_venda = v_venda;
    
    printf("Quantidade em estoque: ");
    scanf("%d", &qntd_est);
    fflush(stdin);
    informacoes.qntd_estoque = qntd_est;

    printf("Quantidade vendida: ");
    scanf("%d", &qntd_vend);
    fflush(stdin);
    informacoes.qntd_vendida = qntd_vend;

    //salvando os dados recebidos no arquivo
    fwrite(&informacoes, sizeof(informacoes), 1, arqOut);

    fclose(arqOut);
    fclose(chave_bin);
    
}

int vender_produto(Info informacoes, Ch_primaria key){
    char nome[50];
    int qntd=0, qntd_est_atual=0, qntd_vend_atual=0;
    float valor_total=0;
    int cont=0;

    arqIn = fopen("sistema_venda.txt", "r+b"); //abrindo arq para vizulizar os dados do produto
	if (arqIn == NULL) {
		printf("Nao foi possivel abrir o arquivo!");
		return 0;
	}

    chave_bin = fopen("chave_bin.txt", "r+b"); //abrindo arq para pegar o nome
	if (chave_bin == NULL) { 
		printf("Nao foi possivel abrir o arquivo!");
		return 0;
	}

    int i = 1;
    printf("\nLISTA DE PRODUTOS A VENDA\n"); //listando nomes chave dos produtos existentes
    while(fread(&key, sizeof(key), 1, chave_bin) > 0){
        if(key.ativo == 1){
            printf("%d) %s\n", i, key.nome);
        }
        i++;
    }

    printf("Digite o NOME do produto que deseja comprar: ");
    scanf("%s", nome);
    printf("Digite a QUANTIDADE que deseja comprar: ");
    scanf("%d", &qntd);


    while(fread(&informacoes, sizeof(informacoes), 1, arqIn) > 0){
        if(key.ativo == 1){
            if(strstr(informacoes.nome, nome) != NULL){
                if(qntd > informacoes.qntd_estoque || informacoes.qntd_estoque == 0){
                    printf("\nNao ha estoque disponivel para atender a venda...\n");
                    return 0;
                }else{
                    valor_total = informacoes.v_d_venda * qntd;
                    printf("O total a ser pago eh de: %0.2f\n", valor_total);
                    
                    arqOut = fopen("sistema_venda.txt", "rb+"); //reabrir arq inicial para vizualizar e dps alterar
                    if (arqOut == NULL) { 
                        printf("Nao foi possivel abrir o arquivo!");
                        return 0;
                    }

                    while(fread(&informacoes, sizeof(informacoes), 1, arqOut) > 0){
                        if(strstr(informacoes.nome, nome) != NULL){
                            qntd_est_atual = informacoes.qntd_estoque - qntd;
                            qntd_vend_atual = informacoes.qntd_vendida + qntd;
                            informacoes.qntd_estoque = qntd_est_atual;
                            informacoes.qntd_vendida = qntd_vend_atual;
                            fseek(arqOut, cont * sizeof(informacoes), SEEK_SET);
                            fwrite(&informacoes, sizeof(informacoes), 1, arqOut);
                            break;
                        }
                        cont++;
                    }
                }
            }
        }
    }

    fclose(arqIn);
    fclose(chave_bin);
    fclose(arqOut);
}

int deleta_produto(Info informacoes,Ch_primaria key){
    char nome[50];
    int ativo=0;

    chave_bin = fopen("chave_bin.txt", "r+b");
	if (chave_bin == NULL) { 
		printf("Nao foi possivel abrir o arquivo!");
		return 0;
	}

    int i = 1;
    printf("\nLISTA DE PRODUTOS EXISTENTES\n"); 
    while(fread(&key, sizeof(key), 1, chave_bin) > 0){
        if(key.ativo == 1){
            printf("%d) %s\n", i, key.nome);
        }
        i++;
    }

    fclose(chave_bin);

    printf("Digite o nome do produto que deseja remover: ");
    scanf("%s", nome);
    int cont=0;
    chave_bin = fopen("chave_bin.txt", "rb+");
	if (chave_bin == NULL) { 
		printf("Nao foi possivel abrir o arquivo!");
		return 0;
	}

    while(fread(&key, sizeof(key), 1, chave_bin) > 0){
        if(strstr(key.nome, nome) != NULL){
            key.ativo = ativo;
            fseek(chave_bin, cont * sizeof(key), SEEK_SET);
            fwrite(&key, sizeof(key), 1, chave_bin);
            break;
        }
        cont++;
    }

    printf("Produto removido com sucesso...\n");
    fclose(chave_bin);

}

void calcula_lucro(Info informacoes, Ch_primaria key){
    float valor_total;
    char nome[50];

    arqIn = fopen("sistema_venda.txt", "r+b"); 
	if (arqIn == NULL) { 
		printf("Nao foi possivel abrir o arquivo!");
		return 0;
	}

    chave_bin = fopen("chave_bin.txt", "r+b");
	if (chave_bin == NULL) { 
		printf("Nao foi possivel abrir o arquivo!");
		return 0;
	}
    
    while(fread(&key, sizeof(key), 1, chave_bin) > 0){
        if(key.ativo == 1){
            strcpy(nome, key.nome);
            while(fread(&informacoes, sizeof(informacoes), 1, arqIn) > 0){
                if(strstr(nome, informacoes.nome) != NULL){
                    valor_total = 0;
                    valor_total = informacoes.qntd_vendida * informacoes.v_d_venda;
                    printf("%s) Lucro: %0.2f\n", informacoes.nome, valor_total);
                    break;
                }
            }
        }
    }

    fclose(arqIn);
    fclose(chave_bin);

}

void calcula_valor_estoque(Info informacoes, Ch_primaria key){
    float valor_total_est=0;
    float valor_cada_est;

    arqIn = fopen("sistema_venda.txt", "r+b"); 
	if (arqIn == NULL) { 
		printf("Nao foi possivel abrir o arquivo!");
		return 0;
	}

    chave_bin = fopen("chave_bin.txt", "r+b");
	if (chave_bin == NULL) { 
		printf("Nao foi possivel abrir o arquivo!");
		return 0;
	}

    while(fread(&key, sizeof(key), 1, chave_bin) > 0){
        if(key.ativo == 1){
            while(fread(&informacoes, sizeof(informacoes), 1, arqIn) > 0){
                if(strstr(key.nome, informacoes.nome) != NULL){
                    valor_cada_est = 0;
                    valor_cada_est = informacoes.qntd_estoque * informacoes.v_d_venda;
                    valor_total_est = valor_total_est + valor_cada_est;
                    printf("\n%s) Quantidade em estoque: %d, Valor total desse estoque: %0.2f\n", informacoes.nome, informacoes.qntd_estoque, valor_cada_est);
                    break;
                }
            }
        }
    }

    printf("Valor total do estoque: %0.2f\n", valor_total_est);

    fclose(arqIn);
    fclose(chave_bin);
}

void repor_estoque(Info informacoes, Ch_primaria key){
    char nome[50];
    int qntd_repor=0;
    int cont=0;

    chave_bin = fopen("chave_bin.txt", "r+b");
	if (chave_bin == NULL) { 
		printf("Nao foi possivel abrir o arquivo!");
		return 0;
	}

    printf("\nLISTA DE PRODUTOS EXISTENTE PARA REPOR ESTOQUE\n"); //listando nomes chave dos produtos existentes
    while(fread(&key, sizeof(key), 1, chave_bin) > 0){
        if(key.ativo == 1){
            printf("produto: %s\n", key.nome);
        }
    }

    printf("Digite o NOME do produto que deseja alterar o estoque: ");
    scanf("%s", nome);
    printf("QUANTIDADE a repor: ");
    do{
        scanf("%d", &qntd_repor);
        if(qntd_repor <= 0){
            printf("Quantidade invalida...\nDigite novamente: ");
        }
    }while(qntd_repor <= 0);
    
    arqIn = fopen("sistema_venda.txt", "r+b"); 
	if (arqIn == NULL) {
		printf("Nao foi possivel abrir o arquivo!");
		return 0;
	}

    while(fread(&informacoes, sizeof(informacoes), 1, arqIn) > 0){
        if(strstr(informacoes.nome, nome) != NULL){
            arqOut = fopen("sistema_venda.txt", "rb+"); //reabrir arq inicial para vizualizar e dps alterar
            if (arqOut == NULL){ 
                printf("Nao foi possivel abrir o arquivo!");
                return 0;
            }

            while(fread(&informacoes, sizeof(informacoes), 1, arqOut) > 0){
                if(strstr(informacoes.nome, nome) != NULL){
                    qntd_repor = informacoes.qntd_estoque + qntd_repor;
                    informacoes.qntd_estoque = qntd_repor;
                    printf("Novo estoque de %s: %d", informacoes.nome, informacoes.qntd_estoque);
                    fseek(arqOut, cont * sizeof(informacoes), SEEK_SET);
                    fwrite(&informacoes, sizeof(informacoes), 1, arqOut);
                    break;
                }
                cont++;
            }
        }
    }

    fclose(chave_bin);
    fclose(arqIn);
    fclose(arqOut);
}