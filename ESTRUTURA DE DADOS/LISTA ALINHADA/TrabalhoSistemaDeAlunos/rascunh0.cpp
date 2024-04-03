// Produzido por LUCAS GARCIA & LUIS AUGUSTO DE SOUZA


// ==================== functions.c ========================== 
// ==================== functions.c ========================== 
// ==================== functions.c ========================== 
// ============================= BASE ======================
#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
// #include "utils.c"
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

typedef struct ClassDatabaseTipoDisciplina {
	string nome;
	int cargaHoraria;
	ClassDatabaseTipoDisciplina *prox;
}TDisciplina;

typedef struct ClassDatabaseTipoHistorico {
	TDisciplina *disciplina;
	float nota;
	float percentualFrequencia;
	string condicao; // Aprovado, Reprovado ou Cursando.
	ClassDatabaseTipoHistorico *prox;	
}THistorico;

typedef struct ClassDatabaseTipoAluno {
    string nome;
	char sexo;
	THistorico *historico;
	ClassDatabaseTipoAluno *ante, *prox;
}TAluno;

typedef struct ClassDatabaseTipoCurso {
    string nome;
	TAluno *alunos;
	ClassDatabaseTipoCurso *ante, *prox;
}TCurso;

typedef struct ClassDatabaseTipoLista {
    TCurso *inicioC;
    TCurso *fimC;
    TDisciplina *inicioD;
    TDisciplina *fimD;
	int total;
}TLista;


// ============================= FIM DO BASE ======================
int menu(){
	int op;
	printf("\n\n\t\t====| MENU |=====\n\n");
	printf("\t0 - Sair (Encerrar a Aplicacao).\n\n");
	printf("\t1 - Inserir DISCIPLINA.\n");
	printf("\t2 - Exibe Todas as DISCIPLINAS.\n\n");
	printf("\t3 - Inserir CURSO.\n");
	printf("\t4 - Exibir Todos os CURSOS.\n\n");
	printf("\t5 - Inserir ALUNO em CURSO.\n");
	printf("\t6 - Exibir Todos os ALUNOS de CURSO especifico.\n");
	printf("\t7 - Excluir ALUNO de CURSO.\n\n");
	printf("\t8 - Inserir HISTORICO para ALUNO.\n");
	printf("\t9 - Exibir HISTORICO de ALUNO.\n");
	printf("\t10 - Excluir HISTORICO de ALUNO.\n\n");
	do {
		printf("Escolha sua opção: ");
		scanf(" %d", &op);
	} while(op < 0 || op > 10);
	return op;
}


void insereDisciplina(TLista *lista, string nome, int cargaHoraria){
    int inseriu = 0;
    TDisciplina *novo = (TDisciplina *)malloc(sizeof(TDisciplina));
    novo->cargaHoraria = cargaHoraria;
	strcpy(novo->nome, nome);
   
    novo->prox = NULL;
    if (lista->inicioD == NULL){
        //Lista encontra-se vazia.
        //Inserir o primeiro e unico elemento da lista ate agora
        lista->inicioD = novo;
        lista->fimD = novo;
        lista->total = 1;
        inseriu = 1;
    }else{
        //Lista ja possui pelo menos 1 elemento
        TDisciplina *atual = lista->inicioD;
        TDisciplina *anterior = NULL;
        while (atual != NULL){
            if (strcmp(atual->nome,novo->nome) == 1){
                if (atual == lista->inicioD){
                    //Inserir novo no inicio da lista
                    novo->prox = atual;
                    lista->inicioD = novo;
                }else{
                    //Inserir novo no meio da lista
                    novo->prox = atual;
                    anterior->prox = novo;
                }
                inseriu = 1;
                lista->total++;
                break;
            }
            anterior = atual;
            atual = atual->prox; //move para o próximo elemento
        }
        if (!inseriu){
            //Inserir elemento no fim da lista
            lista->fimD->prox = novo;
            lista->fimD = novo;
            lista->total++;
        }
        lista->total++;
    }
    printf("\n\t Disciplina  %s Inserida!", nome);
}


void insereCurso(TLista *lista, string nome){
    TCurso *novo = (TCurso *)malloc(sizeof(TCurso));
    TCurso *atual;
    int flag = 0;
    novo->prox = NULL;
    novo->ante = NULL;
    if (lista->inicioC == NULL){
        //Lista encontra-se vazia.
        //Inserir o primeiro e unico elemento da lista ate agora
        lista->inicioC = novo;
        lista->fimC = novo;
        flag = 1;
    }else{
        //Lista ja possui pelo menos 1 elemento
        atual = lista->inicioC;
        while (atual != NULL){
            if (strcmp(atual->nome,novo->nome) > 0){
                //encontrada a posiçao para a inserçao do novo Tfilme
                flag = 1;
                
                if (atual == lista->inicioC){
                    //Inserir novo no inicio da lista
                    novo->prox = atual;
                    atual->ante = novo;
                    lista->inicioC = novo;
                }else{
                    //Inserir novo no meio da lista
                    novo->prox = atual;
                    novo->ante = atual->ante;
                    atual->ante->prox = novo;
                    atual->ante = novo;
                }
                break;
            }
            atual = atual->prox; //move para o próximo elemento
        }
        if (flag == 0){
            //inserir o novo como o ultimo Tfilme da lista
            lista->fimC->prox = novo;
            novo->ante = lista->fimC;
            lista->fimC = novo;
        }
    }
    lista->total++;
	printf("\n\t Curso  %s Inserido!", nome);
}

TCurso *localizaCurso(TLista *lista, string titulo){
	TCurso *atual = lista->inicioC;
	
	while (atual != NULL){
		if(strcmp(atual->nome, titulo) == 0){
			break;
		}//if
		atual = atual->prox;
	}//while
	return atual;
}

// ================ EXIBES =============== 

void exibeDisciplina(TLista *lista){
	TDisciplina *atual = lista->inicioD;
	int cont = 0;
	printf("\n\n\t\t===| EXIBE TODAS AS DISCIPLINAS |===\n\n");
	while (atual != NULL){
		printf("(%d) - %s - %dH.\n",cont+1, atual->nome, atual->cargaHoraria);
		atual = atual->prox;
        cont++;
	}
	printf("\n\n");
}

void exibeCurso(TLista *lista){
   TCurso *atual = lista->inicioC;
	int cont = 0;
	printf("\n\n\t\t===| EXIBE TODOS OS CURSOS |===\n\n");
	while (atual != NULL){
		printf("(%d) - %s.\n",cont+1,atual->nome );
		atual = atual->prox;
        cont++;
	}
	printf("\n\n"); 
}

void exibeAlunosEmCurso(TLista *lista){
	int cont = 0;
	TCurso *curso;
	TAluno *aluno = curso->alunos;
	string nome;
	
	printf("\n\n\t\t===| EXIBE TODOS OS ALUNOS EM UM CURSO |===\n\n");
	printf("\tInforme o NOME do CURSO: ");

	scanf(" %39[^\n]s", nome);
	fflush(stdin);
	
	curso = localizaCurso(lista, nome);
	
	if(curso == NULL){
		printf("\n\n\tERRO: Curso procurado NAO foi encontrado.\n\tCURSO: %s.\n\n",curso->nome);
		system("PAUSE");
	} else {
		printf("O CURSO %s tem os seguintes ALUNOS matriculados", curso->nome);
		while (aluno->prox != NULL){
			printf("(%d) - %s - %s.\n",cont+1,aluno->nome, aluno->sexo );
			aluno = aluno->prox;
			cont++;
		}
	}
	printf("\n\n"); 
}


// ==================== functions.c ========================== 
// ==================== functions.c ========================== 
// ==================== functions.c ========================== 

// =============== INDEX.cpp ======================
// =============== INDEX.cpp ======================
// =============== INDEX.cpp ======================

TLista listas;


void cadastraDisciplina(TLista *lista){
    int cargaHoraria;
    string nome;

    printf("Digite o nome da Disciplina: ");
    scanf(" %39[^\n]s", nome);
    fflush(stdin);
    printf("Digite qual e a carga horaria: ");
    scanf("%d", &cargaHoraria);
    fflush(stdin);

    insereDisciplina(lista, nome, cargaHoraria);
}

void realizaOpcaoDesejada(TLista *listas, int op){
    switch (op){
    case 1:
        cadastraDisciplina(listas);
        break;
    
    case 2:
        exibeDisciplina(listas);
        break;
    
    case 3:
        // cadastraCurso(listas);
        break;
    
    case 4:
        exibeCurso(listas);
        break;
    
    case 5:
        // insereAlunoEmCurso(listas);
        break;
    
    case 6:
        exibeAlunosEmCurso(listas);
        break;
    
    case 7:
        // exibeTodosAlunos(listas);
        break;
    
    case 8:
        // insereHistorico(listas);
        break;
    
    case 9:
        // insereDisciplina(listas);
        break;
    
    case 10:
        // insereDisciplina(listas);
        break;
    
    default:
        printf("\nERRO: Opção invalida, tente novamente\n");
        break;
    }
}

void inicializa(TLista *lista){
    lista->inicioC = NULL;
    lista->inicioD = NULL;
    lista->fimC = NULL;
    lista->fimD = NULL;
    lista->total = 0;
    insereDisciplina(lista, "Prog1",60);  
    insereDisciplina(lista, "Math",90);  
    insereDisciplina(lista, "ED",30);  
    insereDisciplina(lista, "POO",60);   

    exibeDisciplina(lista);
}
//===================================================================
int main(){
    inicializa(&listas);
    int op;
    int sair = 0;
    do{
        op = menu();
        if (op == 0){
            sair = 1;
        }else if ((op < 0)||(op > 10)){
            printf("\nERRO: Opção invalida, tente novamente\n");
        }else{
            realizaOpcaoDesejada(&listas, op);
        }
    } while (sair != 1);
    return 0;
}

// =============== INDEX.cpp ======================
// =============== INDEX.cpp ======================
// =============== INDEX.cpp ======================

/* 
  Tarefa Avaliativa (Semana 08).
  implementação de uma lista encadeada aninhada.
  
*/
/* 
  Tarefa Avaliativa (Semana 08).
  implementação de uma lista encadeada aninhada.
  
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char string[40];

typedef struct tipoDisciplina {
	string nome;
	int cargaHoraria;
	tipoDisciplina *prox;
}TDisciplina;

typedef struct tipoHistorico {
	TDisciplina *disciplina;  
	float nota;
	float percentualFrequencia;
	string condicao; // Aprovado, Reprovado ou Cursando.
	tipoHistorico *prox;	
}THistorico;

typedef struct tipoAluno {
	string nome;
	char sexo;
	THistorico *historico;
	tipoAluno *ante, *prox;
}TAluno;

typedef struct tipoCurso {
	string nome;
	TAluno *alunos;
	tipoCurso *ante, *prox;
}TCurso;

typedef struct tipoLista {
	TCurso *inicioC;
	TCurso *fimC;
	TDisciplina *inicioD;
	TDisciplina *fimD;
    int total;
}TLista;

TLista listas;

void insereDisciplina(TLista *lista, string nome, int cargaHoraria){
    int inseriu = 0;
    TDisciplina *novo = (TDisciplina *)malloc(sizeof(TDisciplina));
    novo->cargaHoraria = cargaHoraria;
    strcpy(novo->nome,nome);
    novo->prox = NULL;
    if (lista->inicioD == NULL){
        //Lista encontra-se vazia.
        //Inserir o primeiro e unico elemento da lista ate agora
        lista->inicioD = novo;
        lista->fimD = novo;
        lista->total = 1;
        inseriu = 1;
    }else{
        //Lista ja possui pelo menos 1 elemento
        TDisciplina *atual = lista->inicioD;
        TDisciplina *anterior = NULL;
        while (atual != NULL){
            if (strcmp(atual->nome,novo->nome) == 1){
                if (atual == lista->inicioD){
                    //Inserir novo no inicio da lista
                    novo->prox = atual;
                    lista->inicioD = novo;
                }else{
                    //Inserir novo no meio da lista
                    novo->prox = atual;
                    anterior->prox = novo;
                }
                inseriu = 1;
                lista->total++;
                break;
            }
            anterior = atual;
            atual = atual->prox; //move para o próximo elemento
        }
        if (!inseriu){
            //Inserir elemento no fim da lista
            lista->fimD->prox = novo;
            lista->fimD = novo;
            lista->total++;
        }
        lista->total++;
    }
}

TDisciplina *defineHisitorico(TLista *lista, string nome){
	TDisciplina *atual = L->inicioD;
	while(atual != NULL)	{
		if(strcmp(atual->nome, nome) == 0) {
			break;
		}//if
		atual = atual->prox;
	}//while
	return atual;
}

TDisciplina *pesquisarDisciplina(string nome){
	
}

void insereHistorico(TAluno *aluno, THistorico *historico){
	string nomeDisci;
	printf("Digite o nome da disciplina: ");
	scanf(" %39[^\n]s", nomeDisci);
	historico->disciplina = pesquisarDisciplina(nomeDisci);
	printf("Digite a nota que o aluno teve nessa disciplina: ");
	scanf("%f", &historico->nota);
	printf("Digite o percentual de presença que o aluno teve nessa disciplina: ");
	scanf("%f", &historico->percentualFrequencia);
	printf("Digite a condiçao que esse aluno esta nessa disciplina(Aprovado/Reprovado/Cursando): ");
	scanf(" %39[^\n]s", historico->condicao);
}

int menu(){
	int op;
	printf("\n\n\t\t====| MENU |=====\n\n");
	printf("\t0 - Sair (Encerrar a Aplicacao).\n\n");
	printf("\t1 - Inserir DISCIPLINA.\n");
	printf("\t2 - Exibe Todas as DISCIPLINAS.\n\n");
	printf("\t3 - Inserir CURSO.\n");
	printf("\t4 - Exibir Todos os CURSOS.\n\n");
	printf("\t5 - Inserir ALUNO em CURSO.\n");
	printf("\t6 - Exibir Todos os ALUNOS de CURSO especifico.\n");
	printf("\t7 - Excluir ALUNO de CURSO.\n\n");
	printf("\t8 - Inserir HISTORICO para ALUNO.\n");
	printf("\t9 - Exibir HISTORICO de ALUNO.\n");
	printf("\t10 - Excluir HISTORICO de ALUNO.\n\n");
	do {
		printf("Escolha sua opção: ");
		scanf(" %d", &op);
	} while(op < 0 || op > 10);
	return op;
}

void inicializa(TLista *lista){
    lista->inicioC = NULL;
    lista->inicioD = NULL;
    lista->fimC = NULL;
    lista->fimD = NULL;
    lista->total = 0; 
	insereDisciplina(lista,"Prog I",90); 
	insereDisciplina(lista,"Prog II",90);
	insereDisciplina(lista,"ED",60);
	insereDisciplina(lista,"OAC",60);
	insereDisciplina(lista,"Adm Financeira",60);
	insereDisciplina(lista,"Redes",60);
	insereDisciplina(lista,"SO",60);     
	
	insereHistorico(lista,);
}

void cadastraDisciplina(TLista *lista){
	string nome;
	int cargahoraria;
    printf("Digite o nome da Disciplina: ");
    scanf(" %39[^\n]s", nome);
    printf("Digite qual e a carga horaria: ");
    scanf("%d", &cargahoraria);
    insereDisciplina(lista,nome,cargahoraria);
}

void exibeDisciplina(TLista *L){
	TDisciplina *atual = L->inicioD;
	int cont = 0;
	printf("\n\n\t\t===| EXIBE LISTA COMPLETA |===\n\n");
	while (atual != NULL){
		printf("(%d) - %s - %dH.\n",cont+1, atual->nome, atual->cargaHoraria);
		atual = atual->prox;
        cont++;
	}
	printf("\n\n");
}

/*void insereAluno(string curso, string nomeAluno, char sexo){
    TAluno *novo = (TAluno *)malloc(sizeof(TAluno));
    TAluno *atual;
    int flag = 0;

    novo->prox = NULL;
    novo->ante = NULL;
    if (lista->primeiro == NULL){
        //Lista encontra-se vazia.
        //Inserir o primeiro e unico elemento da lista ate agora
        lista->primeiro = novo;
        lista->ultimo = novo;
        flag = 1;
    }else{
        //Lista ja possui pelo menos 1 elemento
        atual = lista->primeiro;
        while (atual != NULL){
            if (strcmp(atual->nome,novo->nome) > 0){
                //encontrada a posiçao para a inserçao do novo Tfilme
                flag = 1;
                
                if (atual == lista->primeiro){
                    //Inserir novo no inicio da lista
                    novo->prox = atual;
                    atual->ante = novo;
                    lista->primeiro = novo;
                }else{
                    //Inserir novo no meio da lista
                    novo->prox = atual;
                    novo->ante = atual->ante;
                    atual->ante->prox = novo;
                    atual->ante = novo;
                }
                break;
            }
            atual = atual->prox; //move para o próximo elemento
        }
        if (flag == 0){
            //inserir o novo como o ultimo Tfilme da lista
            lista->ultimo->prox = novo;
            novo->ante = lista->ultimo;
            lista->ultimo = novo;
        }
    }
    lista->total++;
}*/



void insereCurso(TLista *lista, string nome){
    TCurso *novo = (TCurso *)malloc(sizeof(TCurso));
    TCurso *atual;
    int flag = 0;
    ////inserir dados
    // insereAlunosNoCurso();
    novo->prox = NULL;
    novo->ante = NULL;
    if (lista->inicioC == NULL){
        //Lista encontra-se vazia.
        //Inserir o primeiro e unico elemento da lista ate agora
        lista->inicioC = novo;
        lista->fimC = novo;
        flag = 1;
    }else{
        //Lista ja possui pelo menos 1 elemento
        atual = lista->inicioC;
        while (atual != NULL){
            if (strcmp(atual->nome,novo->nome) > 0){
                //encontrada a posiçao para a inserçao do novo Tfilme
                flag = 1;
                
                if (atual == lista->inicioC){
                    //Inserir novo no inicio da lista
                    novo->prox = atual;
                    atual->ante = novo;
                    lista->inicioC = novo;
                }else{
                    //Inserir novo no meio da lista
                    novo->prox = atual;
                    novo->ante = atual->ante;
                    atual->ante->prox = novo;
                    atual->ante = novo;
                }
                break;
            }
            atual = atual->prox; //move para o próximo elemento
        }
        if (flag == 0){
            //inserir o novo como o ultimo Tfilme da lista
            lista->fimC->prox = novo;
            novo->ante = lista->fimC;
            lista->fimC = novo;
        }
    }
    lista->total++;
}

void realizaOpcaoDesejada(TLista *listas, int op){
    switch (op){
    case 1:
        cadastraDisciplina(listas);
        break;
    
    case 2:
        exibeDisciplina(listas);
        break;
    
    case 3:
        //insereDisciplina(listas);
        break;
    
    case 4:
        //insereDisciplina(listas);
        break;
    
    case 5:
        //insereDisciplina(listas);
        break;
    
    case 6:
        //insereDisciplina(listas);
        break;
    
    case 7:
        //insereDisciplina(listas);
        break;
    
    case 8:
        //insereDisciplina(listas);
        break;
    
    case 9:
        //insereDisciplina(listas);
        break;
    
    case 10:
        //insereDisciplina(listas);
        break;
    
    default:
        break;
    }
}
//===================================================================
int main(){
    inicializa(&listas);
    int op;
    int sair = 0;
    do{
        op = menu();
        if (op == 0){
            sair = 1;
        }else if ((op < 0)||(op > 10)){
            printf("\nERRO: Opção invalida, tente novamente\n");
        }else{
            realizaOpcaoDesejada(&listas, op);
        }
    } while (sair != 1);
    return 0;
}