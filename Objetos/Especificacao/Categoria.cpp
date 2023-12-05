#include "Categoria.h"
#include "../../Visual/Reserva.h"

Relva::Relva(int posX, int posY): Alimento(posX, posY, "Relva", 'r', VRelva,
                                           3, 0, "erva", "verdura") {
}

void Relva::Atualiza(term::Terminal &t) {
    if(!isMCriado())
        Reserva::atualConstAlmFich(getMId(), t);
    Alimento::Atualiza(t);
    Reserva::desaparece(getMId(),t);
    Reserva::reproduzr(getMId(), t);
}

[[maybe_unused]] Cenoura::Cenoura(int posX, int posY): Alimento(posX, posY, "Cenoura", 't', VCenoura,
                                               4, 0, "verdura", "") {
}

void Cenoura::Atualiza(term::Terminal &t) {
    Alimento::Atualiza(t);
    Reserva::toxicidadet(getMId(),t);
}

[[maybe_unused]] Corpo::Corpo(int posX, int posY): Alimento(posX, posY, "Corpo", 'p', VCorpo,
                                           10, 0, "carne", "") {
}

void Corpo::Atualiza(term::Terminal &t) {
    Alimento::Atualiza(t);
    Reserva::vnutritivop(getMId(),t);
}

[[maybe_unused]]  Bife::Bife(int posX, int posY): Alimento(posX, posY, "Bife", 'b', VBife,
                                         10, 2, "carne", "ketchup") {
}

void Bife::Atualiza(term::Terminal &t) {
    if(!isMCriado())
        Reserva::atualConstAlmFich(getMId(), t);
    Alimento::Atualiza(t);
    Reserva::desaparece(getMId(),t);
    Reserva::vnutritivob(getMId(),t);
}

[[maybe_unused]]  AlimMisterio::AlimMisterio(int posX, int posY): Alimento(posX, posY, "Alimento-misterio", 'k', 20,
                                                         1, 3, "ketchup", "ketchup") {
}

void AlimMisterio::Atualiza(term::Terminal &t) {
    Alimento::Atualiza(t);
    Reserva::desaparece(getMId(),t);
}
