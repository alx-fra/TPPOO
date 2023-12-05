#ifndef META1POO_ALIMENTO_H
#define META1POO_ALIMENTO_H
#include "Animal.h"
#include "../helpers.h"
using namespace std;

class Alimento {
public:
    virtual void Atualiza(term::Terminal &t);
    [[nodiscard]] const string &getMCheiro0() const;
    void setMCheiro0(const string &mCheiro0);
    [[nodiscard]] const string &getMCheiro1() const;
    void setMCheiro1(const string &mCheiro1);
    [[nodiscard]] bool isMCriado() const;
    void setMCriado(bool mCriado);
    [[nodiscard]] bool isMFilho() const;
    void setMFilho(bool mFilho);
    [[nodiscard]] int getMPosXf() const;
    void setMPosXf(int mPosXf);
    [[nodiscard]] int getMPosYf() const;
    void setMPosYf(int mPosYf);
    [[nodiscard]] int getMTempoVidaAtual() const;
    void setMTempoVidaAtual(int mTempoVidaAtual);
    [[nodiscard]] bool isMVivo() const;
    void setMVivo(bool mVivo);
    [[nodiscard]] const string &getMEspecie() const;
    [[nodiscard]] int getMId() const;
    [[nodiscard]] char getMSimbolo() const;
    [[nodiscard]] int getMDuracao() const;
    void setMDuracao(int mDuracao);
    [[nodiscard]] int getMVnutritivo() const;
    void setMVnutritivo(int mVnutritivo);
    [[nodiscard]] int getMToxicidade() const;
    void setMToxicidade(int mToxicidade);
    [[nodiscard]] int getMPosicaoX() const;
    [[nodiscard]] int getMPosicaoY() const;
    Alimento(int posX, int posY, string especie, char simbolo, int duracao,
             int vnutritivo, int toxicidade, string cheiro0, string cheiro1);
    ~Alimento();
private:
    int m_id;
    char m_simbolo;
    int m_duracao;
    int m_vnutritivo;
    int m_toxicidade;
    int m_posicaoX{};
    int m_posicaoY{};
    string m_cheiro1;
    string m_especie;
    string m_cheiro0;
    bool m_vivo;
    int m_tempoVidaAtual{};
    int m_posXf;
    int m_posYf;
    bool m_filho;
    bool m_criado=false;
};
typedef Alimento Alim;

#endif //META1POO_ALIMENTO_H