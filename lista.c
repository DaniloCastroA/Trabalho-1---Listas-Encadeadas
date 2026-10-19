/**
 * @file lista.c
 * @brief Implementacao do TAD Lista como lista simplesmente encadeada
 *        ordenada por prioridade.
 *
 * EDA - INF1010 - PUC-Rio - Tarefa 1 (Listas encadeadas) - 2026.2
 */

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/**
 * @brief No da lista encadeada.
 *
 * Guarda os dados de um torcedor e o ponteiro para o proximo no da fila.
 */
typedef struct no {
    int        numero;   /**< Identificador do torcedor */
    Categoria  cat;      /**< Categoria (A, B ou G)     */
    struct no* prox;     /**< Proximo no da fila        */
} No;

/**
 * @brief Descritor da fila.
 *
 * Alem do ponteiro para o primeiro no, mantem contadores atualizados a
 * cada insercao e remocao, de modo que as consultas de quantidade
 * exigidas na saida custem O(1) em vez de exigir uma varredura.
 */
struct lista {
    No* prim;                    /**< Primeiro no da fila              */
    int total;                   /**< Total de torcedores na fila      */
    int qtd[NUM_CATEGORIAS];     /**< Quantidade por categoria         */
};

/**
 * @brief Cria uma fila vazia.
 *
 * @return ponteiro para a lista criada, ou NULL em caso de falha de alocacao
 */
Lista* lst_cria(void)
{
    int i;
    Lista* l = (Lista*) malloc(sizeof(Lista));
    if (l == NULL) return NULL;

    l->prim  = NULL;
    l->total = 0;
    for (i = 0; i < NUM_CATEGORIAS; i++)
        l->qtd[i] = 0;

    return l;
}

/**
 * @brief Libera toda a memoria ocupada pela fila.
 *
 * Guarda o ponteiro para o proximo no antes de liberar o atual, evitando
 * acesso a memoria ja devolvida ao sistema.
 *
 * @param l fila a ser liberada (aceita NULL)
 */
void lst_libera(Lista* l)
{
    No* p;
    if (l == NULL) return;

    p = l->prim;
    while (p != NULL) {
        No* t = p->prox;   /* guarda o proximo antes de liberar */
        free(p);
        p = t;
    }
    free(l);
}

/**
 * @brief Procura um torcedor na fila pelo seu numero.
 *
 * Funcao interna ao modulo (static), usada para impedir a insercao de
 * numeros duplicados. Nao faz parte da interface do TAD.
 *
 * @param l fila a ser percorrida
 * @param numero identificador procurado
 * @return ponteiro para o no encontrado, ou NULL se nao existir
 */
static No* busca_numero(Lista* l, int numero)
{
    No* p;
    for (p = l->prim; p != NULL; p = p->prox)
        if (p->numero == numero)
            return p;
    return NULL;
}

/**
 * @brief Insere um torcedor na posicao correta da fila.
 *
 * Percorre a lista enquanto o proximo no tiver prioridade maior ou igual
 * a do novo torcedor (cat do proximo <= cat nova) e encadeia o novo no
 * nesse ponto. Como o avanco continua enquanto as categorias sao IGUAIS,
 * o novo no entra depois de todos os seus pares, preservando a ordem de
 * chegada (FIFO) dentro do grupo. Custo: O(n).
 *
 * @param l fila na qual inserir
 * @param numero identificador do torcedor
 * @param cat categoria do torcedor
 * @return 1 em caso de sucesso, ou 0 se o torcedor ja estava na fila,
 *         se a categoria for invalida ou se houver falha de alocacao
 */
int lst_insere(Lista* l, int numero, Categoria cat)
{
    No* novo;
    No* ant;

    if (l == NULL || cat == CAT_INVALIDA) return 0;

    /* torcedor ja esta na fila: ignora para nao duplicar */
    if (busca_numero(l, numero) != NULL) {
        fprintf(stderr, "Aviso: torcedor %d ja esta na fila; insercao ignorada.\n",
                numero);
        return 0;
    }

    novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        fprintf(stderr, "Erro: falha de alocacao de memoria.\n");
        return 0;
    }
    novo->numero = numero;
    novo->cat    = cat;
    novo->prox   = NULL;

    /* Caso 1: lista vazia ou o novo tem prioridade maior que a do 1o no
       -> insercao no inicio. */
    if (l->prim == NULL || cat < l->prim->cat) {
        novo->prox = l->prim;
        l->prim    = novo;
    }
    /* Caso 2: insercao no meio ou no fim da fila. */
    else {
        ant = l->prim;
        while (ant->prox != NULL && ant->prox->cat <= cat)
            ant = ant->prox;
        novo->prox = ant->prox;
        ant->prox  = novo;
    }

    l->total++;
    l->qtd[cat]++;
    return 1;
}

/**
 * @brief Remove da fila o torcedor cujo atendimento foi concluido.
 *
 * Percorre a fila mantendo um ponteiro para o no anterior. Ao encontrar o
 * no cujo numero e categoria coincidem com os procurados, religa o
 * encadeamento, libera o no e decrementa os contadores. Custo: O(n).
 *
 * @param l fila da qual remover
 * @param numero identificador do torcedor atendido
 * @param cat categoria do torcedor atendido
 * @return 1 se o torcedor foi removido, ou 0 se nao foi encontrado
 */
int lst_remove(Lista* l, int numero, Categoria cat)
{
    No* p;
    No* ant = NULL;

    if (l == NULL || cat == CAT_INVALIDA) return 0;

    for (p = l->prim; p != NULL; ant = p, p = p->prox) {
        if (p->numero == numero && p->cat == cat) {
            if (ant == NULL) l->prim   = p->prox;  /* era o primeiro no */
            else             ant->prox = p->prox;
            free(p);
            l->total--;
            l->qtd[cat]--;
            return 1;
        }
    }

    fprintf(stderr, "Aviso: torcedor %d - %c nao encontrado na fila.\n",
            numero, torc_simbolo(cat));
    return 0;
}

/**
 * @brief Verifica se a fila esta vazia.
 *
 * @param l fila a ser consultada
 * @return 1 se a fila estiver vazia (ou for NULL), 0 caso contrario
 */
int lst_vazia(Lista* l)
{
    return (l == NULL || l->prim == NULL);
}

/**
 * @brief Informa o numero total de torcedores na fila.
 *
 * @param l fila a ser consultada
 * @return quantidade total de torcedores na fila
 */
int lst_total(Lista* l)
{
    return (l == NULL) ? 0 : l->total;
}

/**
 * @brief Informa quantos torcedores de uma dada categoria estao na fila.
 *
 * @param l fila a ser consultada
 * @param cat categoria cuja quantidade se deseja conhecer
 * @return quantidade de torcedores da categoria cat, ou 0 se cat for invalida
 */
int lst_conta(Lista* l, Categoria cat)
{
    if (l == NULL || cat == CAT_INVALIDA) return 0;
    return l->qtd[cat];
}

/**
 * @brief Imprime a fila no formato exigido pelo enunciado.
 *
 * Como a lista e mantida ordenada desde a insercao, basta uma varredura
 * linear para produzir a saida.
 *
 * @param l fila a ser impressa
 */
void lst_imprime(Lista* l)
{
    No* p;
    if (l == NULL) return;

    printf("Total: %d - A: %d - B: %d - G: %d\n",
           l->total, l->qtd[CAT_A], l->qtd[CAT_B], l->qtd[CAT_G]);

    for (p = l->prim; p != NULL; p = p->prox)
        printf("%d - %c\n", p->numero, torc_simbolo(p->cat));
}