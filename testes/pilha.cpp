#include <iostream>

using namespace std;

class Pilha
{
    private:
        int topo;
        int elementos[5];
    
    public:

        Pilha()
        {
            topo =- 1;
        }

        ~Pilha()
        {
            topo=-1;        
        }

        void push(int valor)
        {
            topo++;
            elementos[topo]=valor;
        }

        int pop()
        {
            int val = elementos[topo];
            topo--;
            return val;
        }

        void verificarTopo()
        {
            cout<<elementos[topo]<<endl;
        }
};

int main()
{
    Pilha pilha1;

    int i=0;
    int cont=0;
    while (cont<5)
    {
        cout<<endl<<"Digite um valor para inserir na pilha"<<endl;
        cin>>i;
        pilha1.push(i);
        cont++;
        cout<<"Topo da pilha: ";
        pilha1.verificarTopo(); 
    }
    

    for (int i = 0; i < 5; i++)
    {
        cout<<pilha1.pop()<<" ";
    }



    return 0;
}