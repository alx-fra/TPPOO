#ifndef META1POO_COMIDA_H
#define META1POO_COMIDA_H
#include <string>
#include <sstream>
using namespace std;

class Comida {
private:
    string m_nomeComida;
    int m_pontosNutritivos;
    int m_toxicidade;
public:
    [[nodiscard]] int getMPontosNutritivos() const;

    [[maybe_unused]] Comida(string &nomeComida, int pontos, int toxicidade);

    [[nodiscard]] const string &getMNomeComida() const;

    [[nodiscard]] int getMToxicidade() const;

    [[nodiscard]] string toString() const noexcept;

    friend ostream &operator<<(ostream &os, const Comida &person);

};


#endif //META1POO_COMIDA_H
