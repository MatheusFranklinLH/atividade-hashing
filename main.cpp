#include <iostream>
#include "Diretorio.cpp"
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

std::string toBinaryString(int n, int b)
{
    std::string r;
    std::vector<int> aux;

    while (n != 0){
        aux.push_back(n%2);
        n /= 2;
    }

    if (aux.size() > b)
    {
        cout << "Número invalido" <<endl;
        return "erro";
    }
    for(int i = 0; i < b - aux.size(); i++)
    {
        r+="0";
    }

    for(int i=aux.size()-1; i>=0; i--){
        r += ( aux [i] == 0 ? "0" : "1" );
    }

    return r;
}


void inserePseudochavesAleatorias(int n, int b, Diretorio* d, int k)
{
    unsigned seed = time(0);
    srand(seed);
    int rand_num;

    for(int i=0; i < n; i++){
        rand_num = rand()% (1<<b);
        if(k) rand_num = rand_num / (1<<(b/2)); //Se k for 1, divide o número gerado por 2^(b/2) tornando a primeira metade dos bits iguais a 0
        d->insere(toBinaryString(rand_num, b), false);
    }
}


int main()
{
    int m, b, n, k;
    char imprime;

    cout << "Inserir tamanho M dos Baldes: " << endl;
    cin >> m;

    cout << "Inserir numero de bits B a ser usado nas pseudochaves: " << endl;
    cin >> b;

    cout << "Inserir numero N de pseudochaves a ser inseridas: " << endl;
    cin >> n;

    cout << "Inserir 0 para pseudochaves aleatorias ou 1 para pseudochaves com os bits iniciais iguais: " << endl;
    cin >> k;

    if(k!=0 && k!= 1 && k!=2)
    {
        k=0;
        cout << "Número inválido - inserindo pseudochaves aleatorias" << endl;
    }

    if(m <= 0 || b <=0 || n<0)
    {
        cout << "Erro - Número invalido!" << endl;
        return 0;
    }

    Diretorio d(m,1);

    cout << "Inserindo..." << endl;
    inserePseudochavesAleatorias(n, b, &d, k);


    cout << "Imprimir diretorio? (S/N) " <<endl;
    cin >> imprime;

    if(imprime == 's' || imprime == 'S') d.show();

    d.info();
    return 0;
}
