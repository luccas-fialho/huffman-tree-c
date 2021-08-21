#include "huffman.h"

void inicializarTabFreq(int *tab)
{
    for (int i = 0; i < TAM; i++)
        tab[i] = 0;
}

void preencherTabFreq(char *texto, int *tab)
{
    for (int i = 0; texto[i] != '\0'; i++)
        tab[texto[i]]++;
}

void imprimirTabFreq(int *tab)
{
    printf("\tTabela de frequência\n");
    for (int i = 0; i < TAM; i++)
    {
        if (tab[i] > 0)
            printf("\t%3d = %u = %c\n", i, tab[i], i);
    }
}

void criarLista(Lista *lista)
{
    lista->inicio = NULL;
    lista->tam = 0;
}

int vazia(Lista *lista)
{
    return (lista->inicio == NULL);
}

void inserirOrdenado(Lista *lista, No *elem)
{
    // A lista está vazia?
    if (vazia(lista))
    {
        lista->inicio = elem;
    }
    // Tem frequencia menor que o inicio da lista?
    else if (elem->freq < lista->inicio->freq)
    {
        elem->prox = lista->inicio;
        lista->inicio = elem;
    }
    else
    {
        No *aux = lista->inicio;
        while (aux->prox && aux->prox->freq <= elem->freq)
            aux = aux->prox;
        elem->prox = aux->prox;
        aux->prox = elem;
    }
    lista->tam++;
}

void preencherLista(int *tab, Lista *lista)
{
    No *novo = NULL;
    for (int i = 0; i < TAM; i++)
    {
        if (tab[i] > 0)
        {
            novo = (No *)malloc(sizeof(No));
            if (novo)
            {
                novo->caracter = i;
                novo->freq = tab[i];
                novo->dir = NULL;
                novo->esq = NULL;
                novo->prox = NULL;
                inserirOrdenado(lista, novo);
            }
            else
            {
                printf("\tErro ao alocar memória em preencherLista\n");
                break;
            }
        }
    }
}

void imprimirLista(Lista *lista)
{
    No *aux = lista->inicio;
    printf("\n\tLista ordenada: Tamanho: %d\n", lista->tam);
    while (aux)
    {
        printf("\tCaracter: %c Frequência: %d\n", aux->caracter, aux->freq);
        aux = aux->prox;
    }
}

No *removerNoInicio(Lista *lista)
{
    No *aux = NULL;
    if (!vazia(lista))
    {
        aux = lista->inicio;
        lista->inicio = aux->prox;
        aux->prox = NULL;
        lista->tam--;
    }
    return aux;
}

No *montarArvore(Lista *lista)
{
    No *prim = NULL;
    No *seg = NULL;
    No *novo = NULL;
    while (lista->tam > 1)
    {
        prim = removerNoInicio(lista);
        seg = removerNoInicio(lista);
        novo = (No *)malloc(sizeof(No));
        if (novo)
        {
            novo->caracter = '+';
            novo->freq = prim->freq + seg->freq;
            novo->esq = prim;
            novo->dir = seg;
            novo->prox = NULL;
            inserirOrdenado(lista, novo);
        }
        else
        {
            printf("\n\tErro ao alocar memória em montarArvore\n");
            return NULL;
        }
    }
    return lista->inicio;
}

int ehFolha(No *raiz)
{
    return (raiz->esq == NULL && raiz->dir == NULL);
}

void imprimirArvore(No *raiz, int altura)
{
    if (ehFolha(raiz))
    {
        printf("\tFolha: %c com altura: %d\n", raiz->caracter, altura);
    }
    else
    {
        imprimirArvore(raiz->esq, altura + 1);
        imprimirArvore(raiz->dir, altura + 1);
    }
}

int alturaArvore(No *raiz)
{
    if (raiz == NULL)
    {
        return -1;
    }
    else
    {
        int esq = alturaArvore(raiz->esq);
        int dir = alturaArvore(raiz->dir);
        if (esq > dir)
            return esq + 1;
        else
            return dir + 1;
    }
}

char **alocarDicionario(int colunas)
{
    char **dicionario;
    dicionario = (char **)malloc(TAM * sizeof(char *));
    for (int i = 0; i < TAM; i++)
        dicionario[i] = (char *)calloc(colunas, sizeof(char)); // Aloca memória, limpa ela e retorna o ponteiro p regiao de memoria.
    return dicionario;
}

void gerarDicionario(char **dicionario, No *raiz, char *codigo, int colunas)
{
    char *esq = (char *)malloc(colunas * sizeof(char));
    char *dir = (char *)malloc(colunas * sizeof(char));

    if (ehFolha(raiz))
    {
        strcpy(dicionario[raiz->caracter], codigo);
    }
    else
    {
        strcpy(esq, codigo);
        strcpy(dir, codigo);

        strcat(esq, "0");
        strcat(dir, "1");

        gerarDicionario(dicionario, raiz->esq, esq, colunas);
        gerarDicionario(dicionario, raiz->dir, dir, colunas);
    }
    free(esq);
    free(dir);
}

void imprimirDicionario(char **dicionario)
{
    printf("\n\tDicionario:\n");
    for (int i = 0; i < TAM; i++)
        if (strlen(dicionario[i]) > 0)
            printf("\t%3d: %c: %s\n", i, i, dicionario[i]);
}

char *codificarTexto(char *texto, char **dicionario)
{
    char *textocodificado = (char *)calloc(0, sizeof(char));
    printf("\n");
    for (int i = 0; texto[i] != '\0'; i++)
    {
        strcat(textocodificado, dicionario[texto[i]]);
    }
    return textocodificado;
}

void imprimirTextoCodificado(char *textocodificado)
{
    printf("\tO TEXTO CODIFICADO FICA: %s\n\n", textocodificado);
}

void decodificarTexto(char *textoCodificado, No *raiz)
{
    No *aux = raiz;
    int tamanho = strlen(textoCodificado) + 1;
    printf("\tTEXTO DECODIFICADO: ");
    for (int i = 0; i < tamanho; i++)
    {
        if (ehFolha(aux))
        {
            printf("%c", aux->caracter);
            aux = raiz;
        }
        if (textoCodificado[i] == '1')
        {
            aux = aux->dir;
        }
        if (textoCodificado[i] == '0')
        {
            aux = aux->esq;
        }
    }
    printf("\n\n");
}
