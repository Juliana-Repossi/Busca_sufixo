#ifndef SUFFIX_H
#define SUFFIX_H

#include <time.h>
#include "str.h"

typedef struct {
    String *s;
    int index;
} Suffix;

Suffix* create_suffix(String *s, int index);

void destroy_suffix(Suffix *suf);

void print_suffix(Suffix *suf);

Suffix** create_suf_array(String *text, int N);

void destroy_suf_array(Suffix* *a, int N);

void print_suf_array(Suffix* *a, int N);

// Compara as dois char, tirando a diferença de letra maiuscula e minuscula. Retorna:
// -1 se s1 < s2
//  1 se s1 > s2
//  0 se s1 == s2
static int compara_char (char l1 , char l2);

// Compara as dois Suffix dados. Retorna:
// <0 se s1 < s2
// >0 se s1 > s2
int compare_suffixos(const void *s1, const void *s2);

// ordenação usando quickSort
// retorna o tempo que a ordenação demorou pra ser executada
double sort_suf_array_qsort(Suffix **a, int N);

//ordenação usando insertionSort
// retorna o tempo que a ordenação demorou pra ser executada
double sort_suf_array_insort(Suffix* *a, int N);

void rank(Suffix* *a, int N, String *query);

#endif
