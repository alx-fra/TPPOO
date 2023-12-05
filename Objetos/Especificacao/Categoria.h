#ifndef META2POO_CATEGORIA_H
#define META2POO_CATEGORIA_H
#include "../Alimento.h"
#include "../../helpers.h"

class Relva : public Alimento{
public:
    Relva(int posX, int posY);

    void Atualiza(term::Terminal &t) override;
};
typedef Relva Rel;

class Cenoura : public Alimento{
public:
    [[maybe_unused]] Cenoura(int posX, int posY);

    void Atualiza(term::Terminal &t) override;
};
typedef Cenoura Cen;

class Corpo : public Alimento{
public:
    [[maybe_unused]] Corpo(int posX, int posY);

    void Atualiza(term::Terminal &t) override;
};
typedef Corpo Cor;

class Bife : public Alimento{
public:
    [[maybe_unused]] Bife(int posX, int posY);

    void Atualiza(term::Terminal &t) override;

};
typedef Bife Bif;

class AlimMisterio : public Alimento{
public:
    [[maybe_unused]] AlimMisterio(int posX, int posY);

    void Atualiza(term::Terminal &t) override;

};
typedef AlimMisterio AlmMist;

#endif //META2POO_CATEGORIA_H
