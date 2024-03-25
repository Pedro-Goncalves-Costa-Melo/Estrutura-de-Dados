#include <iostream>
#include <cstring>

using namespace std;

class Heap
{
private:
    int capacidade;
    int* dados;
    int tamanho;
    int pai(int i);
    int esquerda(int i);
    int direita(int i);
    void arruma();
    void corrigeDescendo(int i);
    void corrigeSubindo(int i);
public:
    Heap(int capacidade);
    Heap(int tamVet, int vet[]);
    ~Heap();
    int espiaRaiz();
    int tiraRaiz();
    void insere(int valor);
    void imprime();
    
};

Heap::Heap(int tamVet, int vet[])
{
    dados = new int[tamVet];
    //Copia pela função memcpy da biblioteca <cstring>
    memcpy(dados, vet, tamVet * sizeof(int));
    //For equivalente 
    // for (int i = 0; i < tamVet; i++)
    // {
    //     dados[i]=vet[i];
    // }
    tamanho = tamVet;
    arruma();
    
}

Heap::Heap(int capacidade)
{
    this -> dados = new int[capacidade];
    this->capacidade=capacidade;
    tamanho=0;
}

Heap::~Heap()
{
    delete[] dados;
}

void Heap::imprime()
{
    for (int i = 0; i < tamanho; i++)
    {
        cout<<dados[i]<<" ";
    }
    cout<<endl;
}

void Heap::arruma()
{
    for (int i = (tamanho/2-1); i >= 0; i--)
        corrigeDescendo(i);   
}

int Heap::pai(int i)
{
    return ((i-1)/2);
}

//Retorna a posição do 1° Nó filho de i
int Heap::esquerda(int i)
{
    return (i*2 + 1);
}

//Retorna a posição do 2° Nó filho de i
int Heap::direita(int i)
{
    return (i*2 + 2);
}

void Heap::corrigeDescendo(int i)
{
    int esq = esquerda(i);
    int dir = direita(i);
    int maior = i;

    if (esq < tamanho && dados[esq] > dados[maior])
    {
        maior = esq;
    }

    if (dir < tamanho && dados[dir] > dados[maior])
    {
        maior = dir;
    }

    if (maior!=i)
    {
        swap(dados[i], dados[maior]);
        corrigeDescendo(maior);
    }
}

int Heap::tiraRaiz()
{
    if (tamanho==0)
    {
        cerr << "Erro ao retirar raiz. O Heap esta vazio" << endl;
        exit(EXIT_FAILURE);
    }

    int aux = dados[0];
    swap(dados[0], dados[tamanho-1]);
    tamanho--;
    corrigeDescendo(0);
    return aux;
    
}

void Heap::insere(int valor)
{   
    if (tamanho==capacidade)
    {
        cerr << "Erro ao inserir dado. Heap cheio" <<endl;
        exit(EXIT_FAILURE);
    }
    
    tamanho++;
    dados[tamanho-1] = valor;
    corrigeSubindo(tamanho-1);
    
}

void Heap::corrigeSubindo(int i)
{
    int p = pai(i);
    if (dados[i] > dados[p])
    {
        swap(dados[p], dados[i]);
        corrigeSubindo(p);
    }
    
}

int Heap::espiaRaiz()
{
    return dados[0];
}

int main()
{
    int tam = 13;
    int vet[] = {50,2,90,20,230,43,8,34,66,100,110,3,13};

    Heap *heap = new Heap (tam, vet);

    for (int i = 0; i < tam; i++)
    {
        cout<<heap->tiraRaiz()<< " : ";
        heap->imprime();
    }
    cout<<endl;

    for (int i = 0; i < tam; i++)
    {
        heap->insere(vet[i]);
    }
    
    for (int i = 0; i < tam; i++)
    {
        cout<<heap->tiraRaiz()<< " : ";
    }
    cout<<endl;

    delete heap;
    return 0;
}