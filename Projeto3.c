#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LARGURA 320
#define ALTURA 240
#define CANAIS 3
#define MAX 4800000 //primeiro video 4800000, segundo video 1800000

FILE *frame_inicial;
FILE *frame_atual;

int compara(int frame);

int main(){
	int frame, diferenca=0;
	
	printf("Quantidade de frames a serem analisadas: ");
	scanf("%d", &frame);
	
	for(int i = 2; i <= frame; i++){	
		diferenca = compara(i);
		if(diferenca > MAX){
			printf("Detectamos movimento no frame: %d\n", i);
		}
	}
	
	return 0;
}

int compara(int frame){
	char proximo[10];
	char mat_1[320][240][3], mat_2[320][240][3];
	
	sprintf(proximo, "%03d.rgb", frame); 
	
	frame_inicial = fopen("001.rgb","rb");
		if(frame_inicial == NULL){
			printf("Nao foi possivel abrir o arquivo...\n");
			return 1;
		}

	frame_atual = fopen(proximo, "rb");
		if(frame_atual == NULL){
			printf("Nao foi possivel abrir o arquivo...\n");
			return 1;
		}
	
	for(int i = 0; i < LARGURA; i++){
		for(int j = 0; j < ALTURA; j++){
			for(int k = 0; k < CANAIS; k++){
				fread(&mat_1[i][j][k], sizeof(char), 1, frame_inicial);
				fread(&mat_2[i][j][k], sizeof(char), 1, frame_atual);
			}
		}
	}
	
	int diferenca=0, count=0;
	for(int i = 0; i < LARGURA; i++){
		for(int j = 0; j < ALTURA; j++){
			for(int k = 0; k < CANAIS; k++){
				diferenca = abs(mat_1[i][j][k] - mat_2[i][j][k]); //abs para calcular o MÓDULO.
				count = count + diferenca;
			}
		}
	}
	
	fclose(frame_inicial);
	fclose(frame_atual);
	
	return count;
}


