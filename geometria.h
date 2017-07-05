typedef struct ponto{
    double x;
    double y;
} ponto;

typedef struct linha{
    ponto lvert[99];     //lvert = vértices na linha.
    int lnumvert;        //lnumvert = número de vértices na linha.
} linha;

typedef struct poligono{
    ponto pvert[99];     //pvert = vértices do polígono.
    int pnumvert;        //pnumvert = numéro de vértices no polígono.
} poligono;

// Cria um ponto após receber as variáveis x e y:
void criaPonto(ponto *p, double x, double y);

// Retorna TRUE se os pontos forem idênticos:
int pontoCoincide(ponto P, ponto Q);

//Imprime o ponto p na saída padrão.
void imprimePonto(ponto P);

//Cria a linha após receber o número do vértice e o ponto.
void criaLinha(linha *l, int numVertices, ponto *vertices);

//Verifica se a linha poligonal tem interseção com o polígono:
int linhaInterceptaPoligono(linha L, poligono P);

//Verifica se a linha é simples:
int linhaSimples(linha L);

//Verifica quantas vezes uma linha cruza um polígono:
int pontoCruzaPoligono(linha L, poligono P);

//Cria um polígono após receber o número do vértice e o ponto que deseja se adicionar:
void criaPoligono(poligono *p, int numVertices, ponto *vertices);

// Verifica se o ponto está no interior do polígono:
int pontoEmPoligono(ponto P, poligono Pol);

// Verifica se o polígono é simples:
int poligonoSimples(poligono Pol);

