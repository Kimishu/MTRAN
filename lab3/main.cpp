#include "LexicalAnalyser.h"

using namespace std;

class S{

    LexicalAnalyser ls;

public:
    S(LexicalAnalyser ls){
        this->ls = ls;

    }
};


int main() {

   LexicalAnalyser ls;
//    ls.Analyse();

    S s(ls);




    return 0;
}
