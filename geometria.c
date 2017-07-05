#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "geometria.h"

// Cria um ponto após receber as variáveis x e y:
void criaPonto(ponto *p, double x, double y){
    (*p).x = x;
    (*p).y = y;
}

//Cria a linha após receber o número do vértice e o ponto.
void criaLinha(linha *l, int numVertices, ponto *vertices){
    criaPonto(&(*l).lvert[numVertices], (*vertices).x, (*vertices).y);
    (*l).lnumvert = numVertices + 1;    //Como o vetor de vértices começa do zero, é necessário acrescentar +1 à função
                                        //para ter o número de vértices que há na linha.
}

//Cria um polígono após receber o número do vértice e o ponto que deseja se adicionar:
void criaPoligono(poligono *p, int numVertices, ponto *vertices){
    criaPonto(&(*p).pvert[numVertices], (*vertices).x, (*vertices).y);
    (*p).pnumvert = numVertices + 1;    //Como o vetor de vértices começa do zero, é necessário acrescentar +1 à função
                                        //para ter o número de vértices que há no polígono.
}

//Verifica se a linha poligonal tem interseção com o polígono:
int linhaInterceptaPoligono(linha L, poligono P){
    double det, s, t;
    int i, j;

    for (i=0; i<L.lnumvert-1; i++){         //Primeiro laço, utilizado para comparar cada linha com os polígonos do próximo laço.
        for (j=0; j<P.pnumvert-1; j++){
            det = (P.pvert[j+1].x - P.pvert[j].x) * (L.lvert[i+1].y - L.lvert[i].y) - (P.pvert[j+1].y - P.pvert[j].y) * (L.lvert[i+1].x - L.lvert[i].x);
            s = ( (P.pvert[j+1].x - P.pvert[j].x) * (P.pvert[j].y - L.lvert[i].y) - (P.pvert[j+1].y - P.pvert[j].y) * (P.pvert[j].x - L.lvert[i].x) ) / det;
            t = ( (L.lvert[i+1].x - L.lvert[i].x) * (P.pvert[j].y - L.lvert[i].y) - (L.lvert[i+1].y - L.lvert[i].y) * (P.pvert[j].x - L.lvert[i].x) ) / det;
            if ((s < 1) && (s > 0) && (t < 1) && (t > 0)) return 1;  //Retorna TRUE se a linha intercepta o polígono.
        }
    }
    return 0;   //Retorna FALSE se a linha não intercepta o polígono.
}

//Verifica quantas vezes uma linha cruza um polígono:
int pontoCruzaPoligono(linha L, poligono P){
    double det, s, t;
    int i, j, aux = 0;

    for (i=0; i<L.lnumvert-1; i++){         //Primeiro laço, utilizado para comparar a linha criada na função pontoEmPoligono com o ponto desejado e um outro
        for (j=0; j<P.pnumvert-1; j++){     //ponto com y igual, porém x tendendo ao infinito (INT_MAX da biblioteca limits.h), com o polígono.
            det = (P.pvert[j+1].x - P.pvert[j].x) * (L.lvert[i+1].y - L.lvert[i].y) - (P.pvert[j+1].y - P.pvert[j].y) * (L.lvert[i+1].x - L.lvert[i].x);
            s = ( (P.pvert[j+1].x - P.pvert[j].x) * (P.pvert[j].y - L.lvert[i].y) - (P.pvert[j+1].y - P.pvert[j].y) * (P.pvert[j].x - L.lvert[i].x) ) / det;
            t = ( (L.lvert[i+1].x - L.lvert[i].x) * (P.pvert[j].y - L.lvert[i].y) - (L.lvert[i+1].y - L.lvert[i].y) * (P.pvert[j].x - L.lvert[i].x) ) / det;
            if ((s < 1) && (s > 0) && (t < 1) && (t > 0)) aux = aux +1;  //Adiciona 1 à variável se a linha intercepta uma linha do polígono, diferentemente
        }                                                                //das outras funções, que apenas retornam um caso a linha se intercepte.
    }
    return aux; //Retorna quantas vezes a linha intercepta as linhas do polígono.
}

//Verifica se a linha é simples:
int linhaSimples(linha L){
    double det, s, t;
    int i, j;

    for (i=0; i<L.lnumvert-2; i++){
        for (j=1; j<L.lnumvert-1; j++){
            det = (L.lvert[j+1].x - L.lvert[j].x) * (L.lvert[i+1].y - L.lvert[i].y) - (L.lvert[j+1].y - L.lvert[j].y) * (L.lvert[i+1].x - L.lvert[i].x);
            s = ( (L.lvert[j+1].x - L.lvert[j].x) * (L.lvert[j].y - L.lvert[i].y) - (L.lvert[j+1].y - L.lvert[j].y) * (L.lvert[j].x - L.lvert[i].x) ) / det;
            t = ( (L.lvert[i+1].x - L.lvert[i].x) * (L.lvert[j].y - L.lvert[i].y) - (L.lvert[i+1].y - L.lvert[i].y) * (L.lvert[j].x - L.lvert[i].x) ) / det;
            if ((s < 1) && (s > 0) && (t < 1) && (t > 0)) return 0;  //Retorna FALSE se não é uma linha simples. Ou seja, tem interceções.

        }
    }
    return 1;   //Retorna TRUE se é uma linha simples. Ou seja, sem interceções.
}

// Verifica se o ponto está no interior do polígono:
int pontoEmPoligono(ponto P, poligono Pol){
    int i, aux;
    ponto paux[1];
    linha laux;
    paux[0].x = P.x; paux[0].y = P.y;
    paux[1].x = INT_MAX; paux[1].y = P.y;
    //Aqui cria-se um outro ponto, com y igual ao ponto que deseja-se testar, porém com o x tendendo ao infinito (INT_MAX, no caso).
    for (i=0; i<2; i++)
        criaLinha(&laux, i, &paux[i]);
    aux = pontoCruzaPoligono(laux, Pol);       //Caso aux seja ímpar, significa que o ponto está dentro do polígono e
    if (aux%2 != 0) return 1;                  //retorna 1.
    else return 0;
}

// Verifica se o polígono é simples:
int poligonoSimples(poligono P){
    double det, s, t;
    int i, j;

    for (i=0; i< P.pnumvert-2; i++){            //Primeiro laço, utilizado para comparar cada linha do polígono com suas próprias linhas
        for (j=1; j<P.pnumvert-1; j++){         //representadas pelo outro laço.
            det = (P.pvert[j+1].x - P.pvert[j].x) * (P.pvert[i+1].y - P.pvert[i].y) - (P.pvert[j+1].y - P.pvert[j].y) * (P.pvert[i+1].x - P.pvert[i].x);
            s = ( (P.pvert[j+1].x - P.pvert[j].x) * (P.pvert[j].y - P.pvert[i].y) - (P.pvert[j+1].y - P.pvert[j].y) * (P.pvert[j].x - P.pvert[i].x) ) / det;
            t = ( (P.pvert[i+1].x - P.pvert[i].x) * (P.pvert[j].y - P.pvert[i].y) - (P.pvert[i+1].y - P.pvert[i].y) * (P.pvert[j].x - P.pvert[i].x) ) / det;
            if ((s < 1) && (s > 0) && (t < 1) && (t > 0)) return 0;  //Retorna FALSE se não é um polígono simples. Ou seja, tem interceções.
        }
    }
    return 1;   //Retorna TRUE se é um polígono simples. Ou seja, sem interceções.
}

//Imprime o ponto p na saída padrão.
void imprimePonto(ponto P){
    printf("\n%f", P.x);
    printf("\n%f", P.y);
}

// Retorna TRUE se os pontos forem idênticos:
int pontoCoincide(ponto P, ponto Q){
    if ((P.x == Q.x) && (P.y == Q.y)) return 1;
    else return 0;
}
