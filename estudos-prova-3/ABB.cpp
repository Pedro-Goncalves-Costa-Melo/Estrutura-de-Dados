#include <iostream>

using namespace std;

class noh
{
    friend class ABB;
private:
    noh* filhoEsquerdo;
    noh* filhoDireito;
    int valor;
public:
    noh(int valor)
    {
    filhoDireito = nullptr;
    filhoEsquerdo = nullptr;
    this->valor = valor;
    }
};

class ABB
{
private:
    noh* raiz;
    void percoreEmOrdemAux(noh* atual, int nivel);
    noh* insereAux(noh* umNoh, int umValor);
    noh* buscaAux(int umValor);
    void destruirRecursivamente(noh* umNoh);
    
public:
    ABB()
    {
        raiz = nullptr;
    }
    ~ABB();
    void imprime();
    void insere(int umValor);
    int busca(int umValor);
};

ABB::~ABB()
{
    destruirRecursivamente(raiz);
}

void ABB::destruirRecursivamente(noh* umNoh)
{
    if (umNoh)
    {
        destruirRecursivamente(umNoh->filhoEsquerdo);
        destruirRecursivamente(umNoh->filhoDireito);
        delete umNoh;
    }    
}

void ABB::insere(int valor)
{
    insereAux(raiz, valor);
}

noh* ABB::insereAux(noh* umNoh, int umValor)
{
    if (umNoh==nullptr)
    {
        noh* novoNoh = new noh(umValor);
        return novoNoh;
    }
    else if (umValor < umNoh->valor)
    {
        umNoh->filhoEsquerdo = insereAux(umNoh->filhoEsquerdo, umValor);
        return umNoh;
    }
    else if (umValor >= umNoh->valor)
    {
        umNoh->filhoDireito = insereAux(umNoh->filhoDireito, umValor);
        return umNoh;
    }    
}

void ABB::imprime()
{
    percoreEmOrdemAux(raiz, 0);
}

void ABB::percoreEmOrdemAux(noh* atual, int nivel)
{
}