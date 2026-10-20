/**
 * @file main.c
 * @brief Programa de gerenciamento da fila de venda de ingressos.
 *
 * Le um arquivo de operacoes e mantem, por meio do TAD Lista, a fila
 * unica de torcedores ordenada por prioridade de categoria.
 *
 * Uso:
 *     ./venda_ingressos <arquivo_de_entrada>
 *
 * Formato do arquivo de entrada (uma operacao por linha):
 *     i - <numero> - <categoria>    inclui um torcedor na fila
 *     e - <numero> - <categoria>    exclui (atendimento concluido)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"

/** @brief Tamanho maximo de uma linha do arquivo de entrada. */
#define MAX_LINHA 256

/**
 * @brief Verifica se uma linha contem apenas espacos em branco.
 *
 * Usada para detectar o separador de blocos de operacoes.
 *
 * @param s linha lida do arquivo de entrada
 * @return 1 se a linha for vazia ou contiver apenas espacos, 0 caso contrario
 */
static int linha_vazia(const char* s)
{
    while (*s != '\0') {
        if (!isspace((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}

/**
 * @brief Interpreta uma linha de comando e aciona a operacao no TAD.
 *
 * A leitura e feita com o formato " %c - %d - %c", cujos espacos tornam o
 * programa tolerante a variacoes de espacamento no arquivo. Linhas em
 * formato invalido geram um aviso em stderr e sao ignoradas, de modo que
 * a saida padrao permanece exatamente no formato exigido.
 *
 * @param l fila sobre a qual a operacao sera aplicada
 * @param linha linha lida do arquivo de entrada
 * @return 1 se a linha foi reconhecida e processada, 0 caso contrario
 */
static int processa_linha(Lista* l, const char* linha)
{
    char      op, simbolo;
    int       numero;
    Categoria cat;

    if (sscanf(linha, " %c - %d - %c", &op, &numero, &simbolo) != 3) {
        fprintf(stderr, "Aviso: linha ignorada (formato invalido): %s", linha);
        return 0;
    }

    cat = torc_categoria(simbolo);
    if (cat == CAT_INVALIDA) {
        fprintf(stderr, "Aviso: categoria invalida '%c' na linha: %s",
                simbolo, linha);
        return 0;
    }

    switch (toupper((unsigned char)op)) {
        case 'I':
            lst_insere(l, numero, cat);
            return 1;
        case 'E':
            lst_remove(l, numero, cat);
            return 1;
        default:
            fprintf(stderr, "Aviso: operacao desconhecida '%c' na linha: %s",
                    op, linha);
            return 0;
    }
}

/**
 * @brief Ponto de entrada do programa.
 *
 * Abre o arquivo informado na linha de comando, cria a fila, processa as
 * operacoes bloco a bloco imprimindo a lista atualizada ao fim de cada um
 * e, por fim, libera toda a memoria utilizada.
 *
 * @param argc quantidade de argumentos da linha de comando
 * @param argv vetor de argumentos; argv[1] deve conter o nome do arquivo
 *             de entrada
 * @return 0 em caso de sucesso, ou 1 se o arquivo nao puder ser aberto,
 *         se os argumentos forem invalidos ou se a fila nao puder ser criada
 */
int main(int argc, char* argv[])
{
    FILE*  arq;
    Lista* fila;
    char   linha[MAX_LINHA];
    int    pendente = 0;   /* ha operacoes nao impressas no bloco atual? */
    int    primeiro = 1;   /* controla a linha em branco entre os blocos */

    if (argc != 2) {
        fprintf(stderr, "Uso: %s <arquivo_de_entrada>\n", argv[0]);
        return 1;
    }

    arq = fopen(argv[1], "r");
    if (arq == NULL) {
        fprintf(stderr, "Erro: nao foi possivel abrir o arquivo '%s'.\n", argv[1]);
        return 1;
    }

    fila = lst_cria();
    if (fila == NULL) {
        fprintf(stderr, "Erro: falha ao criar a lista.\n");
        fclose(arq);
        return 1;
    }

    while (fgets(linha, sizeof(linha), arq) != NULL) {
        if (linha_vazia(linha)) {
            /* fim de um bloco de operacoes: imprime a lista atualizada */
            if (pendente) {
                if (!primeiro) printf("\n");
                lst_imprime(fila);
                primeiro = 0;
                pendente = 0;
            }
        } else {
            if (processa_linha(fila, linha))
                pendente = 1;
        }
    }

    /* imprime o ultimo bloco, caso o arquivo nao termine em linha em branco */
    if (pendente) {
        if (!primeiro) printf("\n");
        lst_imprime(fila);
    }

    lst_libera(fila);
    fclose(arq);
    return 0;
}
