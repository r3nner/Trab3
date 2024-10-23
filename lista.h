#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

Aluno* verificarAluno(Sistema* sistema, char matricula[]);

Professor* verificarProf(Sistema* sistema, char codigo[]);

Aluno* verificarVinculo(Sistema* sistema, char matricula[]);

Projeto* verificarCodigo(Sistema* sistema, char codigo[]);

void cadastrarAluno(Sistema* sistema);

void cadastrarProfessor(Sistema* sistema);

void cadastrarProjeto(Sistema* sistema);

void cadastrarVinculo(Sistema* sistema);

void excluiVinculo(Sistema* sistema);

void listaAluno(Sistema* sistema);

void listaProfessor(Sistema* sistema);

void listaProjeto(Sistema* sistema);

void listaVinculo(Sistema* sistema);

#endif // LISTA_H
