#include <iostream>

using namespace std;

int main()
{

    int vetor[10] = {1,2,3,4,5,6,7,8,9,0};
    int* iterador = &vetor[0];
    int* fim = &vetor[10];

    while ( iterador != fim)
    {
        cout<< iterador <<" ";
        iterador = iterador + sizeof(int);
    }
    cout<<endl;

    return 0;

}