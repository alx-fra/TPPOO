#include "Especie.h"

[[maybe_unused]] Coelho::Coelho(int posX, int posY): Animal(posX, posY, "Coelho", 'C', SCoelho, 4,
                                           2, 0, -1, (float) aleatorio(1, 4), 1,
                                           0, VCoelho, 'v', -1, -1,
                                           -1, 10,
                                           8, 50, 10, 0, 0){
}

void Coelho::Atualiza(term::Terminal &t){
    if(!isMCriado())
        Reserva::atualConstAnmFich(getMId(), t);
    Animal::Atualiza(t);
    Reserva::andaC(getMId(), t);
    Reserva::reproduzC(getMId(),t);
    Reserva::comeC(getMId(),t);
    Reserva::fomeC(getMId());
    Reserva::saudeC(getMId());
    Reserva::morteC(getMId(),t);
}

[[maybe_unused]] Ovelha::Ovelha(int posX, int posY): Animal(posX, posY, "Ovelha", 'O', SOvelha, 3,
                                           1, 0, -1, (float) aleatorio(4, 8), 1,
                                           0, VOvelha, 'e', -1, -1,
                                           -1, 15,
                                           15, 100, 12, 0, 0){


}

void Ovelha::Atualiza(term::Terminal &t) {
    if(!isMCriado())
        Reserva::atualConstAnmFich(getMId(), t);
    Animal::Atualiza(t);
    Reserva::andaO(getMId(), t);
    Reserva::reproduzO(getMId(),t);
    Reserva::comeO(getMId(), t);
    Reserva::fomeO(getMId());
    Reserva::saudeO(getMId());
    Reserva::morteO(getMId(),t);
}

Lobo::Lobo(int posX, int posY): Animal(posX, posY, "Lobo",'L', SLobo,  5,
                                           1, 0, -1, 15 , 2,
                                           0, -1, 'c', 2, 0,
                                       instanteNascFilho, -1,
                                           -1, 100, 1, 10, 0){
}

void Lobo::Atualiza(term::Terminal &t) {
    if(!isMCriado())
        Reserva::atualConstAnmFich(getMId(), t);
    Animal::Atualiza(t);
    Reserva::andaL(getMId(),t);
    Reserva::reproduzL(getMId(),t);
    Reserva::comeL(getMId(),t);
    Reserva::fomeL(getMId());
    Reserva::saudeL(getMId());
    Reserva::morteL(getMId(),t);
}

[[maybe_unused]] Canguro::Canguro(int posX, int posY): Animal(posX, posY, "Canguro",'G', SCanguro, 7,
                                       1, 0, 1, 10 , 0,
                                       0, VCanguro, 'X', -1, -1,
                                       -1 , -1,
                                       30, 100, 3, 15, 5){
}

void Canguro::Atualiza(term::Terminal &t) {
    if(!isMCriado())
        Reserva::atualConstAnmFich(getMId(), t);
    Animal::Atualiza(t);
    Reserva::andaG(getMId(), t);
    //ver se está na bolsa e atualiza
    Reserva::bolsaMarsupial(getMId(),t);
    Reserva::reproduzG(getMId(),t);
    Reserva::morteG(getMId(),t);

}

Misterio::Misterio(int posX, int posY): Animal(posX, posY, "Misterio", 'M', 10, 1,
                                               1, 0, -1, 30, 1,
                                               1, 30, 'k', -1, -1,
                                               -1, -1,
                                               -1, -1, -1, 0, 0){
}

void Misterio::Atualiza(term::Terminal &t) {
    Animal::Atualiza(t);
    Reserva::andaM(getMId(), t);
    Reserva::comeM(getMId(),t);
    Reserva::morteM(getMId(), t);
}