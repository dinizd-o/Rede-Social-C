#pragma once

/// <summary>
/// Tipo do valor do item da fila
/// </summary>
typedef int dado_t;

/// <summary>
/// Estrutura com os membros de um item da fila.
/// </summary>
struct noFila_s{
  dado_t dado;
  struct noFila_s *proximo;
};

/// <summary>
/// Tipo "Nó da Fila"
/// </summary>
typedef struct noFila_s noFila_t;

/// <summary>
/// Estrutura com os membros de uma fila.
/// </summary>
struct fila_s{
  noFila_t *inicio;
  noFila_t *fim;
  int tam;
};

/// <summary>
/// Tipo "Fila"
/// </summary>
typedef struct fila_s fila_t;

/* Funções Exportadas */

void iniciarFila(fila_t* fila);
void inserirFila(fila_t *fila, dado_t dado);
noFila_t* removerFila(fila_t *fila);
noFila_t* buscarFila(fila_t* fila, dado_t dado);
void imprimirFila(fila_t fila);
void liberarFila(fila_t * fila);