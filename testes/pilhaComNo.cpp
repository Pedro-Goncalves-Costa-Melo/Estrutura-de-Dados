#include <iostream>

using namespace std;

class No
{
    private:
        string palavra;
        int valor;

    public:
        No(int valor, string palavra)
        {
            this->palavra = palavra;
            this->valor = valor;
        }
        No()
        {
            this->palavra="";
            this->valor=0;
        }

        void defValor(int valor)
        {
            this->valor=valor;
        }

        void defPalavra(string palavra)
        {
            this->palavra=palavra;
        }

        int getValor()
        {
            return this->valor;
        }

        string getPalavra()
        {
            return this->palavra;
        }
};

class Pilha
{
    private:
        int topo;
        int tamanho;
        No nos[5];

    public:
        Pilha()
        {
            topo=-1;
            tamanho=0;
        };


};

int main()
{
}