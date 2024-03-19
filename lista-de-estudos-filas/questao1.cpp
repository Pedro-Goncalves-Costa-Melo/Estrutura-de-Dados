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
        int espia();

};


fila::fila() {
    inicio = nullptr;
    fim = nullptr;
    tam = 0;
}

fila::~fila()
{
    limpafila();
}

int fila:: espia()
{
    if (!vazia())
        return inicio->val;
    return -1; 
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

void removeItens(fila &fila1, fila &fila2)
{
    unsigned tamFila1 = fila1.tamanho();
    unsigned tamFila2 = fila2.tamanho();
    int auxVet[tamFila2];
    bool igual = false;
    fila auxFila;
    int aux=0;

    for (unsigned i = 0; i < tamFila2; i++)
    {
        auxVet[i]=fila2.desenfileira();
    }
    
    for (unsigned i = 0; i < tamFila1; i++)
    {
        igual=false;
        for (unsigned j = 0; j <tamFila2; j++)
        {
            if (auxVet[j]==fila1.espia())
            {
                igual=true;
            }
            
        }
        if (!igual)
        {
            auxFila.enfileira(fila1.desenfileira());
            aux++;

        }
        else
            fila1.desenfileira();
    }
    
    int aux2=0;
    for (int i = 0; i < aux; i++)
    {
        aux2=auxFila.desenfileira();
        fila1.enfileira(aux2);
        cout<<aux2<<" ";
    }
    cout<<endl;
    
};

int main()
{
    int tamFilas;
    cin>>tamFilas;
    fila f1;
    int valor;

    for (int i = 0; i < tamFilas; i++)
    {
        cin>>valor;
        f1.enfileira(valor);
    }
    cin>> tamFilas;
    fila f2;
    for (int i = 0; i < tamFilas; i++)
    {
        cin>>valor;
        f2.enfileira(valor);
    }
    
    removeItens(f1, f2);
}