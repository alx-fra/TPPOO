#include "Comida.h"

[[maybe_unused]] Comida::Comida(string &nomeComida, int pontos, int toxicidade): m_nomeComida(nomeComida), m_pontosNutritivos(pontos), m_toxicidade(toxicidade){
}

const string &Comida::getMNomeComida() const {
    return m_nomeComida;
}

int Comida::getMToxicidade() const {
    return m_toxicidade;
}

string Comida::toString() const noexcept {
    std::ostringstream os;
    os << "Nome comida: " << getMNomeComida();
    os << "\t" << "Pontos nutritivos: " << getMPontosNutritivos();
    os << "\t" << "Toxicidade: " << getMToxicidade();
    return os.str();
}

std::ostream &operator<<(std::ostream &os, const Comida &person) {
    return os << person.toString();
}

int Comida::getMPontosNutritivos() const {
    return m_pontosNutritivos;
}
