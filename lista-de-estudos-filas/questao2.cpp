/*
Filas podem ser implementadas com armazenamento de dados em vetor, se a capacidade fixa não for um problema. Nesse caso, é importante controlar os índices para "dar a volta" no vetor sempre que for necessário. Uma fila assim pode ser chamada de fila circular.

Faça a implementação de uma fila circular fazendo com que a inserção (método Enfileirar) sempre use o início do vetor (posição zero) quando a fila estiver vazia.

Entradas:

Inicialmente, o programa lê um número inteiro que é capacidade da fila a ser criada.

Depois, o programa lê códigos de comandos a executar. Sempre um caractere identificando o comando seguido dos parâmetros necessários para executar o comando, se houverem. Os códigos de comandos são:

t - para terminar a execução do programa
e - para enfileirar um valor - seguido do valor (número inteiro)
d - para desenfileirar um valor
i - para escrever as informações da fila (atributos e conteúdo)
Saídas:

Os comandos d e i são os únicos que produzem saída de dados. Cada um pode ser observado no exemplo.

Exemplo de Entrada e Saída juntos:

3
e 1
e 2
e 3
i
tamanho=3 capacidade=3 inicio=0 fim=2
1 2 3 
d
1
e 4
i
tamanho=3 capacidade=3 inicio=1 fim=0
2 3 4
d
2
d
3
i
tamanho=1 capacidade=3 inicio=0 fim=0
4
t*/

#include <iostream>

using namespace std;

class fila
{
private:
    int tamanho;
    int inicio;
    int fim;
    int capacidade;
    int *vet;
public:
    fila(int capacidade);
    ~fila();
    int espiar();
    int getTamanho();
    int getInicio();
    int getFim();
    int getCapacidade();
    void printFila();

    bool vazia()
    {
        return (tamanho==0);
    }

    bool cheia()
    {
        return(tamanho==capacidade);
    }

    void enfileira(int valor)
    {
        if (cheia())
        {
            cout<<"Fila cheia. Nao e possivel enfileirar"<<endl;
            return;
        }
        
        if (vazia())
            inicio++;

        fim = ((fim+1) % capacidade);
        vet[fim]=valor;
        tamanho++;
    }

    int desenfileira()
    {
        if (vazia())
        {
            cout<<"Fila vazia. Nao e possivel desenfileirar"<<endl;
            return -1;
        }

        int aux = vet[inicio];

        if (inicio==fim)
        {
            fim=-1;
            inicio=-1;
        }
        else
            inicio = ((inicio + 1) % capacidade);
        tamanho--;
        
        return aux;
        
    }

};


fila::fila(int capacidade)
{
    inicio=-1;
    fim=-1;
    this->capacidade=capacidade;
    vet = new int[this->capacidade];
    tamanho=0;
}

fila::~fila()
{
    delete[] vet;
}

void fila::printFila()
{
    int i=inicio;
    do {
        cout << vet[i] << " ";
        i = (i + 1) % capacidade;
    } while (i != (fim + 1) % capacidade);

    cout << endl;
}

int fila::espiar()
{
    if(!vazia())
        return vet[inicio];
    return -1;
}

int fila::getTamanho()
{
    return tamanho;
}

int fila::getCapacidade()
{
    return capacidade;
}

int fila::getFim()
{
    return fim;
}

int fila::getInicio()
{
    return inicio;
}

int main()
{
    int capacidade;
    cin>>capacidade;
    fila f1(capacidade);

    char comando = 'a';

    while (comando!='t')
    {
        cin>>comando;
        switch (comando)
        {
        case 'e':
            int valor;
            cin>>valor;
            f1.enfileira(valor);
            break;
        case 'd':
            cout<<f1.desenfileira()<<endl;
            break;
        case 'i':
            cout<<"tamanho="<<f1.getTamanho()<<" capacidade="<<f1.getCapacidade()<<" inicio="<<f1.getInicio()<<" fim="<<f1.getFim()<<endl;
            f1.printFila();
            break;
        default:
            break;
        }
    }
    
    

    return 0;
}

