/**
 * @file torcedor.c
 * @brief Implementacao do TAD auxiliar Categoria.
 *
 * EDA - INF1010 - PUC-Rio - Tarefa 1 (Listas encadeadas) - 2026.2
 */

#include <ctype.h>
#include "torcedor.h"

/**
 * @brief Converte o caractere lido da entrada na categoria correspondente.
 *
 * Normaliza o caractere para maiuscula antes de compara-lo, de modo que
 * tanto 'a' quanto 'A' sejam aceitos.
 *
 * @param c caractere que identifica a categoria ('A', 'B' ou 'G')
 * @return a Categoria correspondente, ou CAT_INVALIDA se o caractere
 *         nao representar uma categoria valida
 */
Categoria torc_categoria(char c)
{
    switch (toupper((unsigned char)c)) {
        case 'A': return CAT_A;
        case 'B': return CAT_B;
        case 'G': return CAT_G;
        default:  return CAT_INVALIDA;
    }
}

/**
 * @brief Converte a categoria interna no caractere usado na saida.
 *
 * @param cat categoria a ser convertida
 * @return 'A', 'B' ou 'G' conforme a categoria, ou '?' se cat for invalida
 */
char torc_simbolo(Categoria cat)
{
    switch (cat) {
        case CAT_A: return 'A';
        case CAT_B: return 'B';
        case CAT_G: return 'G';
        default:    return '?';
    }
}