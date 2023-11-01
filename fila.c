#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

/// <summary>
/// Função que inicializa a fila.
/// </summary>
/// <param name="fila">Endereço da fila.</param>
void iniciarFila(fila_t* fila){
  fila->inicio = NULL;
  fila->fim = NULL;
  fila->tam = 0;
}

/// <summary>
/// Função que insere elemento na fila.
/// </summary>
/// <param name="fila">Endereço da fila.</param>
/// <param name="dado">Elemento a ser inserido.</param>
void inserirFila(fila_t *fila, dado_t dado){
  noFila_t *aux, *novo = (noFila_t*) malloc(sizeof(noFila_t));

  novo->dado = dado;
  novo->proximo = NULL;
  //SE FOR O PRIMEIRO ELEMENTO
  if(fila->inicio == NULL){
    fila->inicio = novo;
  }
  else{
    fila->fim->proximo = novo;
  }
  fila->fim = novo;
  fila->tam++;
}

/// <summary>
/// Função que remove elemento da fila.
/// </summary>
/// <param name="fila">Endereço da fila.</param>
noFila_t* removerFila(fila_t *fila){
 noFila_t* remover = NULL;

  if(fila->inicio != NULL){
    remover = fila->inicio;
    fila->inicio = remover->proximo;
    fila->tam--;
  }
  else{
    return NULL;
  }
  if(fila->inicio == NULL){
    fila->fim = NULL;
  }
  return remover;
}

/// <summary>
/// Função que busca elemento na fila.
/// </summary>
/// <param name="fila">Endereço da fila.</param>
/// <param name="dado">Elemento a ser buscado.</param>
noFila_t* buscarFila(fila_t* fila, dado_t dado){
  noFila_t *aux, *no = NULL;;
  aux = fila->inicio;
  while(aux && aux->dado != dado){
    aux = aux->proximo;
  }
  if(aux){
    no = aux;
  }
  
  return no;
}

/// <summary>
/// Função que imprime a fila.
/// </summary>
/// <param name="fila">Endereço da fila.</param>
void imprimirFila(fila_t fila){
  noFila_t *no = fila.inicio;
  printf("\n\tFila tam %d\n", fila.tam);
  while(no){
    printf("\t%d\n", no->dado );
    no = no->proximo;
  }
  printf("\n");
}

/// <summary>
/// Função que libera a fila.
/// </summary>
/// <param name="fila">Endereço da fila.</param>
void liberarFila(fila_t * fila){
  noFila_t * aux = fila->inicio;
  while(aux != NULL){
    noFila_t * no = aux->proximo;
    free(aux);
    aux = no->proximo;
  }
}