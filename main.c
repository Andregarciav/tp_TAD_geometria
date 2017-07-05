#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include "geometria.h"

int main(int argc, char **argv){
//Declara as variáveis.
    FILE *entrada;
    char buffer[100], bufferX[100], bufferY[100], tipoTeste[100];
    double aux, auxX, auxY;      //auxX = Auxiliar X; auxY = Auxiliar Y;
    int numPontos, numVertLin, numVertPol, numLinhas, numPol, numTestes, i, j, numDoPonto, numDaLinha, numDoPoligono;
    ponto *vetPnt, *paux;       //vetPnt = vetor de pontos; paux = ponto auxiliar;
    linha *vetLinha;
    poligono *vetPol;
//Abre o arquivo:
    entrada = fopen(argv[1], "r");
    if(!entrada) printf("Erro ao abrir o arquivo.");

//Lê o arquivo e infere o número de pontos à variável numPontos:
    fscanf(entrada, "%s", buffer);
    numPontos = atoi(buffer);

//Cria o vetor de pontos:
    vetPnt = malloc(numPontos*sizeof(ponto));
    for(i=0; i<numPontos; i++){
        fscanf(entrada, "%s", bufferX);
        fscanf(entrada, "%s", bufferY);
        auxX = atof(bufferX);
        auxY = atof(bufferY);
        criaPonto(&vetPnt[i], auxX, auxY);
    }

//Lê o arquivo e infere o número de linhas:
    fscanf(entrada, "%s", buffer);
    numLinhas = atoi(buffer);

//Cria o vetor de linhas:
    vetLinha = malloc(numLinhas*sizeof(linha));
    for(j=0; j<numLinhas; j++){
        fscanf(entrada, "%s", buffer);
        numVertLin = atoi(buffer);
        paux = malloc(numVertLin*sizeof(ponto));

    //Preenche o vetor de linhas com seus devidos pontos.
        for (i=0; i<numVertLin; i++) {
            fscanf(entrada, "%s", bufferX);
            fscanf(entrada, "%s", bufferY);
            auxX = atof(bufferX);
            auxY = atof(bufferY);
            criaPonto(&paux[i], auxX, auxY);
            criaLinha(&vetLinha[j], i, &paux[i]);
        }
    }

//Lê o arquivo e infere o número de polígonos:
    fscanf(entrada, "%s", buffer);
    numPol = atoi(buffer);

//Cria o vetor de polígonos:
    vetPol = malloc(numPol*sizeof(poligono));
    for(j=0; j<numPol; j++){
        // printf("entrei  |%s %d \n" , buffer, numPol);
        fscanf(entrada, "%s", buffer);
        numVertPol = atoi(buffer);
        paux = malloc(numVertPol*sizeof(ponto));

    //Preenche o vetor de polígonos com seus devidos pontos.
        for (i=0; i<numVertPol; i++) {
            fscanf(entrada, "%s", bufferX);
            fscanf(entrada, "%s", bufferY);
            auxX = atof(bufferX);
            auxY = atof(bufferY);
            criaPonto(&paux[i], auxX, auxY);
            criaPoligono(&vetPol[j], i, &paux[i]);
        }
    }

//Lê o número de testes e coloca na variável numTestes:
    fscanf(entrada, " %s", buffer);
    numTestes = atoi(buffer);

//Inicia o procedimento de testes:
    for (i=0; i<numTestes; i++){

    //Lê o tipo de teste que deverá ser feito:
        fscanf(entrada, "%s %s", buffer, tipoTeste);

    //As próximas etapas servem para comparar a string e realizar os testes executando as funções
    //criadas na biblioteca geometria.h.

    //No caso, como o comando "strcmp" retorna 0 se as strings são iguais, é
    //necessário utilizar o operador "!" (NOT).
        if (!(strcmp(tipoTeste, "LINSIMP"))){   //LINSIMP: testa se a linha é simples.
            fscanf(entrada, "%s", buffer);      //Lê o número da linha a ser testada.
            numDaLinha = atoi(buffer);                  //Converte a string do buffer em um inteiro.
            aux = linhaSimples(vetLinha[numDaLinha]);   //Chama a função para realizar o teste.
            if (aux == 1) printf("Linha %d: simples\n", numDaLinha);
            else printf("Linha %d: não simples\n", numDaLinha);
        }
        else if (!(strcmp(tipoTeste, "LINPOL"))){       //LINPOL: testa se a linha intercepta o polígono.
            fscanf(entrada, "%s %s", bufferX,bufferY);  //Lê o número da linha e do polígono a ser testado.
            numDaLinha = atoi(bufferX);                 //Converte as variáveis strings em inteiros.
            numDoPoligono = atoi(bufferY);
            aux = linhaInterceptaPoligono(vetLinha[numDaLinha], vetPol[numDoPoligono]);     //Chama a função para realizar o teste.
            if (aux == 1) printf("Linha %d: intercepta o poligono %d\n", numDaLinha, numDoPoligono);
            else printf("Linha %d: nao intercepta o poligono %d\n", numDaLinha, numDoPoligono);
        }
        else if (!(strcmp(tipoTeste, "POLSIMP"))){      //POLSIMP: verifica se é um poligono simples.
            fscanf(entrada, "%s", buffer);              //Lê o número do polígono.
            numDoPoligono = atoi(buffer);                   //Converte a variável string em um inteiro.
            aux = poligonoSimples(vetPol[numDoPoligono]);   //Chama a função para realizar o teste.
            if (aux == 1) printf("Poligono %d: simples\n", numDoPoligono);
            else printf("Poligono %d: não simples\n", numDoPoligono);
        }
        else if (!(strcmp(tipoTeste, "PTOPOL"))){       //PTOPOL: verifica se o ponto encontra-se dentro do polígono.
            fscanf(entrada, "%s %s", bufferX,bufferY);  //Lê o número do ponto e do polígono.
            numDoPonto = atoi(bufferX);                 //Converte as variáveis string pra int.
            numDoPoligono = atoi(bufferY);
            aux = pontoEmPoligono(vetPnt[numDoPonto], vetPol[numDoPoligono]);   //Chama a função para realizar os testes.
            if (aux == 1) printf("Ponto %d: dentro do poligono %d\n", numDoPonto, numDoPoligono);
            else printf("Ponto %d: fora do poligono %d\n", numDoPonto, numDoPoligono);
        }
    //Caso ocorra algum erro:
        else printf("\nERROR!");
    }
//Fecha-se o arquivo para liberar a memória e retorna 0.
    fclose(entrada);
    return 0;
}
