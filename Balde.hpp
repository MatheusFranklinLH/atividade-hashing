#ifndef BALDE_H_INCLUDED
#define BALDE_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>

class Balde
{
    private:

        int tam, p_local, id;
        std::vector<std::string> pseudochaves;

    public:

        Balde(int m, int b, int b_id);
        ~Balde();
        int getTam();
        int getPLocal();
        int getId();
        std::vector<std::string> getPseudochaves();
        bool insere(std::string pseudochave);
        void limpa();
        int aumentaP();
        void show(std::string prefixo);
        float getFatorCarga();
        int getNumPseudochaves();
};

#endif