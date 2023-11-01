#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "posts.h"
#include "uteis.h"
#include "tabelaHash.h"
#include "perfil.h"

#define TAMANHO_HASH 1009

/**
 * Função de inicialização.
 * @return Lista vazia.
 */
void iniciarPostagens(postagens_t* lista){
  lista->inicio = NULL;
  lista->tam = 0;
  lista->id = 0;
}

/**
 * Função que insere um item no início da lista.
 * @param lista Lista onde o item será inserido.
 * @param item Item a ser inserido na lista.
 * @return Lista atualizada com o novo item.
 */
void inserirPostagem(postagens_t *lista, char item[]){
  noPostagem_t *novo = malloc(sizeof(noPostagem_t));
  
  strcpy(novo->post, item);
  novo->proximo = lista->inicio;
  novo->idPost = lista->id;
  lista->inicio = novo;
  lista->tam++; 
  lista->id++;
  tabelaHash_inicializa(&(lista->inicio->curtidas), TAMANHO_HASH, funcaoHash);
}

/**
 * Função que procura e remove um item da lista caso o item esteja presente.
 * @param lista Lista ontem o item ser procurado.
 * @param idPost Id do item a ser procurado.
 * @return Nó removido da lista.
 */
noPostagem_t* removerPostagem(postagens_t *lista, int idPost){
 noPostagem_t* remover = NULL, *aux;

  if(lista->inicio){
    if(lista->inicio->idPost == idPost){
      remover = lista->inicio;
      lista->inicio = remover->proximo;
      lista->tam--;
    }
    else{
      aux = lista->inicio;
      while(aux->proximo && lista->inicio->idPost != idPost){
        aux = aux->proximo;
      }
      if(aux->proximo){
        remover = aux->proximo;
        aux->proximo = remover->proximo;
         lista->tam--;
      }
    }
  }

  return remover;
}

/**
 * Função que procura um item da lista.
 * @param lista Lista ontem o item ser procurado.
 * @param idPost Id do item a ser procurado.
 * @return Endereço do nó encontrado na lista.
 */
noPostagem_t* buscarPostagem(postagens_t* lista, int idPost){
  noPostagem_t* aux, *no = NULL;
  aux = lista->inicio;
  while(aux && aux->idPost != idPost){
    aux = aux->proximo;
  }
  if(aux){
    no = aux;
  }
  
  return no;
}

/**
 * Função que imprime as postagens da lista.
 * @param lista Lista cujo itens serão impressos.
 * @param idUsuario Id do usuário que solicitou a impressão.
 * @param nPostagens A quantidade de postagens que serão impressas.
 */
void imprimirPostagens(postagens_t lista, int idUsuario, int nPostagens){
  noPostagem_t *no = lista.inicio;
  int i = 0;
  printf("\n\t%d Posts\n\n", lista.tam);
  
  while(no && i < nPostagens){
    i++;
    if(tabelaHash_estaPresente(&(no->curtidas), idUsuario)){
      printf("\t%d - %s *\U0001F44D\n\n", no->idPost, no->post);
    }
    else{
      printf("\t%d - %s\n\n", no->idPost, no->post);
    }
    no = no->proximo;
  }
  printf("\n");
}

/**
 * Função que libera a memória utilizada pela lista.
 * @param lista Lista a ter a memória liberada.
 */
void liberaPostagens(postagens_t * lista) {

  noPostagem_t * atual = lista->inicio;

  while (atual != NULL) {
    noPostagem_t * tmp = atual->proximo;
    tabelaHash_finaliza(&(atual->curtidas));
    free(atual);
    atual = tmp;
  }
}