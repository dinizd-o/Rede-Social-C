#pragma once

#include "lista.h"

/// <summary>
/// Estrutura com os membros de um vertice do grafo.
/// </summary>
struct vertice_s{
  lista_t * adj;
};

/// <summary>
/// Tipo "Vertice"
/// </summary>
typedef struct vertice_s vertice_t;

/// <summary>
/// Estrutura com os membros de um grafo.
/// </summary>
struct grafo_s{
  unsigned int numVertices;
  unsigned int numArestas;
  vertice_t * vertices;
};

// <summary>
/// Tipo "Grafo"
/// </summary>
typedef struct grafo_s grafo_t;

/* Funções Exportadas */

void inicializaGrafo(grafo_t * grafo);
void criarVertice(grafo_t * grafo, int vertice);
bool_t criarAresta(grafo_t * grafo, int verticeSaida, int verticeChegada);
bool_t removerAresta(grafo_t * grafo, int verticeSaida, int verticeChegada);
void imprimirGrafo(grafo_t * grafo);
void liberaGrafo(grafo_t * grafo);
bool_t buscaAresta(grafo_t * grafo, int verticeSaida, int verticeChegada);
int * buscaEmLargura(grafo_t * grafo, int verticeInicial);