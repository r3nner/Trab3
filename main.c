#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

void listaAluno(Sistema* sistema){ //imprimir os alunos
    Aluno* p;
    printf("===== ALUNOS CADASTRADOS =====\n\n");
    for (p= sistema->lista_alunos; p!= NULL; p= p->prox){
        printf("========\nNome: %s\nMatricula: %s\nTelefone: %s\n\n", p->nome, p->matricula, p->telefone);
    }
}

void listaProfessor(Sistema* sistema){ //imprimir os professores
    Professor* p;
    printf("===== PROFESSORES CADASTRADOS =====\n\n");
    for (p= sistema->lista_professores; p!= NULL; p= p->prox){
        printf("========\nNome: %s\nCodigo: %s\nDepartamento: %s\n\n", p->nome, p->codigo, p->departamento);
    }
}

void listaProjeto(Sistema* sistema){ //imprimir os projetos
    Projeto* p;
    printf("====== PROJETOS CADASTRADOS =======\n\n");
    for (p= sistema->lista_projetos; p!= NULL; p= p->prox){
        printf("========\nCodigo: %s\nDescricao: %s\nTipo: %s\nOrcamento Total: %.2f reais\nOrcamento Disponivel: %.2f reais\nProfessor Coordenador: %s\n\n", p->codigo, p->descricao, p->tipo, p->orcamento_aprovado, p->orcamento_disponivel, p->professor_responsavel->nome);
    }
}

void listaVinculo(Sistema* sistema){ //imprimir os vinculos
    Vinculo* p;
    printf("======== VINCULOS CADASTRADOS ========\n\n");
    for (p= sistema->lista_vinculos; p!= NULL; p= p->prox){
        printf("========\nNome do aluno: %s\nDescricao do projeto: %s\nValor da bolsa: %.2f reais\n\n", p->aluno->nome, p->projeto->descricao, p->valor_bolsa);
    }
}

void gerar_relatorio(Sistema* sistema){ //gerar o relatorio final
    if (sistema->lista_projetos == NULL) {
        printf("Nenhum projeto cadastrado!\n");
        return;
    }
    Projeto* projeto_atual = sistema->lista_projetos; //para buscar info do projeto
    while (projeto_atual!=NULL){
        printf("\n\nProjeto Codigo: %s\nTipo: %s\nProfessor Coordenador: %s\n", projeto_atual->codigo, projeto_atual->tipo, projeto_atual->professor_responsavel->nome);
        printf("Orcamento disponivel: %.2f reais\n", projeto_atual->orcamento_disponivel);

        Vinculo* vinculo_atual = sistema->lista_vinculos; //para buscar info do vinculo
        int encontrou_vinculo = 0;
        while (vinculo_atual!=NULL) {
            if (vinculo_atual->projeto->codigo== projeto_atual->codigo) {
                printf("Aluno vinculado: %s, Valor Bolsa Mensal: %.2f reais\n", vinculo_atual->aluno->nome, vinculo_atual->valor_bolsa);
                encontrou_vinculo= 1;
            }
            vinculo_atual= vinculo_atual->prox;
        }
        if (encontrou_vinculo==0) {
            printf("Nao ha alunos vinculados a este projeto.\n");
        }
        projeto_atual = projeto_atual->prox;
    }
}

int main(){
    Sistema sistema;
    inicializar_sistema(&sistema);
    int escolha, escolha2;
    do {
        printf("================== PROJETOS E BOLSISTAS ==================\n\n");
        printf("Escolha o que deseja fazer:\n\n");
        printf("[1] Incluir Aluno\n[2] Listar Aluno\n[3] Incluir Projeto\n[4] Listar Projeto\n[5] Incluir/Excluir Vinculo\n[6] Listar Vinculo\n[7] Incluir Professor\n[8] Listar Professor\n[9] Gerar Relatorio\n[0] Sair\n\n========================\n");
        scanf("%d", &escolha);
        switch (escolha){
            case 1: //incluir aluno
                cadastrarAluno(&sistema);
                break;

            case 2: //listar aluno
                listaAluno(&sistema);
                break;

            case 3:  //incluir projeto
                cadastrarProjeto(&sistema);
                break;

            case 4:  //listar projeto
                listaProjeto(&sistema);
                break;

            case 5:  //inclui ou exclui vinculo
                printf("Voce deseja: \n[1] Incluir Vinculo\n[2] Excluir Vinculo\n");
                scanf("%d", &escolha2);
                switch (escolha2){
                case 1:
                    cadastrarVinculo(&sistema);
                    break;
                case 2:
                    excluiVinculo(&sistema);
                    break;

                default:
                    printf("\n====== Comando nao reconhecido ========\n\n");
                    break;
                }
                break;

            case 6:  //lista vinculo
                listaVinculo(&sistema);
                break;

            case 7:   //inclui professor
                cadastrarProfessor(&sistema);
                break;

            case 8:  //lista professor
                listaProfessor(&sistema);
                break;

            case 9:  //lista professor
                gerar_relatorio(&sistema);
                break;

            case 0:
                break;
            default:
                printf("\n====== Comando nao reconhecido ========\n\n");
                break;
        }
    } while (escolha != 0);
}
