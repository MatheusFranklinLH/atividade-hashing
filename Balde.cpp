#include "Balde.hpp"

Balde::Balde(int m, int d, int b_id)
{
    this->tam = m;
    this->p_local = d;
    this->id = b_id;
}

Balde::~Balde() {}

int Balde::getTam()
{
    return tam;
}

int Balde::getPLocal()
{
    return p_local;
}

int Balde::getId()
{
    return id;
}

std::vector<std::string> Balde::getPseudochaves()
{
    return pseudochaves;
}

bool Balde::insere(std::string pseudochave)
{
    if(pseudochaves.size()<tam)
    {
        pseudochaves.push_back(pseudochave);
        return true;
    }
    return false;

}

void Balde::limpa()
{
    pseudochaves.clear();
}

int Balde::aumentaP()
{
    p_local++;
    return p_local;
}

void Balde::show(std::string prefixo)
{
    prefixo.resize(p_local);
    std::cout << "Balde: " << id << " chaves comecadas em " << prefixo <<" profundidade local: " << p_local << " fator de carga: " << getFatorCarga() <<"\n";

    for(int i=0; i<pseudochaves.size(); i++)
    {
        std::cout << pseudochaves[i] << " ";
    }
    std::cout << "\n";
}

float Balde::getFatorCarga()
{
    return (float) pseudochaves.size()/tam;
}

int Balde::getNumPseudochaves()
{
    return pseudochaves.size();
}
