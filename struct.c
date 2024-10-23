#include "struct.h"
#include "lista.h"

void inicializar_sistema(Sistema* sistema) {
    sistema->lista_alunos = NULL;
    sistema->lista_professores = NULL;
    sistema->lista_projetos = NULL;
    sistema->lista_vinculos = NULL;
}
