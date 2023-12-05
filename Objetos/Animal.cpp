#include "Animal.h"

Animal::Animal(int posX, int posY, string nomeEspecie, char simbolo, int saude, int percecao, int NumMaxPosPorInst,
               int idade, int velocFuga, float peso, int fomeGanhPorInstante, int saudePerdPorInst, int instMorte,
               char cheiroalimPreferido, int velocidade, int n_filhos, int instNascFilho, int PesoAnimFugir,
               int tempoReproducao, int probFilhoNascer, int distMaxFIlho, int VNutricCorpo, int NToxiciCorpo):
        m_posicaoX(posX), m_posicaoY(posY), m_nomeEspecie(std::move(nomeEspecie)), m_simbolo(simbolo), m_saude(saude), m_percecao(percecao), m_NumMaxPosPorInst(NumMaxPosPorInst),
        m_idade(idade), m_velocFuga(velocFuga), m_peso(peso), m_fomeGanhPorInstante(fomeGanhPorInstante), m_saudePerdPorInst(saudePerdPorInst), m_instMorte(instMorte),
        m_cheiroalimPreferido(cheiroalimPreferido), m_velocidade(velocidade), m_nFilhos(n_filhos), m_instNascFilho(instNascFilho), m_PesoAnimFugir(PesoAnimFugir),
        m_tempoReproducao(tempoReproducao), m_probFilhoNascer(probFilhoNascer), m_distMaxFIlho(distMaxFIlho), m_VNutricCorpo(VNutricCorpo), m_NToxiciCorpo(NToxiciCorpo) {

    m_id = criaId();
    m_nomeProprio = "NA";
    m_vivo = true;
    m_fome=0;
    m_hist= nullptr;
    m_size = 1;
    m_hist = new Comida* [m_size];
    m_distObjetivo=-1;
    m_PosXF=-1;
    m_PosYF=-1;
    clearAllComida();
}

Animal::~Animal() {
    delete []m_hist;
}

int Animal::criaId(){
    id++;
    return id;
}

void Animal::clearAllComida() noexcept {
    for(unsigned int i = 0; i < m_size; i++)
        m_hist[i] = nullptr;
    m_histSize = 0;
}

bool Animal::addMemberToHist(Comida *cm) noexcept {
    int i = _getFirstAvailableIndex();
    string NA="NA";
    if (i == -1) {
        m_hist[m_size] = new Comida(NA,0,0);
        i=m_size;
        m_hist[i] = nullptr;
        m_size++;
    }

    m_hist[i] = cm;
    m_histSize++;
    return true;
}

int Animal::_getFirstAvailableIndex() const noexcept {
    for(int i = 0; i < m_size; i++)
        if(m_hist[i] == nullptr)
            return i;
    return -1;
}

string Animal::toString() const noexcept {
    std::ostringstream os;
    os << "\nTamanho do historico de comidas: " << m_histSize << " {";
    if (m_histSize == 0)
        os << "\n\tHistorico: Vazio";
    else {
        for(unsigned int auxi = 0; auxi < m_histSize; auxi++) {
            if (m_hist[auxi] != nullptr) {
                os << "\n\t\t" << auxi << " - " << m_hist[auxi]->toString();
            } else {
                os << "\n\t\t" << auxi << " - Vazio";
            }
        }
    }
    os << " }";
    return os.str();
}

int Animal::getMId() const {
    return m_id;
}

const string &Animal::getMNomeProprio() const {
    return m_nomeProprio;
}

const string &Animal::getMNomeEspecie() const {
    return m_nomeEspecie;
}

bool Animal::isMVivo() const {
    return m_vivo;
}

void Animal::setMVivo(bool mVivo) {
    m_vivo = mVivo;
}

int Animal::getMFome() const {
    return m_fome;
}

void Animal::setMFome(int mFome) {
    m_fome = mFome;
}

int Animal::getMPosicaoX() const {
    return m_posicaoX;
}

void Animal::setMPosicaoX(int mPosicaoX) {
    m_posicaoX = mPosicaoX;
}

int Animal::getMPosicaoY() const {
    return m_posicaoY;
}

void Animal::setMPosicaoY(int mPosicaoY) {
    m_posicaoY = mPosicaoY;
}

Comida **Animal::getMHist() const {
    return m_hist;
}

int Animal::getMHistSize() const {
    return m_histSize;
}

int Animal::getMSize() const {
    return m_size;
}

void Animal::setMSize(int mSize) {
    m_size = mSize;
}

char Animal::getMSimbolo() const {
    return m_simbolo;
}

void Animal::setMSimbolo(char mSimbolo) {
    m_simbolo = mSimbolo;
}

int Animal::getMSaude() const {
    return m_saude;
}

int Animal::getMPercecao() const {
    return m_percecao;
}

int Animal::getMNumMaxPosPorInst() const {
    return m_NumMaxPosPorInst;
}

void Animal::setMNumMaxPosPorInst(int mNumMaxPosPorInst) {
    m_NumMaxPosPorInst = mNumMaxPosPorInst;
}

int Animal::getMIdade() const {
    return m_idade;
}

void Animal::setMIdade(int mIdade) {
    m_idade = mIdade;
}

int Animal::getMVelocFuga() const {
    return m_velocFuga;
}

float Animal::getMPeso() const {
    return m_peso;
}

void Animal::setMPeso(float mPeso) {
    m_peso = mPeso;
}

int Animal::getMFomeGanhPorInstante() const {
    return m_fomeGanhPorInstante;
}

int Animal::getMSaudePerdPorInst() const {
    return m_saudePerdPorInst;
}

void Animal::setMSaudePerdPorInst(int mSaudePerdPorInst) {
    m_saudePerdPorInst = mSaudePerdPorInst;
}

int Animal::getMInstMorte() const {
    return m_instMorte;
}

void Animal::setMInstMorte(int mInstMorte) {
    m_instMorte = mInstMorte;
}

char Animal::getMCheiroalimPreferido() const {
    return m_cheiroalimPreferido;
}

int Animal::getMVelocidade() const {
    return m_velocidade;
}

int Animal::getMNFilhos() const {
    return m_nFilhos;
}

int Animal::getMInstNascFilho() const {
    return m_instNascFilho;
}

void Animal::setMInstNascFilho(int mInstNascFilho) {
    m_instNascFilho = mInstNascFilho;
}

int Animal::getMPesoAnimFugir() const {
    return m_PesoAnimFugir;
}

int Animal::getMTempoReproducao() const {
    return m_tempoReproducao;
}

int Animal::getMProbFilhoNascer() const {
    return m_probFilhoNascer;
}

int Animal::getMDistMaxFIlho() const {
    return m_distMaxFIlho;
}

int Animal::getMVNutricCorpo() const {
    return m_VNutricCorpo;
}

int Animal::getMNToxiciCorpo() const {
    return m_NToxiciCorpo;
}

void Animal::Atualiza(term::Terminal &t) {
    setMIdade(getMIdade()+1);
}

int Animal::getMPosXobjetivo() const {
    return m_posXobjetivo;
}

void Animal::setMPosXobjetivo(int mPosXobjetivo) {
    m_posXobjetivo = mPosXobjetivo;
}

int Animal::getMPosYObjetivo() const {
    return m_PosYObjetivo;
}

void Animal::setMPosYObjetivo(int mPosYObjetivo) {
    m_PosYObjetivo = mPosYObjetivo;
}

int Animal::getMDistObjetivo() const {
    return m_distObjetivo;
}

void Animal::setMDistObjetivo(int mDistObjetivo) {
    m_distObjetivo = mDistObjetivo;
}

void Animal::setMSaude(int mSaude) {
    m_saude = mSaude;
}

int Animal::getMPosXf() const {
    return m_PosXF;
}

void Animal::setMPosXf(int mPosXf) {
    m_PosXF = mPosXf;
}

int Animal::getMPosYf() const {
    return m_PosYF;
}

void Animal::setMPosYf(int mPosYf) {
    m_PosYF = mPosYf;
}

int Animal::getMInstNasc() const {
    return m_instNasc;
}

void Animal::setMInstNasc(int mInstNasc) {
    m_instNasc = mInstNasc;
}

int Animal::getMPosXp() const {
    return m_PosXP;
}

void Animal::setMPosXp(int mPosXp) {
    m_PosXP = mPosXp;
}

int Animal::getMPosYp() const {
    return m_PosYP;
}

void Animal::setMPosYp(int mPosYp) {
    m_PosYP = mPosYp;
}

int Animal::getMIdPai() const {
    return m_idPai;
}

void Animal::setMIdPai(int mIdPai) {
    m_idPai = mIdPai;
}

bool Animal::isBolsaMarsupial() const {
    return bolsaMarsupial;
}

void Animal::setBolsaMarsupial(bool setbmarsupial) {
    Animal::bolsaMarsupial = setbmarsupial;
}

int Animal::getInstBolsa() const {
    return instBolsa;
}

void Animal::setInstBolsa(int setmarsupial) {
    Animal::instBolsa = setmarsupial;
}

bool Animal::isMCriado() const {
    return m_criado;
}

void Animal::setMCriado(bool mCriado) {
    m_criado = mCriado;
}


std::ostream &operator<<(std::ostream &os, const Animal &an) {
    return os << an.toString();
}