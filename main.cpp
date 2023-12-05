#include "Visual/Reserva.h"
#include "helpers.h"

using namespace std;
using namespace term;
term::Terminal &t = term::Terminal::instance();
// canto superior esquerdo da area visivel
int row;
int col;
//tamanho da area visivel
int rows;
int cols;
void load(const string &fich, const Reserva& reserve);
void validacao(string comandos, const Reserva& reserve);
void numLinhas();
void numColunas();

int main() {
    string filename = "constantes.txt";
    Reserva::addFromFile(filename, t);
    numLinhas();
    numColunas();
    Reserva::auxNumLin=*linhas;
    Reserva::auxNumCol=*colunas;
    Reserva reserve(*linhas, *colunas);
    //inicializar os cantos
    row=0;
    col=0;
    //inicializar o tamanho da area visivel
    rows = 15;
    cols = 15;
    t << move_to(35,3) <<  "Insira um comando (\"exit\" para sair):\n";
    for(int i=1; i<20; i++) {
        t.init_color(i, i, 0);
    }
    for(int i=0; i<20; i++) {
       // t  << set_color(i) << i;
    }
    do {
        t << move_to(0,0);
        Reserva::printAreaVisivel(t, row, col, rows, cols);
        *linhas=Reserva::auxNumLin;
        *colunas=Reserva::auxNumCol;
        t << no_color();
        Window window = Window(35, 0, 25, 3);
        std::string s;
        s.resize(200);
        window >> s;
        if (s == "KEY_UP" && row > 0 && !s.empty()) {
            row--;
            continue;
        }else
        if (s == "KEY_DOWN" && row < *linhas - rows && !s.empty()) {
            row++;
            continue;
        }else
        if (s == "KEY_LEFT"  && col > 0 && !s.empty()) {
            col--;
            continue;
        }else
        if (s == "KEY_RIGHT" && col < *colunas - cols&& !s.empty()) {
            col++;
            continue;
        }else{
            if (strcmp(s.c_str(), "exit") == 0) {
                exit(3817);
            } else if(s != "KEY_UP" && s != "KEY_DOWN" && s != "KEY_LEFT" && s != "KEY_RIGHT" && !s.empty()) {
                validacao(s, reserve);
            }
            continue;
        }
    } while(true);
}

void load(const string &fich, const Reserva& reserve) {

    ifstream ficheiro(fich);
    if (!ficheiro) {
        t << "o ficheiro " + fich + " nao existe\n";
    }
    string comandos;
    while (getline(ficheiro, comandos)) {
        validacao(comandos, reserve);
    }
    ficheiro.close();
}

void validacao(string comandos, const Reserva& reserve) {

    vector<string> comands;
    int npalavras, i;
    bool invalid = false;
    string tmp;
    vector<string> words;


    stringstream ss(comandos);
    while (getline(ss, tmp, ' ')) {
        words.push_back(tmp);
    }
    i = 0;

    for (auto it = words.begin(); it != words.end(); ++it) {
        i++;
    }
    npalavras = i;
    if (strcmp(words[0].c_str(), "animal") == 0 && (npalavras == 2 || npalavras == 4)) {
        if (strcmp(words[1].c_str(), "c") == 0 || strcmp(words[1].c_str(), "l") == 0 ||
            strcmp(words[1].c_str(), "o") == 0 ||
            strcmp(words[1].c_str(), "m") == 0 || strcmp(words[1].c_str(), "g") == 0) {
            if (npalavras == 2) {
                invalid = false;
            } else {
                for (int j = 0; j < strlen(words[2].c_str()) && !invalid; j++) {
                    if (isdigit(words[2][j])) {
                        invalid = false;
                    } else {
                        invalid = true;
                    }
                }
                for (int j = 0; j < strlen(words[3].c_str()) && !invalid; j++) {
                    if (isdigit(words[3][j])) {
                        invalid = false;
                    } else {
                        invalid = true;
                    }
                }
            }
        } else {
            invalid = true;
        }
        if (!invalid && npalavras == 2) {
            //procurar posXRandom e posYRandom na reserva vazias
            Reserva::EspacoVazioVector(0, *linhas, *colunas);
            //t << Reserva::cleanColRandom << "   ";
            //t << Reserva::cleanLinRandom << "   ";
            Reserva::AddAnml(words[1], t, Reserva::cleanLinRandom, Reserva::cleanColRandom);
        } else if (!invalid && npalavras == 4) {
            if (stoi(words[2]) < *colunas && stoi(words[3]) < *linhas ) {
                Reserva::AddAnml(words[1], t, stoi(words[2]), stoi(words[3]));
            }
            else
                invalid = true;
        }
    }
    else if (strcmp(words[0].c_str(), "kill") == 0 && npalavras == 3) {
        for (int j = 0; j < strlen(words[1].c_str()) && !invalid; j++) {
            if (isdigit(words[1][j])) {
                invalid = false;
            } else {
                invalid = true;
            }
        }
        for (int j = 0; j < strlen(words[2].c_str()) && !invalid; j++) {
            if (isdigit(words[2][j])) {
                invalid = false;
            } else {
                invalid = true;
            }
        }
        if(!invalid){
            Reserva::removeAnimByPos(stoi(words[1]), stoi(words[2]), t);
        }
    }
    else if (strcmp(words[0].c_str(), "killid") == 0 && npalavras == 2) {
        for (int j = 0; j < strlen(words[1].c_str()) && !invalid; j++) {
            if (isdigit(words[1][j])) {
                invalid = false;
            } else {
                invalid = true;
            }
            if(!invalid){
                Reserva::removeAnimByID(stoi(words[1]), t);
            }
        }
    }
    else if (strcmp(words[0].c_str(), "food") == 0 && (npalavras == 2 || npalavras == 4)) {
        if (strcmp(words[1].c_str(), "r") == 0 || strcmp(words[1].c_str(), "t") == 0 || strcmp(words[1].c_str(), "p") == 0 ||
            strcmp(words[1].c_str(), "b") == 0 ||
            strcmp(words[1].c_str(), "a") == 0) {
            if (npalavras == 2) {
                invalid = false;
            } else {
                for (int j = 0; j < strlen(words[2].c_str()) && !invalid; j++) {
                    if (isdigit(words[2][j])) {
                        invalid = false;
                    } else {
                        invalid = true;
                    }
                }
                for (int j = 0; j < strlen(words[3].c_str()) && !invalid; j++) {
                    if (isdigit(words[3][j])) {
                        invalid = false;
                    } else {
                        invalid = true;
                    }
                }
            }
        } else {
            invalid = true;
        }
        if (!invalid && npalavras == 2) {
            //procurar posXRandom e posYRandom na reserva vazias
            if(Reserva::EspacoVazioVector(1,*linhas, *colunas) == -1){
                t << "Impossivel adicionar alimento, falta de espaco";
            }else{
                t << " lin:" <<Reserva::cleanLinRandom << "   ";
                t << " col:" << Reserva::cleanColRandom << "   ";
                Reserva::AddAlimento(words[1], t, Reserva::cleanLinRandom, Reserva::cleanColRandom);
            }
        } else if (!invalid && npalavras == 4) {
            if (stoi(words[2]) < *colunas && stoi(words[3]) < *linhas )
                Reserva::AddAlimento(words[1], t, stoi(words[2]), stoi(words[3]));
            else
                invalid = true;
        }
    }
    else if (strcmp(words[0].c_str(), "feed") == 0 && npalavras == 5) {
        for (int j = 0; j < strlen(words[1].c_str()) && !invalid; j++) {
            if (isdigit(words[1][j])) {
                invalid = false;
            } else {
                invalid = true;
            }
        }
        for (int j = 0; j < strlen(words[2].c_str()) && !invalid; j++) {
            if (isdigit(words[2][j])) {
                invalid = false;
            } else {
                invalid = true;
            }
        }
        for (int j = 0; j < strlen(words[3].c_str()) && !invalid; j++) {
            if (isdigit(words[3][j])) {
                invalid = false;
            } else {
                invalid = true;
            }
        }
        for (int j = 0; j < strlen(words[4].c_str()) && !invalid; j++) {
            if (isdigit(words[4][j])) {
                invalid = false;
            } else {
                invalid = true;
            }
        }
        if(!invalid){
            Reserva::feedByPos(t,stoi(words[1]),stoi(words[2]),stoi(words[3]),stoi(words[4]));

        }
    }else if (strcmp(words[0].c_str(), "feedid") == 0 && npalavras==4) {
        //id
        for (int j = 0; j < strlen(words[1].c_str()) && !invalid; j++) {
            if (isdigit(words[1][j])) {
                invalid = false;
            } else {
                invalid = true;
            }
        }
        //pontos nutritivos
        for (int j = 0; j < strlen(words[2].c_str()) && !invalid; j++) {
            if (isdigit(words[2][j])) {
                invalid = false;
            } else {
                invalid = true;
            }
        }
        //pontos de toxicidade
        for (int j = 0; j < strlen(words[3].c_str()) && !invalid; j++) {
            if (isdigit(words[3][j])) {
                invalid = false;
            } else {
                invalid = true;
            }
        }
        if(!invalid){
            Reserva::feedById(t,stoi(words[1]),stoi(words[2]),stoi(words[3]));
        }
    } else if (strcmp(words[0].c_str(), "nofood") == 0 && (npalavras == 2 || npalavras == 3)) {
        for (int j = 0; j < strlen(words[1].c_str()) && !invalid; j++) {
            if (isdigit(words[1][j])) {
                invalid = false;
            } else {
                invalid = true;
            }
        }
        if (npalavras == 3)
            for (int j = 0; j < strlen(words[2].c_str()) && !invalid; j++) {
                if (isdigit(words[2][j])) {
                    invalid = false;
                } else {
                    invalid = true;
                }
            }
        if (!invalid && npalavras == 2) {
            Reserva::removeAlimByID(stoi(words[1]));
        } else if (!invalid && npalavras == 3) {
            Reserva::removeAlimByPos(stoi(words[1]),stoi(words[2]));
        }
    } else if (strcmp(words[0].c_str(), "empty") == 0 && npalavras == 3) {
        for (int j = 0; j < strlen(words[1].c_str()) && !invalid; j++) {
            if (isdigit(words[1][j])) {
                invalid = false;
            } else {
                invalid = true;
            }
        }
        for (int j = 0; j < strlen(words[2].c_str()) && !invalid; j++) {
            if (isdigit(words[2][j])) {
                invalid = false;
            } else {
                invalid = true;
            }
        }
        if(!invalid){
            Reserva::empty(t,stoi(words[1]), stoi(words[2]));
        }

    } else if (strcmp(words[0].c_str(), "see") == 0 && npalavras == 3) {
        for (int j = 0; j < strlen(words[1].c_str()) && !invalid; j++) {
            if (isdigit(words[1][j])) {
                invalid = false;
            } else {
                invalid = true;
            }
        }
        for (int j = 0; j < strlen(words[2].c_str()) && !invalid; j++) {
            if (isdigit(words[2][j])) {
                invalid = false;
            } else {
                invalid = true;
            }
        }
        if(!invalid){
            Reserva::see(t, stoi(words[1]), stoi(words[2]));
        }
    } else if (strcmp(words[0].c_str(), "info") == 0 && npalavras == 2) {
        for (int j = 0; j < strlen(words[1].c_str()) && !invalid; j++) {
            if (isdigit(words[1][j])) {
                invalid = false;
            } else {
                invalid = true;
            }
        }
        if(!invalid){
            Reserva::info(t, stoi(words[1]));
        }
    } else if (strcmp(words[0].c_str(), "n") == 0 && npalavras == 1) {
        invalid = false;
        Reserva::morte(t);
        Reserva::morteAlm(t);
        Reserva::nextInst(t);
        Reserva::morte(t);
        Reserva::morteAlm(t);
    } else if (strcmp(words[0].c_str(), "n") == 0 && npalavras == 2) {
        for (int j = 0; j < strlen(words[1].c_str()) && !invalid; j++) {
            if (isdigit(words[1][j])) {
                invalid = false;
            } else {
                invalid = true;
            }
        }
        if(!invalid){
            Reserva::morte(t);
            Reserva::morteAlm(t);
            Reserva::nextInst(t,stoi(words[1]));
            Reserva::morte(t);
            Reserva::morteAlm(t);
        }
    } else if (strcmp(words[0].c_str(), "n") == 0 && npalavras == 3) {
        for (int j = 0; j < strlen(words[1].c_str()) && !invalid; j++) {
            if (isdigit(words[1][j])) {
                invalid = false;
            } else {
                invalid = true;
            }
        }
        for (int j = 0; j < strlen(words[2].c_str()) && !invalid; j++) {
            if (isdigit(words[2][j])) {
                invalid = false;
            } else {
                invalid = true;
            }
        }
        if(!invalid){
            Reserva::morte(t);
            Reserva::morteAlm(t);
            Reserva::nextInst(t, stoi(words[1]), stoi(words[2]));
            Reserva::morte(t);
            Reserva::morteAlm(t);
        }
    } else if (strcmp(words[0].c_str(), "anim") == 0 && npalavras == 1) {
        invalid = false;
        Reserva::printAnms(t);
    } else if (strcmp(words[0].c_str(), "visanim") == 0 && npalavras == 1) {
        invalid = false;
        Reserva::visanim(t);
    } else if (strcmp(words[0].c_str(), "alim") == 0 && npalavras == 1) {
        invalid = false;
        Reserva::printAlmt(t);
    } else if (strcmp(words[0].c_str(), "store") == 0 && npalavras == 2) {
        if(!invalid){
            Reserva::store(t,words[1]);
        }
    } else if (strcmp(words[0].c_str(), "restore") == 0 && npalavras == 2) {
        if(!invalid){
            Reserva::restore(t, words[1]);
            //inicializar os cantos
            row=0;
            col=0;
        }
    }else if (strcmp(words[0].c_str(), "load") == 0 && npalavras == 2) {
        invalid=false;
        load(words[1], reserve);
    } else if (strcmp(words[0].c_str(), "slide") == 0 && npalavras == 3) {
        if (strcmp(words[1].c_str(), "up") == 0 || strcmp(words[1].c_str(), "down") == 0 ||
            strcmp(words[1].c_str(), "right") == 0 ||
            strcmp(words[1].c_str(), "left") == 0) {
            for (int j = 0; j < strlen(words[1].c_str()) && !invalid; j++) {
                if (isdigit(words[1][j])) {
                    invalid = true;
                } else {
                    invalid = false;
                }
            }
            if(!invalid) {
                if (strcmp(words[1].c_str(), "up") != 0 && row > 0) {
                    row--;
                }else
                if (strcmp(words[1].c_str(), "down") != 0 && row < *linhas - rows ) {
                    row++;
                }else
                if (strcmp(words[1].c_str(), "left") != 0  && col > 0) {
                    col--;
                }else
                if (strcmp(words[1].c_str(), "right") != 0 && col < *colunas - cols ) {
                    col++;
                }
            }
        } else {
            invalid = true;
        }
    }
    if (invalid) {
        t << move_to(85,29) << comandos << " -> sintaxe invalida\n";
    } else {
        t << move_to(85,29) << comandos << " -> sintaxe valida\n";

    }
    comandos.clear();
    tmp.clear();
    words.clear();
    ss.clear();
}

void numLinhas(){
    string linhasstr;
    do {
        t << move_to(0,0) << "Indique o numero de linhas entre 16 e 500:\n";
        t >> linhasstr;
        for (int i = 0; i < linhasstr.length(); ++i) {
            if (isdigit(linhasstr[i]) == 0) {
                linhasstr = "0";
            }
        }
        if(!linhasstr.empty())
            *linhas = stoi(linhasstr);
        if (*linhas < 16 || *linhas > 500 || linhasstr.empty()) {
            t.clear();
            t << move_to(0,2) << "Numero invalido, tente novamente";
        }
    } while (*linhas < 16 || *linhas > 500 || linhasstr.empty());
}

void numColunas(){
    string colunasstr;
    do {
        t << move_to(0,2)<< "Indique o numero de colunas entre 16 e 500:\n";
        t >> colunasstr;
        for (int i = 0; i < colunasstr.length(); ++i) {
            if (isdigit(colunasstr[i]) == 0) {
                colunasstr = "0";
            }
        }
        if (!colunasstr.empty())
            *colunas = stoi(colunasstr);
        if (*colunas < 16 || *colunas > 500 || colunasstr.empty()) {
            t << move_to(0,3)<< "\n";
            t << move_to(0,4)<< "Numero invalido, tente novamente\n";
        }
    } while (*colunas < 16 || *colunas > 500);
}