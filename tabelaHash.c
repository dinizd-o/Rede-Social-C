/**
 * @file   tabelaHashA_LE.c
 * @brief  Implementação da tabela hash utilizando
 *         Hash Aberto e Lista Encadeada.
 */

/* Inclusões */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include "lista.h"
#include "tabelaHash.h"

/// <summary>
/// Função que inicializa uma tabela hash.
/// </summary>
/// <param name="tabHash">Endereço da tabela.</param>
/// <param name="tamanho">Tamanho da tabela.</param>
/// <param name="funcaoHash">Endereço da função de cálculo Hash.</param>
void tabelaHash_inicializa(tabelaHash_t* tabHash, uint32_t tamanho, hash_f funcaoHash) {

  uint32_t i;

  // Cria o espaço para as listas da tabela
  tabHash->tabela = malloc(sizeof(lista_t*) * tamanho);
  if (tabHash->tabela == NULL) return;

  tabHash->tamanho = tamanho;
  tabHash->funcaoHash = funcaoHash;
  tabHash->nItens = 0;

  // Cria as listas
  for (i = 0; i < tamanho; i++) {
    tabHash->tabela[i] = lista_cria();
  }
}

/// <summary>
/// Função que finaliza uma tabela hash.
/// </summary>
/// <param name="tabHash"></param>
void tabelaHash_finaliza(tabelaHash_t* tabHash) {
  
  uint32_t i;

  // Destroi as listas
  for (i = 0; i < tabHash->tamanho; i++) {
    lista_libera(tabHash->tabela[i]);
  }

  // Libera o espaço para as listas
  free(tabHash->tabela);

  tabHash->funcaoHash = NULL;
  tabHash->tabela = NULL;
  tabHash->tamanho = 0;
  tabHash->nItens = 0;
}

/// <summary>
/// 
/// </summary>
/// <param name="tabHash"></param>
/// <param name="posicao"></param>
/// <returns></returns>
static uint32_t tabelaHash_posicaoSegura(tabelaHash_t* tabHash, uint32_t posicao) {
  return posicao % tabHash->tamanho;
}

/// <summary>
/// Função que insere um item na tabela hash.
/// </summary>
/// <param name="tabHash">Endereço da tabela.</param>
/// <param name="item">Item a ser inserido.</param>
/// <returns>
/// VERDADEIRO caso o item seja inserido na tabela corretamente, ou
/// FALSO caso ele já esteja na tabela.
/// </returns>
bool_t tabelaHash_insere(tabelaHash_t* tabHash, itemTh_Id_t item){

  uint32_t posicao;
  itemLista_t* itemLista;

  // Calcula a posição onde inserir o elemento
  posicao = tabHash->funcaoHash(item);
  posicao = tabelaHash_posicaoSegura(tabHash, posicao);

  // Verifica se o item já está na lista
  // Procura na lista
  itemLista = lista_busca(tabHash->tabela[posicao], item);
  if (itemLista != NULL) return FALSO;

  // Vai na lista e insere
  lista_insereInicio(tabHash->tabela[posicao], item);

  // Se chegou até aqui é porque conseguiu inserir
  tabHash->nItens++;
  return VERDADEIRO;
}

/// <summary>
/// Função que verifica se um determinado item está presente na tabela hash.
/// </summary>
/// <param name="tabHash">Endereço da tabela.</param>
/// <param name="item">Item a ser procurado.</param>
/// <returns></returns>
bool_t tabelaHash_estaPresente(tabelaHash_t* tabHash, itemTh_Id_t item) {

  uint32_t posicao;
  itemLista_t* itemLista;

  // Calcula a posição onde inserir o elemento
  posicao = tabHash->funcaoHash(item);
  posicao = tabelaHash_posicaoSegura(tabHash, posicao);

  // Procura na lista
  itemLista = lista_busca(tabHash->tabela[posicao], item);

  // Verifica se encontrou
  return itemLista != NULL;
}

/// <summary>
/// Função que remove um item da tabela hash.
/// </summary>
/// <param name="tabHash">Endereço da tabela.</param>
/// <param name="item">Item a ser removido.</param>
/// <returns></returns>
bool_t tabelaHash_remove(tabelaHash_t* tabHash, itemTh_Id_t item) {

  uint32_t posicao;
  bool_t removeu;

  // Calcula a posição onde inserir o elemento
  posicao = tabHash->funcaoHash(item);
  posicao = tabelaHash_posicaoSegura(tabHash, posicao);

  // Tenta remover
  removeu = lista_retira(tabHash->tabela[posicao], item);
  if (removeu) tabHash->nItens--;
  return removeu;
}

/// <summary>
/// Função que imprime todos os elementos da tabela hash.
/// </summary>
/// <param name="tabHash">Endereço da tabela.</param>
void tabelaHash_imprime(tabelaHash_t* tabHash) {

  uint32_t i;

  printf("\t%"PRIu64" curtidas:\n", tabHash->nItens);

  for (i = 0; i < tabHash->tamanho; i++) {
    lista_imprime(tabHash->tabela[i]);
  }
}

/// <summary>
/// Função que retorna todos os elementos da tabela hash.
/// </summary>
/// <param name="tabHash">Endereço da tabela.</param>
int * tabelaHash_retornaElementos(tabelaHash_t* tabHash){
  
  int i, j;
  int * elementos = (int*) malloc(sizeof(int) * (tabHash->nItens + 1));
  int * elementosLista;
  elementos[0] = 0;
  
  for (i = 0; i < tabHash->tamanho; i++) {
    elementosLista = lista_retornaElementos(tabHash->tabela[i]);
    if(elementosLista[0] > 0){
      for(j = 1; j <= elementosLista[0]; j++){
        elementos[0]++;
        elementos[elementos[0]] = elementosLista[j];
      }
    }
    free(elementosLista);
  }

  return elementos;
}

uint32_t funcaoHash(int chave){
  return chave;
}