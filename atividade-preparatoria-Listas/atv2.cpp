/* 
 * Classe listadup, uma lista dinamicamente duplamente encadeada
 * 
 * by Joukim, 2017-2019, Estruturas de Dados
 * alterado em 2023 by Renato
 */

#include <iostream>
#include <cstdlib>

using namespace std;

struct acaoPrograma{
    int identificador;
    string nomeAcao;
    int tempoExecucao; 
    int tempoConsumido;
};


class noh {
friend class listadup;
private: 
    acaoPrograma acao; // poderia ser outro tipo de variável
    noh* proximo;
    noh* anterior;
public:
    //noh();
    noh(acaoPrograma d);
};

// construindo dado chamando seu construtor
noh::noh(acaoPrograma d){
    acao = d;
    proximo = NULL;
    anterior = NULL;
}


// lista dinamicamente encadeada
class listadup {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista    
public:
    listadup();
    listadup(const listadup& umaLista);
    ~listadup();
    // sobrecarga do operador de atribuição
    listadup& operator=(const listadup& umaLista);  
    // inserção, remoção e procura
    void insereNoFim(acaoPrograma acao);
    void insereNoInicio(acaoPrograma acao);
    void insereNaPosicao(int posicao, acaoPrograma acao);
    int procura(string valor); // retorna a posicao
    void imprime();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
};


// constrói uma lista inicialmente vazia
listadup::listadup() {
    tamanho=0;
    primeiro=nullptr;
    ultimo=nullptr;
}

// construtor de cópia
listadup::listadup(const listadup& umaLista) {
    tamanho=0;
    primeiro=nullptr;
    ultimo=nullptr;

    noh* aux = umaLista.primeiro;

    while (aux != nullptr)
    {
        insereNoFim(aux->acao);
        aux = aux->proximo;
    }
    
}

// destrutor da lista (chama função privada auxiliar)
listadup::~listadup( ) {
    removeTodos();
}    

// remove todos os elementos da lista
void listadup::removeTodos( ) {

    noh* aux = primeiro;
    noh* temp;
    while (aux!=nullptr)
    {
        temp=aux;
        aux = aux->proximo;
        delete temp;
    }
    
}    

// sobrecarga do operador de atribuição
listadup& listadup::operator=(const listadup& umaLista){
    // limpa a lista atual
    removeTodos();
     // percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umaLista.primeiro;
    
    while (aux != NULL) {
        insereNoFim(aux->acao);
        aux = aux->proximo;  
    }
    
    return *this; 
}  

// insere por no final da lista
void listadup::insereNoFim(acaoPrograma acao) {

    noh* novo = new noh(acao);

    if (vazia())
    {
        primeiro=novo;
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

// insere no início da lista
void listadup::insereNoInicio(acaoPrograma acao) {
 
    noh* novo = new noh(acao);

    if (vazia())
    {
        primeiro=novo;
        ultimo = novo;
    }
    else
    {
        novo->proximo = primeiro;
        primeiro->anterior=novo;
        primeiro = novo;
    }
    tamanho++;
}

// insere em uma determinada posição da lista
void listadup::insereNaPosicao(int posicao, acaoPrograma acao){
    
    noh* novo = new noh(acao);

    if ((posicao <= tamanho) && (posicao>=0))
    {
        if (vazia())
        {
            primeiro = novo;
            ultimo = novo;
        }
        else if (posicao==0)
        {
            insereNoInicio(acao);
        }
        else if (posicao==tamanho)
        {
            insereNoFim(acao);
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
            novo->proximo = aux->proximo;
            aux->proximo->anterior = novo;
            aux->proximo = novo;
            novo->anterior = aux;
        }
        
        
    }
    
}
                   

int listadup::procura(string valor) {

}

// método básico que *percorre* uma lista, imprimindo seus elementos
void listadup::imprime() {
   
}

// verifica se a lista está vazia
inline bool listadup::vazia() {

}

void listadup::removeNoInicio() {

}


void listadup::removeNoFim() {

}


int main() {
    listadup minhaLista;
    acaoPrograma info;
    char comando;
    int posicao;
    string nomeEquipe;

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaLista.insereNoInicio(info);
                    break;
                case 'h': // inserir
                    cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaLista.insereNoFim(info);
                    break;             
                case 'm': // inserir
                    cin >> posicao;
                    cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaLista.insereNaPosicao(posicao,info);
                    break;             
                case 's': // procurar
                    cin >> nomeEquipe;
                    posicao = minhaLista.procura(nomeEquipe);
                    if(posicao == -1)
                        cout << "Nao encontrado"<< endl;
                    else
                        cout << posicao << endl;
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
