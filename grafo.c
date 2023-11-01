#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "tipos.h"
#include "fila.h"

/// <summary>
/// Função que inicializa o grafo.
/// </summary>
/// <param name="grafo">Endereço do grafo.</param>
void inicializaGrafo(grafo_t * grafo){
  grafo->numArestas = 0;
  grafo->numVertices = 0;
  grafo->vertices = NULL;
}

/// <summary>
/// Função que cria um vertice no grafo.
/// </summary>
/// <param name="grafo">Endereço do grafo.</param>
/// <param name="vertice">Vertice a ser criado.</param>
void criarVertice(grafo_t * grafo, int vertice){
  grafo->numVertices++;
  grafo->vertices = realloc(grafo->vertices, sizeof(vertice_t) * grafo->numVertices);
  grafo->vertices[vertice].adj = lista_cria();
}

/// <summary>
/// Função que cria uma aresta no grafo.
/// </summary>
/// <param name="grafo">Endereço do grafo.</param>
/// <param name="verticeSaida">Vertice de saída da aresta.</param>
/// <param name="verticeChegada">Vertice de entrada da aresta.</param>
bool_t criarAresta(grafo_t * grafo, int verticeSaida, int verticeChegada){
  int i;
  
  if(grafo->vertices == NULL) return FALSO;
  if(verticeSaida < 0 || verticeChegada >= grafo->numVertices) return FALSO;
  if(verticeChegada < 0 || verticeSaida >= grafo->numVertices) return FALSO;

  itemLista_t* itemLista;
  itemLista = lista_busca(grafo->vertices[verticeSaida].adj, verticeChegada);
  if (itemLista != NULL) return FALSO;

  lista_insereInicio(grafo->vertices[verticeSaida].adj, verticeChegada);
  grafo->numArestas++;
  return VERDADEIRO;
}

/// <summary>
/// Função que remove uma aresta no grafo.
/// </summary>
/// <param name="grafo">Endereço do grafo.</param>
/// <param name="verticeSaida">Vertice de saída da aresta.</param>
/// <param name="verticeChegada">Vertice de entrada da aresta.</param>
bool_t removerAresta(grafo_t * grafo, int verticeSaida, int verticeChegada){
  int i;
  
  if(grafo->vertices == NULL) return FALSO;
  if(verticeSaida < 0 || verticeChegada >= grafo->numVertices) return FALSO;
  if(verticeChegada < 0 || verticeSaida >= grafo->numVertices) return FALSO;
  
  itemLista_t* itemLista;
  itemLista = lista_busca(grafo->vertices[verticeSaida].adj, verticeChegada);
  if (itemLista == NULL) return FALSO;

  lista_retira(grafo->vertices[verticeSaida].adj, verticeChegada);
  grafo->numArestas--;
  
  return VERDADEIRO;
}

/// <summary>
/// Função que imprimir o grafo.
/// </summary>
/// <param name="grafo">Endereço do grafo.</param>
void imprimirGrafo(grafo_t * grafo){
  printf("Vértices: %d\nArestas: %d\n\n", grafo->numVertices, grafo->numArestas);
  int i;
  for(i = 0; i < grafo->numVertices; i++){
    printf("V%d: ", i);
    lista_imprime(grafo->vertices[i].adj);
    printf("\n");
  }
}

/// <summary>
/// Função que verifica se uma aresta existe no grafo.
/// </summary>
/// <param name="grafo">Endereço do grafo.</param>
/// <param name="verticeSaida">Vertice de saída da aresta.</param>
/// <param name="verticeChegada">Vertice de entrada da aresta.</param>
bool_t buscaAresta(grafo_t * grafo, int verticeSaida, int verticeChegada){
  int i;
  
  if(grafo->vertices == NULL) return FALSO;
  if(verticeSaida < 0 || verticeChegada >= grafo->numVertices) return FALSO;
  if(verticeChegada < 0 || verticeSaida >= grafo->numVertices) return FALSO;

  itemLista_t* itemLista;
  itemLista = lista_busca(grafo->vertices[verticeSaida].adj, verticeChegada);
  if (itemLista == NULL) 
    return FALSO;
  else
    return VERDADEIRO;
}

/// <summary>
/// Função que cria uma aresta no grafo.
/// </summary>
/// <param name="grafo">Endereço do grafo.</param>
/// <param name="verticeInicial">Vertice pelo qual a busca vai começar.</param>
int * buscaEmLargura(grafo_t * grafo, int verticeInicial){
  int cont = 1;
  int * vertices = (int*) calloc(grafo->numVertices, sizeof(int));
  
  fila_t fila;
  iniciarFila(&fila);
  
  inserirFila(&fila, verticeInicial);
  vertices[verticeInicial] = cont;
  
  while(fila.inicio != NULL){
    noFila_t * vertice = removerFila(&fila);
    
    if(vertice != NULL){
      cont = vertices[vertice->dado] + 1;
      int * adjacentes = lista_retornaElementos(grafo->vertices[vertice->dado].adj);
      
      if(adjacentes[0] > 0){
        for(int i = 1; i <= adjacentes[0]; i++){
          if(vertices[adjacentes[i]] == 0){
            inserirFila(&fila, adjacentes[i]);
            vertices[adjacentes[i]] = cont;
          }
        }
      }
      free(adjacentes);
    }
    free(vertice);
  }

  liberarFila(&fila);
  
  return vertices;
}

/// <summary>
/// Função que libera o grafo.
/// </summary>
/// <param name="grafo">Endereço do grafo.</param>
void liberaGrafo(grafo_t * grafo){
  for(int i = 0; i < grafo->numVertices; i++){
    lista_libera(grafo->vertices[i].adj);
  }
  free(grafo->vertices);
}