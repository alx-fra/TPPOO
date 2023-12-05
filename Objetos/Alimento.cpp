#include "Alimento.h"
using namespace std;

Alimento::Alimento(int posX, int posY, string especie, char simbolo, int duracao, int vnutritivo,
                   int toxicidade, string cheiro0, string cheiro1):
                   m_posicaoX(posX), m_posicaoY(posY), m_especie(std::move(especie)), m_simbolo(simbolo),
                   m_duracao(duracao), m_vnutritivo(vnutritivo), m_toxicidade(toxicidade), m_cheiro0(std::move(cheiro0)), m_cheiro1(std::move(cheiro1)){
    m_id = Animal::criaId();
    m_vivo = true;
    m_posXf=-1;
    m_posYf=-1;
    m_filho=false;
}

const string &Alimento::getMEspecie() const {
    return m_especie;
}

int Alimento::getMId() const {
    return m_id;
}

char Alimento::getMSimbolo() const {
    return m_simbolo;
}

int Alimento::getMDuracao() const {
    return m_duracao;
}

void Alimento::setMDuracao(int mDuracao) {
    m_duracao = mDuracao;
}

int Alimento::getMVnutritivo() const {
    return m_vnutritivo;
}

void Alimento::setMVnutritivo(int mVnutritivo) {
    m_vnutritivo = mVnutritivo;
}

int Alimento::getMToxicidade() const {
    return m_toxicidade;
}

void Alimento::setMToxicidade(int mToxicidade) {
    m_toxicidade = mToxicidade;
}

int Alimento::getMPosicaoX() const {
    return m_posicaoX;
}

int Alimento::getMPosicaoY() const {
    return m_posicaoY;
}

Alimento::~Alimento() = default;

const string &Alimento::getMCheiro0() const {
    return m_cheiro0;
}

void Alimento::setMCheiro0(const string &mCheiro0) {
    m_cheiro0 = mCheiro0;
}

const string &Alimento::getMCheiro1() const {
    return m_cheiro1;
}

void Alimento::setMCheiro1(const string &mCheiro1) {
    m_cheiro1 = mCheiro1;
}

void Alimento::Atualiza(term::Terminal &t) {
    setMTempoVidaAtual(getMTempoVidaAtual()+1);
}

bool Alimento::isMVivo() const {
    return m_vivo;
}

void Alimento::setMVivo(bool mVivo) {
    m_vivo = mVivo;
}

int Alimento::getMTempoVidaAtual() const {
    return m_tempoVidaAtual;
}

void Alimento::setMTempoVidaAtual(int mTempoVidaAtual) {
    m_tempoVidaAtual = mTempoVidaAtual;
}

int Alimento::getMPosXf() const {
    return m_posXf;
}

void Alimento::setMPosXf(int mPosXf) {
    m_posXf = mPosXf;
}

int Alimento::getMPosYf() const {
    return m_posYf;
}

void Alimento::setMPosYf(int mPosYf) {
    m_posYf = mPosYf;
}

bool Alimento::isMFilho() const {
    return m_filho;
}

void Alimento::setMFilho(bool mFilho) {
    m_filho = mFilho;
}

bool Alimento::isMCriado() const {
    return m_criado;
}

void Alimento::setMCriado(bool mCriado) {
    m_criado = mCriado;
}
