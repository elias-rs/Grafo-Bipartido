#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <queue>
#define MAX 100

void verifica_bipartido(int matriz[MAX][MAX], int vertices, int cor[MAX]){ 
	int grupo1[MAX], grupo2[MAX], contador1 = 0, contador2 = 0, bipartido = 1; 
	std :: queue <int> fila; 
	for(int i = 0; i < vertices; i++){ 
		if(cor[i] == -1){ 
			cor[i] = 0; 
			grupo1[contador1++] = i; 
            fila.push(i); 
            while (!fila.empty()) {
                int x = fila.front(); 
                fila.pop(); 
                for (int y = 0; y < vertices; y++) { 
                    if (matriz[x][y] == true && cor[y] == -1) { 
                        cor[y] = (1 - cor[x]); 
						if (cor[y] == 0) {
                            grupo1[contador1++] = y;
                        } else {
                            grupo2[contador2++] = y;
                        }
                        fila.push(y); 
                    } else {
						if (matriz[x][y] == true && cor[y] == cor[x]) { 
							bipartido = 0;
							break;
						}
					}
                }
            }
		}
	}
	for(int i = 0; i < vertices; i++){ 
		grupo1[i]++;
		grupo2[i]++;
	}
	if (bipartido == 1) {
        printf("\nGrafo Bipartido: SIM\n\n");
        printf("Grupo 1: ");
        for (int i = 0; i < contador1; i++) {
            printf("%d ", grupo1[i]);
        }
        printf("\n\n");
        printf("Grupo 2: ");
        for (int i = 0; i < contador2; i++) {
            printf("%d ", grupo2[i]);
        }
        printf("\n\n");
    } else {
        printf("\nGrafo Bipartido: NAO\n\n");
    }
}

int main (){
	char nome_arquivo[50], aux[MAX];
	int opcao, matriz_arq[MAX][MAX], cor[MAX];
	opcao = 1;
	while(opcao != 0){ 
		int tamanho = 0;
		printf("====================== BIPARTIDO ======================");
		printf("\n[1] - Continuar\n[0] - Sair\nEscolha uma opcao: ");
		scanf("%d", &opcao);
		if(opcao == 1){
			system("cls");
			fflush(stdin);
			printf("Informe o nome do arquivo: ");
			gets(nome_arquivo);
			FILE *arquivo; 
			strcat(nome_arquivo,".txt"); 
			if((arquivo = fopen(nome_arquivo,"r")) != NULL){
				while(fgets(aux, MAX, arquivo)){  
					char *elemento;
					elemento = strtok(aux, " "); 
					while (elemento != NULL){
						elemento = strtok(NULL, " "); 
					}
					tamanho++; 
				}
				fclose(arquivo);
				if((arquivo = fopen(nome_arquivo,"r")) != NULL){
					printf("\n");
					for(int i = 0; i < tamanho; i++){
						for(int j = 0; j < tamanho; j++){
							fscanf(arquivo, "%d", &matriz_arq[i][j]);
							printf("%d ", matriz_arq[i][j]); 
						}
						printf("\n");
					}
				}
				fclose(arquivo);
				for (int i = 0; i < tamanho; i++){
					cor[i] = -1; 
				}
				verifica_bipartido(matriz_arq, tamanho, cor); // O(N^3)
			}else{
				printf("\nErro ao abrir o arquivo/Erro ao localizar o arquivo\n\n");
				system("pause");
				system("cls");
			}
		}else{
			if(opcao != 0 && opcao != 1){
				printf("\n\nOpcao invalida!\n\n");
				system("pause");
			}
		}
	}
	return 0;
}