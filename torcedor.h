/**
 * @file torcedor.h
 * @brief TAD auxiliar que representa a categoria de um torcedor.
 *
 * Define o tipo Categoria e as conversoes entre o simbolo lido do
 * arquivo de entrada ('A', 'B' ou 'G') e a representacao interna
 * utilizada pelo TAD Lista.
 *
 */

#ifndef TORCEDOR_H
#define TORCEDOR_H

/**
 * @brief Categorias de torcedor, ordenadas pela prioridade de atendimento.
 *
 * Os valores numericos sao atribuidos de forma crescente conforme a
 * prioridade DECRESCE. Assim, "ter prioridade maior" equivale a "ter
 * valor numerico menor", e toda a ordenacao da fila se reduz a uma
 * comparacao de inteiros.
 */
typedef enum {
    CAT_A = 0,        /**< Socio Torcedor A - maior prioridade        */
    CAT_B = 1,        /**< Socio Torcedor B - prioridade intermediaria */
    CAT_G = 2,        /**< Venda Geral      - menor prioridade        */
    CAT_INVALIDA = 3  /**< Valor sentinela para erro de leitura       */
} Categoria;

/** @brief Quantidade de categorias validas (A, B e G). */
#define NUM_CATEGORIAS 3

/**
 * @brief Converte o caractere lido da entrada na categoria correspondente.
 *
 * Aceita tanto maiusculas quanto minusculas.
 *
 * @param c caractere que identifica a categoria ('A', 'B' ou 'G')
 * @return a Categoria correspondente, ou CAT_INVALIDA se o caractere
 *         nao representar uma categoria valida
 */
Categoria torc_categoria(char c);

/**
 * @brief Converte a categoria interna no caractere usado na saida.
 *
 * @param cat categoria a ser convertida
 * @return 'A', 'B' ou 'G' conforme a categoria, ou '?' se cat for invalida
 */
char torc_simbolo(Categoria cat);

#endif /* TORCEDOR_H */
