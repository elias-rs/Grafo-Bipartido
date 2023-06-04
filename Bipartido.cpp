#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <queue>
#define MAX 100

void verifica_bipartido(int matriz[MAX][MAX], int vertices, int cor[MAX]){ // peso O(N^3 + N). Logo O(N^3)
	int grupo1[MAX], grupo2[MAX], contador1 = 0, contador2 = 0, bipartido = 1; //variáveis que vão separar cada vértice em determinado grupo
	std :: queue <int> fila; // função fila da biblioteca <queue> do C++
	for(int i = 0; i < vertices; i++){ // O(N)
		if(cor[i] == -1){ // no main todo o vetor cor tem elementos com valor -1
			cor[i] = 0; // vetor cor passando por i recebe 0 para não influenciar na chamada do mesmo vetor, porém com outros índices
			grupo1[contador1++] = i; //as variáveis contador1 e 2 são auxiliares no preenchimento dos vetores
            fila.push(i); // insere elemento na fila usando contador i
            while (!fila.empty()) { // O(N)
			// O laço só termina a execução quando a fila estiver vazia
                int x = fila.front(); // x recebe o primeiro da fila
                fila.pop(); // depois que x recebeu o valor ele é retirado da fila
                for (int y = 0; y < vertices; y++) { // O(N)
                    if (matriz[x][y] == true && cor[y] == -1) { // verificação se há uma matriz e que seus vértices tem cor -1
                        cor[y] = (1 - cor[x]); // alternagem das cores entre y e x, lembrando que x recebe elemento da fila, enquanto y é crescente
						if (cor[y] == 0) {
                            grupo1[contador1++] = y;
                        } else {
                            grupo2[contador2++] = y;
                        }
                        fila.push(y); // insere elemento na fila usando contador y
                    } else {
						if (matriz[x][y] == true && cor[y] == cor[x]) { // se as cores forem identicas logo os vértices tocam com vários outros vértices, impossibilitando a criação dos dois grupos
							bipartido = 0;
							break;
						}
					}
                }
            }
		}
	}
	for(int i = 0; i < vertices; i++){ // laço apenas para que os vértices sejam incrementados por 1, pois não existe vértice que começa com 0
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
	//Entrada do usuario para continuar ou sair
	while(opcao != 0){ // O (N * (N + N^2 + N^2 + N^3)). Logo O(N^4)
		inicio:
		int tamanho = 0;
		printf("====================== BIPARTIDO ======================");
		printf("\n[1] - Continuar\n[0] - Sair\nEscolha uma opcao: ");
		scanf("%d", &opcao);
		if(opcao == 1){
			system("cls");
			fflush(stdin);
			printf("Informe o nome do arquivo: ");
			gets(nome_arquivo);
			FILE *arquivo; // ponteiro do tipo FILE/arquivo
			strcat(nome_arquivo,".txt"); // concatenação da string + a extensão ".txt"
			if((arquivo = fopen(nome_arquivo,"r")) != NULL){
				// laço para deteminar a quantidade de vértices existem no arquivo e finaliza ao encontrar o EOF
				while(fgets(aux, MAX, arquivo)){ // fgets(string, tamanho, forma de entrada) = String recebe o arquivo de texto 
					char *elemento; // ponteiro de String
					elemento = strtok(aux, " "); // separação dos elementos da String quando encontra um espaço " "
					while (elemento != NULL){
						elemento = strtok(NULL, " "); // durante o laço o strtok vai fazer passagem por todos os elementos separados por espaço " " usando NULL, pois sem NULL o ponteiro sempre apontará para o primeiro elemento
					}
					tamanho++; // variável que tem a quantidade exata de vértices
				}
				fclose(arquivo);
				if((arquivo = fopen(nome_arquivo,"r")) != NULL){
					printf("\n");
					for(int i = 0; i < tamanho; i++){// Esses 2 for tem peso O(N^2)
						for(int j = 0; j < tamanho; j++){
							fscanf(arquivo, "%d", &matriz_arq[i][j]);// leitura do arquivo com a gravacao da matriz para a variavel matriz_arq
							printf("%d ", matriz_arq[i][j]); // impressão na tela a matriz que veio do arquivo
						}
						printf("\n");
					}
				}
				fclose(arquivo);
				for (int i = 0; i < tamanho; i++){ // O(N)
					cor[i] = -1; // definindo o valor do vetor inteiro para -1 (nota: o vetor tem a quantidade de vértices lida pelo arquivo)
				}
				// função que verifica se o grafo é bipartido
				verifica_bipartido(matriz_arq, tamanho, cor); // O(N^3)
			}else{
				printf("\nErro ao abrir o arquivo/Erro ao localizar o arquivo\n\n");
				system("pause");
				system("cls");
				goto inicio;
			}
		}else{
			if(opcao != 0 && opcao != 1){
				printf("\n\nOpcao invalida!\n\n");
				system("pause");
				goto inicio;
			}
		}
	}
	return 0;
}