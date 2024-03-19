#include <iostream>

using namespace std;

class no
{
    friend class pilha;
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

class pilha
{
    private:
        no* topo;
        unsigned tam;
    public:
        pilha();
        ~pilha();
        unsigned tamanho();
        void empilha (int valor);
        int desempilha();
        void limpaPilha();
        bool vazia();

};

pilha:: pilha()
{
    topo = nullptr;
    tam=0;
}

pilha::~pilha()
{
    limpaPilha();
}

void pilha::limpaPilha()
{
    while (!vazia())
    {
        desempilha();
    }
    
}

unsigned pilha:: tamanho()
{
    return tam;
}

void pilha:: empilha(int valor)
{
    no* novo = new no(valor);
    novo->proximo = topo;
    topo = novo;
    tam++;
}

int pilha::desempilha()
{
    int valor = topo-> val;
    no* temp = topo;
    topo = topo->proximo;
    delete temp;
    tam--;

    return valor;
}

bool pilha:: vazia()
{
    return (topo==NULL);
}

int main()
{
    pilha p1;
    int num;
    cin>>num;

    while (num>=0)  
    {
        p1.empilha(num);
        cin>> num;
    }

    cout<< p1.tamanho()<< endl;

    while ( !p1.vazia() )
    {
        cout<<p1.desempilha()<<" ";
    }
    cout<<endl;
    
    
    return 0;
}