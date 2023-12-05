#ifndef META1POO_ANIMAL_H
#define META1POO_ANIMAL_H
#include "Especificacao/Comida.h"
#include "../helpers.h"
static int id = 0;
using namespace std;

class Animal {
public:
    virtual void Atualiza(term::Terminal &t);
    [[nodiscard]] int getMId() const;
    [[nodiscard]] const string &getMNomeProprio() const;
    [[nodiscard]] const string &getMNomeEspecie() const;
    [[nodiscard]] bool isMVivo() const;
    void setMVivo(bool mVivo);
    [[nodiscard]] int getMFome() const;
    void setMFome(int mFome);
    [[nodiscard]] int getMPosicaoX() const;
    void setMPosicaoX(int mPosicaoX);
    [[nodiscard]] int getMPosicaoY() const;
    void setMPosicaoY(int mPosicaoY);
    [[nodiscard]] Comida **getMHist() const;
    [[nodiscard]] int getMHistSize() const;
    [[nodiscard]] int getMSize() const;
    void setMSize(int mSize);
    [[nodiscard]] char getMSimbolo() const;
    void setMSimbolo(char mSimbolo);
    [[nodiscard]] int getMSaude() const;
    [[nodiscard]] int getMPercecao() const;
    [[nodiscard]] int getMNumMaxPosPorInst() const;
    void setMNumMaxPosPorInst(int mNumMaxPosPorInst);
    [[nodiscard]] int getMIdade() const;
    void setMIdade(int mIdade);
    [[nodiscard]] int getMVelocFuga() const;
    [[nodiscard]] float getMPeso() const;
    void setMPeso(float mPeso);
    [[nodiscard]] int getMFomeGanhPorInstante() const;
    [[nodiscard]] int getMSaudePerdPorInst() const;
    void setMSaudePerdPorInst(int mSaudePerdPorInst);
    [[nodiscard]] int getMInstMorte() const;
    void setMInstMorte(int mInstMorte);
    [[nodiscard]] char getMCheiroalimPreferido() const;
    [[nodiscard]] int getMVelocidade() const;
    [[nodiscard]] int getMNFilhos() const;
    [[nodiscard]] int getMInstNascFilho() const;
    void setMInstNascFilho(int mInstNascFilho);
    [[nodiscard]] int getMPesoAnimFugir() const;
    [[nodiscard]] int getMTempoReproducao() const;
    [[nodiscard]] int getMProbFilhoNascer() const;
    [[nodiscard]] int getMDistMaxFIlho() const;
    [[nodiscard]] int getMVNutricCorpo() const;
    [[nodiscard]] int getMNToxiciCorpo() const;
    Animal() = delete;
    Animal(int posX, int posY, string nomeEspecie, char simbolo, int saudeInic, int percecao,
           int NumMaxPosPorInst, int idade, int velocFuga, float peso, int fomeGanhPorInstante,
           int saudePerdPorInst, int instMorte, char cheiroalimPreferido, int velocidade, int n_filhos,
           int instNascFilho, int PesoAnimFugir,
           int tempoReproducao, int probFilhoNascer, int distMaxFIlho, int VNutricCorpo, int NToxiciCorpo);
    ~Animal();
    //soma um ao id static e retorna esse valor (não há id's iguais)
    static int criaId();
    void clearAllComida() noexcept;
    bool addMemberToHist(Comida *cm) noexcept;
    [[nodiscard]] string toString() const noexcept;
    [[nodiscard]] bool isMCriado() const;
    void setMCriado(bool mCriado);
    [[nodiscard]] int getInstBolsa() const;
    void setInstBolsa(int setmarsupial);
    [[nodiscard]] bool isBolsaMarsupial() const;
    void setBolsaMarsupial(bool setbmarsupial);
    [[nodiscard]] int getMIdPai() const;
    void setMIdPai(int mIdPai);
    [[nodiscard]] int getMPosXp() const;
    void setMPosXp(int mPosXp);
    [[nodiscard]] int getMPosYp() const;
    void setMPosYp(int mPosYp);
    [[nodiscard]] int getMInstNasc() const;
    void setMInstNasc(int mInstNasc);
    [[nodiscard]] int getMPosXf() const;
    void setMPosXf(int mPosXf);
    [[nodiscard]] int getMPosYf() const;
    void setMPosYf(int mPosYf);
    [[nodiscard]] int getMPosXobjetivo() const;
    void setMPosXobjetivo(int mPosXobjetivo);
    [[nodiscard]] int getMPosYObjetivo() const;
    void setMPosYObjetivo(int mPosYObjetivo);
    [[nodiscard]] int getMDistObjetivo() const;
    void setMDistObjetivo(int mDistObjetivo);
    void setMSaude(int mSaude);
private:
    int m_id;
    string m_nomeProprio;
    string m_nomeEspecie;
    bool m_vivo;
    int m_fome{};
    int m_posicaoX;
    int m_posicaoY;
    Comida **m_hist;
    int m_histSize{};
    int m_size;
    char m_simbolo;
    int m_saude;
    int m_percecao;
    int m_NumMaxPosPorInst;
    int m_idade;
    int m_velocFuga; //-1 se nao for canguro
    float m_peso;
    int m_fomeGanhPorInstante;
    int m_saudePerdPorInst;
    int m_instMorte;
    char m_cheiroalimPreferido;
    int m_velocidade; // -1 se nao for lobo
    int m_nFilhos; //-1 se nao for lobo
    int m_instNascFilho; //gerado à nascenca entre 5 e instMorte, -1 se nao for um lobo
    int m_PesoAnimFugir;
    int m_tempoReproducao;
    int m_probFilhoNascer; //100 se nao for coelho
    int m_distMaxFIlho;
    int m_VNutricCorpo;
    int m_NToxiciCorpo;
    int m_distObjetivo;
    int m_posXobjetivo{};
    int m_PosYObjetivo{};
    int m_PosXF;
    int m_PosYF;
    int m_instNasc=-1;
    int m_PosXP=-1;
    int m_PosYP=-1;
    int m_idPai=-1;
    bool bolsaMarsupial=false;
    int instBolsa=-1;
    bool m_criado=false;
    /// Devolve o index para o primeiro slot disponível
    /// no vector dinâmico de historico.
    [[nodiscard]] int _getFirstAvailableIndex() const noexcept;
};

typedef Animal Anim;

const bool operator<<(Animal &a, Comida *c) noexcept; /// Insert comida

const bool operator>>(Animal &a, Comida *c) noexcept; /// Remove comida

std::ostream &operator<<(std::ostream &os, const Animal &anml);

term::Terminal &operator<<(term::Terminal t, const Animal &anml);

#endif //META1POO_ANIMAL_H
