#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class piece;
ostream &operator<<(ostream&, const piece&);

class piece
{
    private:
        string pieceType;
        char side;
        int xPos;
        int yPos;

    public:
        piece();
        piece(piece *);
        piece(string, char, int, int);
        ~piece();
        char getSide();
        string getPieceType();
        int getX();
        int getY();
        void setX(int);
        void setY(int);
        friend ostream& operator<<(ostream&, const piece&);
        void operator[](int);
        piece& operator+(string);

};

#endif