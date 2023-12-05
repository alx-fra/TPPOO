#ifndef META2POO_HELPERS_H
#define META2POO_HELPERS_H


#include "Visual/Terminal.h"
#include <cstdlib>
#include <random>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <chrono>
#include <thread>
#include <ostream>
#include <utility>
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;
//caso nao esteja nos valores do constantes.txt
static int SCoelho = 20;
static int VCoelho = 30;
static int SOvelha = 30;
static int VOvelha = 35;
static int SLobo = 25;
static int VLobo = 40;
static int SCanguro = 20;
static int VCanguro = 70;
static int VRelva = 20;
static int VBife = 30;



static int VCenoura = -1; //INFINITA
static int VCorpo = -1; //INFINITA

static vector<string> v_const;
// Generate a random number in the range [min, max] (inclusive)
int aleatorio(int min, int max);

#endif //META2POO_HELPERS_H
