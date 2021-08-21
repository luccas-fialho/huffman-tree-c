/* 
    UNIVERSIDADE TECNOLÓGICA FEDERAL DO PARANÁ
    DISCIPLINA: ESTRUTURA DE DADOS 2
    TRABALHO REALIZADO POR: LUCCAS FIALHO DOS SANTOS
*/

#include "huffman.h"

int main()
{
    char *texto = "Trabalho de estrutura de dados 2";
    int tabelaFreq[TAM];
    Lista lista;
    No *arvore;
    int altura;
    char **dicionario;
    char *textocodificado;

    setlocale(LC_ALL, "Portuguese");

    /* TABELA DE FREQUENCIA */
    inicializarTabFreq(tabelaFreq);
    preencherTabFreq(texto, tabelaFreq);
    imprimirTabFreq(tabelaFreq);

    /* LISTA ENCADEADA ORDENADA */
    criarLista(&lista);
    preencherLista(tabelaFreq, &lista);
    imprimirLista(&lista);

    /* MONTAR A ÁRVORE DE HUFFMAN */
    arvore = montarArvore(&lista);
    printf("\n\tÁrvore de Huffman\n");
    imprimirArvore(arvore, 0);

    /* GERAR A TABELA DE CÓDIGOS */
    altura = alturaArvore(arvore) + 1;
    dicionario = alocarDicionario(altura);
    gerarDicionario(dicionario, arvore, "", altura);
    imprimirDicionario(dicionario);

    /* CODIFICAR */
    textocodificado = codificarTexto(texto, dicionario);
    imprimirTextoCodificado(textocodificado);

    /* DECODIFICAR */
    decodificarTexto(textocodificado, arvore);

    /* APRESENTANDO RESULTADOS */
    printf("\tRESULTADOS:\n");
    int tamReal = strlen(texto) * 8;
    printf("\tTamanho do texto descompactado: %d bits ou %.0f Bytes.\n", tamReal, round((float)tamReal / 8.0));

    int tamDescompactado = strlen(textocodificado);
    printf("\tTamanho do texto compactado: %d bits ou %.0f Bytes.\n", tamDescompactado, round((float)tamDescompactado / 8.0));

    float porcentagem = 100.0 - ((float)(tamDescompactado * 100) / (float)tamReal);
    printf("\tTexto comprimido em aproximadamente: %.0f%%\n\n", round(porcentagem));

    /* DESALOCAR MEMÓRIA */
    /* free(lista);
    free(arvore);
    free(dicionario);
    free(textocodificado); */

    return 0;
}
