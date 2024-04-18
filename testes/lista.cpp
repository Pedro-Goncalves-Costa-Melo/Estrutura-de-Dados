#include <iostream>

using namespace std;

typedef int Dado;

class noh{
    friend class lista;
    private:
        const Dado dado;
        noh* proximo;
    public:
        noh(Dado d = 0);
};

noh::noh(Dado d) : dado(d){
    proximo=nullptr;
}

class lista{
    private:
        noh* primeiro;
        noh* ultimo;
        int tamanho;
        void removeTodos();
        void ImprimeReversoAux(noh* umNoh);
    public:
        lista();
        lista(const lista& umaLista);
        ~lista();
        lista& operator=(const lista& umaLista);
        inline void insere(Dado dado);
        void insereNoFim(Dado dado);
        void insereNoInicio(Dado dado);
        void insereNaPosicao(int posicao, Dado dado);
        int procura(Dado valor);
        void imprime();
        void imprimeReverso();
        inline bool vazia();
        int removeNoFim();
        int removeNoInicio();
};

lista::lista()
{
    tamanho=0;
    primeiro=NULL;
    ultimo=nullptr;
}

//Construtor de cópia
lista::lista(const lista& umaLista)
{
    tamanho=0;
    primeiro=NULL;
    ultimo=NULL;

    noh* aux = umaLista.primeiro;

    while (aux !=NULL)
    {
        insereNoFim(aux->dado);
        aux = aux->proximo;
    }
}

lista::~lista()
{
    removeTodos();
}

void lista::removeTodos()
{
    noh*aux = primeiro;
    noh* temp;

    while (aux !=nullptr)
    {
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }
    
    tamanho=0;
    primeiro=NULL;
    ultimo=nullptr;
}

lista &lista::operator=(const lista& umaLista)
{
    removeTodos();

    noh* aux = umaLista.primeiro;

    while (aux !=nullptr)
    {
        insereNoFim(aux->dado);
        aux = aux->proximo;
    }
    
    return *this;
}

void lista::insere(Dado dado)
{
    insereNoFim(dado);
}

void lista::insereNoFim(Dado dado)
{
    noh* novo = new noh(dado);

    if (vazia())
    {
        primeiro = novo;
        ultimo = novo;
    }
    else
    {
        ultimo->proximo = novo;
        ultimo=novo;
    }
    tamanho++;
}

void lista::insereNoInicio(Dado dado)
{
    noh* novo = new noh(dado);
    if (vazia())
    {
        primeiro=novo;
        ultimo=novo;
    }
    else
    {
        novo->proximo = primeiro;
        primeiro=novo;
    }
    tamanho++;
    
}

void lista::insereNaPosicao(int posicao, Dado dado)
{
    noh* novo = new noh(dado);

    if ((posicao<=tamanho) && (posicao>=0))
    {
        if (vazia())
        {
            primeiro=novo;
            ultimo=novo;
        }
        else if (posicao==0)
        {
            novo->proximo=primeiro;
            primeiro=novo;
        }
        else if (posicao==tamanho)
        {
            ultimo->proximo=novo;
            ultimo=novo;
        }
        else
        {
            noh* aux = primeiro;
            int posAux=0;

            while (posAux < (posicao-1))
            {
                aux = aux->proximo;
                posAux++;
            }
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
    }
    else
    {
        cerr<<"POSICAO INDEVIDA"<<endl;
        exit(EXIT_FAILURE);
    }
}

int lista::procura(Dado valor)
{
    noh* aux = primeiro;
    int posAux = 0;

    while ((aux!=NULL) && (aux->dado != valor))
    {
        posAux++;
        aux = aux->proximo;
    }

    if (aux==nullptr)
        posAux=-1;
        
    return posAux;
    
    
}

void lista::imprime()
{
    noh* aux = primeiro;

    while (aux!=nullptr)
    {
        cout<<aux->dado<<" ";
        aux = aux->proximo;
    }
    cout<<endl;
}

void lista::imprimeReverso()
{
    ImprimeReversoAux(primeiro);
    cout<<endl;
}

void lista::ImprimeReversoAux(noh* umNoh)
{
    if (umNoh!=NULL)
    {
        ImprimeReversoAux(umNoh->proximo);
        cout<< umNoh->dado<<" ";
    }
    
}

inline bool lista::vazia()
{
    return tamanho==0;
}

int lista::removeNoFim()
{
    if (vazia())
    {
        cerr<<"REMOCAO EM LISTA VAZIA"<<endl;
        exit(EXIT_FAILURE);
    }
    

    int intAux = ultimo->dado;
    noh* aux = primeiro;
    noh* anterior;

    while (aux->proximo !=nullptr)
    {
        anterior=aux;
        aux=aux->proximo;
    }

    delete ultimo;
    anterior->proximo=nullptr;
    ultimo=aux;

    //importante decrementar o tamanho primeiro, porque a verificação do vazia pode usar o tamanho
    tamanho--;
    if (tamanho==0)
        primeiro=nullptr;
    
    return intAux;
    
}

int lista::removeNoInicio()
{
    if (vazia())
    {
        cerr<<"REMOCAO EM LISTA VAZIA"<<endl;
        exit(EXIT_FAILURE);
    }

    noh* aux =primeiro;
    int retorno = primeiro->dado;
    primeiro= primeiro->proximo;
    delete aux;

    //importante decrementar o tamanho primeiro, porque a verificação do vazia pode usar o tamanho
    tamanho--;
    if (vazia())
        ultimo=nullptr;
    
    return retorno;
}

int main()
{
    lista minhaLista;

    cout<<"****TESTE DA LISTA****"<<endl;
    cout<<"Quantidade de valores a inserir: ";
    int valor, num;
    cin>>num;
    cout<<endl;

    for (int i = 0; i < num; i++)
    {
        cin>>valor;
        minhaLista.insere(valor);
    }
    minhaLista.imprime();

    minhaLista.insereNoInicio(18);
    minhaLista.insereNaPosicao(3, 25);
    minhaLista.imprime();
    minhaLista.imprimeReverso();

    cout<<minhaLista.procura(0) <<endl;
    cout<<minhaLista.procura(50) <<endl;
    cout<<minhaLista.procura(12) <<endl;
    
    //construtor de cópia
    cout<<"Sobrecarga do contrutor de copia"<<endl;
    lista outraLista(minhaLista);
    outraLista.imprime();
    outraLista.imprimeReverso();

    //Sobrecarga do operadir de atribuição
    cout<<"Sobrecarga do operador de atribuicao"<<endl;
    lista maisUmaLista;
    maisUmaLista = outraLista;

    maisUmaLista.imprime();
    maisUmaLista.imprimeReverso();

    maisUmaLista.removeNoFim();
    maisUmaLista.removeNoFim();
    maisUmaLista.imprime();
    maisUmaLista.imprimeReverso();

    return 0;
}