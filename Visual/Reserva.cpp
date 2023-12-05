#include "Reserva.h"

int Reserva::cleanLinRandom=0;
int Reserva::cleanColRandom=0;
int Reserva::auxNumLin=1;
int Reserva::auxNumCol=1;

void Reserva::AddAlimento(string categoria, term::Terminal &t, int posX, int posY, int tox, int saude) {
    Alimento* novo = nullptr;
    bool flag = false;
    switch (categoria.at(0)) {
        case 'r':
            novo = new Rel(posX,posY);
            break;
        case 't':
            novo = new Cen(posX,posY);
            break;
        case 'p':
            novo = new Cor(posX,posY);
            break;
        case 'b':
            novo = new Bif(posX,posY);
            break;
        case 'a':
            novo = new AlmMist(posX,posY);
            break;

    }
    if(novo != nullptr) {
        auto i = alimInReserva.begin();
        for (; i != alimInReserva.end(); i++) {
            if ((*i)->getMPosicaoX() == posX && (*i)->getMPosicaoY() == posY) {
                flag = true;
                t << "Ja exite um alimento na posicao " << posX << "/" << posY;
            }
        }
        //nao há um alimento nessa posicao
        if(!flag) {
            if(tox != -1 && saude != -1){
                //corpo da ovelha, com vnutritivo = saude da ovelha e tox=0
                novo->setMToxicidade(0);
                novo->setMVnutritivo(saude);
            }
            alimInReserva.push_back(novo);
            Reserva::atualConstAlmFich(novo->getMId(), t);
        }
    }

}

void Reserva::AddAnml(string especie, term::Terminal &t, int posX, int posY) {
    Animal* novo = nullptr;
    switch (especie.at(0)) {
        case 'c':
            novo = new Coe(posX,posY);
            break;
        case 'o':
            novo = new Ove(posX,posY);
            break;
        case 'l':
            novo = new Lob(posX,posY);
            break;
        case 'g':
            novo = new Cang(posX,posY);
            //porque o primeiro canguro nao tem pai, logo nao se pode manter perto dele
            novo->setMIdPai(-2);
            break;
        case 'm':
            novo = new Mist(posX,posY);
    }
    if(novo != nullptr) {
        novo->setMInstNasc(instante);
        animInReserva.push_back(novo);
        Reserva::atualConstAnmFich(novo->getMId(), t);
    }
}

Reserva::Reserva(int linres, int colres) {
    content.resize(linres, vector<char>(colres));
    for (int i = 0; i < linres; ++i) {
        for (int j = 0; j < colres; ++j) {
            content[i][j] = '+';
        }
    }
}

Reserva::~Reserva() = default;

void Reserva::printAreaVisivel(term::Terminal &t, int row, int col, int rows, int cols){
    auto alim = alimInReserva.begin();
    for (; alim != alimInReserva.end(); alim++){
        content[(*alim)->getMPosicaoX()][(*alim)->getMPosicaoY()] = (*alim)->getMSimbolo();
    }
    auto anim = animInReserva.begin();
    for (; anim != animInReserva.end(); anim++){
        content[(*anim)->getMPosicaoX()][(*anim)->getMPosicaoY()] = (*anim)->getMSimbolo();
    }
    t<<"---------------------------------\n";
    for (int i = 0; i < rows; i++)
    {
        t<< "|-";
        for (int j = 0; j < cols; j++)
        {
            t << content[row + i][col + j] << '-';
        }
        t<< '|';
        t << '\n';
    }
    t<<"---------------------------------\n";
}


void Reserva::removeAlimByID(unsigned idrename) {
    auto i = alimInReserva.begin();
    for (; i != alimInReserva.end(); i++)
        if ((*i)->getMId() == idrename)
            break;

    if (i != alimInReserva.end()) {
        content[(*i)->getMPosicaoX()][(*i)->getMPosicaoY()] = '+';
        delete *i;
        alimInReserva.erase(i);
    }
}

void Reserva::removeAnimByID(unsigned idremove, term::Terminal t) {
    auto i = animInReserva.begin();
    for (; i != animInReserva.end(); i++)
        if ((*i)->getMId() == idremove)
            break;

    if (i != animInReserva.end()) {
        if((*i)->getMSimbolo()=='O'){
            //cria alimento do tipo corpo
            int x,y;
            x=(*i)->getMPosicaoX();
            y=(*i)->getMPosicaoY();
            // fazer o alimento dar a volta se passou os limites
            if (x < 0 || x >= auxNumLin || y < 0 || y >= auxNumCol) {
                int atualizaPos = (x + auxNumLin) % auxNumLin;
                x=atualizaPos;
                atualizaPos = (y + auxNumCol) % auxNumCol;
                y=atualizaPos;
            }
            AddAlimento("p",t,x,y,0, (*i)->getMSaude());
        }else if((*i)->getMSimbolo()=='L'){
            //cria alimento do tipo corpo
            int x,y;
            x=(*i)->getMPosicaoX();
            y=(*i)->getMPosicaoY();
            // fazer o alimento dar a volta se passou os limites
            if (x < 0 || x >= auxNumLin || y < 0 || y >= auxNumCol) {
                int atualizaPos = (x + auxNumLin) % auxNumLin;
                x=atualizaPos;
                atualizaPos = (y + auxNumCol) % auxNumCol;
                y=atualizaPos;
            }
            AddAlimento("p",t,x,y,0, 10);
        }else if((*i)->getMSimbolo()=='G'){
            //cria alimento do tipo corpo
            int x,y;
            x=(*i)->getMPosicaoX();
            y=(*i)->getMPosicaoY();
            // fazer o alimento dar a volta se passou os limites
            if (x < 0 || x >= auxNumLin || y < 0 || y >= auxNumCol) {
                int atualizaPos = (x + auxNumLin) % auxNumLin;
                x=atualizaPos;
                atualizaPos = (y + auxNumCol) % auxNumCol;
                y=atualizaPos;
            }
            AddAlimento("p",t,x,y,5, 15);
        }
        content[(*i)->getMPosicaoX()][(*i)->getMPosicaoY()] = '+';
        delete *i;
        animInReserva.erase(i);
    }
}

void Reserva::removeAlimByPos(int x, int y) {
    auto i = alimInReserva.begin();
    for (; i != alimInReserva.end(); i++)
        if ((*i)->getMPosicaoX() == x && (*i)->getMPosicaoY() == y)
            break;

    if (i != alimInReserva.end()) {
        delete *i;
        alimInReserva.erase(i);
        content[x][y] = '+';
    }
}

void Reserva::removeAnimByPos(int x, int y, term::Terminal t) {
    auto i = animInReserva.begin();
    for (; i != animInReserva.end(); i++)
        if ((*i)->getMPosicaoX() == x && (*i)->getMPosicaoY() == y)
            break;

    if (i != animInReserva.end()) {
        if((*i)->getMSimbolo()=='O'){
            //cria alimento do tipo corpo
            int posX,posY;
            posX=(*i)->getMPosicaoX();
            posY=(*i)->getMPosicaoY();
            // fazer o alimento dar a volta se passou os limites
            if (posX < 0 || posX >= auxNumLin || posY < 0 || posY >= auxNumCol) {
                int atualizaPos = (posX + auxNumLin) % auxNumLin;
                posX=atualizaPos;
                atualizaPos = (posY + auxNumCol) % auxNumCol;
                posY=atualizaPos;
            }
            AddAlimento("p", t, posX, posY, 0, (*i)->getMSaude());
        }else if((*i)->getMSimbolo()=='L'){
            //cria alimento do tipo corpo
            int posX,posY;
            posX=(*i)->getMPosicaoX();
            posY=(*i)->getMPosicaoY();
            // fazer o alimento dar a volta se passou os limites
            if (posX < 0 || posX >= auxNumLin || posY < 0 || posY >= auxNumCol) {
                int atualizaPos = (posX + auxNumLin) % auxNumLin;
                posX=atualizaPos;
                atualizaPos = (posY + auxNumCol) % auxNumCol;
                posY=atualizaPos;
            }
            AddAlimento("p", t, posX, posY, 0, 10);
        }else if((*i)->getMSimbolo()=='G'){
            //cria alimento do tipo corpo
            int posX,posY;
            posX=(*i)->getMPosicaoX();
            posY=(*i)->getMPosicaoY();
            // fazer o alimento dar a volta se passou os limites
            if (posX < 0 || posX >= auxNumLin || posY < 0 || posY >= auxNumCol) {
                int atualizaPos = (posX + auxNumLin) % auxNumLin;
                posX=atualizaPos;
                atualizaPos = (posY + auxNumCol) % auxNumCol;
                posY=atualizaPos;
            }
            AddAlimento("p", t, posX, posY, 5, 15);
        }
        delete *i;
        animInReserva.erase(i);
        content[x][y] = '+';
    }
}

void Reserva::see(term::Terminal &t, int x, int y) {
    auto i = animInReserva.begin();
    for (; i != animInReserva.end(); i++)
        if ((*i)->getMPosicaoX() == x && (*i)->getMPosicaoY() == y) {
            if (i != animInReserva.end()) {
                t << "ID: " << to_string((*i)->getMId()) << " Tipo: Animal "
                  << "Nome especie: " << (*i)->getMNomeEspecie() << " "
                  << "Posicao X/Y: " << to_string((*i)->getMPosicaoX()) << '/' << to_string((*i)->getMPosicaoY())
                  << " ";

                if ((*i)->isMVivo() == 0)
                    t << "O animal esta morto... ";
                else if ((*i)->isMVivo() == 1)
                    t << "O animal esta vivo... ";

                t << "Massa: " << to_string((*i)->getMPeso()) << " "
                  << "Fome: " << to_string((*i)->getMFome()) << " "
                  << "Saude: " << to_string((*i)->getMSaude()) << " ";
                //historico
                t << (*i)->toString();
                t << "\n";
            }
        }

    auto a = alimInReserva.begin();
    for (; a != alimInReserva.end(); a++)
        if ((*a)->getMPosicaoX() == x && (*a)->getMPosicaoY() == y) {
            if (a != alimInReserva.end()) {
                t << "ID: " << to_string((*a)->getMId()) << " Tipo: Alimento "
                  << "Nome especie: " << (*a)->getMEspecie() << " "
                  << "Posicao X/Y: " << to_string((*a)->getMPosicaoX()) << '/' << to_string((*a)->getMPosicaoY()) << " "
                  << "Toxicidade: " << to_string((*a)->getMToxicidade()) << " "
                  << "Valor nutritivo: " << to_string((*a)->getMVnutritivo()) << " "
                  << "Cheiro: " << (*a)->getMCheiro0() << ' ' << (*a)->getMCheiro1() << " "
                  << "\n";
            }
        }

}

int Reserva::EspacoVazioVector(int tipo, int lin, int col) {
    //tipo==0 -> procurar espaco para animal
    //tipo==1 -> procurar espaco para alimento
    int flag;
    //conta numero de tentativas, se for = numero de espacos é porque é impossivel adicionar mais alimentos
    int count=0;
    if(tipo==0){
        //qualquer lugar esteja ocupado ou nao
        Reserva::cleanColRandom= aleatorio(0, col-1);
        Reserva::cleanLinRandom= aleatorio(0, lin-1);
        return 0;
    }else if(tipo==1){
        //procurar lugar onde nao esteja já um alimento
        do{
            flag=false;
            Reserva::cleanColRandom= aleatorio(0, col-1);
            Reserva::cleanLinRandom= aleatorio(0, lin-1);

            auto i = alimInReserva.begin();
            for (; i != alimInReserva.end(); i++) {
                if ((*i)->getMPosicaoX() == Reserva::cleanLinRandom && (*i)->getMPosicaoY() == Reserva::cleanColRandom) {
                    flag=true;
                }
            }
            count++;
            if (i != alimInReserva.end() && flag == false) {
                return 0;
            }else if(count == col*lin){
                return -1;
            }

        } while (flag==true && count!=col*lin );
    }
    return 0;
}

void Reserva::feedByPos(term::Terminal &t, int x, int y, int pntNut, int tox) {
    auto i = animInReserva.begin();
    for (; i != animInReserva.end(); i++)
        if ((*i)->getMPosicaoX() == x && (*i)->getMPosicaoY() == y)
            break;

    limpaEcra(t);
    if (i != animInReserva.end()) {
        string user = "user";
        auto *a = new Comida(user, pntNut, tox);
        (*i)->addMemberToHist(a);
        t << (*i)->getMNomeEspecie() << " alimentado com sucesso\n";
    }else
        t << "Nenhum animal na posicao " << x << " " << y << "\n";
}
void Reserva::limpaEcra(term::Terminal &t){
    t << move(17,0); clrtoeol();
    t << move(18,0); clrtoeol();
    t << move(19,0); clrtoeol();
    t << move(20,0); clrtoeol();
    t << move(21,0); clrtoeol();
    t << move(22,0); clrtoeol();
    t << move(23,0); clrtoeol();
    t << move(24,0); clrtoeol();
    t << move(25,0); clrtoeol();
    t << move(26,0); clrtoeol();
    t << move(27,0); clrtoeol();
    t << move(28,0); clrtoeol();
    t << move(29,0); clrtoeol();
    t << move(17,0);
}

void Reserva::feedById(term::Terminal &t, int idToFeed, int pntNut, int tox) {
    auto i = animInReserva.begin();
    for (; i != animInReserva.end(); i++)
        if ((*i)->getMId()==idToFeed)
            break;

    limpaEcra(t);
    if (i != animInReserva.end()) {
        string user = "user";
        auto *a = new Comida(user, pntNut, tox);
        (*i)->addMemberToHist(a);
        t << (*i)->getMNomeEspecie() << " alimentado com sucesso";
    }else
        t << "Nenhum animal com o id " << idToFeed;
}

void Reserva::empty(term::Terminal &t, int x, int y) {
    //apagar quantos animais estiverem la
    int flag=false;
    do {
        auto i = animInReserva.begin();
        for (; i != animInReserva.end(); i++)
            if ((*i)->getMPosicaoX() == x && (*i)->getMPosicaoY() == y)
                break;

        if (i != animInReserva.end()) {
            animInReserva.erase(i);
            delete *i;
            content[x][y] = '+';
        }else if(i == animInReserva.end()){
            flag=true;
        }
    }while(flag!=true);
    //se houver alimento apagar
    auto s = alimInReserva.begin();
    for (; s != alimInReserva.end(); s++)
        if ((*s)->getMPosicaoX() == x && (*s)->getMPosicaoY() == y)
            break;

    if (s != alimInReserva.end()) {
        alimInReserva.erase(s);
        delete *s;
        content[x][y] = '+';
        t << "Apagado com suceesso!";
    }

}

void Reserva::info(term::Terminal &t, int infoID) {
    int flag=false;
    auto i = animInReserva.begin();
    for (; i != animInReserva.end(); i++)
        if ((*i)->getMId() == infoID)
            break;
    limpaEcra(t);
    if (i != animInReserva.end()) {
        flag=true;
        t << "ID: " << to_string((*i)->getMId()) << " Tipo: Animal "
          << "Nome especie: " << (*i)->getMNomeEspecie() << " "
          << "Posicao X/Y: " << to_string((*i)->getMPosicaoX()) << '/' << to_string((*i)->getMPosicaoY())
          << " ";

        if ((*i)->isMVivo() == 0)
            t << "O animal esta morto... ";
        else if ((*i)->isMVivo() == 1)
            t << "O animal esta vivo... ";

        t << "Massa: " << to_string((*i)->getMPeso()) << " "
          << "Fome: " << to_string((*i)->getMFome()) << " "
          << "Saude: " << to_string((*i)->getMSaude()) << " ";
        //historico
        t << (*i)->toString();
        t << "\n";
    }

    auto alm = alimInReserva.begin();
    for (; alm != alimInReserva.end(); alm++)
        if ((*alm)->getMId() == infoID)
            break;


    if (alm != alimInReserva.end()) {
        flag=true;
        t << "ID: " << to_string((*alm)->getMId()) << " Tipo: Alimento "
          << "Nome especie: " << (*alm)->getMEspecie() << " "
          << "Posicao X/Y: " << to_string((*alm)->getMPosicaoX()) << '/' << to_string((*alm)->getMPosicaoY()) << " "
          << "Toxicidade: " << to_string((*alm)->getMToxicidade()) << " "
          << "Valor nutritivo: " << to_string((*alm)->getMVnutritivo()) << " "
          << "Cheiro: " << (*alm)->getMCheiro0() << '/' << (*alm)->getMCheiro1() << " "
          << "\n";
    }

    if(!flag)
        t << "Nada criado com o id" + to_string(infoID);
}

void Reserva::visanim(term::Terminal &t) {
    extern int row;
    extern int col;
    extern int rows;
    extern int cols;
    auto i = animInReserva.begin();
    limpaEcra(t);
    for (; i != animInReserva.end(); i++)
        if (( (*i)->getMPosicaoX() >= row && (*i)->getMPosicaoX() < rows + row ) && ( (*i)->getMPosicaoY() >= col && (*i)->getMPosicaoY() < cols + col) )
        {
            if (i != animInReserva.end()) {
                t << "ID: " << (*i)->getMId() << " Especie: " << (*i)->getMNomeEspecie() << " Saude: " << (*i)->getMSaude() << '\n';
            }else
                t << "Nenhum animal na area visivel da reserva";
        }
}


int Reserva::printAnms(term::Terminal &t) {
    limpaEcra(t);
    if(animInReserva.empty()) {
        t << "Nao existem animais..." << "\n";
        return 1;
    }
    for (auto & i : animInReserva) {
        t << "ID: " << i->getMId() << " Especie: " << i->getMNomeEspecie() << " Saude: " << i->getMSaude() << '\n';
    }
    return 0;
}


void Reserva::printAlmt(term::Terminal &t) {
    limpaEcra(t);
    if(alimInReserva.empty()) {
        t << "Nao existem alimentos..." << " ";
    }
    for (auto & i : alimInReserva) {
        t << "ID: " << i->getMId() << " ";
        t << "Especie: " << i->getMEspecie() << " ";
        t << "Duracao: " << i->getMDuracao() << " ";
        t << "Valor Nutritivo: " << i->getMVnutritivo() << " ";
        t << "Posicao X/Y: " << i->getMPosicaoX() <<  '/' << i->getMPosicaoY() << " ";
        t << "Toxicidade: " << i->getMToxicidade() << " ";
        t << "Cheiro: " << i->getMCheiro0() << ' ' << i->getMCheiro1() << " ";
        t << "\n";
    }
}

void Reserva::store(term::Terminal &t, const string& nomeFich) {
    limpaEcra(t);
    // Abrir
    std::ofstream out_file(nomeFich+".txt");

    //escrever tamanho
    out_file << (int)content.size() << " ";
    out_file << (int)content[0].size() << endl;

    // escrever tamanho da reserva
    out_file << content.size() << endl;

// escrever valores (char) da reserva
    for (auto & i : content) {
        for (char j : i) {
            out_file << j << " ";
        }
        out_file << endl;
    }

// tamanho alimInReserva
    out_file << alimInReserva.size() << endl;

// escrever valores de alim
    for (auto & i : alimInReserva) {
        out_file << i->getMId() << " ";
        out_file << i->getMSimbolo() << " ";
        out_file << i->getMDuracao() << " ";
        out_file << i->getMVnutritivo() << " ";
        out_file << i->getMToxicidade() << " ";
        out_file << i->getMPosicaoX() << " ";
        out_file << i->getMPosicaoY() << " ";
        out_file << i->getMCheiro0() << " ";
        out_file << i->getMCheiro1() << " ";
        out_file << i->getMEspecie() << " ";
        out_file << i->isMVivo() << " ";
        out_file << i->getMTempoVidaAtual() << " ";
        out_file << i->getMPosXf() << " ";
        out_file << i->getMPosYf() << " ";
        out_file << i->isMFilho() << " ";
        out_file << i->isMCriado() << " ";
    }

// tam animInreserva
    out_file << animInReserva.size() << endl;

    // escrever valores
    for (auto & i : animInReserva) {
        out_file << i->getMId() << " ";
        out_file << i->getMNomeProprio() << " ";
        out_file << i->getMNomeEspecie() << " ";
        out_file << i->isMVivo() << " ";
        out_file << i->getMFome() << " ";
        out_file << i->getMPosicaoX() << " ";
        out_file << i->getMPosicaoY() << " ";
        out_file << i->getMSize() << " ";
        out_file << i->getMSimbolo() << " ";
        out_file << i->getMSaude() << " ";
        out_file << i->getMPercecao() << " ";
        out_file << i->getMNumMaxPosPorInst() << " ";
        out_file << i->getMIdade() << " ";
        out_file << i->getMVelocFuga() << " ";
        out_file << i->getMPeso() << " ";
        out_file << i->getMFomeGanhPorInstante() << " ";
        out_file << i->getMSaudePerdPorInst() << " ";
        out_file << i->getMInstMorte() << " ";
        out_file << i->getMCheiroalimPreferido() << " ";
        out_file << i->getMVelocidade() << " ";
        out_file << i->getMNFilhos() << " ";
        out_file << i->getMInstNascFilho() << " ";
        out_file << i->getMPesoAnimFugir() << " ";
        out_file << i->getMTempoReproducao() << " ";
        out_file << i->getMProbFilhoNascer() << " ";
        out_file << i->getMDistMaxFIlho() << " ";
        out_file << i->getMVNutricCorpo() << " ";
        out_file << i->getMNToxiciCorpo() << " ";
        out_file << i->getMDistObjetivo() << " ";
        out_file << i->getMPosXobjetivo() << " ";
        out_file << i->getMPosYObjetivo() << " ";
        out_file << i->getMPosXf() << " ";
        out_file << i->getMPosYf() << " ";
        out_file << i->getMInstNasc() << " ";
        out_file << i->getMPosXp() << " ";
        out_file << i->getMPosYp() << " ";
        out_file << i->getMIdPai() << " ";
        out_file << i->isBolsaMarsupial() << " ";
        out_file << i->getInstBolsa() << " ";
        out_file << i->isMCriado() << endl;

        // Write the number of foods in the Animal's food vectornumero de comidas
         out_file << i->getMHistSize() << endl;

// escrever historico
        for (int j = 0; j < i->getMHistSize(); j++) {
            out_file << i->getMHist()[j]->getMNomeComida() << " "
                     << i->getMHist()[j]->getMPontosNutritivos() << " "
                     << i->getMHist()[j]->getMToxicidade() << endl;
        }

    }

    out_file.close();
    t << "Reserva guardada com sucesso!";
}

void Reserva::restore(term::Terminal &t, const string& nomeFich) {
    limpaEcra(t);
    // abrir
    std::ifstream in_file(nomeFich+".txt");

    //ler tamanho
    in_file >> *linhas >> *colunas;
    Reserva::auxNumLin=*linhas;
    Reserva::auxNumCol=*colunas;

    content.clear();

    content.resize(*linhas, vector<char>(*colunas));

    content.clear();

    // ler tamanho content
    int content_size;
    in_file >> content_size;

    // ler para content os valores char
    for (int i = 0; i < content_size; i++) {
        std::vector<char> auxLinha;
        for (int j = 0; j < content[i].size(); j++) {
            char ch;
            in_file >> ch;
            auxLinha.push_back(ch);
        }
        content.push_back(auxLinha);
    }

    // ler tam alim
    int alimInReserva_size;
    in_file >> alimInReserva_size;

    alimInReserva.clear();

    // ler valores para alim
    for (int i = 0; i < alimInReserva_size; i++) {
        int idres, duracao, vnutritivo, toxicidade, posX, posY;
        string especie, cheiro0, cheiro1;
        char simbolo;
        bool vivo, filho, criado;
        int tempoVidaAtual, posXf, posYf;
        in_file >> id >> simbolo >> duracao >> vnutritivo >> toxicidade >> posX >> posY >>
        cheiro0 >> cheiro1 >> especie >> vivo >> tempoVidaAtual >> posXf >> posYf >> filho >> criado;
        alimInReserva.push_back(new Alim(posX, posY, especie, simbolo, duracao, vnutritivo, toxicidade, cheiro0, cheiro1));
        alimInReserva.at(alimInReserva.size()-1)->setMCheiro0(cheiro0);
        alimInReserva.at(alimInReserva.size()-1)->setMCheiro1(cheiro1);
        alimInReserva.at(alimInReserva.size()-1)->setMVivo(vivo);
        alimInReserva.at(alimInReserva.size()-1)->setMTempoVidaAtual(tempoVidaAtual);
        alimInReserva.at(alimInReserva.size()-1)->setMPosXf(posXf);
        alimInReserva.at(alimInReserva.size()-1)->setMPosYf(posYf);
        alimInReserva.at(alimInReserva.size()-1)->setMFilho(filho);
        alimInReserva.at(alimInReserva.size()-1)->setMCriado(criado);
        Reserva::atualConstAlmFich(alimInReserva.at(alimInReserva.size()-1)->getMId(), t);
    }

    // ler tam anim
    int animInReserva_size;
    in_file >> animInReserva_size;

    animInReserva.clear();

    // ler valores anim
    for (int i = 0; i < animInReserva_size; i++) {
        int idauxAn, saudeInic, percecao, numMaxPosPorInst, idade, velocFuga, fomeGanhPorInstante, saudePerdPorInst,
                instMorte, n_filhos, instNascFilho, pesoAnimFugir, tempoReproducao, probFilhoNascer, distMaxFilho,
                vNutricCorpo, nToxiciCorpo, velocidade, posX, posY, distObjetivo, posXObjetivo, posYObjetivo, posXf, posYf, instNasc, posXp, posYp, idPai, instBolsa;
        string nomeProprio,nomeEspecie;
        char simbolo, cheiroalimPreferido;
        float peso;
        bool vivo, criado, bolsaMarsupial;
        int fome;
        int size;
        in_file >> idauxAn >> nomeProprio >> nomeEspecie >> vivo >> fome >> posX >> posY >> size >> simbolo >> saudeInic >> percecao
                >> numMaxPosPorInst >> idade
                >> velocFuga >> peso >> fomeGanhPorInstante >> saudePerdPorInst >> instMorte >> cheiroalimPreferido
                >> velocidade >> n_filhos >> instNascFilho >> pesoAnimFugir >> tempoReproducao >> probFilhoNascer
                >> distMaxFilho >> vNutricCorpo >> nToxiciCorpo >> distObjetivo >> posXObjetivo >> posYObjetivo >>
                posXf >> posYf >> instNasc >> posXp >> posYp >> idPai >> bolsaMarsupial >> instBolsa >> criado;
        animInReserva.push_back(
                new Anim(posX, posY, nomeEspecie, simbolo, saudeInic, percecao, numMaxPosPorInst, idade, velocFuga, peso,
                         fomeGanhPorInstante, saudePerdPorInst, instMorte, cheiroalimPreferido, velocidade, n_filhos,
                         instNascFilho, pesoAnimFugir, tempoReproducao, probFilhoNascer, distMaxFilho, vNutricCorpo,
                         nToxiciCorpo));
        animInReserva.at(animInReserva.size()-1)->setMVivo(vivo);
        animInReserva.at(animInReserva.size()-1)->setMFome(fome);
        animInReserva.at(animInReserva.size()-1)->setMSize(size);
        animInReserva.at(animInReserva.size()-1)->setMDistObjetivo(distObjetivo);
        animInReserva.at(animInReserva.size()-1)->setMPosXobjetivo(posXObjetivo);
        animInReserva.at(animInReserva.size()-1)->setMPosYObjetivo(posYObjetivo);
        animInReserva.at(animInReserva.size()-1)->setMPosXf(posXf);
        animInReserva.at(animInReserva.size()-1)->setMPosYf(posYf);
        animInReserva.at(animInReserva.size()-1)->setMInstNasc(instNasc);
        animInReserva.at(animInReserva.size()-1)->setMPosXp(posXp);
        animInReserva.at(animInReserva.size()-1)->setMPosYp(posYp);
        animInReserva.at(animInReserva.size()-1)->setMIdPai(idPai);
        animInReserva.at(animInReserva.size()-1)->setBolsaMarsupial(bolsaMarsupial);
        animInReserva.at(animInReserva.size()-1)->setInstBolsa(instBolsa);
        animInReserva.at(animInReserva.size()-1)->setMCriado(criado);
        Reserva::atualConstAnmFich(animInReserva.at(animInReserva.size()-1)->getMId(), t);

        // ler tam historico
        int hist_size;
        in_file >> hist_size;

        // ler valores historico
        string nomeComida;
        int PNutritivos, Toxic;
        for (int j = 0; j < hist_size; j++) {
            in_file >> nomeComida >> PNutritivos >> Toxic;
            auto *a = new Comida(nomeComida, PNutritivos, Toxic);
            animInReserva[i]->addMemberToHist(a);
        }

    }

    in_file.close();
    t << "recuperado com sucesso...";
}

void Reserva::nextInst(term::Terminal &t, int N, int P) {
    do {
        vector <int> auxX;
        vector <int> auxY;
        vector <char> simb;
        int x=-1,y=-1;
        bool flag=false;
        //para a saude do carneiro ser igual à da ovelha
        int saude;
        int idpai;
        int posPaiX, posPaiY;
        instante++;

    //atualiza alimentos
    auto alm = alimInReserva.begin();
    for (; alm != alimInReserva.end(); alm++) {
        flag=false;
        (*alm)->Atualiza(t);

        //ve se ja existem alimentos na posicao
        auto j = alimInReserva.begin();
        for (; j != alimInReserva.end(); j++) {
            if ((*j)->getMPosicaoX() == (*alm)->getMPosXf() && (*j)->getMPosicaoY() == (*alm)->getMPosYf()) {
                flag = true;
            }
        }

        if ((*alm)->getMPosXf() != -1 && (*alm)->getMPosYf() != -1 && !flag && !(*alm)->isMFilho()) {
            if ((*alm)->getMSimbolo() == 'r'){
                auxX.push_back( (*alm)->getMPosXf() );
                auxY.push_back( (*alm)->getMPosYf() );
                simb.push_back((*alm)->getMSimbolo());
                (*alm)->setMPosXf(-1);
                (*alm)->setMPosYf(-1);
                (*alm)->setMFilho(true);
            }
        }
    }

    for (int a = 0; a < auxX.size(); ++a) {
        if(auxX.at(a) != -1 && auxY.at(a) != -1){
            Alimento* novo = nullptr;
            switch (simb.at(a)) {
                case 'r':
                    novo = new Relva(auxX.at(a),auxY.at(a));
                    break;
            }
            if(novo != nullptr) {
                alimInReserva.push_back(novo);
                Reserva::atualConstAlmFich(novo->getMId(), t);
            }
        }
    }


    auxX.clear();
    auxY.clear();
    simb.clear();

        //atualiza animais
        auto i = animInReserva.begin();
        for (; i != animInReserva.end(); i++) {
            content[(*i)->getMPosicaoX()][(*i)->getMPosicaoY()] = '+';
            (*i)->Atualiza(t);

            if ((*i)->getMPosXf() != -1 && (*i)->getMPosYf() != -1) {
                if ((*i)->getMSimbolo() == 'C' || (*i)->getMSimbolo() == 'O' || (*i)->getMSimbolo() == 'L' || (*i)->getMSimbolo() == 'G'){
                    auxX.push_back( (*i)->getMPosXf() );
                    auxY.push_back( (*i)->getMPosYf() );
                    simb.push_back((*i)->getMSimbolo());
                    saude=(*i)->getMSaude();
                    idpai=(*i)->getMId();
                    posPaiX=(*i)->getMPosicaoX();
                    posPaiY=(*i)->getMPosicaoY();
                    (*i)->setMPosXf(-1);
                    (*i)->setMPosYf(-1);
                }
            }

        }

    for (int a = 0; a < auxX.size(); ++a) {
        if(auxX.at(a) != -1 && auxY.at(a) != -1){
            Animal* novo = nullptr;
            switch (simb.at(a)) {
                case 'C':
                    novo = new Coe(auxX.at(a),auxY.at(a));
                    break;
                case 'O':
                    novo = new Ove(auxX.at(a),auxY.at(a));
                    novo->setMSaude(saude);
                    break;
                case 'L':
                    novo = new Lobo(auxX.at(a),auxY.at(a));
                    break;

                case 'G':
                    novo = new Cang (auxX.at(a),auxY.at(a));
                    novo->setMIdPai(idpai);
                    novo->setMPosXp(posPaiX);
                    novo->setMPosYp(posPaiY);
                    break;
                case 'M':
                    novo = new Misterio(auxX.at(a),auxY.at(a));
                    break;
            }
            if(novo != nullptr) {
                novo->setMInstNasc(instante);
                animInReserva.push_back(novo);
                Reserva::atualConstAnmFich(novo->getMId(), t);
            }
        }
    }
    N--;
   } while (N > 0);
}


void Reserva::andaC(int idC, term::Terminal &t) {
    limpaEcra(t);
    int distAlmnt;
    int distInmg;
    bool objetivo=true;

    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++)
        if ((*h)->getMId() == idC)
            break;

    if (h != animInReserva.end()) {
        if ((*h)->getMDistObjetivo() == -1)
            objetivo = false;
        distAlmnt = (int)round(sqrt(
                ((*h)->getMPosXobjetivo() - (*h)->getMPosicaoX()) * ((*h)->getMPosXobjetivo()- (*h)->getMPosicaoX()) +
                ((*h)->getMPosYObjetivo() - (*h)->getMPosicaoY()) * ((*h)->getMPosYObjetivo() - (*h)->getMPosicaoY())));
        if(distAlmnt > 4){
            //perde objetivo de vista
            (*h)->setMDistObjetivo(-1);
            objetivo=false;
        }
        auto i = alimInReserva.begin();
        for (; i != alimInReserva.end(); i++) {
            if ((*i)->getMCheiro0() == "verdura" || (*i)->getMCheiro1() == "verdura") {
                //calcular distancia ao alimento e se for menor atualizar objetivo
                distAlmnt = (int)round(sqrt(
                        ((*i)->getMPosicaoX() - (*h)->getMPosicaoX()) * ((*i)->getMPosicaoX() - (*h)->getMPosicaoX()) +
                        ((*i)->getMPosicaoY() - (*h)->getMPosicaoY()) * ((*i)->getMPosicaoY() - (*h)->getMPosicaoY())));
                //se estiver dentro da sua percecao e for menor que o atual objetivo atualiza objetivo(ou se nao tiver objetivo)
                //sqrt(32) é a distancia ente um ponto e um ponto a 4 char de distancia(percecao)
                if (distAlmnt <= 4 && (distAlmnt < (*h)->getMDistObjetivo() || !objetivo)) {
                    objetivo = true;
                    (*h)->setMPosXobjetivo((*i)->getMPosicaoX());
                    (*h)->setMPosYObjetivo((*i)->getMPosicaoY());
                    (*h)->setMDistObjetivo(distAlmnt);
                }
            }
        }


        bool inimigo = false;
        int xInimigo, yInimigo;
        //procura inimigo
        auto a = animInReserva.begin();
        for (; a != animInReserva.end(); a++) {
            //ver se é inimigo e calcular distancia-> se estiver na sua percecao foge
            if ((*a)->getMPeso() > 10) {
                distInmg = (int)round(sqrt(
                        ((*a)->getMPosicaoX() - (*h)->getMPosicaoX()) * ((*a)->getMPosicaoX() - (*h)->getMPosicaoX()) +
                        ((*a)->getMPosicaoY() - (*h)->getMPosicaoY()) * ((*a)->getMPosicaoY() - (*h)->getMPosicaoY())));
                //se estiver dentro da sua percecao é porque viu o inimigo, tem de fugir
                if (distInmg <= 4 || (*a)->getMId() != (*h)->getMId()) {
                    inimigo = true;
                    xInimigo = (*a)->getMPosicaoX();
                    yInimigo = (*a)->getMPosicaoY();
                }
            }
        }

        //distancia do andamento
        int distan=aleatorio(1, 2);
        if ((*h)->getMFome() > 10)
            distan=aleatorio(1, 3);
        else if((*h)->getMFome() > 20)
            distan=aleatorio(1, 4);

          if (inimigo) {
            //foge
            //ciclo que calcula randoms e repete enquanto a distancia ao inimigo nao for menor que a atual;
            int distaux,auxX, auxY;
            do{
                auxX= aleatorio((*h)->getMPosicaoX()-distan,(*h)->getMPosicaoX()+distan);
                auxY= aleatorio((*h)->getMPosicaoY()-distan,(*h)->getMPosicaoY()+distan);
                distaux = (int)round(sqrt(
                        (auxX - xInimigo) * (auxX - xInimigo) +
                        (auxY - yInimigo) * (auxY - yInimigo)));

               // t << "Vou: " << auxX << " /" << auxY;
            }while(distaux <= distInmg);
            content[(*h)->getMPosicaoX()][(*h)->getMPosicaoY()]='+';
            (*h)->setMPosicaoX(auxX);
            (*h)->setMPosicaoY(auxY);

        } else if (objetivo) {
            int distaux,auxX, auxY,aux1X,aux1Y;
            //ver se pode ir direto ao objetivo
            distaux = (int)round(sqrt(
                    ((*h)->getMPosicaoX() - (*h)->getMPosXobjetivo()) * ((*h)->getMPosicaoX()- (*h)->getMPosXobjetivo()) +
                    ((*h)->getMPosicaoY() - (*h)->getMPosYObjetivo()) * ((*h)->getMPosicaoY() - (*h)->getMPosYObjetivo())));
            if(distaux <= distan || distaux <= 2){
                auxX=(*h)->getMPosXobjetivo();
                auxY=(*h)->getMPosYObjetivo();
            }else{
                do{
                    auxX= aleatorio((*h)->getMPosicaoX()-1,(*h)->getMPosicaoX()+1);
                    auxY= aleatorio((*h)->getMPosicaoY()-1,(*h)->getMPosicaoY()+1);
                    distaux = (int)round(sqrt(
                            (auxX - (*h)->getMPosXobjetivo()) * (auxX - (*h)->getMPosXobjetivo()) +
                            (auxY - (*h)->getMPosYObjetivo()) * (auxY - (*h)->getMPosYObjetivo())));
                    aux1X= aleatorio((*h)->getMPosicaoX()-2,(*h)->getMPosicaoX()+2);
                    aux1Y= aleatorio((*h)->getMPosicaoY()-2,(*h)->getMPosicaoY()+2);
                    if(sqrt(
                            (auxX - (*h)->getMPosXobjetivo()) * (auxX - (*h)->getMPosXobjetivo()) +
                            (auxY - (*h)->getMPosYObjetivo()) * (auxY - (*h)->getMPosYObjetivo())) < distaux){
                        distan = 2;
                        auxX=aux1X;
                        auxY=aux1Y;
                    }else{
                        distan = 1;
                    }
                }while(distaux > (*h)->getMDistObjetivo() || (distaux == (*h)->getMDistObjetivo() && (auxX != (*h)->getMPosXobjetivo() || auxY != (*h)->getMPosYObjetivo())));
            }
            content[(*h)->getMPosicaoX()][(*h)->getMPosicaoY()]='+';
            (*h)->setMPosicaoX(auxX);
            (*h)->setMPosicaoY(auxY);

        } else {
            int direcao = aleatorio(0, 3);
            if (direcao == 0) {
                (*h)->setMPosicaoX((*h)->getMPosicaoX() - distan);
            } else if (direcao == 1) {
                (*h)->setMPosicaoX((*h)->getMPosicaoX() + distan);
            } else if (direcao == 2) {
                (*h)->setMPosicaoY((*h)->getMPosicaoY() - distan);
            } else if (direcao == 3) {
                (*h)->setMPosicaoY((*h)->getMPosicaoY() + distan);
            }
        }

        // fazer o animal dar a volta
        if ((*h)->getMPosicaoX() < 0 || (*h)->getMPosicaoX() >= auxNumLin || (*h)->getMPosicaoY() < 0 || (*h)->getMPosicaoY() >= auxNumCol) {
            int atualizaPos = ((*h)->getMPosicaoX() + auxNumLin) % auxNumLin;
            (*h)->setMPosicaoX(atualizaPos);
            atualizaPos = ((*h)->getMPosicaoY() + auxNumCol) % auxNumCol;
            (*h)->setMPosicaoY(atualizaPos);
        }


    }

}

void Reserva::comeC(int idC, term::Terminal &t) {
    limpaEcra(t);
    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++)
        if ((*h)->getMId() == idC)
            break;

    if (h != animInReserva.end()) {

    auto i = alimInReserva.begin();
    for (; i != alimInReserva.end(); i++)
        if ((*i)->getMPosicaoX() == (*h)->getMPosicaoX() && (*i)->getMPosicaoY() == (*h)->getMPosicaoY())
            break;
    if (i != alimInReserva.end() && ( (*i)->getMCheiro0()=="verdura" || (*i)->getMCheiro1()=="verdura" )) {
        string esp = (*i)->getMEspecie();
        int vnut =  (*i)->getMVnutritivo();
        int tox = (*i)->getMToxicidade();
        auto *a = new Comida( esp,vnut,tox);
        (*h)->addMemberToHist(a);
        //somar à fome o valor nutritivo
        (*h)->setMFome((*h)->getMFome()-vnut);
        //subtrair à saude o valor de toxicidade
        (*h)->setMSaude((*h)->getMSaude()-tox);
        //apagar objetivo
        (*h)->setMDistObjetivo(-1);
        delete *i;
        alimInReserva.erase(i);
        content[(*i)->getMPosicaoX()][(*i)->getMPosicaoY()] = '+';
    }

    }

}

void Reserva::fomeC(int idC) {
    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++)
        if ((*h)->getMId() == idC)
            break;
    if (h != animInReserva.end()) {
        (*h)->setMFome((*h)->getMFome() +1);
        if ((*h)->getMFome() > 20) {
            (*h)->setMSaudePerdPorInst(2);
            (*h)->setMNumMaxPosPorInst(4);
        } else if ((*h)->getMFome() > 10) {
            (*h)->setMSaudePerdPorInst(1);
            (*h)->setMNumMaxPosPorInst(3);
        }
    }
}

void Reserva::morteC(int idAux, term::Terminal &t) {
    limpaEcra(t);
    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++) {
        if ((*h)->getMId() == idAux && (((*h)->getMSaude() <= 0 || (*h)->getMIdade() >= (*h)->getMInstMorte()))) {
            (*h)->setMVivo(false);
        }
    }
}

void Reserva::saudeC(int idC) {
    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++)
        if ((*h)->getMId() == idC)
            break;
    if (h != animInReserva.end()) {
        int saude = (*h)->getMSaude();
        int saudePerdida = (*h)->getMSaudePerdPorInst();
        (*h)->setMSaude(saude - saudePerdida);
    }
}

void Reserva::reproduzC(int idC, term::Terminal &t) {
    limpaEcra(t);
    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++)
        if ((*h)->getMId() == idC)
            break;

    if (h != animInReserva.end()) {
        if (instante - (*h)->getMInstNasc() > (*h)->getMInstNascFilho() + 8 ) {
            //ja passaram 8 instantes desde o nascimento
            //criar filho
            int prob = aleatorio(0, 100);
            if (prob <= 50) {
                //nasce
                int dx = aleatorio(-10, 10) + (*h)->getMPosicaoX();
                int dy = aleatorio(-10, 10) + (*h)->getMPosicaoY();
                // fazer o animal dar a volta
                if (dx < 0 || dx >= auxNumLin || dy < 0 || dy >= auxNumCol) {
                    int atualizaPos = (dx + auxNumLin) % auxNumLin;
                    dx=atualizaPos;
                    atualizaPos = (dy + auxNumCol) % auxNumCol;
                    dy=atualizaPos;
                }
                (*h)->setMPosXf(dx);
                (*h)->setMPosYf(dy);
                }
            //alterar o instante de nascimento
            (*h)->setMInstNascFilho(instante);
            }
        }
    }

void Reserva::morte(term::Terminal &t) {
    limpaEcra(t);
            auto i = animInReserva.begin();
            do {
                for (; i != animInReserva.end(); i++)
                    if (!(*i)->isMVivo())
                        break;

                if (i != animInReserva.end()) {
                    if((*i)->getMSimbolo()=='O'){
                        //cria alimento do tipo corpo
                        int x,y;
                        x=(*i)->getMPosicaoX();
                        y=(*i)->getMPosicaoY();
                        // fazer o alimento dar a volta se passou os limites
                        if (x < 0 || x >= auxNumLin || y < 0 || y >= auxNumCol) {
                            int atualizaPos = (x + auxNumLin) % auxNumLin;
                            x=atualizaPos;
                            atualizaPos = (y + auxNumCol) % auxNumCol;
                            y=atualizaPos;
                        }
                        AddAlimento("p",t,x,y,0, (*i)->getMSaude());
                    }else if((*i)->getMSimbolo()=='L'){
                        //cria alimento do tipo corpo
                        int x,y;
                        x=(*i)->getMPosicaoX();
                        y=(*i)->getMPosicaoY();
                        // fazer o alimento dar a volta se passou os limites
                        if (x < 0 || x >= auxNumLin || y < 0 || y >= auxNumCol) {
                            int atualizaPos = (x + auxNumLin) % auxNumLin;
                            x=atualizaPos;
                            atualizaPos = (y + auxNumCol) % auxNumCol;
                            y=atualizaPos;
                        }
                        AddAlimento("p",t,x,y,0, 10);
                    }else if((*i)->getMSimbolo()=='G'){
                        //cria alimento do tipo corpo
                        int x,y;
                        x=(*i)->getMPosicaoX();
                        y=(*i)->getMPosicaoY();
                        // fazer o alimento dar a volta se passou os limites
                        if (x < 0 || x >= auxNumLin || y < 0 || y >= auxNumCol) {
                            int atualizaPos = (x + auxNumLin) % auxNumLin;
                            x=atualizaPos;
                            atualizaPos = (y + auxNumCol) % auxNumCol;
                            y=atualizaPos;
                        }
                        AddAlimento("p",t,x,y,5, 15);
                    }
                    content[(*i)->getMPosicaoX()][(*i)->getMPosicaoY()] = '+';
                    delete *i;
                    animInReserva.erase(i);
                }
            } while (i != animInReserva.end());
}

void Reserva::andaO(int idO, term::Terminal &t) {
    limpaEcra(t);
        int distAlmnt;
        int distInmg;
        bool objetivo=true;

        auto h = animInReserva.begin();
        for (; h != animInReserva.end(); h++)
            if ((*h)->getMId() == idO)
                break;

        if (h != animInReserva.end()) {
            if ((*h)->getMDistObjetivo() == -1)
                objetivo = false;
            distAlmnt = (int)round(sqrt(
                    ((*h)->getMPosXobjetivo() - (*h)->getMPosicaoX()) * ((*h)->getMPosXobjetivo()- (*h)->getMPosicaoX()) +
                    ((*h)->getMPosYObjetivo() - (*h)->getMPosicaoY()) * ((*h)->getMPosYObjetivo() - (*h)->getMPosicaoY())));
            if(distAlmnt > 3){
                //perde objetivo de vista
                (*h)->setMDistObjetivo(-1);
                objetivo=false;
            }

            auto i = alimInReserva.begin();
            for (; i != alimInReserva.end(); i++) {
                if ((*i)->getMCheiro0() == "erva" || (*i)->getMCheiro1() == "erva") {
                    //calcular distancia ao alimento e se for menor atualizar objetivo
                    distAlmnt = (int)round(sqrt(
                            ((*i)->getMPosicaoX() - (*h)->getMPosicaoX()) * ((*i)->getMPosicaoX() - (*h)->getMPosicaoX()) +
                            ((*i)->getMPosicaoY() - (*h)->getMPosicaoY()) * ((*i)->getMPosicaoY() - (*h)->getMPosicaoY())));
                    //se estiver dentro da sua percecao e for menor que o atual objetivo atualiza objetivo(ou se nao tiver objetivo)
                    //sqrt(32) é a distancia ente um ponto e um ponto a 4 char de distancia(percecao)
                    if (distAlmnt <= 3 && (distAlmnt < (*h)->getMDistObjetivo() || !objetivo)) {
                        objetivo = true;
                        (*h)->setMPosXobjetivo((*i)->getMPosicaoX());
                        (*h)->setMPosYObjetivo((*i)->getMPosicaoY());
                        (*h)->setMDistObjetivo(distAlmnt);
                    }
                }
            }


            bool inimigo = false;
            int xInimigo, yInimigo;
            //procura inimigo
            auto a = animInReserva.begin();
            for (; a != animInReserva.end(); a++) {
                //ver se é inimigo e calcular distancia-> se estiver na sua percecao foge
                if ((*a)->getMPeso() > 15) {
                    distInmg = (int)round(sqrt(
                            ((*a)->getMPosicaoX() - (*h)->getMPosicaoX()) * ((*a)->getMPosicaoX() - (*h)->getMPosicaoX()) +
                            ((*a)->getMPosicaoY() - (*h)->getMPosicaoY()) * ((*a)->getMPosicaoY() - (*h)->getMPosicaoY())));
                    //se estiver dentro da sua percecao é porque viu o inimigo, tem de fugir
                    if (distInmg <= 3 || (*a)->getMId() != (*h)->getMId()) {
                        //t << "VIU O INIMIGO";
                        //viu o inimigo
                        inimigo = true;
                        xInimigo = (*a)->getMPosicaoX();
                        yInimigo = (*a)->getMPosicaoY();
                    }
                }
            }

            //distancia do andamento
            int distan=1;
            if ((*h)->getMFome() > 15)
                distan=aleatorio(1, 2);

            if (inimigo) {
                //foge
                //ciclo que calcula randoms e repete enquanto a distancia ao inimigo nao for menor que a atual;
                int distaux,auxX, auxY;
                do{
                    auxX= aleatorio((*h)->getMPosicaoX()-distan,(*h)->getMPosicaoX()+distan);
                    auxY= aleatorio((*h)->getMPosicaoY()-distan,(*h)->getMPosicaoY()+distan);
                    distaux = (int)round(sqrt(
                            (auxX - xInimigo) * (auxX - xInimigo) +
                            (auxY - yInimigo) * (auxY - yInimigo)));

                    // t << "Vou: " << auxX << " /" << auxY;
                }while(distaux <= distInmg);
                content[(*h)->getMPosicaoX()][(*h)->getMPosicaoY()]='+';
                (*h)->setMPosicaoX(auxX);
                (*h)->setMPosicaoY(auxY);

            } else if (objetivo) {
                int distaux,auxX, auxY,aux1X,aux1Y;
                //ver se pode ir direto ao objetivo
                distaux = (int)round(sqrt(
                        ((*h)->getMPosicaoX() - (*h)->getMPosXobjetivo()) * ((*h)->getMPosicaoX()- (*h)->getMPosXobjetivo()) +
                        ((*h)->getMPosicaoY() - (*h)->getMPosYObjetivo()) * ((*h)->getMPosicaoY() - (*h)->getMPosYObjetivo())));
                if(distaux <= 1 || (distaux <= 2 && (*h)->getMFome() > 15)) {
                    auxX = (*h)->getMPosXobjetivo();
                    auxY = (*h)->getMPosYObjetivo();
                }else {
                    do {
                        auxX = aleatorio((*h)->getMPosicaoX() - 1, (*h)->getMPosicaoX() + 1);
                        auxY = aleatorio((*h)->getMPosicaoY() - 1, (*h)->getMPosicaoY() + 1);
                        distaux = (int)round(sqrt(
                                (auxX - (*h)->getMPosXobjetivo()) * (auxX - (*h)->getMPosXobjetivo()) +
                                (auxY - (*h)->getMPosYObjetivo()) * (auxY - (*h)->getMPosYObjetivo())));
                        aux1X = aleatorio((*h)->getMPosicaoX() - 2, (*h)->getMPosicaoX() + 2);
                        aux1Y = aleatorio((*h)->getMPosicaoY() - 2, (*h)->getMPosicaoY() + 2);
                        if (sqrt(
                                (auxX - (*h)->getMPosXobjetivo()) * (auxX - (*h)->getMPosXobjetivo()) +
                                (auxY - (*h)->getMPosYObjetivo()) * (auxY - (*h)->getMPosYObjetivo())) < distaux &&
                            (*h)->getMFome() > 15) {
                            distan = 2;
                            auxX = aux1X;
                            auxY = aux1Y;
                        } else {
                            distan = 1;
                        }
                    } while (distaux > (*h)->getMDistObjetivo() || (distaux == (*h)->getMDistObjetivo() && (auxX != (*h)->getMPosXobjetivo() || auxY != (*h)->getMPosYObjetivo())));
                }
                content[(*h)->getMPosicaoX()][(*h)->getMPosicaoY()]='+';
                (*h)->setMPosicaoX(auxX);
                (*h)->setMPosicaoY(auxY);

            } else {
                int direcao = aleatorio(0, 3);
                if (direcao == 0) {
                    (*h)->setMPosicaoX((*h)->getMPosicaoX() - distan);
                } else if (direcao == 1) {
                    (*h)->setMPosicaoX((*h)->getMPosicaoX() + distan);
                } else if (direcao == 2) {
                    (*h)->setMPosicaoY((*h)->getMPosicaoY() - distan);
                } else if (direcao == 3) {
                    (*h)->setMPosicaoY((*h)->getMPosicaoY() + distan);
                }
            }

            // fazer o animal dar a volta
            if ((*h)->getMPosicaoX() < 0 || (*h)->getMPosicaoX() >= auxNumLin || (*h)->getMPosicaoY() < 0 || (*h)->getMPosicaoY() >= auxNumCol) {
                int atualizaPos = ((*h)->getMPosicaoX() + auxNumLin) % auxNumLin;
                (*h)->setMPosicaoX(atualizaPos);
                atualizaPos = ((*h)->getMPosicaoY() + auxNumCol) % auxNumCol;
                (*h)->setMPosicaoY(atualizaPos);
            }


        }

}

void Reserva::reproduzO(int idO, term::Terminal &t) {
    limpaEcra(t);
    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++)
        if ((*h)->getMId() == idO)
            break;

    if (h != animInReserva.end()) {
        if (instante - (*h)->getMInstNasc() > (*h)->getMInstNascFilho() + 15 ) {
            //ja passaram 8 instantes desde o nascimento
            //criar filho
                //nasce
                int dx = aleatorio(-12, 12) + (*h)->getMPosicaoX();
                int dy = aleatorio(-12, 12) + (*h)->getMPosicaoY();
                // fazer o animal dar a volta
                if (dx < 0 || dx >= auxNumLin || dy < 0 || dy >= auxNumCol) {
                    int atualizaPos = (dx + auxNumLin) % auxNumLin;
                    dx=atualizaPos;
                    atualizaPos = (dy + auxNumCol) % auxNumCol;
                    dy=atualizaPos;
                }
                (*h)->setMPosXf(dx);
                (*h)->setMPosYf(dy);
            //alterar o instante de nascimento
            (*h)->setMInstNascFilho(instante);
        }

    }

}

void Reserva::comeO(int idO, term::Terminal &t) {
    limpaEcra(t);
    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++)
        if ((*h)->getMId() == idO)
            break;

    if (h != animInReserva.end()) {

        auto i = alimInReserva.begin();
        for (; i != alimInReserva.end(); i++)
            if ((*i)->getMPosicaoX() == (*h)->getMPosicaoX() && (*i)->getMPosicaoY() == (*h)->getMPosicaoY())
                break;
        if (i != alimInReserva.end() && ( (*i)->getMCheiro0()=="erva" || (*i)->getMCheiro1()=="erva" )) {
            string esp = (*i)->getMEspecie();
            int vnut =  (*i)->getMVnutritivo();
            int tox = (*i)->getMToxicidade();
            auto *a = new Comida( esp,vnut,tox);
            (*h)->addMemberToHist(a);
            //somar à fome o valor nutritivo
            (*h)->setMFome((*h)->getMFome()-vnut);
            //subtrair à saude o valor de toxicidade
            (*h)->setMSaude((*h)->getMSaude()-tox);
            //apagar objetivo
            (*h)->setMDistObjetivo(-1);
            delete *i;
            alimInReserva.erase(i);
            content[(*i)->getMPosicaoX()][(*i)->getMPosicaoY()] = '+';
        }

    }

}

void Reserva::fomeO(int idO) {
    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++)
        if ((*h)->getMId() == idO)
            break;

    if (h != animInReserva.end()) {
        (*h)->setMFome((*h)->getMFome() +1);
        if ((*h)->getMFome() > 20) {
            (*h)->setMSaudePerdPorInst(2);
        } else if ((*h)->getMFome() > 15) {
            (*h)->setMSaudePerdPorInst(1);
            (*h)->setMNumMaxPosPorInst(2);
        }
    }
}

void Reserva::saudeO(int idO) {
    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++)
        if ((*h)->getMId() == idO)
            break;

    if (h != animInReserva.end()) {
        int saude = (*h)->getMSaude();
        int saudePerdida = (*h)->getMSaudePerdPorInst();
        (*h)->setMSaude(saude - saudePerdida);
    }
}

void Reserva::morteO(int idO, term::Terminal &t) {
    limpaEcra(t);
    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++) {
        if ((*h)->getMId() == idO && (((*h)->getMSaude() <= 0 || (*h)->getMIdade() >= (*h)->getMInstMorte()))) {
            (*h)->setMVivo(false);
        }
    }
}

void Reserva::andaG(int idG, term::Terminal &t) {
    limpaEcra(t);
    int distAlmnt;
    int distInmg;
    bool crianca = false;

    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++)
        if ((*h)->getMId() == idG)
            break;

    if (h != animInReserva.end()) {
        //atualiza pos pai
        auto p = animInReserva.begin();
        for (; p != animInReserva.end(); p++)
            if ((*p)->getMId() == (*h)->getMIdPai())
                break;
        if (p != animInReserva.end()) {
            (*h)->setMPosXp((*p)->getMPosXp());
            (*h)->setMPosYp((*p)->getMPosYp());
        }


        bool inimigo = false;
        int distaux, auxX, auxY;
        int xInimigo, yInimigo;

        //distancia do andamento
        int distan = 1;
        if ((*h)->getMPosXp() != -1 && (*h)->getMPosYp() != -1 && (*h)->getMIdade() < 10)
            crianca = true;
        if((*h)->getMIdade() >= 10){
            crianca=false;
            (*h)->setMPosXp(-1);
            (*h)->setMPosYp(-1);
        }

        //porque o primeiro canguro nao tem pai para seguir nem pai onde se proteger do inimigo entao age como adulto
        if (!crianca || (*h)->getMIdPai() == -2) {

            //t << "ADULTO";

            int direcao = aleatorio(0, 3);

            if (direcao == 0) {
                (*h)->setMPosicaoX((*h)->getMPosicaoX() - distan);
            } else if (direcao == 1) {
                (*h)->setMPosicaoX((*h)->getMPosicaoX() + distan);
            } else if (direcao == 2) {
                (*h)->setMPosicaoY((*h)->getMPosicaoY() - distan);
            } else if (direcao == 3) {
                (*h)->setMPosicaoY((*h)->getMPosicaoY() + distan);
            }
        } else{
            //procurar animal alem do pai e de si proprio para ter medo
            int distInmgAux=-1;//guarda o inimigo mais proximo
            auto a = animInReserva.begin();
            for (; a != animInReserva.end(); a++) {
                //ver se nao é o pai e nem ele proprio
                if ((*a)->getMPosicaoX() != (*h)->getMPosXp() && (*a)->getMPosicaoY() != (*h)->getMPosYp() && (*a)->getMPosicaoX() != (*h)->getMPosicaoX() && (*a)->getMPosicaoY() != (*h)->getMPosicaoY()) {
                    distInmg = (int)round(sqrt(
                            ((*a)->getMPosicaoX() - (*h)->getMPosicaoX()) *
                            ((*a)->getMPosicaoX() - (*h)->getMPosicaoX()) +
                            ((*a)->getMPosicaoY() - (*h)->getMPosicaoY()) *
                            ((*a)->getMPosicaoY() - (*h)->getMPosicaoY())));
                    //se estiver dentro da sua percecao é porque viu o inimigo, tem de fugir
                    if (distInmg <= 7 && (distInmg < distInmgAux || distInmgAux==-1)) {
                        //viu o inimigo
                        inimigo = true;
                        xInimigo = (*a)->getMPosicaoX();
                        yInimigo = (*a)->getMPosicaoY();
                        distInmgAux=distInmg;
                    }
                }
            }


            if (inimigo) {
                int aux1X, aux1Y;
                int distAoPai = (int)round(sqrt(
                        ((*h)->getMPosicaoX() - (*h)->getMPosXp()) * ((*h)->getMPosicaoX() - (*h)->getMPosXp()) +
                        ((*h)->getMPosicaoY() - (*h)->getMPosYp()) * ((*h)->getMPosicaoY() - (*h)->getMPosYp())));

                //ver se pode ir direto ao pai
                if (distAoPai <= 2) {
                    auxX = (*h)->getMPosXp();
                    auxY = (*h)->getMPosYp();
                } else {

                    do {
                        auxX = aleatorio((*h)->getMPosicaoX() - 2, (*h)->getMPosicaoX() + 2);
                        auxY = aleatorio((*h)->getMPosicaoY() - 2, (*h)->getMPosicaoY() + 2);
                        distaux = (int)round(sqrt(
                                (auxX - (*h)->getMPosXp()) * (auxX - (*h)->getMPosXp()) +
                                (auxY - (*h)->getMPosYp()) * (auxY - (*h)->getMPosYp())));
                        if(auxX == (*h)->getMPosXp() && auxY == (*h)->getMPosYp())
                            break;
                    } while (distaux >= distAoPai);

                }
                content[(*h)->getMPosicaoX()][(*h)->getMPosicaoY()] = '+';
                (*h)->setMPosicaoX(auxX);
                (*h)->setMPosicaoY(auxY);


            } else if(!inimigo){
                int count=0;
                int distAoPai;
                do {
                    auxX = aleatorio((*h)->getMPosicaoX() - 1, (*h)->getMPosicaoX() + 1);
                    auxY = aleatorio((*h)->getMPosicaoY() - 1, (*h)->getMPosicaoY() + 1);
                    distAoPai = (int)round(sqrt(
                            (auxX - (*h)->getMPosXp()) * (auxX - (*h)->getMPosYp()) +
                            (auxY - (*h)->getMPosXp()) * (auxY - (*h)->getMPosYp())));
                    count++;
                } while (distAoPai > 4 && count <= 8);
                content[(*h)->getMPosicaoX()][(*h)->getMPosicaoY()] = '+';
                (*h)->setMPosicaoX(auxX);
                (*h)->setMPosicaoY(auxY);
            }


            }

        // fazer o animal dar a volta
        if ((*h)->getMPosicaoX() < 0 || (*h)->getMPosicaoX() >= auxNumLin || (*h)->getMPosicaoY() < 0 ||
            (*h)->getMPosicaoY() >= auxNumCol) {
            int atualizaPos = ((*h)->getMPosicaoX() + auxNumLin) % auxNumLin;
            (*h)->setMPosicaoX(atualizaPos);
            atualizaPos = ((*h)->getMPosicaoY() + auxNumCol) % auxNumCol;
            (*h)->setMPosicaoY(atualizaPos);
        }
        }


}

void Reserva::reproduzG(int idG, term::Terminal &t) {
    limpaEcra(t);

    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++)
        if ((*h)->getMId() == idG)
            break;


    if (h != animInReserva.end()) {

        if (instante - (*h)->getMInstNasc() > (*h)->getMInstNascFilho() + 30 ) {
            //ja passaram 8 instantes desde o nascimento
            //criar filho

                //nasce
                int dx = aleatorio(-3, 3) + (*h)->getMPosicaoX();
                int dy = aleatorio(-3, 3) + (*h)->getMPosicaoY();
                // fazer o animal dar a volta
                if (dx < 0 || dx >= auxNumLin || dy < 0 || dy >= auxNumCol) {
                    int atualizaPos = (dx + auxNumLin) % auxNumLin;
                    dx=atualizaPos;
                    atualizaPos = (dy + auxNumCol) % auxNumCol;
                    dy=atualizaPos;
                }
                (*h)->setMPosXf(dx);
                (*h)->setMPosYf(dy);
            //alterar o instante de nascimento
            (*h)->setMInstNascFilho(instante);
        }

    }
}

void Reserva::morteG(int idO, term::Terminal &t) {
    limpaEcra(t);
    auto o = animInReserva.begin();
    for (; o != animInReserva.end(); o++)
        if ((*o)->getMId() == idO)
            break;

    int idPai = (*o)->getMIdPai();

    if ((*o)->getMIdade() >= (*o)->getMInstMorte()) {
        (*o)->setMVivo(false);
    }

    //ver se o pai morreu
    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++)
        if ((*h)->getMId() == idPai && idPai != -1) {
            break;
        }
    // se nao há pai e ele está na bolsa marsupial morre
    if(h == animInReserva.end() && (*o)->isBolsaMarsupial()){
        (*h)->setMVivo(false);
    }
}

void Reserva::bolsaMarsupial(int idG, term::Terminal &t) {
    limpaEcra(t);
    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++)
        if ((*h)->getMId() == idG)
            break;

    if (h != animInReserva.end()) {
        if((*h)->getMIdade() > 20)
            (*h)->setMPeso(20);


        auto i = animInReserva.begin();
        for (; i != animInReserva.end(); i++)
            if ((*i)->getMPosicaoX() == (*h)->getMPosicaoX() && (*i)->getMPosicaoY() == (*h)->getMPosicaoY() && (*i)->getMId() == (*h)->getMIdPai())
                break;

        if (i != animInReserva.end() || (*h)->isBolsaMarsupial()) {
            if((*h)->isBolsaMarsupial()){
                //ver se ja vai sair e atualizar posicao para a do pai
                if(instante >= (*h)->getInstBolsa() + 5){
                    (*h)->setBolsaMarsupial(false);
                    (*h)->setInstBolsa(-1);
                }else{
                    (*h)->setMSimbolo('X');
                    (*h)->setMPosicaoX((*h)->getMPosXp());
                    (*h)->setMPosicaoY((*h)->getMPosYp());
                }
            }else{
                (*h)->setBolsaMarsupial(true);
                //t << "INSTANTE:" << instante;
                (*h)->setInstBolsa(instante);
            }

        }

    }

}

void Reserva::andaL(int idL, term::Terminal &t) {
    limpaEcra(t);
    int distAlmnt;
    int distInmg;
    bool objetivo=false;

    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++)
        if ((*h)->getMId() == idL)
            break;

    if (h != animInReserva.end()) {
        int xObj, yObj, xObjAux, yObjAux, distObj=-1;
        auto i = alimInReserva.begin();
        for (; i != alimInReserva.end(); i++) {
            if ((*i)->getMCheiro0() == "carne" || (*i)->getMCheiro1() == "carne") {
                //calcular distancia ao alimento e se for menor atualizar objetivo
                distAlmnt = (int)round(sqrt(
                        ((*i)->getMPosicaoX() - (*h)->getMPosicaoX()) * ((*i)->getMPosicaoX() - (*h)->getMPosicaoX()) +
                        ((*i)->getMPosicaoY() - (*h)->getMPosicaoY()) * ((*i)->getMPosicaoY() - (*h)->getMPosicaoY())));
                //se estiver dentro da sua percecao e a distancia for menor que o atual objetivo
                //sqrt(32) é a distancia ente um ponto e um ponto a 4 char de distancia(percecao)
                if (distAlmnt <= 5 && (distAlmnt < distObj || distObj == -1)) {
                    objetivo = true;
                    xObj=(*i)->getMPosicaoX();
                    yObj=(*i)->getMPosicaoY();
                    distObj=distAlmnt;
                }
            }
        }

        //ver se tem um animal perto
        int xAnm, yAnm, xAnmAux, yAnmAux, distAnm;
        float pesoAux=0;
        bool animalPerto=false;
        //procura inimigo
        auto a = animInReserva.begin();
        for (; a != animInReserva.end(); a++) {
                distInmg = (int)round(sqrt(
                        ((*a)->getMPosicaoX() - (*h)->getMPosicaoX()) * ((*a)->getMPosicaoX() - (*h)->getMPosicaoX()) +
                        ((*a)->getMPosicaoY() - (*h)->getMPosicaoY()) * ((*a)->getMPosicaoY() - (*h)->getMPosicaoY())));
                //se estiver dentro da sua percecao é porque viu o inimigo, tem de se aproximar
                if (distInmg <= 5 && (*a)->getMId() != (*h)->getMId() && (*a)->getMPeso()>pesoAux) {
                        pesoAux = (*a)->getMPeso();
                        //viu o inimigo
                        animalPerto = true;
                        xAnm = (*a)->getMPosicaoX();
                        yAnm = (*a)->getMPosicaoY();

                }
        }

        //distancia do andamento
        int distan=1;
        if ((*h)->getMFome() > 15)
            distan=2;

        if (objetivo) {
            int distaux=0,auxX, auxY,aux1X,aux1Y;
            //ver se pode ir direto ao objetivo

            if(distObj <= distan){
                auxX=xObj;
                auxY=yObj;
            }else{
                do {
                    if ((*h)->getMFome() > 15) {
                        // Distância máxima é de 2
                        auxX = aleatorio((*h)->getMPosicaoX() - 2, (*h)->getMPosicaoX() + 2);
                        auxY = aleatorio((*h)->getMPosicaoY() - 2, (*h)->getMPosicaoY() + 2);
                    } else {
                        // Distância máxima é de 1
                        auxX = aleatorio((*h)->getMPosicaoX() - 1, (*h)->getMPosicaoX() + 1);
                        auxY = aleatorio((*h)->getMPosicaoY() - 1, (*h)->getMPosicaoY() + 1);
                    }
                    distaux = (int)round(sqrt((auxX - xObj) * (auxX - xObj) +
                                   (auxY - yObj) * (auxY - yObj)));
                    if(auxX == xObj && auxY == yObj){
                        break;
                    }
                } while (distaux >= distObj);
            }
            content[(*h)->getMPosicaoX()][(*h)->getMPosicaoY()]='+';
            (*h)->setMPosicaoX(auxX);
            (*h)->setMPosicaoY(auxY);
        }else if(animalPerto){
            int distaux,auxX, auxY,aux1X,aux1Y;
            //ver se pode ir direto ao inimigo
            //distancia ao inimigo
            int distanInit = (int)round(sqrt( (xAnm - (*h)->getMPosicaoX()) * (xAnm - (*h)->getMPosicaoX()) +
                                   (yAnm - (*h)->getMPosicaoY()) * (yAnm - (*h)->getMPosicaoY())));
            if(distanInit <= distan){
                xAnmAux=xAnm;
                yAnmAux=yAnm;
            }else {
                do {
                if ((*h)->getMFome() > 15) {
                    // Distância máxima é de 3
                    xAnmAux = aleatorio((*h)->getMPosicaoX() - 3, (*h)->getMPosicaoX() + 3);
                    yAnmAux = aleatorio((*h)->getMPosicaoY() - 3, (*h)->getMPosicaoY() + 3);
                } else {
                    // Distância máxima é de 2
                    xAnmAux = aleatorio((*h)->getMPosicaoX() - 2, (*h)->getMPosicaoX() + 2);
                    yAnmAux = aleatorio((*h)->getMPosicaoY() - 2, (*h)->getMPosicaoY() + 2);
                }
                distAnm = (int)round(sqrt((xAnmAux - xAnm) * (xAnmAux - xAnm) +
                               (yAnmAux - yAnm) * (yAnmAux - yAnm)));
                if(xAnm == xAnmAux && yAnm == yAnmAux){
                    break;
                }
                } while (distAnm >= distanInit );
            }
        content[(*h)->getMPosicaoX()][(*h)->getMPosicaoY()]='+';
        (*h)->setMPosicaoX(xAnmAux);
        (*h)->setMPosicaoY(yAnmAux);
        } else {
            int direcao = aleatorio(0, 3);

            if (direcao == 0) {
                (*h)->setMPosicaoX((*h)->getMPosicaoX() - distan);
            } else if (direcao == 1) {
                (*h)->setMPosicaoX((*h)->getMPosicaoX() + distan);
            } else if (direcao == 2) {
                (*h)->setMPosicaoY((*h)->getMPosicaoY() - distan);
            } else if (direcao == 3) {
                (*h)->setMPosicaoY((*h)->getMPosicaoY() + distan);
            }
        }
        // fazer o animal dar a volta
        if ((*h)->getMPosicaoX() < 0 || (*h)->getMPosicaoX() >= auxNumLin || (*h)->getMPosicaoY() < 0 || (*h)->getMPosicaoY() >= auxNumCol) {
            int atualizaPos = ((*h)->getMPosicaoX() + auxNumLin) % auxNumLin;
            (*h)->setMPosicaoX(atualizaPos);
            atualizaPos = ((*h)->getMPosicaoY() + auxNumCol) % auxNumCol;
            (*h)->setMPosicaoY(atualizaPos);
        }
    }
}

void Reserva::reproduzL(int idL, term::Terminal &t) {
    limpaEcra(t);
    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++)
        if ((*h)->getMId() == idL)
            break;


    if (h != animInReserva.end()) {

        if (instante == (*h)->getMInstNascFilho()) {
            //nasce
            int dx = aleatorio(-15, 15) + (*h)->getMPosicaoX();
            int dy = aleatorio(-15, 15) + (*h)->getMPosicaoY();
            // fazer o animal dar a volta
            if (dx < 0 || dx >= auxNumLin || dy < 0 || dy >= auxNumCol) {
                int atualizaPos = (dx + auxNumLin) % auxNumLin;
                dx=atualizaPos;
                atualizaPos = (dy + auxNumCol) % auxNumCol;
                dy=atualizaPos;
            }
            (*h)->setMPosXf(dx);
            (*h)->setMPosYf(dy);
        }

    }

}

void Reserva::comeL(int idL, term::Terminal &t) {
    limpaEcra(t);
    //COMER
    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++)
        if ((*h)->getMId() == idL)
            break;

    if (h != animInReserva.end()) {

        auto i = alimInReserva.begin();
        for (; i != alimInReserva.end(); i++)
            if ((*i)->getMPosicaoX() == (*h)->getMPosicaoX() && (*i)->getMPosicaoY() == (*h)->getMPosicaoY())
                break;
        if (i != alimInReserva.end() && ((*i)->getMCheiro0() == "carne" || (*i)->getMCheiro1() == "carne")) {
            string esp = (*i)->getMEspecie();
            int vnut = (*i)->getMVnutritivo();
            int tox = (*i)->getMToxicidade();
            auto *a = new Comida(esp, vnut, tox);
            (*h)->addMemberToHist(a);
            //somar à fome o valor nutritivo
            (*h)->setMFome((*h)->getMFome() - vnut);
            //subtrair à saude o valor de toxicidade
            (*h)->setMSaude((*h)->getMSaude() - tox);
            //apagar objetivo
            delete *i;
            alimInReserva.erase(i);
            content[(*i)->getMPosicaoX()][(*i)->getMPosicaoY()] = '+';
        }


        //MATAR MAIS LEVE
        //ver se tem um animal perto
        int xAnm, yAnm, xAnmAux, yAnmAux, distAnm, distInmg;
        float pesoAux = 0;
        bool animalPerto = false;
        //procura inimigo
        auto a = animInReserva.begin();
        for (; a != animInReserva.end(); a++) {
            distInmg = (int)round(sqrt(
                    ((*a)->getMPosicaoX() - (*h)->getMPosicaoX()) * ((*a)->getMPosicaoX() - (*h)->getMPosicaoX()) +
                    ((*a)->getMPosicaoY() - (*h)->getMPosicaoY()) * ((*a)->getMPosicaoY() - (*h)->getMPosicaoY())));

            if (distInmg <= 1 && (*a)->getMId() != (*h)->getMId()) {
                //se mais leve mata
                if((*h)->getMPeso() > (*a)->getMPeso()){
                    (*a)->setMVivo(false);
                }
                // se na mesma posicao e for mais pesado luta
                if((*h)->getMPeso() < (*a)->getMPeso() && (*h)->getMPosicaoX() == (*a)->getMPosicaoX() && (*h)->getMPosicaoY() == (*a)->getMPosicaoY()){
                    int sobrevive = aleatorio(0,2);
                    if(sobrevive==0){
                        (*a)->setMVivo(false);
                    }else if(sobrevive == 1){
                        (*h)->setMVivo(false);
                    }
                }
            }
        }
    }
}

void Reserva::fomeL(int idL) {
    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++)
        if ((*h)->getMId() == idL)
            break;

    if (h != animInReserva.end()) {
        (*h)->setMFome((*h)->getMFome() + 2);
        if ((*h)->getMFome() > 25) {
            (*h)->setMSaudePerdPorInst(2);
        } else if ((*h)->getMFome() > 15) {
            (*h)->setMSaudePerdPorInst(1);
            (*h)->setMNumMaxPosPorInst(2);
        }
    }
}

void Reserva::saudeL(int idL) {
    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++)
        if ((*h)->getMId() == idL)
            break;

    if (h != animInReserva.end()) {
        int saude = (*h)->getMSaude();
        int saudePerdida = (*h)->getMSaudePerdPorInst();
        (*h)->setMSaude(saude - saudePerdida);
    }
}

void Reserva::morteL(int idL, term::Terminal &t) {
    limpaEcra(t);
    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++) {
        if ((*h)->getMId() == idL && (*h)->getMSaude() <= 0 ) {
            (*h)->setMVivo(false);
        }
    }
}

void Reserva::desaparece(int idR, term::Terminal &t) {
    limpaEcra(t);
    auto h = alimInReserva.begin();
    for (; h != alimInReserva.end(); h++) {
        if ((*h)->getMId() == idR && (*h)->getMTempoVidaAtual() >= (*h)->getMDuracao()) {
            (*h)->setMVivo(false);
        }
    }
}

void Reserva::morteAlm(term::Terminal &terminal) {
    auto i = alimInReserva.begin();
    do {
        for (; i != alimInReserva.end(); i++)
            if (!(*i)->isMVivo())
                break;

        if (i != alimInReserva.end()) {
            content[(*i)->getMPosicaoX()][(*i)->getMPosicaoY()] = '+';
            delete *i;
            alimInReserva.erase(i);
        }
    } while (i != alimInReserva.end());
}

void Reserva::reproduzr(int idR, term::Terminal &t){
    limpaEcra(t);
    auto h = alimInReserva.begin();
    for (; h != alimInReserva.end(); h++)
        if ((*h)->getMId() == idR)
            break;

    int perc = (int)round(0.75 * (*h)->getMDuracao());

    if (h != alimInReserva.end()) {

        if ((*h)->getMTempoVidaAtual() >= perc) {
            //escolher valores de x e y entre 8 e 8 posicoes de distancia
            int aux1X,aux2X, aux1Y, aux2Y;
            aux1X = aleatorio(-8, -4);
            aux2X = aleatorio(4,8);
            if(aleatorio(0,1)==0)
                aux1X=aux2X;
            aux1Y = aleatorio(-8, -4);
            aux2Y = aleatorio(4,8);
            if(aleatorio(0,1)==0)
                aux1Y=aux2Y;
            //nasce
            int dx = aux1X + (*h)->getMPosicaoX();
            int dy = aux1Y + (*h)->getMPosicaoY();
            // fazer o animal dar a volta
            if (dx < 0 || dx >= auxNumLin || dy < 0 || dy >= auxNumCol) {
                int atualizaPos = (dx + auxNumLin) % auxNumLin;
                dx=atualizaPos;
                atualizaPos = (dy + auxNumCol) % auxNumCol;
                dy=atualizaPos;
            }
            (*h)->setMPosXf(dx);
            (*h)->setMPosYf(dy);
        }

    }
}

void Reserva::toxicidadet(int idT, term::Terminal &t) {
    limpaEcra(t);
    auto h = alimInReserva.begin();
    for (; h != alimInReserva.end(); h++)
        if ((*h)->getMId() == idT)
            break;

    if (h != alimInReserva.end()) {
        int tox = (*h)->getMToxicidade();
        int tempvida = (*h)->getMTempoVidaAtual();

        for (int i = 0; i < tempvida; i += 10) {
            if (tox < 3) {
                tox++;
            }
        }

        (*h)->setMToxicidade(tox);
    }
}

void Reserva::vnutritivop(int idP, term::Terminal &t){
    limpaEcra(t);
    auto h = alimInReserva.begin();
    for (; h != alimInReserva.end(); h++)
        if ((*h)->getMId() == idP)
            break;

    if (h != alimInReserva.end()) {
        if ((*h)->getMTempoVidaAtual() < 2 * VCorpo)
            (*h)->setMToxicidade((*h)->getMToxicidade() + 1);

        (*h)->setMVnutritivo((*h)->getMVnutritivo() - 1);
    }
}

void Reserva::vnutritivob(int idB, term::Terminal &t) {
    limpaEcra(t);
    auto h = alimInReserva.begin();
    for (; h != alimInReserva.end(); h++)
        if ((*h)->getMId() == idB)
            break;

    if (h != alimInReserva.end()) {
        if((*h)->getMVnutritivo() > 0)
            (*h)->setMVnutritivo((*h)->getMVnutritivo() - 1);
    }
}

void Reserva::addFromFile(const string &filename, term::Terminal &t){
    limpaEcra(t);
    fstream file;
    string line;
    string nome;
    string valor;

    file.open(filename, std::fstream::in);

    if (file) {
        while (getline(file, line)) {
            std::istringstream iss(line);
            std::getline(iss, nome, '=');
            std::getline(iss, valor);
            v_const.emplace_back(nome);
        }
        file.close();
    }

}

void Reserva::atualConstAnmFich(int idA, term::Terminal &t){
    limpaEcra(t);
    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++)
        if ((*h)->getMId() == idA)
            break;
    char a[10];
    int b;
    (*h)->setMCriado(true);
    switch ((*h)->getMSimbolo()) {
        case 'C':
            sscanf(v_const[0].c_str(),"%s %d", a, &b);
            if(strcmp(a,"SCoelho") == 0)
                (*h)->setMSaude(b);
            sscanf(v_const[1].c_str(),"%s %d", a, &b);
            if(strcmp(a,"VCoelho") == 0)
                (*h)->setMInstMorte(b);
            break;
        case 'O':
            sscanf(v_const[2].c_str(),"%s %d", a, &b);
            if(strcmp(a,"SOvelha") == 0)
                (*h)->setMSaude(b);
            sscanf(v_const[3].c_str(),"%s %d", a, &b);
            if(strcmp(a,"VOvelha") == 0)
                (*h)->setMInstMorte(b);
            break;
        case 'L':
            sscanf(v_const[4].c_str(),"%s %d", a, &b);
            if(strcmp(a,"SLobo") == 0)
                (*h)->setMSaude(b);
            break;
        case 'G':
            sscanf(v_const[5].c_str(),"%s %d", a, &b);
            if(strcmp(a,"SCanguro") == 0)
                (*h)->setMSaude(b);
            sscanf(v_const[6].c_str(),"%s %d", a, &b);
            if(strcmp(a,"VCanguro") == 0)
                (*h)->setMInstMorte(b);
            break;
    }
}

void Reserva::atualConstAlmFich(int idA, term::Terminal &t) {
    limpaEcra(t);
    auto h = alimInReserva.begin();
    for (; h != alimInReserva.end(); h++)
        if ((*h)->getMId() == idA)
            break;
    char a[10];
    int b;
    (*h)->setMCriado(true);
    switch ((*h)->getMSimbolo()) {
        case 'r':
            sscanf(v_const[7].c_str(),"%s %d", a, &b);
            if(strcmp(a,"VRelva") == 0)
                (*h)->setMDuracao(b);
            break;
        case 'O':
            sscanf(v_const[8].c_str(),"%s %d", a, &b);
            if(strcmp(a,"VBife") == 0)
                (*h)->setMDuracao(b);
            break;
    }
}


void Reserva::andaM(int idM, term::Terminal &t) {
    limpaEcra(t);
    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++)
        if ((*h)->getMId() == idM)
            break;

            int direcao = aleatorio(0, 3);

            if (direcao == 0) {
                (*h)->setMPosicaoX((*h)->getMPosicaoX() - 1);
            } else if (direcao == 1) {
                (*h)->setMPosicaoX((*h)->getMPosicaoX() + 1);
            } else if (direcao == 2) {
                (*h)->setMPosicaoY((*h)->getMPosicaoY() - 1);
            } else if (direcao == 3) {
                (*h)->setMPosicaoY((*h)->getMPosicaoY() + 1);
            }

        // fazer o animal dar a volta
        if ((*h)->getMPosicaoX() < 0 || (*h)->getMPosicaoX() >= auxNumLin || (*h)->getMPosicaoY() < 0 || (*h)->getMPosicaoY() >= auxNumCol) {
            int atualizaPos = ((*h)->getMPosicaoX() + auxNumLin) % auxNumLin;
            (*h)->setMPosicaoX(atualizaPos);
            atualizaPos = ((*h)->getMPosicaoY() + auxNumCol) % auxNumCol;
            (*h)->setMPosicaoY(atualizaPos);
        }
    }

void Reserva::comeM(int idM, term::Terminal &t) {
    limpaEcra(t);
    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++)
        if ((*h)->getMId() == idM)
            break;

    if (h != animInReserva.end()) {

        auto i = alimInReserva.begin();
        for (; i != alimInReserva.end(); i++)
            if ((*i)->getMPosicaoX() == (*h)->getMPosicaoX() && (*i)->getMPosicaoY() == (*h)->getMPosicaoY())
                break;
        if (i != alimInReserva.end() && ( (*i)->getMCheiro0()=="ketchup" || (*i)->getMCheiro1()=="ketchup" )) {
            string esp = (*i)->getMEspecie();
            int vnut =  (*i)->getMVnutritivo();
            int tox = (*i)->getMToxicidade();
            auto *a = new Comida( esp,vnut,tox);
            (*h)->addMemberToHist(a);
            (*h)->setMSaude((*h)->getMSaude()-tox);
            delete *i;
            alimInReserva.erase(i);
            content[(*i)->getMPosicaoX()][(*i)->getMPosicaoY()] = '+';
        }

    }

}

void Reserva::morteM(int idAux, term::Terminal &t) {
    limpaEcra(t);
    auto h = animInReserva.begin();
    for (; h != animInReserva.end(); h++) {
        if ((*h)->getMId() == idAux && (((*h)->getMSaude() <= 0 || (*h)->getMIdade() >= (*h)->getMInstMorte()))) {
            (*h)->setMVivo(false);
        }
    }
}
