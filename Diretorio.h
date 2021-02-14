#include <string>
#include <vector>
#include <iostream>
#include "Balde.h"

class Diretorio
{
private:
    int p_global, tam_balde, b_id, n_pseudochaves, n_baldes, contFC;
    float fatorCargaMedio;
    std::vector<Balde*> baldes;
    std::string toBinary(int n, int b);
    int getBaldesVazios();

public:
    Diretorio(int m, int p);
    ~Diretorio();
    bool insere(std::string pseudochave, bool reinsercao);
    void divide_balde(int b_idx);
    void duplica_diretorio();
    void show();
    float getFatorCarga();
    float getFatorCargaMedio();
    void info();

};
