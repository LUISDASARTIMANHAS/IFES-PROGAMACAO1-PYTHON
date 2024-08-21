// ============================= BASE ======================
#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Defina constantes para as sequências de escape ANSI das cores

// RED ERROR
#define RED "\x1b[31m"
// BLUE SISTEMA
#define BLUE "\x1b[34m"
// GREEN OK 
#define GREEN "\x1b[32m"
// YELLOW PERGUNTAS
#define YELLOW "\x1b[33m"
// RESET REDEFINIR
#define RESET "\x1b[0m"
#define SEPARETOR BLUE "\n================================================\n"  RESET

typedef char string[101];

struct ClassDatabase {
    int codigo;
    char nome[101];
    float preco;
    int qtde;
}; typedef struct ClassDatabase Database;

typedef struct ClassDatabaseTipoAtor {
    string nome;
    ClassDatabaseTipoAtor *prox;
}TAtor;

typedef struct ClassDatabaseTipoElenco {
    TAtor *ator;
    ClassDatabaseTipoElenco *prox;
}TElenco;

typedef struct ClassDatabaseTipoFilme {
    string titulo;
    int anoProducao;
    ClassDatabaseTipoFilme *ante,*prox;
    TElenco *elenco;
}TFilme;

typedef struct ClassDatabaseFilme {
    TFilme *inicioF;
    TFilme *fimF;
    TAtor *inicioA;
    TAtor *fimA;
}TLista;

FILE * abrirArquivo(char * nomeArq, char * modo) {
    // ABRIR o arquivo
    FILE * arq;
    arq = fopen( nomeArq, modo );
    if ( arq == NULL) {
        printf(RED "ERRO ao abrir o arquivo." RESET);
        exit(-1);
    }
    return arq;
}

void abrirArquivoLogs() {
    // ABRIR o arquivo
    int cont = 0;
    FILE * arq;
    arq = fopen( "../data/logs.txt", "a+");
    while ((arq == NULL) && cont < 3){
        printf(RED "ERRO ao abrir o arquivo." RESET);
        arq = fopen( "../data/logs.txt", "a+");
    }
}
void carregarArquivo(FILE * arquivo, Database * vetProd, int *qtde) {
    fread( qtde, sizeof(int), 1, arquivo  );
    fread( vetProd, sizeof(Database), *qtde, arquivo  );
}
void gravarArquivo(FILE * arquivo, Database * vetProd, int qtde) {
    fwrite( &qtde, sizeof(int), 1, arquivo  );
    fwrite( vetProd, sizeof(Database), qtde, arquivo  );
}

void correct(){
    SetConsoleOutputCP(65001);
}

// ============================= FIM DO BASE ======================

void head(){
    correct();
    FILE * logs;
    logs = abrirArquivo("../data/logs.txt","a+");
    printf(SEPARETOR);
    printf(BLUE"\n\t LUIS_DAS_ARTIMANHAS & PINGOBRAS S.A");
    printf("\n\t Iniciando o programa....." RESET);
    printf(SEPARETOR);
    // save in logs
    fprintf(logs,SEPARETOR);
    fprintf(logs,"\n\t LUIS_DAS_ARTIMANHAS & PINGOBRAS S.A");
    fprintf(logs,"\n\t Iniciando programa.....");
    fprintf(logs,SEPARETOR);
    fclose(logs);
}

void copy(){
    FILE * logs;
    logs = abrirArquivo("../data/logs.txt","a+");
    correct();
    printf(SEPARETOR);
    printf(BLUE "\n\t DEVS:");
    printf("\n\t LUIS_DAS_ARTIMANHAS.");
    printf("\n\t PINGOBRAS S.A" RESET);
    printf(SEPARETOR);
    // save in logs
    fprintf(logs,"\n----------------------------------------------------");
    fprintf(logs,"\n\t DEVS:");
    fprintf(logs,"\n\t LUIS_DAS_ARTIMANHAS.");
    fprintf(logs,"\n\t PINGOBRAS S.A");
    fprintf(logs,"\n----------------------------------------------------\n");
    fclose(logs);
}

// inputs personalizados e modificados
float input(){
    float value;
    fflush(stdin);
    scanf("%f", &value);
    return value;
}
void inputS(char destino[]){
    fflush(stdin);
    scanf(" %100[^\n]s", destino);
}


// validadores
void validNome(char destino[]){
    do{
        printf(YELLOW "\nInsira o nome do Produto: " RESET);
        inputS(destino);
    }while (strlen(destino) < 3);
}

int validCod(){
    int cod;
    do{
        printf(YELLOW "\nInsira o código do Produto: " RESET);
        cod = input();
    }while (cod < 1);
    return cod;
}

float validTaxa(){
    float porcent;
    printf(YELLOW "\nInsira a porcentagem de aumento ou desconto: " RESET);
    int tax = input();

    while((tax <= 0 ) || (tax > 100)){
        printf(RED "\nA taxa não pode ser menor do que 0 ou maior que 100!\n" RESET);
        printf(YELLOW "\nInsira a porcentagem de aumento ou desconto: " RESET);
        tax = input();
    }
    porcent = (tax/100);
    return porcent;
}

int validQuantidade(){
    int qtd;
    do{
        printf(YELLOW "\nInsira a quantidade do Produto: " RESET);
        qtd = input();
    }while (qtd < 0);
    return qtd;
}

int validDia(){
    int dia;
    do{
        printf(YELLOW "\nInsira o dia de validade: " RESET);
        dia = input();
    }while ((dia < 1) || (dia > 31));
    return dia;
}

int validMes(){
    int mes;
    do{
        printf(YELLOW "\nInsira o mês de validade: " RESET);
        mes = input();
    }while ((mes < 1)||(mes > 12));
    return mes;
}

int validAno(){
    int ano;
    do{
        printf(YELLOW "\nInsira o Ano de validade: " RESET);
        ano = input();
    }while ((ano < 1900)||(ano > 3050));
    return ano;
}
int validNum(){
    printf("Insira um numero: ");
    int num = input();

    while(num < 0){
        printf("Salario invalido.");
        printf("Insira Seu salario: ");
        num = input();
    }
    return num;
}
int validNota(){
    float nota;
    do{
        printf("Insira uma Nota: ");
        nota = input();
    }while ((nota < 0) || ( nota > 10));
    return nota;
}
int validMatricula(){
    float matricula;
    do{
        printf("Insira sua matricula: ");
        matricula = input();
    }while (matricula < 0);
    return matricula;
}
float validPreco(){
    float prise;
    do{
        printf(YELLOW "\nInsira o preço do Produto: " RESET);
        prise = input();
    }while (prise < 0);
    return prise;
}
int validIdade(){
    printf("Insira sua idade: ");
    int idade = input();
    while((idade <= 0) || (idade >= 50)){
        printf("Idade invalida.");
        printf("Insira sua idade: ");
        idade = input();
        
    }
    return idade;
}
int validSalario(){
    printf("Insira seu salario: ");
    int salario = input();
    
    while(salario < 0){
        printf("Salario invalido.");
        printf("Insira Seu salario: ");
        salario = input();
    }
    return salario;
}
int validAltura(){
    float alt;
    do{
        printf("Insira a altura: ");
        alt = input();
    }while (alt < 0);
    return alt;
}
int validBase(){
    float base;
    do{
        printf("Insira a base: ");
        base = input();
    }while (base < 0);
    return base;
}
int validRaio(){
    float raio;
    do{
        printf("Insira o raio: ");
        raio = input();
    }while (raio < 0);
    return (raio*raio);
}

int validQTD(){
    float qtd;
    do{
        printf("Insira a quantidade de produto: ");
        qtd = input();
    }while (qtd < 0);
    return qtd;
}
void imprimirArray(int *array, int qtde){
    int i;

    for (i = 0; i < qtde; i++){
        printf("%d  ",array[i]);
    }
}
int fatorial(){
    int i,num, fat;
    printf("Informe o número: ");
    scanf("%d", &num);
    fat = 1;
    for(i=num; i > 1 ; i--) {
        fat = fat * i;
    }
    return fat;
}
int lerOpcaoCalc() {
    int op;
    printf("\n\nCALCULAR A ÁREA:\n");
    printf("1-Retângulo\n");
    printf("2-Círculo\n");
    printf("0-Sair\n");
    printf("Informe sua opção: ");
    scanf("%d", &op);
    // VALIDAR a opção entre 0, 1 e 2
    return op;
}

int somar(int num1, int num2){
    int total = num1 + num2;
    printf("\nSomando os numeros: %d + %d\n", num1,num2);
    return total;
}
int diminuir(int num1, int num2){
    int total = num1 - num2;
    printf("\n Subtraindo os numeros: %d - %d\n", num1,num2);
    return total;
}
float calcMedia3(float n1,float n2,float n3){
    float media = (n1 + n2 + n3 )/3;
    return media;
}
int menuPay(){
    printf("\n=======SELECIONAR FORMA DE PAGAMENTO=======\n");
    printf("1-A vista\n");
    printf("2-A prazo\n");
    printf("=====================\n");
    printf("Forma: ");
    int opc = input();

    return opc;
}

int calcArRetangulo(){
    float base = validBase();
    float altura = validAltura();
    float area = base * altura;
    return area;
}
int calcArCirculo(){
    float raio = validRaio();
    float area = M_PI * raio;
    return area;
}

// void saveArray(int *i,int *array,int data){
//     char continuar;
//     do{
//         array[*i] = data;
//         (*i)++;
//         printf("\nDeseja continuar? ");
//         scanf(" %c",&continuar);
//         continuar = toupper(continuar);
//     } while(continuar == "S");
// }

void removerArray(int *qtde, int *array, int pos){
    int i;
    for (i = pos; i < (*qtde)-1; i++){
        array[i] = array[i+1];
    }
    (*qtde)--;
}

void alocarMEM(int **database,int *maxSpace){
    printf("Entre com a quantidade de números: ");
    int quant_numeros = input();
    *database = (int *) malloc (quant_numeros * sizeof (int) );
    *maxSpace = quant_numeros;
}

void reAlocarMEM(int **database, int *maxSpace){
    printf("\nVoce tem alocado: %d \n",*maxSpace);
    printf("Entre com a quantidade a mais de elementos: ");
    int qtdeNova = input();
    *maxSpace = (qtdeNova+(*maxSpace));
    int tam = (*maxSpace) * sizeof (int);

    *database = (int *) realloc (*database , tam );
}

// funções do trabalho

struct Date{
    int dia;
    int mes;
    int ano;
};typedef struct Date Data;
struct ClassProduto{
    int cod;
    char nome[101];
    float prise;
    int quantidade;
    Data validade;
};typedef struct ClassProduto Produto;

int menu() {
    correct();
	int op;
	// system("@cls||clear");  // LIMPA A TELA
	printf(BLUE "\n\nSISTEMA DE ESTOQUE\n\n" RESET);
	printf(GREEN "1 - Inserir\n");
	printf("2 - Pesquisar por número\n");
	printf("3 - Pesquisar por nome\n");
	printf("4 - Atualizar\n");
	printf("5 - Maior\n" RESET);
	printf(RED "6 - Excluir\n" RESET);
	printf(GREEN "7 - Listar\n"  RESET);
	printf(RED "0 - Sair\n" RESET);
	do {
		printf(YELLOW "Escolha sua opção: " RESET);
		scanf(" %d", &op);
	} while(op < 0 || op > 7);
	return op;
}


void insereAtor(TLista *DB, string nome){
    TAtor *novo = (TAtor *)malloc(sizeof(TAtor));
    TAtor *atual = DB->inicioA;
    TAtor *anterior = NULL;
    int inseriu = 0;
    

    novo->prox = NULL;
    strcpy(novo->nome,nome);
    printf("\nINSERINDO ATOR: %s...",nome);

    if(DB->inicioA == NULL){
        DB->inicioA = novo;
        DB->fimA = novo;
    }else{
        while(atual != NULL){
            if (strcmp(atual->nome,novo->nome) > 0)	{
                inseriu = 1;
                if(atual == DB->inicioA)	{
                    novo->prox = atual;
                    DB->inicioA = novo;	
                } else {
                    novo->prox = anterior->prox;
                    anterior->prox = novo;
                }
                break;
            }
            anterior = atual;
            atual = atual->prox;
        }
        
        if(!inseriu){
            DB->fimA->prox = novo;
            DB->fimA = novo;
        }
    }
}

void insereFilme(TLista *DB, string titulo, int ano){
    TFilme *novo = (TFilme *)malloc(sizeof(TFilme));
    TFilme *atual = DB->inicioF;
    TFilme *anterior = NULL;
    int inseriu = 0;

    novo->ante = NULL;
    novo->prox = NULL;
    novo->elenco = NULL;
    novo->anoProducao = ano;
    strcpy(novo->titulo,titulo);
    printf("\nINSERINDO FILME: %s...",titulo);

    if(DB->inicioF == NULL){
        DB->inicioF = novo;
        DB->fimF = novo;
    }else{
        inseriu = 0;
        anterior = atual->ante;
        while(atual != NULL){
            if (strcmp(atual->titulo,novo->titulo) > 0)	{
                inseriu = 1;
                novo->prox = atual;
                atual->ante = novo;

                if(anterior == NULL){
                    DB->inicioF = novo;	
                } else {
                    anterior->prox = novo;
                    novo->ante = anterior;
                }
                break;
            }
            atual = atual->prox;
        }
        
        if(!inseriu){
            DB->fimF->prox = novo;
            novo->ante = DB->fimF;
            DB->fimF = novo;
        }
    }
}

void cadastraAtor(TLista *DB){
    string nome;

    printf("\n\n\t=====| INSERE ATOR|=====\n\n");
    printf("\tInforme o nome do ator: ");
    fflush(stdin);
    inputS(nome);

    insereAtor(DB, nome);
}

void cadastraFilme(TLista *DB){
    string titulo;
    int ano;


    printf("\n\n\t=====| CADASTRO DE FILMES |=====\n\n");
    printf(YELLOW"\tTITULO: ");
    fflush(stdin);
    inputS(titulo);

    printf("\n\n\tANO DE PRODUÇÃO: "RESET);
    fflush(stdin);
    ano = input();

    insereFilme(DB, titulo, ano);
}

void exibeAtores(TLista *DB){
	TAtor *atual = DB->inicioA;
	int cont = 0;
	
	printf("\n\n");
	printf("+----------------------------------------------------+\n");
	while (atual != NULL)	{
		printf("\t(%d) - %s.\n", ++cont, atual->nome);
		atual = atual->prox;
	}//while
	printf("+----------------------------------------------------+\n\n\n");
}

void exibeFilmes(TLista *DB){
	TFilme *atual = DB->inicioF;
    TElenco *cursor;
    TAtor *ator;
	int cont = 0;
	
	printf("\n\n");
	printf(BLUE"+----------------------------------------------------+\n");
	while (atual != NULL)	{
		printf("\t(%d) - %s [%d].\n", ++cont, atual->titulo, atual->anoProducao);
        if (atual->elenco !=NULL){
            printf("\n");
            cursor = atual->elenco;
            while (cursor != NULL){

                printf("\t\t%s\n",cursor->ator->nome);
                cursor = cursor->prox;
            }
            
        }
        
		atual = atual->prox;
	}//while
	printf("+----------------------------------------------------+\n\n\n"RESET);
}

TFilme *localizaFilme(TLista *DB, string titulo){
	TFilme *atual = DB->inicioF;
	
	while (atual != NULL){
		if(strcmp(atual->titulo, titulo) == 0){
			break;
		}//if
		atual = atual->prox;
	}//while
	return atual;
}

TAtor *localizaAtor(TLista *DB, string nome){
	TAtor *atual = DB->inicioA;
	
	while(atual != NULL)	{
		if(strcmp(atual->nome, nome) == 0) {
			break;
		}//if
		atual = atual->prox;
	}//while
	return atual;
}

void relacionarFilmeAtor(TFilme *filme, TAtor *a){
	TElenco *novo = (TElenco *)malloc(sizeof(TElenco));
	
	novo->prox = NULL;
	novo->ator = a;
	
	if(filme->elenco != NULL){
	   TElenco *atual = filme->elenco;
	   while(atual->prox != NULL){
			atual = atual->prox;
       }//while
	   atual->prox = novo;		
	} else {
	   filme->elenco = novo;
	}//if
}

void criaElenco(TLista *DB, string titulo, string nomeAtor){
	TFilme *f = localizaFilme(DB,titulo);
	if(f != NULL){
		TAtor *a = localizaAtor(DB, nomeAtor);
		
		if(a != NULL)	{
			relacionarFilmeAtor(f,a);
		}//if
	}//if	
}