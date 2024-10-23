#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno {
    char matricula[100];
    char nome[100];
    char telefone[100];
    struct Aluno* prox;
} Aluno;

typedef struct Professor {
    char codigo[100];
    char nome[100];
    char departamento[100];
    struct Professor* prox;
} Professor;

typedef struct Projeto {
    char codigo[100];
    char descricao[100];
    char tipo[100];
    float orcamento_aprovado;
    float orcamento_disponivel;
    Professor* professor_responsavel;
    struct Projeto* prox;
} Projeto;

typedef struct Vinculo {
    Aluno* aluno;
    Projeto* projeto;
    float valor_bolsa;
    struct Vinculo* prox;
} Vinculo;

typedef struct Sistema {
    Aluno* lista_alunos;
    Professor* lista_professores;
    Projeto* lista_projetos;
    Vinculo* lista_vinculos;
} Sistema;

void inicializar_sistema(Sistema* sistema);

#endif
