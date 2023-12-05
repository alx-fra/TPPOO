#ifndef META2POO_ESPECIE_H
#define META2POO_ESPECIE_H


#include "../../Visual/Reserva.h"

#include "../../helpers.h"

static int instanteNascFilho = aleatorio(5, VLobo);

class Coelho : public Animal{
public:
    [[maybe_unused]] Coelho(int posX,int posY);

    void Atualiza(term::Terminal &t) override;
};
typedef Coelho Coe;

class Ovelha : public Animal{
public:
    [[maybe_unused]] Ovelha(int posX,int posY);

    void Atualiza(term::Terminal &t) override;
};
typedef Ovelha Ove;

class Lobo : public Animal{
public:
    Lobo(int posX,int posY);

    void Atualiza(term::Terminal &t) override;
};
typedef Lobo Lob;

class Canguro : public Animal{
public:
    [[maybe_unused]] Canguro(int posX,int posY);

    void Atualiza(term::Terminal &t) override;
};
typedef Canguro Cang;

class Misterio : public Animal{
public:
    Misterio(int posX,int posY);

    void Atualiza(term::Terminal &t) override;
};
typedef Misterio Mist;

#endif //META2POO_ESPECIE_H
