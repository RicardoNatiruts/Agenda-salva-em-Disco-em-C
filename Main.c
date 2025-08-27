#define TAM_MAX 100

#include<stdio.h>
#include<string.h>

typedef struct{
    int ID;
    char nome[128];
    char numero[16];
}Ctt;

void CarregarCSV(char *nome, Ctt *dados, int *cont, int *num){

    FILE *arquivo = fopen(nome, "r");//leitura

    if (arquivo == NULL){
        return;
    }

    char buffet[256];
    fgets(buffet, 256, arquivo);

    while (fscanf(arquivo, "%d\t%127s\t%15s\n", &dados[*cont].ID, dados[*cont].nome, dados[*cont].numero) == 3){

        if (dados[*cont].ID>*num){
            *num = dados[*cont].ID;
        }
        (*cont)++;
    }
    fclose(arquivo);
    printf("Agenda Carregada\n");
}



void Inserir(Ctt *dados, int *Num, int *cont){
    puts("\nAdicionar novo contato");
    (*Num)++;
    dados[*cont].ID = *Num;
    puts("Digite o nome: ");
    scanf("%s", dados[*cont].nome);
    puts("Digite seu telefone: ");
    scanf("%s", dados[*cont].numero);
    printf("Contato registardo\n");
    (*cont)++;
}

int InserirCSV(Ctt *dados, int cont, char *nome){
    FILE *arquivo = fopen(nome, "w");

    if (arquivo==NULL){
        printf("Erro ao abrir arquivo\n");
        return -1;
    }
    fprintf(arquivo, "ID / Nome / Número\n");

    for (int i = 0; i < cont; i++){
        fprintf(arquivo, "%d \t %s \t %s\n", dados[i].ID, dados[i].nome, dados[i].numero);
    }
    fclose(arquivo);

    return 0;
}

int Apagar(Ctt *dados, int *cont, char *nome){
    int oper, ind = -1;

    puts("Apagar contato\n");
    puts("Digite o ID da pessoa que deseja apagar: \n");
    scanf("%d", &oper);
    for (int i = 0; i < *cont; i++){
        if (oper == dados[i].ID){
            ind = i;
            break;
        }
    }
    if (ind == -1){
        return 1;
    }

    for (int i = ind; i < (*cont-1); i++){
        dados[i] = dados[i+1];
    }

    (*cont)--;

    return InserirCSV(dados, *cont, nome);
}

void Buscar(Ctt dados[], int cont){
    int oper;
    char chama[128], number[16];

    puts("Buscar contato\n");
    puts("\n<1>Nome\t <2>Número\n");
    scanf("%d", &oper);
    switch (oper){
    case 1:
        puts("Digite o nome da pessoa: ");
        scanf("%s", chama);

        for (int i = 0; i < cont; i++){
            if (strstr(dados[i].nome, chama)!=NULL){
                printf("Contato encontrado: \n");
                printf("%s, telefone %s, ID: %d\n", dados[i].nome, dados[i].numero, dados[i].ID);
                return;
            }
        }
        break;


    case 2:
        puts("Digite o número da pessoa: ");
        scanf("%s", number);

        for (int i = 0; i < cont; i++){
            if (strstr(dados[i].numero, number)!=NULL){
                printf("Contato encontrado: \n");
                printf("%s, telefone %s, ID: %d\n", dados[i].nome, dados[i].numero, dados[i].ID);
                return;
            }
        }
        break;
        
    default:
        break;
    }
}

void Mostrar(Ctt dados[], int cont){
    for (int i = 0; i < cont; i++){
        printf("Nome: %s\nID: %d\nTelefone: %s\n", dados[i].nome, dados[i].ID, dados[i].numero);
    }
}

int main(){
    int oper, cont=0, num=0, resultado=0;
    Ctt dados[TAM_MAX];

    CarregarCSV("dados.csv", dados, &cont, &num);

    do{
        printf("Agenda de Contatos:\n");
        printf("Escreva a função desejada:\n");
        printf("<1> Adicionar Contato\t<2> Apagar Contato\t<3> Buscar\t<4> Lista\t<5> Sair\n");
        scanf("%d", &oper);
        if (oper<1 || oper>5){
            printf("Número sem função");
            return 0;
        }
        else{
            switch (oper){
            case 1:
                
                printf("Adicionar Contato\n");
                Inserir(dados, &num, &cont);
                resultado = InserirCSV(dados, cont, "dados.csv");
                if (resultado == 0){
                    printf("Arquivo 'dados.csv' foi gravado com sucesso!\n");
                } 
                else {
                    printf("Ocorreu um erro ao gravar o arquivo.\n");
                }
                break;

            case 2:
                printf("Apagar Contato\n");
                resultado = Apagar(dados, &cont, "dados.csv");
                if (resultado == 0){
                    printf("Contato apagado com sucesso!\n");
                } 
                else if (resultado == 1){
                    printf("ID não encontrado\n");
                }
                else{
                    printf("Ocorreu um erro ao gravar o arquivo.\n");
                }
                break;
            
            case 3:
                printf("Buscar Contato\n");
                Buscar(dados, cont);
                break;

            case 4:
                printf("Listar Contatos\n");
                Mostrar(dados, cont);

            default:
                break;
            }
        }
        
    } while (oper!=5);
    
}