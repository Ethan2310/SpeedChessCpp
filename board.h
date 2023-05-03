#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include <fstream>

using namespace std;

class board
{
    private:
        int numWhitePieces;
        int numBlackPieces;
        piece ** whitePieces;
        piece ** blackPieces;
        string ** chessboard;
        string move;
        char sideToMove;
        board& operator++();

    public:
        board(string);
        ~board();
        board& operator--();
        bool checkIfPieceHasCheck(string, int, int, int, int);

};

#endif