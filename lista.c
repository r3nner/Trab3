#include "lista.h"
#include "struct.h"


Aluno* verificarAluno(Sistema* sistema, char matricula[]){
    Aluno* encontrado = sistema->lista_alunos;
    while (encontrado != NULL) {
        if (!strcmp(encontrado->matricula, matricula)) {
            return encontrado;
        }
        encontrado = encontrado->prox;
    }
    return NULL;
}

Professor* verificarProf(Sistema* sistema, char codigo[]){
    Professor* encontrado = sistema->lista_professores;
    while (encontrado != NULL) {
        if (!strcmp(encontrado->codigo, codigo)) {
            return encontrado;
        }
        encontrado = encontrado->prox;
    }
    return NULL;
}

Projeto* verificarProjeto(Sistema* sistema, char codigo[]){
    Projeto* encontrado = sistema->lista_projetos;
    while (encontrado != NULL) {
        if (!strcmp(encontrado->codigo, codigo)) {
            return encontrado;
        }
        encontrado = encontrado->prox;
    }
    return NULL;

}

Aluno* verificarVinculo(Sistema* sistema, char matricula[]){
    Aluno* p;
    for (p = sistema->lista_alunos;p != NULL; p = p->prox){
        if (!strcmp(matricula, p->matricula)){
            return p;
        }
    }
    return NULL;
}

Projeto* verificarCodigo(Sistema* sistema, char codigo[]){
    Projeto* p;
    for (p = sistema->lista_projetos; p != NULL; p = p->prox){
        if (!strcmp(codigo, p->codigo)){
            return p;
        }
    }
    return NULL;
}

void cadastrarAluno(Sistema* sistema){

    char matricula[100];

    printf("\n======== CADASTRO DE ALUNO ========\n\n");
    printf("\nDigite a matricula do aluno: ");
    scanf(" %[^\n]s", matricula);

    if (verificarAluno(sistema, matricula)!=NULL) {
        printf("\nJa existe um aluno com essa matricula! Tente novamente.\n\n");
        return;
    }

    Aluno* novo_aluno= (Aluno*)malloc(sizeof(Aluno));
    if (novo_aluno == NULL){
        printf("Erro em alocacao.\n");
        exit(1);
    }
    strcpy(novo_aluno->matricula, matricula);
    //novo_aluno->matricula= matricula;

    printf("Digite o nome do aluno: ");
    scanf(" %[^\n]s", novo_aluno->nome);
    printf("Digite o telefone: ");
    scanf(" %[^\n]s", novo_aluno->telefone);

    novo_aluno->prox=sistema->lista_alunos;
    sistema->lista_alunos= novo_aluno;

    printf("\nAluno cadastrado!\n\n");
}

void cadastrarProfessor(Sistema* sistema){
    char codigo[100];
    printf("\n======== CADASTRO DE PROFESSOR ========\n\n");
    printf("\nDigite o codigo do professor: ");
    scanf(" %[^\n]s", codigo);

    if (verificarProf(sistema, codigo)!=NULL) {
        printf("\nJa existe um professor com esse codigo! Tente novamente.\n\n");
        return;
    }

    Professor* novo_prof= (Professor*)malloc(sizeof(Professor));
    if (novo_prof == NULL){
        printf("Erro em alocacao.\n");
        exit(1);
    }

    strcpy(novo_prof->codigo, codigo);
    printf("Digite o nome do professor: ");
    scanf(" %[^\n]s", novo_prof->nome);
    printf("Digite o departamento: ");
    scanf(" %[^\n]s", novo_prof->departamento);

    novo_prof->prox=sistema->lista_professores;
    sistema->lista_professores= novo_prof;
    printf("\nProfessor cadastrado!\n\n");
}

void cadastrarProjeto(Sistema* sistema){
    char codigo[100], codigo_prof[100];
    printf("\n======== CADASTRO DE PROJETO ========\n\n");
    printf("\nDigite o codigo do projeto: ");
    scanf(" %[^\n]s", codigo);

    if (verificarProjeto(sistema, codigo)!=NULL) {
        printf("\nJa existe um projeto com esse codigo!\n\n");
        return;
    }

    printf("Qual o codigo do professor responsavel pelo projeto: \n");
    scanf(" %[^\n]s", codigo_prof);

    Professor* prof_projeto= verificarProf(sistema, codigo_prof);
    if (prof_projeto==NULL){
        printf("\nProfessor nao existe, cadastro cancelado!\n\n");
        return;
    }
    Projeto* projeto= (Projeto*)malloc(sizeof(Projeto));
    if (projeto == NULL){
        printf("Erro em alocacao.\n");
        exit(1);
    }
    strcpy(projeto->codigo, codigo);
    printf("Escreva a descricao do projeto: \n");
    scanf(" %[^\n]s", projeto->descricao);
    printf("Escreva o tipo do projeto: \n");
    scanf(" %[^\n]s", projeto->tipo);
    printf("Qual o orcamento aprovado do projeto: \n");
    scanf(" %f", &projeto->orcamento_aprovado);


    projeto->orcamento_disponivel=projeto->orcamento_aprovado;

    projeto->professor_responsavel= prof_projeto;

    projeto->prox=sistema->lista_projetos;
    sistema->lista_projetos= projeto;
    printf("\nProjeto cadastrado!\n\n");

}

void cadastrarVinculo(Sistema* sistema){

    printf("\n======== CADASTRO DE VINCULO ========\n\n");

    char codprojeto[100], matricula[100];
    float orcamento_atual, valor_bolsa, bolsaanual;
    Aluno* alunoproj;
    Projeto* projvinculo;

    printf("Digite a matricula do aluno do projeto: ");
    scanf(" %[^\n]s", matricula);

    alunoproj= verificarAluno(sistema, matricula);
    if (alunoproj==NULL){
        printf("\nNao existe aluno com essa matricula\n\n");
        return;
    }

    printf("Digite o codigo do projeto: ");
    scanf(" %[^\n]s", codprojeto);

    projvinculo = verificarProjeto(sistema, codprojeto);
    if (projvinculo==NULL){
        printf("\nNao existe projeto com esse codigo!\n\n");
        return;
    }

    printf("Digite o valor da bolsa: ");
    scanf(" %f", &valor_bolsa);

    bolsaanual= valor_bolsa*12;

    if (projvinculo->orcamento_disponivel<bolsaanual){
        printf("\nOrcamento indisponivel! Bolsa cancelada!\n\n");
        return;
    }

    projvinculo->orcamento_disponivel=projvinculo->orcamento_disponivel-bolsaanual;

    Vinculo* novo_vinculo = (Vinculo*) malloc(sizeof(Vinculo));
    if (novo_vinculo == NULL){
        printf("Erro em alocacao.\n");
        exit(1);
    }
    novo_vinculo->aluno = alunoproj;
    novo_vinculo->projeto = projvinculo;
    novo_vinculo->valor_bolsa = valor_bolsa;
    novo_vinculo->prox = sistema->lista_vinculos;
    sistema->lista_vinculos = novo_vinculo;

    printf("Vínculo cadastrado com sucesso!\n\n");

}

void excluiVinculo(Sistema* sistema) {
    char matricula[100];
    printf("Digite o numero da matricula do aluno:\n");
    scanf(" %[^\n]s", matricula);
    Aluno *l = verificarVinculo(sistema, matricula);
    if (l == NULL) {
        printf("\nNao existe um aluno com essa matricula!\n");
        return;
    }
    char codigo[100];
    printf("Digite o codigo do projeto:\n");
    scanf(" %[^\n]s", codigo);

    Projeto *m = verificarCodigo(sistema, codigo);
    if (m == NULL) {
        printf("\nNao existe um projeto com esse codigo!\n");
        return;
    }

    int meses;
    printf("Digite a quantidade de meses em que a bolsa nao sera mais paga:\n");
    scanf("%d", &meses);


    Vinculo* p = sistema->lista_vinculos;
    Vinculo* ant = NULL;
    for (; p != NULL; p = p->prox){

        if (!strcmp(p->aluno->matricula, matricula)){
            break;
        }
        ant = p;
    }
    if (p == NULL){
        printf("Vinculo nao encontrado. Tente novamente!\n");
        return;
    }
    p->projeto->orcamento_disponivel += meses * p->valor_bolsa;

    if (ant == NULL){
        sistema->lista_vinculos = p->prox;
    } else {
        ant->prox = p->prox;
    }
    free(p);
    return;
}
