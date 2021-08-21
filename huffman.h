#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <locale.h>

#define TAM 256

typedef struct no
{
    unsigned char caracter;
    int freq;
    struct no *esq, *dir, *prox;
} No;

typedef struct
{
    No *inicio;
    int tam;
} Lista;

/* Inicializa a tabela com valores 0 */
void inicializarTabFreq(int *tab);

/* Preenche a tabela com a frequencia dos caracteres da frase */
void preencherTabFreq(char *texto, int *tab);

/* Imprime a tabela com a frequencia dos caracteres */
void imprimirTabFreq(int *tab);

/* Cria a lista encadeada */
void criarLista(Lista *lista);

/* Verifica se a lista está vazia */
int vazia(Lista *lista);

/* Insere um elemento ordenadamente na lista */
void inserirOrdenado(Lista *lista, No *elem);

/* Preenche a lista encadeada com os caracteres com frequencia crescente */
void preencherLista( int *tab, Lista *lista);

/* Imprime a lista encadeada */
void imprimirLista(Lista *lista);

/* Remove um elemento do começo da lista */
No *removerNoInicio(Lista *lista);

/* Monta a árvore de Huffman */
No *montarArvore(Lista *lista);

/* Verifica se um nó é uma folha */
int ehFolha(No *raiz);

/* Imprime a árvore de Huffman e a altura de cada caracter da frase */
void imprimirArvore(No *raiz, int altura);

/* Retorna a altura da árvore */
int alturaArvore(No *raiz);

/* Aloca dinamicamente uma matriz de strings */
char **alocarDicionario(int colunas);

/* Gera o dicionário percorrendo a árvore e gerando os códigos binários de cara caracter */
void gerarDicionario(char **dicionario, No *raiz, char *codigo, int colunas);

/* Imprime o dicionário com os códigos de cada caracter */
void imprimirDicionario(char **dicionario);

/* Retorna o texto codificado, os bits de todos os caracteres */
char *codificarTexto( char *texto, char **dicionario);

/* Imprime o texto codificado */
void imprimirTextoCodificado(char *textocodificado);

/* Decodifica e imprime o texto, voltando ao original */
void decodificarTexto(char *textoCodificado, No *raiz);
