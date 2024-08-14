/* 
 * Classe lista, uma lista dinamicamente encadeada
 * 
 * by Joukim, 2017-2019, Estruturas de Dados
 * alterado em 2023 by Renato
 * alterado em 2024 by Pedro
 */

#include <iostream>
#include <cstdlib>

using namespace std;


struct equipe{
    string nomeEquipe;
    string lider;
    string linguagem; 
    int qtdMembros;
};

class noh {
friend class lista;
private:
    equipe elenco; // poderia ser outro tipo de variável
    noh* proximo;
public:
    //noh();
    noh(equipe d);
};

// construindo time chamando seu construtor
noh::noh(equipe d){
    elenco = d;
    proximo = NULL;
}


// lista dinamicamente encadeada
class lista {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista
     // imprime reverso a partir de um nó -> exemplo de uso de recursão
    void imprimeReversoAux(noh* umNoh);
public:
    // construtores e destrutor
    lista();
    lista(const lista& umaLista);
    ~lista();
    // sobrecarga do operador de atribuição
    lista& operator=(const lista& umaLista);  
    // inserção, remoção e procura
    inline void insere(equipe elenco);
    void insereNoFim(equipe elenco);
    void insereNoInicio(equipe elenco);
    int procura(string valor); // retorna a posição do nó com va
    // métodos adicionais (impressão, vazia)
    void imprime();
    void imprimeReverso();
    inline bool vazia();
    equipe removeNoFim();
    equipe removeNoInicio();
    void removePorNome(string valor, lista& l1);
};

void lista:: removePorNome(string valor, lista& l1)
{
    if (vazia()) {
        throw runtime_error("Remoção em lista vazia!");
    }

    bool encontrou = false;
    lista listaAux;
    while (!l1.vazia())
    {
        //cout<<"entrou primeiro while ";
        if (l1.primeiro->elenco.lider!=valor)
        {
            //cout<<"entrou if ";
            listaAux.insereNoFim(l1.removeNoInicio());
        }
        else
        {
            l1.removeNoInicio();
            encontrou=true;
            // cout<<"entrou else ";
        }
    }
    //cout<<endl;
    while (!listaAux.vazia())
    {
        //cout<<"entrou segundo while"<<endl;
        l1.insereNoFim(listaAux.removeNoInicio());
    }
    if (!encontrou)
    {
        cout<<"Nao encontrado"<<endl;
    }
}

// constrói uma lista inicialmente vazia
lista::lista() 
{
    tamanho=0;
    primeiro=nullptr;
    ultimo=nullptr;
}

// construtor de cópia
lista::lista(const lista& umaLista) 
{
    tamanho=0;
    primeiro=nullptr;
    ultimo=nullptr;

    noh* aux = umaLista.primeiro;

    while (aux !=nullptr)
    {
        insereNoFim(aux->elenco);
        aux = aux -> proximo;
    }
    
}

// destrutor da lista (chama função privada auxiliar)
lista::~lista( ) {
    removeTodos();
}    

// remove todos os elementos da lista
void lista::removeTodos( ) {

    noh* aux = primeiro;
    noh* temp;

    while (aux !=nullptr)
    {
        temp=aux;
        aux=aux->proximo;
        delete temp;
    }
    
    tamanho=0;
    primeiro=nullptr;
    ultimo=nullptr;

}    

// sobrecarga do operador de atribuição
lista& lista::operator=(const lista& umaLista){
    // limpa a lista atual
    removeTodos();
     // percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umaLista.primeiro;
    
    while (aux != NULL) {
        insereNoFim(aux->elenco);
        aux = aux->proximo;  
    }
    
    return *this; 
}  

// insere no final da lista
void lista::insereNoFim(equipe elenco) {

    noh* novo = new noh(elenco);

    if (vazia())
    {
        primeiro = novo;
        ultimo = novo;
    }
    else
    {
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}

// insere no início da lista
void lista::insereNoInicio(equipe elenco) 
{
    noh* novo = new noh(elenco);
    if (vazia())
    {
        primeiro=novo;
        ultimo=novo;
    }
    else
    {
        novo->proximo=primeiro;
        primeiro=novo;
    }
    tamanho++;
}

//procura a posição de um determinado elemento
int lista::procura(string valor) {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    } 
    noh* aux = primeiro;
    int posAux = 0;

    while ((aux!=nullptr) && (aux->elenco.nomeEquipe != valor))
    {
        posAux++;
        aux = aux->proximo;
    }
    
    if (aux==nullptr)
    {
        posAux=-1;
    }
    return posAux;
}


// método básico que *percorre* uma lista, imprimindo seus elementos
// poderia percorrer fazendo outra ação (multiplicando valores, por exemplo)
void lista::imprime() {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    } 

    noh* aux = primeiro;

    while (aux!=nullptr)
    {
        cout<< "(" <<aux->elenco.nomeEquipe<< ", " <<aux->elenco.lider<<", "<<aux->elenco.linguagem<<", "<<aux->elenco.qtdMembros<<")"<<endl;
        aux=aux->proximo;
    }
    
    cout<<"IMPRIMINDO REVERSO"<<endl;


}

// verifica se a lista está vazia
inline bool lista::vazia() {
    return (tamanho==0);
}
   
equipe lista::removeNoFim() {

    if (vazia()) {
        throw runtime_error("Remoção em lista vazia!");
    } 

    noh* aux = primeiro;
    noh* anterior;
    equipe auxEquipe = ultimo->elenco;

    while (aux->proximo !=nullptr)
    {
        anterior=aux;
        aux=aux->proximo;
    }
    
    delete ultimo;
    anterior->proximo=nullptr;
    ultimo=aux;

    tamanho--;
    if (tamanho==0)
    {
        primeiro = nullptr; 
    }

    return auxEquipe;
}
    
equipe lista::removeNoInicio() {
    if (vazia()) {
        throw runtime_error("Remoção em lista vazia!");
    } 
    noh* aux = primeiro;
    equipe auxEquipe = primeiro->elenco;
    primeiro = primeiro->proximo;
    delete aux;

    tamanho--;
    if (vazia())
    {
        ultimo=nullptr;
    }
    return auxEquipe;
}

int main() {
    lista minhaLista;
    equipe info;
    char comando;
    int posicao;
    string nomeEquipe;

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoInicio(info);
                    break;
                case 'h': // inserir
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoFim(info);
                    break;             
                case 'm': // inserir
                    cin >> posicao;
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    cout<<"Operação não permitida!"<<endl;
                    break;             
                case 's': // remover
                    cin >> nomeEquipe;
                    if (minhaLista.procura(nomeEquipe) !=-1)
                        cout<< minhaLista.procura(nomeEquipe)<<endl;
                    else
                        cout<<"Nao encontrado"<<endl;
                    break;                    
                case 'r': // remover
                    minhaLista.removeNoInicio();
                    break;
                case 'a': // remover
                    minhaLista.removeNoFim();
                    break;                                   
                case 'p': // limpar tudo
                    minhaLista.imprime();
                    break;
                case 'x':
                    cin>>nomeEquipe;
                    minhaLista.removePorNome(nomeEquipe, minhaLista);
                    break;
                case 'f': // finalizar
                    // checado no do-while
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    cout << endl;
    return 0;
}
