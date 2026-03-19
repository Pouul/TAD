#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "poli.h"

int square(int base, int expoente){
    if(expoente == 0){return 1;}
    
    int resultado = 1;    
    for(int i = 0; i <= expoente ; i++){
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
    
    for(int i = 0; i <= p->grau; i++){
        if(p->coeficientes[i] == 0){
            continue;
        }
        resultado += p->coeficientes[p->grau-i]*square(x, p->grau-i);
    }
    
    return resultado;
}

polinomio * poli_soma(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que soma dois polinomios e gera um terceiro
    int maiorGrau = 0;
    polinomio *pq;
    if (p->grau > q->grau){
        pq = poli_create(p->grau);
        maiorGrau = p->grau;
    }
    else{
        pq = poli_create(q->grau);
        maiorGrau = q->grau;
    }
    for (int i = 0; i < maiorGrau; i++)
    {
        if (!(i > p->grau) ){
            if(!(p->coeficientes[i] == 0)){
                pq->coeficientes[i] += p->coeficientes[i];
            }
        }
        if (!(i > q->grau) ){
            if(!(q->coeficientes[i] == 0)){
                pq->coeficientes[i] += q->coeficientes[i];
            }
        }
    }
    
    return pq;
}

polinomio * poli_mult(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que multiplica dois polinomios e gera um terceiro
    int multiploGrau = 0;
    polinomio *pq;
    multiploGrau = p->grau + q->grau;
    pq = poli_create(multiploGrau);
    
    for (int i = 0; i < p->grau; i++)
    {
        for (int j = 0; j < q->grau; j++)
        {
            pq->coeficientes[i+j] += p->coeficientes[i]*q->coeficientes[j];
        }
        
    }
    
    return pq;
}

polinomio * poli_div(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que divide dois polinomios e gera um terceiro
    int grau_d = p->grau - q->grau;
    polinomio *d = poli_create(grau_d);
    polinomio *aux = p;
    while (grau_d >= 0) {
        int parcial = aux->coeficientes[aux->grau]/q->coeficientes[q->grau];
        poli_ins_termo(d, grau_d, parcial);
        for (int i = 0; i < grau_d; i++) {
            poli_ins_termo(aux, grau_d - i, aux->coeficientes[aux->grau - i - 1] - (q->coeficientes[q->grau - i] * parcial));
        }
        grau_d--;
    }

    return d;
}


