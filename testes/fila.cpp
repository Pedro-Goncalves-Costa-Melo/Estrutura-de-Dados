#include <iostream>

using namespace std;

class no
{
    friend class fila;
    private:
        int val;
        no* proximo;
    public:
        no(int valor);
};

no::no(int valor)
{
    val = valor;
    proximo = NULL;
}

class fila
{
    private:
        no* inicio;
        no* fim;
        unsigned tam;
    public:
        fila();
        ~fila();
        unsigned tamanho();
        void enfileira (int valor);
        int desenfileira();
        void limpafila();
        bool vazia();

};

fila:: fila()
{
    inicio = nullptr;
    fim = nullptr;
    tam=0;
}

fila::~fila()
{
    limpafila();
}

void fila::limpafila()
{
    while (!vazia())
    {
        desenfileira();
    }
    
}

unsigned fila:: tamanho()
{
    return tam;
}

void fila:: enfileira(int valor)
{
    no* novo = new no(valor);
    if (tam==0)
    {
        inicio = novo;
    }
    else
    {
        fim->proximo = novo;
    }
    fim = novo;
    tam++;
}

int fila::desenfileira()
{
    int valor = inicio->val;
    no* temp = inicio;
    inicio = inicio->proximo;
    delete temp;
    tam--;

    if (tam==0)
        fim=nullptr;
        
    return valor;
}

bool fila:: vazia()
{
    return (inicio==NULL);
}

int main()
{
    fila f1;
    int num;
    cin>>num;

    while (num>=0)  
    {
        f1.enfileira(num);
        cin>> num;
    }

    cout<< f1.tamanho()<< endl;

    while ( !f1.vazia() )
    {
        cout<<f1.desenfileira()<<" ";
    }
    cout<<endl;
    
    
    return 0;
}