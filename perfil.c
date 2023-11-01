#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uteis.h"
#include "posts.h"
#include "tabelaHash.h"
#include "grafo.h"
#include "perfil.h"

#define N_CONHECIDOS 2
#define NUM_POSTAGENS 10

/// <summary>
/// Função que inicializa a lista de perfis.
/// </summary>
/// <param name="perfis">Endereço da lista de perfis.</param>
void iniciarPerfis(perfil_t * perfis){
  perfis->nPerfis = 0;
  perfis->perfis = NULL;
}

/// <summary>
/// Função que aloca memória para o perfil que está sendo registrado.
/// </summary>
/// <param name="perfis">Endereço da lista de perfis.</param>
void alocarPerfil(perfil_t * perfis){
  int nPerfis = perfis->nPerfis + 1;
  perfis->perfis = (dadosPerfil_t**) realloc(perfis->perfis, sizeof(dadosPerfil_t*) * (nPerfis));
  perfis->perfis[nPerfis-1] = malloc(sizeof(dadosPerfil_t));
}

/// <summary>
/// Função que cria o registro de um perfil.
/// </summary>
/// <param name="perfis">Endereço da lista de perfis.</param>
/// <param name="grafo">Endereço do grafo de relacionamentos.</param>
void registrarPerfil(perfil_t * perfis, grafo_t * grafo){
  char nome[NOME_TAMANHO_MAXIMO];

  printf("\nNome: ");
  fgets(nome, NOME_TAMANHO_MAXIMO, stdin);
  uteis_removeQuebraLinhaFinal(nome);

  alocarPerfil(perfis);
  
  perfis->perfis[perfis->nPerfis]->idPerfil = perfis->nPerfis;
  strcpy(perfis->perfis[perfis->nPerfis]->nome, nome);
  perfis->perfis[perfis->nPerfis]->atividade = 1;
  
  iniciarPostagens(&(perfis->perfis[perfis->nPerfis]->postagensPerfil));
  
  criarVertice(grafo, perfis->perfis[perfis->nPerfis]->idPerfil);
  
  printf("\nPerfil criado com sucesso!\nId: %d\nNome: %s\n", perfis->perfis[perfis->nPerfis]->idPerfil, perfis->perfis[perfis->nPerfis]->nome);

  perfis->nPerfis++;

}

/// <summary>
/// Função usada para logar no sistema.
/// </summary>
/// <param name="perfis">Endereço da lista de perfis.</param>
dadosPerfil_t * logarPerfil(perfil_t * perfis){
  int i, registrado, idLogin;
  char lixo;
  char busca[NOME_TAMANHO_MAXIMO];
  dadosPerfil_t * registroBusca;
    
  printf("\nInforme o nome do perfil: ");
  fgets(busca, NOME_TAMANHO_MAXIMO, stdin);
  uteis_removeQuebraLinhaFinal(busca);

  printf("\nInforme o ID do perfil: ");
  scanf("%d%c", &idLogin, &lixo);
   
  for(i = 0; i < perfis->nPerfis; i++){
    
    registrado = strcmp(busca, perfis->perfis[i]->nome);
        
    if(registrado == 0 && idLogin == perfis->perfis[i]->idPerfil){
      perfis->perfis[i]->atividade = 1;
      registroBusca = perfis->perfis[i];
      return registroBusca;
    }
  }
  
  return NULL;
}

/// <summary>
/// Função que lista todos os usuários registrados.
/// </summary>
/// <param name="perfis">Endereço da lista de perfis.</param>
void listarUsuarios(perfil_t * perfis){
  printf("\n");
  for(int i = 0; i < perfis->nPerfis; i++){
    if(perfis->perfis[i]->atividade == 1)
      printf("%d - %s\n", perfis->perfis[i]->idPerfil, perfis->perfis[i]->nome);
  }
}

/// <summary>
/// Função que desativa um perfil.
/// </summary>
/// <param name="perfil">Endereço do perfil que está sendo desativado.</param>
void desativarPerfil(dadosPerfil_t * perfil){
  int opcao;
  char lixo;
  
  printf("\nConfirmar desativação do perfil atual?\n1 - Sim\n2 - Não\n");
  scanf("%d%c", &opcao, &lixo);

  if(opcao == 1){
    perfil->atividade = 0;
  }
}

/// <summary>
/// Função que retorna os dados de um perfil através do Id.
/// </summary>
/// <param name="idPerfil">Id do perfil que está sendo procurado.</param>
/// <param name="perfis">Endereço da lista de perfis.</param>
dadosPerfil_t * getPerfilById(int idPerfil, perfil_t * perfis){
  int i;
  for(i = 0; i < perfis->nPerfis; i++){
    if(perfis->perfis[i]->idPerfil == idPerfil && perfis->perfis[i]->atividade == 1){
       return (perfis->perfis[i]);
    }
  }
  
  return NULL;
}

/// <summary>
/// Função para seguir um perfil.
/// </summary>
/// <param name="grafo">Endereço do grafo de relacionamentos.</param>
/// <param name="idUsuarioLogado">Id do usuário logado.</param>
/// <param name="idPerfil">Id do perfil seguido.</param>
void seguirPerfil(grafo_t * grafo, int idUsuarioLogado, int idPerfil){
  criarAresta(grafo, idUsuarioLogado, idPerfil);
}

/// <summary>
/// Função para deixar de seguir um perfil.
/// </summary>
/// <param name="grafo">Endereço do grafo de relacionamentos.</param>
/// <param name="idUsuarioLogado">Id do usuário logado.</param>
/// <param name="idPerfil">Id do perfil seguido.</param>
void deixarDeSeguirPerfil(grafo_t * grafo, int idUsuarioLogado, int idPerfil){
  removerAresta(grafo, idUsuarioLogado, idPerfil);
}

/// <summary>
/// Função que imprimir os relacionamentos de um perfil.
/// </summary>
/// <param name="grafo">Endereço do grafo de relacionamentos.</param>
/// <param name="perfis">Endereço da lista de perfis.</param>
/// <param name="perfil">Endereço do perfil que está sendo visualizado.</param>
void imprimirRelacionamentos(grafo_t * grafo, perfil_t * perfis, dadosPerfil_t * perfil, dadosPerfil_t * usuarioLogado){
  int *busca;
  int i;
  busca = buscaEmLargura(grafo, perfil->idPerfil);
  
  printf("\t%s está seguindo:\n", perfil->nome);
  for(i = 0; i < grafo->numVertices; i++){
    if(busca[i] > 1 && busca[i] <= N_CONHECIDOS){
      dadosPerfil_t * amigo = getPerfilById(i, perfis);
      if(amigo)
        printf("\t%d - %s\n", amigo->idPerfil, amigo->nome);
    }
  }
  free(busca); 

  int opcao, id;
  char lixo;
  do{
    printf("\nO que deseja fazer?\n0 - Voltar\n1 - Entrar em um perfil\n");
    scanf("%d%c", &opcao, &lixo);
    
    switch(opcao){
      case 1:
        printf("\nInforme o ID do perfil que deseja visualizar\n");
        scanf("%d", &id);
        if(id != usuarioLogado->idPerfil){
          verPerfil(id, perfis, usuarioLogado, grafo);
        }
        opcao = 0;
      break;
    }
  }while(opcao != 0);
}

/// <summary>
/// Função que permite ver as informações de um perfil.
/// </summary>
/// <param name="idPerfil">Id do perfil que está sendo visualizado.</param>
/// <param name="perfis">Endereço da lista de perfis.</param>
/// <param name="usuarioLogado">Endereço dos dados do perfil logado.</param>
/// <param name="grafo">Endereço do grafo de relacionamentos.</param>
void verPerfil(int idPerfil, perfil_t * perfis, dadosPerfil_t * usuarioLogado, grafo_t * grafo){
  dadosPerfil_t * perfil = getPerfilById(idPerfil, perfis);

  if(perfil){
    int opcao;
    
    do{
      if(buscaAresta(grafo, usuarioLogado->idPerfil, idPerfil)){
        printf("\n\tPerfil - %d | %s *\U0001F498\n",perfil->idPerfil ,perfil->nome);
        printf("\nO que deseja fazer nesse perfil?\n0 - Voltar\n1 - Deixar de Seguir\n2 - Postagens\n3 - Ver relacionamentos\n");
      }
      else{
        printf("\n\tPerfil - %d | %s\n",perfil->idPerfil ,perfil->nome);
        printf("\nO que deseja fazer nesse perfil?\n0 - Voltar\n1 - Seguir\n2 - Postagens\n3 - Ver relacionamentos\n");
      }
      
      scanf("%d", &opcao);
      
      switch(opcao){
        case 1:
          if(buscaAresta(grafo, usuarioLogado->idPerfil, idPerfil))
            deixarDeSeguirPerfil(grafo, usuarioLogado->idPerfil, idPerfil);
          else
            seguirPerfil(grafo, usuarioLogado->idPerfil, idPerfil);
        break;
          
        case 2:
          menuPostagens(perfil->postagensPerfil, usuarioLogado, perfis);
        break;

        case 3:
         imprimirRelacionamentos(grafo, perfis, perfil, usuarioLogado);
        break;
      }
      
    }while(opcao != 0);
  }
  else{
    printf("\nPerfil não encontrado");
  }
}

/// <summary>
/// Função que permite ver as informações do perfil logado.
/// </summary>
/// <param name="perfilLogado">Dados do perfil logado.</param>
/// <param name="perfis">Endereço da lista de perfis.</param>
/// <param name="grafo">Endereço do grafo de relacionamentos.</param>
void verPerfilLogado(dadosPerfil_t * perfilLogado, perfil_t * perfis, grafo_t * grafo){
  
  if(perfilLogado){
    char lixo;
    int opcao;
    int idPost;
    
    do{
      printf("\n\tPerfil - %d | %s\n",perfilLogado->idPerfil ,perfilLogado->nome);
      printf("\nO que deseja fazer nesse perfil?\n0 - Voltar\n1 - Ver relacionamentos\n2 - Ver postagens\n3 - Fazer Postagem\n4 - Deletar uma postagem\n");
      scanf("%d%c", &opcao, &lixo);
      switch(opcao){

        case 1: 
          imprimirRelacionamentos(grafo, perfis, perfilLogado, perfilLogado);
        break;
        
        case 2:
          menuPostagens(perfilLogado->postagensPerfil, perfilLogado, perfis);
        break;

        case 3:
          criarPostagem(perfilLogado);
        break;

        case 4:
          printf("Informe o ID do post que deseja deletar\n");
          scanf("%d", &idPost);
          removerPostagem(&(perfilLogado->postagensPerfil), idPost);
        break;
        
      }
    }while(opcao != 0);
  }
}

/// <summary>
/// Função que cria uma postagem e insere na lista.
/// </summary>
/// <param name="login">Endereço do perfil que está criando a postagem.</param>
void criarPostagem(dadosPerfil_t * login){
  char post[TAMANHO_STRING_POSTAGEM];
  
  printf("Escreva seu post:\n");
  fgets(post,TAMANHO_STRING_POSTAGEM, stdin);
  uteis_removeQuebraLinhaFinal(post);
  
  inserirPostagem(&(login->postagensPerfil), post);
}

/// <summary>
/// Função que curte uma postagem.
/// </summary>
/// <param name="idUsuario">Id do usuário que está curtindo a postagem.</param>
/// <param name="idPostagem">Id da postagem que está sendo curtida.</param>
/// <param name="postagens">Lista das postagens do perfil visualizado.</param>
void curtirPostagem(int idUsuario, int idPostagem, postagens_t postagens){
  noPostagem_t * postagem = buscarPostagem(&postagens, idPostagem);
  if(postagem){
    tabelaHash_insere(&(postagem->curtidas), idUsuario);
  }
  else{
    printf("\tPostagem não encontrada\n");
  }
}

/// <summary>
/// Função que curte uma postagem.
/// </summary>
/// <param name="idUsuario">Id do usuário que está descurtindo a postagem.</param>
/// <param name="idPostagem">Id da postagem que está sendo descurtida.</param>
/// <param name="postagens">Lista das postagens do perfil visualizado.</param>
void descurtirPostagem(int idUsuario, int idPostagem, postagens_t postagens){
  noPostagem_t * postagem = buscarPostagem(&postagens, idPostagem);
  if(postagem){
    tabelaHash_remove(&(postagem->curtidas), idUsuario);
  }
}

/// <summary>
/// Função que detalha uma postagem.
/// </summary>
/// <param name="idPostagem">Id da postagem que vai ser detalhada.</param>
/// <param name="postagens">Lista de postagens.</param>
/// <param name="idUsuario">Id do usuário que está visualizando.</param>
void detalharPostagem(int idPostagem, postagens_t postagens, perfil_t * perfis, int idUsuario){
  noPostagem_t * postagem = buscarPostagem(&postagens, idPostagem);
  
  if(postagem){
    int i;
    int * curtidas;
    
    curtidas = tabelaHash_retornaElementos(&(postagem->curtidas));
    
    if(tabelaHash_estaPresente(&(postagem->curtidas), idUsuario)){
      printf("\t%d - %s *\U0001F44D\n", postagem->idPost, postagem->post);
    }
    else{
      printf("\t%d - %s\n", postagem->idPost, postagem->post);
    }
    printf("\n\tCurtidas: %d\n", curtidas[0]);
    
    if(curtidas[0] > 0){
      for(i = 1; i <= curtidas[0]; i++){
        dadosPerfil_t * perfilCurtida;
        perfilCurtida = getPerfilById(curtidas[i], perfis);
        
        printf("\t%s\n", perfilCurtida->nome);
      }
    }
    free(curtidas);
  }
}

/// <summary>
/// Função que exibe o menu de postagens
/// </summary>
/// <param name="postagens">Lista de postagens do perfil selecionado.</param>
/// <param name="usuarioLogado">Endereço dos dados do perfil logado.</param>
/// <param name="perfis">Endereço da lista de perfis existentes.</param>
void menuPostagens(postagens_t postagens, dadosPerfil_t * usuarioLogado, perfil_t * perfis){
  int opcao;
  char lixo;
  int idPostagem;
  do{
    printf("\nO que deseja fazer nas postagens?\n0 - Voltar\n1 - Imprimir Postagens\n2 - Curtir\n3 - Descurtir\n4 - Detalhar Postagem\n");
      scanf("%d", &opcao);
    
      switch(opcao){
        case 1:
          imprimirPostagens(postagens, usuarioLogado->idPerfil, NUM_POSTAGENS);
        break;
        
        case 2:
          printf("Qual o ID da publicação que deseja curtir?\n");
          scanf("%d%c", &idPostagem, &lixo);
          curtirPostagem(usuarioLogado->idPerfil, idPostagem, postagens);
        break;
        
        case 3:
          printf("Qual o ID da publicação que deseja descurtir?\n");
          scanf("%d%c", &idPostagem, &lixo);
          descurtirPostagem(usuarioLogado->idPerfil, idPostagem, postagens);
        break;
        
        case 4:
          printf("Qual o ID da publicação que deseja detalhar?\n");
          scanf("%d%c", &idPostagem, &lixo);
          detalharPostagem(idPostagem, postagens, perfis, usuarioLogado->idPerfil);
        break;
      }
  }while(opcao != 0);
}

/// <summary>
/// Função que exibe o menu inicial.
/// </summary>
/// <param name="grafo">Endereço do grafo de relacionamentos.</param>
/// <param name="perfis">Endereço da lista de perfis.</param>
/// <param name="login">Endereço da varíavel de login.</param>
dadosPerfil_t * menuInicial(grafo_t * grafo, perfil_t * perfis, dadosPerfil_t * login){
  int selecao;
  char lixo;
  
  do{
    printf("\nO que deseja fazer?\n0 - Finalizar programa\n1 - Logar\n2 - Registrar\n");
    scanf("%d%c", &selecao, &lixo);
      
    switch(selecao){
      case 1:
        while(selecao == 1){
          login = logarPerfil(perfis);
          if(login == NULL){
            printf("\nPerfil não encontrado, o que deseja fazer?\n1 - Tentar logar novamente\n2 - Voltar à tela inicial\n");
            scanf("%d%c", &selecao, &lixo);
          }
          else{
            printf("\n\tBem vindo, %s\n", login->nome);
            return login;
          }
        }
      break;
  
      case 2:
        registrarPerfil(perfis, grafo);
      break;
    }
  }while(selecao != 0);
  
  return  NULL;
}

/// <summary>
/// Função que exibe o menu principal do perfil logado.
/// </summary>
/// <param name="grafo">Endereço do grafo de relacionamentos.</param>
/// <param name="perfis">Endereço da lista de perfis.</param>
/// <param name="login">Endereço dos dados do perfil logado.</param>
void menuPrincipal(grafo_t * grafo, perfil_t * perfis, dadosPerfil_t * login){
  int selecao;
  int id;
  char lixo;
  
  do{
    printf("\nO que deseja fazer?\n0 - Sair\n1 - Listar Usuários\n2 - Desativar Perfil\n3 - Fazer Postagem\n4 - Ver perfil\n5 - Ver próprio perfil\n");
    scanf("%d%c", &selecao, &lixo);
      
    switch(selecao){
      case 1:
        listarUsuarios(perfis);
      break;
        
      case 2:
        desativarPerfil(login);
        if(login->atividade == 0)
          selecao = 0;
      break;

      case 3:
        criarPostagem(login);
      break;

      case 4:
        printf("\nInforme o ID do perfil que deseja visualizar\n");
        scanf("%d", &id);
        if(id != login->idPerfil){
          verPerfil(id, perfis, login, grafo);
        }
      break;

      case 5:
        verPerfilLogado(login, perfis, grafo);
      break;

      case 6:
        imprimirGrafo(grafo);
      break;
    }
  }while(selecao != 0);
}

/// <summary>
/// Função que libera a memória alocada para cada perfil.
/// </summary>
/// <param name="perfis">Endereço da lista de perfis.</param>
void liberarPerfis(perfil_t * perfis){
  int i;
  for(i = 0; i < perfis->nPerfis; i++){
    liberaPostagens(&(perfis->perfis[i]->postagensPerfil));
    free(perfis->perfis[i]);
  }
  free(perfis->perfis);
}