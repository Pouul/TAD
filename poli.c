#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "poli.h"

int square(int base, int expoente){
    if(expoente == 0){return 1;}
    
    int resultado = 1;    
    for(int i = 0; i < expoente ; i++){
        resultado *= base;
    }
    return resultado;
}

polinomio * poli_create(int grau){
    // TODO: Implemente aqui a solucao para operacao create
    polinomio *p = (polinomio *) malloc(sizeof(polinomio));
    p->coeficientes = calloc(grau + 1, sizeof(int));
    p->grau = grau;
    p->termos = 0;
    return p;
}

void poli_destroy(polinomio **p){
    // TODO: Implemente aqui a solucao para operacao destroy
    *p = NULL;
    return;
}

int poli_ins_termo(polinomio *p, int exp, int coef) {
    // TODO: Implemente aqui a solucao para operacao insere coeficiente
    if (exp < 0 || exp > p->grau) return 0;
    if (coef != 0 && p->coeficientes[exp] == 0) p->termos++;
    p->coeficientes[exp] = coef;
    return 1;
}

int poli_get_termo(polinomio *p, int exp, int *coef){
    // TODO: Implemente aqui a solucao para operacao get coeficiente
    if (exp < 0 || exp > p->grau || p->coeficientes[exp] == 0) return 0;
    *coef = p->coeficientes[exp];
    return 1;
}

int calcula_px(polinomio *p, int x){
    int resultado = 0;
    
    for(int i = p->grau; i >= 0; i--){
        if(p->coeficientes[i] == 0){
            continue;
        }
        resultado += p->coeficientes[i] * square(x, i);
    }
    
    return resultado;
}

polinomio * poli_soma(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que soma dois polinomios e gera um terceiro
    int maiorGrau;
    polinomio *menor, *maior;
    polinomio *pq;
    if (p->grau > q->grau) {
        pq = poli_create(p->grau);
        maior = p;
        menor = q;
    } else {
        pq = poli_create(q->grau);
        maior = q;
        menor = p;
    }
    maiorGrau = pq->grau;

    for (int i = maiorGrau; i >= 0; i--) {
        if (i > menor->grau) {
            pq->coeficientes[i] = maior->coeficientes[i];
        } else {
            pq->coeficientes[i] = maior->coeficientes[i] + menor->coeficientes[i];
        }
    }
    
    return pq;
}

polinomio * poli_mult(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que multiplica dois polinomios e gera um terceiro
    polinomio *pq;
    int multiploGrau = p->grau + q->grau;
    pq = poli_create(multiploGrau);
    
    for (int i = p->grau; i >= 0; i--)
    {
        for (int j = q->grau; j >= 0; j--)
        {
            pq->coeficientes[i+j] += p->coeficientes[i]*q->coeficientes[j];
        }
        
    }
    
    return pq;
}

polinomio * poli_div(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que divide dois polinomios e gera um terceiro
    int grau_d = p->grau - q->grau;
    // Cira o polinomio resultante já com o grau correto
    polinomio *d = poli_create(grau_d);
    // Cria um polinomio auxiliar que muda a cada divisao feita, tambem é possivel retornar o resto caso fosse desejado
    polinomio *aux = p;
    // Loop para fazer as divisoes
    while (grau_d >= 0) {
        // Calcula coeficiente do grau "grau_d" do polinomio resultado e insere no d
        int parcial = aux->coeficientes[aux->grau]/q->coeficientes[q->grau];
        poli_ins_termo(d, grau_d, parcial);
        // Loop para preencher o polinomio auxiliar para a proxima divisao
        for (int i = 0; i < grau_d; i++) {
            poli_ins_termo(aux, grau_d - i, aux->coeficientes[aux->grau - i - 1] - (q->coeficientes[q->grau - i] * parcial));
        }
        // Atualiza o indices dos polinomios manipulados
        grau_d--;
        aux->grau--;
    }

    return d;
}


