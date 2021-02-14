#include "Diretorio.h"

Diretorio::Diretorio(int m, int p)
{
    this->tam_balde = m;
    this->p_global = p;
    this->b_id = 0;
    this->n_pseudochaves = 0;
    this->n_baldes = 0;
    this->fatorCargaMedio = 0;
    this->contFC = 0;

    for(int i=0; i<(1<<p); i++) // Aloca 2^p baldes dentro do vetor de baldes
    {
        baldes.push_back(new Balde(m, p, b_id++));
        n_baldes++;
    }
}

Diretorio::~Diretorio(){}

bool Diretorio::insere(std::string pseudochave, bool reinsercao)
{
    std::string bits_esquerda = pseudochave.substr(0,p_global); //Obtem os d bits mais a esquerda da pseudochave
    int idx_dir = std::stoi(bits_esquerda, nullptr, 2); //Obtem o indice do balde onde alocar a pseudochave

   if(baldes[idx_dir]->insere(pseudochave)) //Testa se o balde está cheio
   {
       if(!reinsercao) n_pseudochaves++;
       //std::cout << "Inserindo chave " << pseudochave << " no diretorio " << idx_dir << " ! profundidade global: " << p_global
       //<< " profundidade local: " << baldes[idx_dir]->getPLocal() << "Balde: " << baldes[idx_dir]->getId() << "\n";
       //std::cout << "Inserindo chave: " << pseudochave << " fator de carga: " << getFatorCarga() << "\n";
       fatorCargaMedio +=  getFatorCarga();
       contFC++;

       return true;
   }else if(baldes[idx_dir]->getPLocal() == p_global)  //Se profundidade local = global, duplica diretorio
   {
       //std::cout << "Duplicando diretorio: " << idx_dir << " Balde: " << baldes[idx_dir]->getId() << " pseudochave: " << pseudochave << "\n ";
       //std::cout << "Fator de Carga Do diretorio antigo: " << getFatorCarga();
       duplica_diretorio();
       insere(pseudochave, false);
       return true;
   }else
   {
        //std::cout << "Dividindo balde: " << baldes[idx_dir]->getId() << " pseudochave: " << pseudochave << "\n ";
        //std::cout << "Fator de carga do balde antigo: " << baldes[idx_dir]->getFatorCarga();
        divide_balde(idx_dir);
        insere(pseudochave, false);
        //std::cout << " Fator de Carga do balde novo: " << getFatorCarga() << "\n";
        return true;
   }
}

void Diretorio::divide_balde(int b_idx)
{
    int i, dif_prof, p_local;
    dif_prof = p_global - baldes[b_idx]->getPLocal();
    p_local = baldes[b_idx]->aumentaP();
    std::vector<std::string> aux = baldes[b_idx]->getPseudochaves();

    //Procurar o primeiro indice no vetor de baldes em que aparece o balde cheio
    for(i=0; i<baldes.size(); i++){
        if(baldes[i]->getPseudochaves() == aux){
            break;
        }
    }

    baldes[b_idx]->limpa();
    baldes[i] = new Balde(tam_balde, p_local, b_id++);
    n_baldes++;

    //Fazer com que a primeira metade dos diretorios que apontam para o balde cheio, apontem para um balde novo
    for(int j=i+1; j< i+(1<<dif_prof)/2; j++){
        baldes[j] = baldes[i];
    }

    for(i=0; i<aux.size(); i++)
    {
        insere(aux[i], true); //Insere novamente as pseudochaves que estavam no balde
    }

}

void Diretorio::duplica_diretorio()
{
    p_global++;
    baldes.resize(1<<p_global, baldes[0]); //redefine o tamanho do diretorio para 2^profundidade global nova

    for(int i=baldes.size()-1; i>0; i--)
    {
        baldes[i] = baldes[i/2]; //ajusta os ponteiros do diretorio
    }
}

void Diretorio::show()
{
    std::string aux;
    std::cout << "Profundidade Global: " << p_global << " numero de diretorios: " << baldes.size() << " fator de carga: " << getFatorCarga() << std::endl;

    for(int i = 0; i < baldes.size(); i++)
    {
        aux = toBinary(i, p_global);
        std::cout << "\n" << "Diretorio " << i << " pseudochaves comecadas em " << aux <<" chaves: " << std::endl;
        baldes[i]->show(aux);
    }
}

float Diretorio::getFatorCarga()
{
    return (float) n_pseudochaves / (tam_balde*n_baldes);
}

std::string Diretorio::toBinary(int n, int b)
{
    std::string r;
    std::vector<int> aux;

    while (n != 0){
        aux.push_back(n%2);
        n /= 2;
    }

    if (aux.size() > b)
    {
        std::cout << "Número invalido" <<std::endl;
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

float Diretorio::getFatorCargaMedio()
{
    return fatorCargaMedio/contFC;
}

void Diretorio::info()
{
    std::cout << "===============================================" << std::endl;
    std::cout << "Tamanho dos diretorios: " << baldes.size() << std::endl;
    std::cout << "Numero de baldes: " << n_baldes << std::endl;
    std::cout << "Baldes vazios: " << getBaldesVazios() << std::endl;
    std::cout << "Baldes nao vazios: " << n_baldes - getBaldesVazios() << std::endl;
    std::cout << "Profundidade global: " << p_global << std::endl;
    std::cout << "Fator de carga final: " << getFatorCarga() << std::endl;
    std::cout << "Fator de carga medio durante execucao: " << getFatorCargaMedio() << std::endl;
    std::cout << "===============================================" << std::endl;

}

int Diretorio::getBaldesVazios()
{
    int cont=0;
    int aux = -1;
    for(int i=0; i<baldes.size(); i++)
    {
        if(baldes[i]->getNumPseudochaves() == 0 && baldes[i]->getId()!=aux)
        {
            cont++;
            aux = baldes[i]->getId();
        }
    }
    return cont;
}
