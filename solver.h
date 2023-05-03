#ifndef SOLVER_H
#define SOLVER_H

#include "board.h"

using namespace std;

class solver
{
    private:
        int numGames;
        board** boards;

    public:
        solver(string);
        ~solver();

};

#endif