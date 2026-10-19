/**
 * @file lista.h
 * @brief TAD Lista: fila unica de torcedores em lista encadeada.
 *
 * A fila e implementada como uma lista simplesmente encadeada mantida
 * permanentemente ordenada por prioridade de categoria (A > B > G) e,
 * dentro de uma mesma categoria, pela ordem de chegada (FIFO).
 *
 * A estrutura interna (struct lista) e opaca: o cliente do TAD enxerga
 * apenas o ponteiro Lista* e as operacoes declaradas neste arquivo.
 *
 * EDA - INF1010 - PUC-Rio - Tarefa 1 (Listas encadeadas) - 2026.2
 */

#ifndef LISTA_H
#define LISTA_H

#include "torcedor.h"

/** @brief Tipo abstrato da fila de torcedores (implementacao em lista.c). */
typedef struct lista Lista;

/**
 * @brief Cria uma fila vazia.
 *
 * Aloca o descritor da lista e zera o ponteiro para o primeiro no e
 * todos os contadores.
 *
 * @return ponteiro para a lista criada, ou NULL em caso de falha de alocacao
 */
Lista* lst_cria(void);

/**
 * @brief Libera toda a memoria ocupada pela fila.
 *
 * Percorre a lista liberando cada no e, ao final, libera o descritor.
 * Aceita NULL, caso em que nao faz nada.
 *
 * @param l fila a ser liberada
 */
void lst_libera(Lista* l);

/**
 * @brief Insere um torcedor na posicao correta da fila.
 *
 * O novo torcedor e colocado depois de todos os torcedores de prioridade
 * maior ou igual a sua e antes de todos os de prioridade menor. Entre
 * torcedores de mesma categoria a ordem de chegada (FIFO) e preservada.
 * Insercoes com numero ja existente na fila sao recusadas.
 * Custo: O(n).
 *
 * @param l fila na qual inserir
 * @param numero identificador do torcedor
 * @param cat categoria do torcedor
 * @return 1 em caso de sucesso, ou 0 se o torcedor ja estava na fila,
 *         se a categoria for invalida ou se houver falha de alocacao
 */
int lst_insere(Lista* l, int numero, Categoria cat);

/**
 * @brief Remove da fila o torcedor cujo atendimento foi concluido.
 *
 * A remocao nao depende de ordenacao: o torcedor e localizado por
 * (numero, categoria) e pode estar em qualquer posicao da fila, nao
 * apenas no inicio. Custo: O(n).
 *
 * @param l fila da qual remover
 * @param numero identificador do torcedor atendido
 * @param cat categoria do torcedor atendido
 * @return 1 se o torcedor foi removido, ou 0 se nao foi encontrado
 */
int lst_remove(Lista* l, int numero, Categoria cat);

/**
 * @brief Verifica se a fila esta vazia.
 *
 * @param l fila a ser consultada
 * @return 1 se a fila estiver vazia (ou for NULL), 0 caso contrario
 */
int lst_vazia(Lista* l);

/**
 * @brief Informa o numero total de torcedores na fila.
 *
 * O total e mantido em um contador atualizado a cada insercao e remocao,
 * de modo que a consulta custa O(1).
 *
 * @param l fila a ser consultada
 * @return quantidade total de torcedores na fila
 */
int lst_total(Lista* l);

/**
 * @brief Informa quantos torcedores de uma dada categoria estao na fila.
 *
 * Os contadores por categoria sao mantidos nas insercoes e remocoes,
 * de modo que a consulta custa O(1).
 *
 * @param l fila a ser consultada
 * @param cat categoria cuja quantidade se deseja conhecer
 * @return quantidade de torcedores da categoria cat, ou 0 se cat for invalida
 */
int lst_conta(Lista* l, Categoria cat);

/**
 * @brief Imprime a fila no formato exigido pelo enunciado.
 *
 * Escreve em stdout uma linha de cabecalho com os totais, seguida de uma
 * linha por torcedor na ordem da fila:
 *
 *     Total: 7 - A: 3 - B: 2 - G: 2
 *     1 - A
 *     3 - A
 *     ...
 *
 * @param l fila a ser impressa
 */
void lst_imprime(Lista* l);

#endif /* LISTA_H */