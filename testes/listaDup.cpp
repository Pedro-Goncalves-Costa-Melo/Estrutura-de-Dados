#include <iostream>

using namespace std;

typedef int Dado;

class noh
{
friend class listaDup;
private:
    const Dado dado;
    noh* proximo;
    noh* anterior;
public:
    noh(Dado d=0);
    ~noh();
};

noh::noh(Dado d) : dado(d)
{

    proximo=NULL;
    anterior=NULL;
}

noh::~noh()
{
}

class listaDup{
    private:
        noh* primeiro;
        noh* ultimo;
        int tamanho;
        void removeTodos();
    public:
        listaDup();
        listaDup(const listaDup& umaLista);
        ~listaDup();
        listaDup& operator=(const listaDup& umaLista);
        inline void insere(Dado dado);
        void insereNoFim(Dado dado);
        void insereNoInicio(Dado dado);
        void insereNaPosicao(int posicao, Dado dado);
        int procura(Dado valor);
        void imprime();
        inline bool vazia();
        int removeNoFim();
        int removeNoInicio();
        void removeValor(Dado dado);
};

listaDup::listaDup()
{
    tamanho=0;
    primeiro=nullptr;
    ultimo=nullptr;
}

void listaDup::insere(Dado dado)
{
    insereNoFim(dado);
}

int listaDup::removeNoInicio()
{
    if (vazia())
    {
        cerr<<"REMOCAO EM LISTA VAZIA"<<endl;
        exit(EXIT_FAILURE);
    }

    noh* aux =primeiro;
    int retorno = primeiro->dado;
    primeiro= primeiro->proximo;
    if (primeiro !=NULL)
        primeiro->anterior=nullptr;
    delete aux;

    //importante decrementar o tamanho primeiro, porque a verificação do vazia pode usar o tamanho
    tamanho--;
    if (vazia())
        ultimo=nullptr;
    
    return retorno;
}

int listaDup::removeNoFim()
{
    if (vazia())
    {
        cerr<<"REMOCAO EM LISTA VAZIA"<<endl;
        exit(EXIT_FAILURE);
    }

    noh* aux =ultimo;
    int retorno = ultimo->dado;
    ultimo = ultimo->anterior;
    if (ultimo!=nullptr)
        ultimo->proximo=NULL;
    delete aux;

    //importante decrementar o tamanho primeiro, porque a verificação do vazia pode usar o tamanho
    tamanho--;
    if (vazia())
        ultimo=nullptr;
    
    return retorno;
}

listaDup::listaDup(const listaDup& umaLista)
{
    tamanho=0;
    primeiro=nullptr;
    ultimo=nullptr;

    noh* aux = umaLista.primeiro;

    while (aux != nullptr)
    {
        insereNoFim(aux->dado);
        aux = aux->proximo;
    }
    
}

listaDup::~listaDup()
{
    removeTodos();
}

void listaDup::removeTodos()
{
    noh* aux = primeiro;
    noh*temp;
    while (aux!=nullptr)
    {
        temp=aux;
        aux = aux->proximo;
        delete temp;
    }
    
}

listaDup& listaDup::operator=(const listaDup& umaLista)
{
    removeTodos();

    noh* aux = umaLista.primeiro;

    while (aux != nullptr)
    {
        insereNoFim(aux->dado);
        aux = aux->proximo;
    }
    
    return *this;
}

void listaDup::insereNoFim(Dado dado)
{
    noh* novo = new noh(dado);

    if (vazia())
    {
        primeiro= novo;
        ultimo=novo;
    }
    else
    {
        ultimo->proximo = novo;
        novo->anterior = ultimo;
        ultimo = novo;
    }
    tamanho++;
    
}

void listaDup::insereNoInicio(Dado dado)
{
    noh* novo = new noh(dado);

    if (vazia())
    {
        primeiro = novo;;
        ultimo=novo;
    }
    else
    {
        novo->proximo=primeiro;
        primeiro->anterior=novo;
        primeiro = novo;

    }
    tamanho++;
}


void listaDup::insereNaPosicao(int posicao, Dado dado)
{
    noh* novo = new noh(dado);

    if (((posicao <=tamanho) && (posicao>=0)))
    {
        
        if(vazia())
        {
            primeiro =novo;
            ultimo=novo;
        }
        else if (posicao==0)
        {
            insereNoInicio(dado);
        }
        else if (posicao==tamanho)
        {
            insereNoFim(dado);
        }
        else
        {
            noh* aux = primeiro;
            int posAux = 0;

            while (posAux < posicao-1)
            {
                aux=aux->proximo;
                posAux++;
            }
            novo->proximo=aux->proximo;
            aux->proximo->anterior=novo;
            aux->proximo=novo;
            novo->anterior=aux;
        }
        tamanho++;
    }
    else
    {
        cerr<<"ERRO POSICAO INVALIDA!!!!!!!!!!!!!!"<<endl;
        exit(EXIT_FAILURE);
    }
}

int listaDup::procura(Dado valor)
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

void listaDup::imprime()
{
    noh* aux = primeiro;

    while (aux!=nullptr)
    {
        cout<<aux->dado<<" ";
        aux = aux->proximo;
    }
    cout<<endl;

    aux=ultimo;
    while (aux!=nullptr)
    {
        cout<<aux->dado<<" ";
        aux = aux->anterior;
    }
    cout<<endl;
}

inline bool listaDup::vazia()
{
    return tamanho==0;
}

void listaDup::removeValor(Dado valor)
{
    noh* aux = primeiro;

    while ((aux!=NULL) && (aux->dado != valor))
    {
        aux = aux->proximo;
    }

    if (aux==nullptr)
    {
        cerr<<"ERRO VALOR NAO ENCONTRADO!!!!!!!!!!!!!!"<<endl;
        exit(EXIT_FAILURE);
    }
    else{
        noh* anterior = aux->anterior;
        noh* proximo = aux->proximo;
        if(anterior!=nullptr)
            anterior->proximo = proximo;
        else
            primeiro = aux -> proximo;
        if(proximo!=nullptr)
            proximo->anterior = anterior;
        else
            ultimo =aux->anterior;
        delete aux;
    }
    tamanho--;
    if (vazia())    
    {
        primeiro=NULL;
        ultimo=nullptr;
    }
}

int main()
{
    listaDup minhaLista;

    cout<<"***** TESTE DA LISTA DUPLAMENTE ENCADEADA *****"<<endl;

    minhaLista.insere(5);
    minhaLista.insere(3);
    minhaLista.insere(1);
    minhaLista.insere(0);
    minhaLista.insere(6);
    minhaLista.insereNoInicio(18);
    minhaLista.insereNaPosicao(3, 25);
    minhaLista.imprime();

    cout<<minhaLista.procura(3) <<endl;
    cout<<minhaLista.procura(50) <<endl;
    cout<<minhaLista.procura(6) <<endl;
    
    //construtor de cópia
    cout<<"Sobrecarga do contrutor de copia"<<endl;
    listaDup outraLista(minhaLista);
    outraLista.insereNoInicio(99);
    outraLista.insereNoFim(10);

    //Sobrecarga do operadir de atribuição
    cout<<"Sobrecarga do operador de atribuicao"<<endl;
    listaDup maisUmaLista;
    maisUmaLista = outraLista;
    maisUmaLista.insereNoInicio(31);
    maisUmaLista.insereNoFim(13);

    cout<<endl;
    minhaLista.imprime();
    outraLista.imprime();
    maisUmaLista.imprime();
    
    minhaLista.removeNoFim();
    minhaLista.removeNoInicio();
    minhaLista.removeNoFim();
    minhaLista.removeNoInicio();
    minhaLista.removeNoFim();
    minhaLista.removeNoInicio();
    minhaLista.imprime();
    minhaLista.removeValor(25);
    minhaLista.imprime();

    outraLista.removeValor(10);
    outraLista.imprime();

    maisUmaLista.removeValor(31);
    maisUmaLista.imprime();
    return 0;
}

