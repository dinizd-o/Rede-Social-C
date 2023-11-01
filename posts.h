#pragma once

#include "tabelaHash.h"

#define TAMANHO_STRING_POSTAGEM (140+1)

/// <summary>
/// Estrutura com os membros de um item da lista de postagens.
/// </summary>
struct noPostagem_s{
  int idPost;
  char post[TAMANHO_STRING_POSTAGEM];
  tabelaHash_t curtidas;
  struct noPostagem_s *proximo;
};

/// <summary>
/// Tipo "Nó da Lista"
/// </summary>
typedef struct noPostagem_s noPostagem_t;

/// <summary>
/// Estrutura com os membros de uma lista de postagens.
/// </summary>
struct postagens_s{
  noPostagem_t *inicio;
  int tam;
  int id;
};

/// <summary>
/// Tipo "Postagem"
/// </summary>
typedef struct postagens_s postagens_t;

/* Funções Exportadas */

void iniciarPostagens(postagens_t* lista);
void inserirPostagem(postagens_t *lista, char string[]);
noPostagem_t* removerPostagem(postagens_t *lista, int idPost);
noPostagem_t* buscarPostagem(postagens_t* lista, int id);
void imprimirPostagens(postagens_t lista, int idUsuario, int nPostagens);
void liberaPostagens(postagens_t * lista);