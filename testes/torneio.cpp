#include <iostream>
#include <cstring>

using namespace std;

const int INVALIDO = -1;

class Torneio
{
private:
    int* dados;
    int capacidade;
    int inicioDados;
    int tamanho;
    int pai(int i);
    int esquerda(int i);
    int direita(int i);
    void arruma();
    void copiaMaior(int i);
    void copiaSubindo(int i);
public:
    Torneio(int numFolhas);
    Torneio(int tamVet, int vet[]);
    ~Torneio();
    void insere(int valor);
    void imprime();
    
};

Torneio::Torneio(int tam, int vet[])
{
    capacidade=1;
    while (capacidade<tam)
        capacidade*=2;
    
    capacidade=capacidade-1 + tam;

    dados = new int[capacidade];
    inicioDados = capacidade - tam;

    cout<<"inicio dados: "<<inicioDados<<endl;
    cout<<"capacidade: "<<capacidade<<endl;

    memcpy(&dados[inicioDados], vet, tam*sizeof(int));

    tamanho=tam;
    arruma();
}

Torneio::Torneio(int numFolhas)
{
    capacidade=1;
    while(capacidade<numFolhas)
        capacidade*=2;

    capacidade = capacidade-1 + numFolhas
}

Torneio::~Torneio()
{
    delete[] dados;
}

void Torneio::arruma()
{
    cout<<"arruma: "<<inicioDados -1 << endl;
    for (int i = inicioDados - 1; i >= 0; i--)
    {
        copiaMaior(i);
    }
    
}

int Torneio::pai(int i)
{
    return ((i-1)/2);
}

//Retorna a posição do 1° Nó filho de i
int Torneio::esquerda(int i)
{
    return (i*2 + 1);
}

//Retorna a posição do 2° Nó filho de i
int Torneio::direita(int i)
{
    return (i*2 + 2);
}

void Torneio::copiaMaior(int i)
{
    int esq = esquerda(i);
    int dir = direita(i);

    cout<<"i: "<< i << " e: " << esq << " d: " << dir << endl;
    int maior = INVALIDO;
    if (esq<capacidade)
    {
        if ((dir<capacidade) && (dados[dir] > dados[esq]))
            maior=dir;
        else
            maior = esq;

        dados[i] = dados[maior];        
    }
    else
        dados[i]=INVALIDO;
    
}

int main()
{
    return 0;
}