#pragma once 

#include "posts.h"
#include "grafo.h"

#define NOME_TAMANHO_MAXIMO (30 +1)

/// <summary>
/// Estrutura com os dados de um perfil
/// </summary>
struct dadosPerfil_s {
  int idPerfil;  
  char nome[NOME_TAMANHO_MAXIMO];
  int atividade;
  postagens_t postagensPerfil;
};

/// Tipo "Dados Perfil"
typedef struct dadosPerfil_s dadosPerfil_t;

/// <summary>
/// Estrutura com a lista dos perfis existentes
/// </summary>
struct perfil_s {
  dadosPerfil_t ** perfis;
  unsigned int nPerfis;
};

/// Tipo "Lista de Perfis"
typedef struct perfil_s perfil_t;

/* Funções Exportadas */

void iniciarPerfis(perfil_t * perfis);
void alocarPerfil(perfil_t * perfis);
void registrarPerfil(perfil_t * perfis, grafo_t * grafo);
dadosPerfil_t * logarPerfil(perfil_t * perfis);
void listarUsuarios(perfil_t * perfis);
void desativarPerfil(dadosPerfil_t * perfil);
dadosPerfil_t * getPerfilById(int idPerfil, perfil_t * perfis);
void seguirPerfil(grafo_t * grafo, int idUsuarioLogado, int idPerfil);
void deixarDeSeguirPerfil(grafo_t * grafo, int idUsuarioLogado, int idPerfil);
void imprimirRelacionamentos(grafo_t * grafo, perfil_t * perfis, dadosPerfil_t * perfil, dadosPerfil_t * usuarioLogado);
void verPerfil(int idPerfil, perfil_t * perfis, dadosPerfil_t * usuarioLogado, grafo_t * grafo);
void verPerfilLogado(dadosPerfil_t * perfilLogado, perfil_t * perfis, grafo_t * grafo);

void criarPostagem(dadosPerfil_t * login);
void curtirPostagem(int idUsuario, int idPostagem, postagens_t postagens);
void descurtirPostagem(int idUsuario, int idPostagem, postagens_t postagens);
void detalharPostagem(int idPostagem, postagens_t postagens, perfil_t * perfis, int idUsuario);
void menuPostagens(postagens_t postagens, dadosPerfil_t * usuarioLogado, perfil_t * perfis);

dadosPerfil_t * menuInicial(grafo_t * grafo, perfil_t * perfis, dadosPerfil_t * login);
void menuPrincipal(grafo_t * grafo, perfil_t * perfis, dadosPerfil_t * login);

void liberarPerfis(perfil_t * perfis);
