#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void InterpoladorLagrange();

int main(){
    
    InterpoladorLagrange();
    
    return 0;
}

void InterpoladorLagrange(){
    int vet1_pts[3];
    vet1_pts[0] = -1;
    vet1_pts[1] = 0;
    vet1_pts[2] = 3;
    int vet1_fx[3];
    vet1_fx[0] = 15;
    vet1_fx[1] = 8;
    vet1_fx[2] = -1;
    printf("\n\nTabela 1)\n");
    printf("   X | ");
    for(int i = 0; i < 3; i++){
        printf("%d |", vet1_pts[i]);
    }
    printf("\n");
    printf("f(X) | ");
    for(int i = 0; i < 3; i++){
        printf("%d |", vet1_fx[i]);
    }
    printf("\n");
    
    int op;
    printf("Digite a tabela desejada : ");
    scanf("%d", &op);

    switch(op){
        int A=0, a0, a1, a2, B=0, b0=0, b1=0, b2=0, C=0, c1=0, c2=0, c0=0, deno0=0, deno1=0, deno2=0, mmc;
        int op=0, fx=0, result=0;

        case 1:
            a0 = 1;
            b0 = (-(vet1_pts[1]))+(-(vet1_pts[2]));
            c0 = (-(vet1_pts[1]))*(-(vet1_pts[2]));
            deno0 = ((vet1_pts[0])-(vet1_pts[1]))*((vet1_pts[0])-(vet1_pts[2]));
            printf("%d %d %d %d\n",a0, b0, c0, deno0);
            if(deno0 < 0){
                deno0 = fabs(deno0);
                a0 = -(a0);
                b1 = -(b0);
                c1 = -(c0);
            }

            a1 = 1;
            b1 = (-(vet1_pts[0]))+(-(vet1_pts[2]));
            c1 = (-(vet1_pts[0]))*(-(vet1_pts[2]));
            deno1 = ((vet1_pts[1])-(vet1_pts[0]))*((vet1_pts[1])-(vet1_pts[2]));
            printf("%d %d %d %d\n",a1, b1, c1, deno1);
            if(deno1 < 0){
                deno1 = fabs(deno1);
                a1 = -(a1);
                b1 = -(b1);
                c1 = -(c1);
            }

            a2 = 1;
            b2 = (-(vet1_pts[0]))+((vet1_pts[1]));
            c2 = (-(vet1_pts[0]))*(-(vet1_pts[1]));
            deno2 = ((vet1_pts[2])-(vet1_pts[0]))*((vet1_pts[2])-(vet1_pts[1]));
            printf("%d %d %d %d\n",a2, b2, c2, deno2);
            if(deno2 < 0){
                deno2 = fabs(deno2);
                a2 = -(a2);
                b2 = -(b2);
                c2 = -(c2);
            }

            a0 = vet1_fx[0]*(a0);
            b0 = vet1_fx[0]*(b0);
            c0 = vet1_fx[0]*c0;

            a1 = vet1_fx[1]*(a1);
            b1 = vet1_fx[1]*(b1);
            c1 = vet1_fx[1]*(c1);

            a2 = vet1_fx[2]*(a2);
            b2 = vet1_fx[2]*(b2);
            c2 = vet1_fx[2]*(c2);
        
            //reorganizando os valores do numerador com o denominador comum
            mmc = 12; 
            a0 = ((mmc/deno0)*(a0));
            b0 = ((mmc/deno0)*(b0));
            c0 = ((mmc/deno0)*(c0));
            
            a1 = ((mmc/deno1)*(a1));
            b1 = ((mmc/deno1)*(b1));
            c1 = ((mmc/deno1)*(c1));

            a2 = ((mmc/deno2)*(a2));
            b2 = ((mmc/deno2)*(b2));
            c2 = ((mmc/deno2)*(c2));

            A = a0 + a1 + a2;
            //printf("A: %d\n", A);
            B = b0 + b1 + b2;
            //printf("B: %d\n", B);
            C = c0 + c1 + c2;
            //printf("C: %d", C);

            A = A/mmc;
            B = B/mmc;
            C = C/mmc;
            //printf("%d %d %d", A, B, C);
            printf("\nO polinominio interpolar de Lagrande eh: (%dX)^2 + (%dX) + (%d)!!\n", A, B, C);
            printf("Deseja calcular algum X de funcao nesse polinomio?\nDigite 1 para sim, Digite 2 para nao: ");
            scanf("%d", &op);
            if(op == 2){
                return 0;
            }else{
                printf("\nDigite o valor de X da funcao que deseja saber: ");
                scanf("%d", &fx);

                A = A*(fx);
                A = pow(A, 2);
                B = B*(fx);

                result = A + B + C;

                printf("\nO resultado de f(%d) eh %d!!", fx, result);
                return 0;
            }

        break;

    }

}

