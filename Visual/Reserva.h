#ifndef META1POO_RESERVA_H
#define META1POO_RESERVA_H
#include "../Objetos/Alimento.h"
#include "../Objetos/Especificacao/Especie.h"
#include "../Objetos/Especificacao/Comida.h"
#include "../Objetos/Especificacao/Categoria.h"
#include "../helpers.h"
using namespace std;
static vector<vector<char>> content;
static vector<Alim *> alimInReserva;
static vector<Anim *> animInReserva;
static int instante;
static int l= 0, c = 0;
static int *linhas = &l,*colunas = &c;

class Reserva {
public:
    static int cleanColRandom;
    static int cleanLinRandom;
    Reserva(int linres, int colres);
    ~Reserva();
    static void AddAlimento(string categoria, term::Terminal &t, int posX, int posY, int tox=-1, int saude=-1);
    static void AddAnml(string especie, term::Terminal &t, int posX, int posY);
    static void removeAlimByID(unsigned idrename);
    static void removeAnimByID(unsigned idremove, term::Terminal t);
    static void morte(term::Terminal &t);
    static void removeAlimByPos(int x, int y);
    static void removeAnimByPos(int x, int y, term::Terminal t);
    static void feedByPos(term::Terminal &t, int x, int y, int pntNut, int tox);
    static void feedById(term::Terminal &t, int idToFeed, int pntNut, int tox);
    static void empty(term::Terminal &t, int x, int y);
    static void see(term::Terminal &t, int x, int y);
    static void visanim(term::Terminal &t);
    static void printAreaVisivel(term::Terminal &t, int row, int col, int rows, int cols);
    static int EspacoVazioVector(int tipo, int lin, int col);
    static void info(term::Terminal &t, int infoID);
    static int printAnms(term::Terminal &t);
    static void printAlmt(term::Terminal &t);
    static void store(term::Terminal &t, const string& nomeFich);
    static void restore(term::Terminal &t, const string& nomeFich);
    static void nextInst(term::Terminal &t, int N=1, int P=0);
    static void andaC(int idC, term::Terminal &t);
    static void comeC(int idC, term::Terminal &t);
    static void fomeC(int idC);
    static void saudeC(int idC);
    static void morteC(int id, term::Terminal &t);
    static void reproduzC(int idC, term::Terminal &t);
    static int auxNumLin;
    static int auxNumCol;
    static void andaO(int idO, term::Terminal &terminal);
    static void reproduzO(int id, term::Terminal &terminal);
    static void comeO(int idO, term::Terminal &t);
    static void fomeO(int id);
    static void saudeO(int idO);
    static void morteO(int idO, term::Terminal &t);
    static void andaG(int idG, term::Terminal &t);
    static void reproduzG(int idG, term::Terminal &t);
    static void morteG(int idO, term::Terminal &t);
    static void bolsaMarsupial(int idG, term::Terminal &t);
    static void andaL(int idL, term::Terminal &t);
    static void reproduzL(int idL, term::Terminal &t);
    static void comeL(int idL, term::Terminal &t);
    static void fomeL(int idL);
    static void saudeL(int idL);
    static void morteL(int idL, term::Terminal &t);
    static void desaparece(int idR, term::Terminal &t);
    static void morteAlm(term::Terminal &terminal);
    static void reproduzr(int idR, term::Terminal &t);
    static void toxicidadet(int idT, term::Terminal &t);
    static void vnutritivop(int idP, term::Terminal &t);
    static void vnutritivob(int idB, term::Terminal &t);
    static void atualConstAnmFich(int idA, term::Terminal &t);
    static void addFromFile(const string &filename, term::Terminal &t);
    static void atualConstAlmFich(int idA, term::Terminal &t);
    static void limpaEcra(term::Terminal &t);
    static void andaM(int idC, term::Terminal &t);
    static void comeM(int idC, term::Terminal &t);
    static void morteM(int idAux, term::Terminal &t);
};


#endif //META1POO_RESERVA_H
