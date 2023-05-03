#include "piece.h"

piece::piece()
{
}

piece::piece(piece * newPiece)
{
    this->pieceType = newPiece->pieceType;
    this->side = newPiece->side;
    this->xPos = newPiece->xPos;
    this->yPos = newPiece->yPos;
}

piece::piece(string pType, char side, int x, int y)
{
    this->pieceType = pType;
    this->side = side;
    this->xPos = x;
    this->yPos = y;
}

piece::~piece()
{
    // delete this;

    cout << "(" << xPos << "," << yPos << ") " << side << " " << pieceType << " deleted\n";
}

char piece::getSide()
{
    return this->side;
}

string piece::getPieceType()
{
    return this->pieceType;
}

int piece::getX()
{
    return this->xPos;
}

int piece::getY()
{
    return this->yPos;
}

void piece::setX(int x)
{
    this->xPos = x;
}

void piece::setY(int y)
{
    this->yPos = y;
}

void piece::operator[](int pos)
{
    if (pos == 0)
        cout << "x coord: " << this->xPos << endl;
    else if (pos == 1)
        cout << "y coord: " << this->yPos << endl;
    else cout << "Invalid Index\n";
}

piece& piece::operator+(string move)
{
    int moveX, moveY;
    string substring;

    istringstream moveInfo(move);

    getline(moveInfo, substring, ',');
    stringstream convertToInt1(substring);
    convertToInt1 >> moveX;

    getline(moveInfo, substring, ',');
    stringstream convertToInt2(substring);
    convertToInt2 >> moveY;

    if (moveX >= 0 && moveX <= 7)
    {
        if (moveY >= 0 && moveY <= 7)
        {
            this->xPos = moveX;
            this->yPos = moveY;
            return *this;
        }
    }   
    
    return *this;
}

ostream& operator<<(ostream& output, const piece& t)
{
    output << t.side << " " << t.pieceType << " at [" << t.xPos << "," << t.yPos << "]\n";

    return output;
}