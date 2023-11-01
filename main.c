#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uteis.h"
#include "tabelaHash.h"
#include "grafo.h"
#include "posts.h"
#include "perfil.h"

#define SUCESSO 0

int main(int argc, char * argv[]){

  int selecao = 1;
  char lixo;
  
  ///Criação da lista de perfis
  perfil_t perfis;
  iniciarPerfis(&perfis);

  ///Variável usada para manter os dados de um perfil logado
  dadosPerfil_t * login;

  ///Criação do grafo de relacionamentos
  grafo_t grafo;
  inicializaGrafo(&grafo);
  
  while(selecao != 0){
    login = menuInicial(&grafo, &perfis, login);
    if(login != NULL)
      menuPrincipal(&grafo, &perfis, login);
    else
      selecao = 0;
  }

  liberarPerfis(&perfis);
  
  return SUCESSO;
}