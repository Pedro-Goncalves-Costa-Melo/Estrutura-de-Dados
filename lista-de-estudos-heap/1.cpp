/*
    Implemente uma classe MinHeap que tem um construtor que recebe um vetor de elementos. Durante a criação do MinHeap, alguns elementos deverão ser reposicionados para que passem a ter as propriedades de um min heap. O construtor (ou método usado no construtor) deverá escrever passo a passo como fica o armazenamento após a correção descendo de cada posição.

Note que não é para escrever os valores do heap após cada troca, os valores do heap devem ser escritos após todas as trocas (zero ou mais) realizadas para a correção de uma posição.

Implemente a função principal que cria um heap a partir do vetor.

Entradas:

A quantidade de elementos a serem lidos.
Os elementos (números inteiros) a serem armazenados no heap.
Saídas:

Para cada posição a ser corrigida:

A posição, seguida de dois pontos;
Todos os elementos armazenados após a reorganização iniciada na posição em questão.
Note a ausência de espaço antes do dois pontos e a presença do espaço depois, como em qualquer sinal de pontuação.

Exemplo de Entrada:

6
9 8 7 5 -1 -3
Exemplo de Saída:

2: 9 8 -3 5 -1 7 
1: 9 -1 -3 5 8 7 
0: -3 -1 7 5 8 9
*/

#include<iostream>
#include<cstring>

using namespace std;

class Heap
{
private:
    int tamanho;
    int capacidade;
    int* dados;
    void Arruma();
    void CorrigeDescendo(int i);
    void Imprime();

    int Pai(int i)
    {
        return ((i-1)/2);
    }
    int Esquerda(int i)
    {
        return (i*2 + 1);
    }
    int Direita(int i)
    {
        return (i*2 + 2);
    }
public:
    Heap(int tam, int vet[]);
    ~Heap();
    
};

Heap::Heap(int tam, int vet[])
{
    dados = new int[tam];
    memcpy(dados, vet, tam * sizeof(int));
    tamanho = tam;
    Arruma();
}

Heap::~Heap()
{
    delete[] dados;
}

void Heap:: Arruma()
{
    for (int i = (tamanho/2-1); i >= 0; i--)
    {
        CorrigeDescendo(i);
        cout<<i<<": ";
        Imprime();
    }
    
}

void Heap:: CorrigeDescendo(int i)
{
    int esq = Esquerda(i);
    int dir = Direita(i);
    int menor = i;

    if (esq < tamanho && dados[esq] < dados[menor])
    {
        menor=esq;
    }
    
    if (dir<tamanho && dados[dir] < dados[menor])
    {
        menor = dir;
    }
    
    if (menor!=i)
    {
        swap(dados[menor], dados[i]);
        CorrigeDescendo(menor);
    }
    
}

void Heap::Imprime()
{
    for (int i = 0; i < tamanho; i++)
    {
        cout<<dados[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    int tam;
    cin>>tam;
    int vet[tam];
    for (int i = 0; i < tam; i++)
    {
        cin>>vet[i];
    }
    
    Heap *heap = new Heap(tam, vet);

    delete[] heap;
    return 0;
}
