#include "board.h"

board::board(string pieceList)
{
    numWhitePieces = 0;
    numBlackPieces = 0;
    whitePieces = new piece*[16];
    blackPieces = new piece*[16];

    for (int i = 0; i < 16; i++)
    {
        whitePieces[i] = NULL;
        blackPieces[i] = NULL;
    }

    chessboard = new string*[8];
    
    for (int r = 0; r < 8; r++)
    {
        chessboard[r] = new string[8];
        for (int c = 0; c < 8; c++)
            chessboard[r][c] = "-";
    }

    ifstream piecesList;
    string line;
    piecesList.open(pieceList.c_str());

    getline(piecesList, line);
    sideToMove = line[0];
    getline(piecesList, line);
    move = line;

    int xPosition, yPosition, currNumPieces = 0;
    string pieceName, pieceSideTemp, xCoord, yCoord;
    char pieceSide;

    while (getline(piecesList, line) && (currNumPieces < 16))
    {
        istringstream pieceInfo(line);
        getline(pieceInfo, pieceSideTemp, ',');
        pieceSide = pieceSideTemp[0];
        getline(pieceInfo, pieceName, ',');
        getline(pieceInfo, xCoord, ',');
        stringstream convertToInt(xCoord);
        convertToInt >> xPosition;
        getline(pieceInfo, yCoord, ',');
        stringstream convertToInt2(yCoord);
        convertToInt2 >> yPosition;

        if (pieceSide == 'w')
        {   
            char pieceCode[3];

            if (pieceName == "king")
            {
                pieceCode[0] = pieceSide;
                pieceCode[1] = 'K';
            } 
            else 
            {
                pieceCode[0] = pieceSide;
                pieceCode[1] = pieceName[0];
            }
            
            whitePieces[numWhitePieces++] = new piece(pieceName, pieceSide, xPosition, yPosition);
            chessboard[xPosition][yPosition] = pieceCode;
        }
        
        else if (pieceSide == 'b')
        {
            char pieceCode[3];

            if (pieceName == "king")
            {
                pieceCode[0] = pieceSide;
                pieceCode[1] = 'K';
            } 
            else 
            {
                pieceCode[0] = pieceSide;
                pieceCode[1] = pieceName[0];
            }
            
            blackPieces[numBlackPieces++] = new piece(pieceName, pieceSide, xPosition, yPosition);
            chessboard[xPosition][yPosition] = pieceCode;
        }
    }

    currNumPieces++;
    piecesList.close();

    // cout << endl;
    // for (int row = 0; row < 8; row++)
    // {
    //     for (int col = 0; col < 8; col++)
    //         cout << chessboard[row][col] << "\t";
    //     cout << endl; 
    // } 
    // cout << endl;      
}

board::~board()
{
    for (int d = 0; d < 16; d++)
    {
        if (blackPieces[d] != NULL)
            delete blackPieces[d];
    }
    delete [] blackPieces;
    blackPieces = NULL;

    for (int e = 0; e < 16; e++)
    {
        if (whitePieces[e] != NULL)
            delete whitePieces[e];
    }
    delete [] whitePieces;
    whitePieces = NULL;

    for (int r = 0; r < 8; r++)
        delete [] chessboard[r];
    delete [] chessboard;

    cout << "Num Pieces Removed: " << numWhitePieces + numBlackPieces << endl;
}

board& board::operator++()
{
    string tempX, tempY, fromXY, toXY;
    int fromX, fromY, toX, toY;

    istringstream moveInfo(move);

    getline(moveInfo, tempX, ',');
    stringstream convertToInteger3(tempX);
    convertToInteger3 >> fromX;

    getline(moveInfo, tempY, ',');
    stringstream convertToInteger4(tempY);
    convertToInteger4 >> fromY;

    fromXY = tempX + "," + tempY;

    getline(moveInfo, tempX, ',');
    stringstream convertToInteger5(tempX);
    convertToInteger5 >> toX;

    getline(moveInfo, tempY, ',');
    stringstream convertToInteger6(tempY);
    convertToInteger6 >> toY;

    toXY = tempX + "," + tempY;

    bool flag = false;
    int counter = 0;
    char pieceCode[3];

    if (sideToMove == 'w')
    {
        while ((flag == false) && (counter < numWhitePieces))
        {
            if (whitePieces[counter] != NULL)
            {
                if ((whitePieces[counter]->getX() == fromX) && (whitePieces[counter]->getY() == fromY))
                {
                    whitePieces[counter]->operator+(toXY);
                    chessboard[fromX][fromY] = "-";

                    if (whitePieces[counter]->getPieceType() == "king")
                    {
                        pieceCode[0] = 'w';
                        pieceCode[1] = 'K';
                    } 
                    else 
                    {
                        pieceCode[0] = 'w';
                        pieceCode[1] = whitePieces[counter]->getPieceType()[0];
                    }

                    chessboard[toX][toY] = pieceCode;
                    flag = true;
                }
                else counter++;
            }
        }
    }

    else if (sideToMove == 'b')
    {
        while ((flag == false)  && (counter < numBlackPieces))
        {
            if (blackPieces[counter] != NULL)
            {
                if ((blackPieces[counter]->getX() == fromX) && (blackPieces[counter]->getY() == fromY))
                {
                    blackPieces[counter]->operator+(toXY);
                    chessboard[fromX][fromY] = "-";

                    if (blackPieces[counter]->getPieceType() == "king")
                    {
                        pieceCode[0] = 'b';
                        pieceCode[1] = 'K';
                    } 
                    else 
                    {
                        pieceCode[0] = 'b';
                        pieceCode[1] = blackPieces[counter]->getPieceType()[0];
                    }

                    chessboard[toX][toY] = pieceCode;
                    flag = true;
                }
                else counter++;
            }
        }
    }
    
    // for (int row = 0; row < 8; row++)
    // {
    //     for (int col = 0; col < 8; col++)
    //         cout << chessboard[row][col] << "\t";
    //     cout << endl;
    // } 
    // cout << endl;
    
    return *this;
}

bool board::checkIfPieceHasCheck(string pieceType, int xPos, int yPos, int kingX, int kingY)
{
    char pieceCode;
    bool kingFound = false;
    int pieceNumMoves = 0, posYMove = 0, posXMove = 0;
    string piecePosCode = chessboard[xPos][yPos];

    //===================================== PAWN CODE =====================================
    if (pieceType == "pawn")
    {
        if (piecePosCode[0] == 'w')
        {
            posXMove = xPos - 1;

            while ((pieceNumMoves < 2) && (posXMove >= 0) && (posXMove <= 7))
            {
                if ((pieceNumMoves < 2) && (posXMove == kingX) && (yPos == kingY))
                    return true;
                else 
                {
                    posXMove--;
                    pieceNumMoves++;
                }
            }
            
            return false;
        }

        else if (piecePosCode[0] == 'b')
        {
            posXMove = xPos + 1;

            while ((pieceNumMoves < 2) && (posXMove >= 0) && (posXMove <= 7))
            {
                if ((pieceNumMoves < 2) && (posXMove == kingX) && (yPos == kingY))
                    return true;
                else 
                {
                    posXMove++;
                    pieceNumMoves++;
                }
            }

            return false;
        }

        else 
            return false;
    }

    //===================================== ROOK CODE =====================================
    else if (pieceType == "rook")
    {
        // ==================== Horizontal Check ====================
        //Right-side check
        posYMove = yPos + 1;
        while ((posYMove >= 0) && (posYMove <= 7))
        {
            if ((xPos == kingX) && (posYMove == kingY))
                return true;
            else posYMove++;
        }

        //Left-side check
        posYMove = yPos - 1;
        while ((posYMove >= 0) && (posYMove <= 7))
        {
            if ((xPos == kingX) && (posYMove == kingY))
                return true;
            else posYMove--;
        }


        // ==================== Vertical Check ====================
        //Top-side check
        posXMove = xPos - 1;

        while ((posXMove >= 0) && (posXMove <= 7))
        {
            if ((posXMove == kingX) && (yPos == kingY))
                return true;
            else posXMove--;
        }

        //Bottom-side check
        posXMove = xPos + 1;
        while ((posXMove >= 0) && (posXMove <= 7))
        {
            if ((posXMove == kingX) && (yPos == kingY))
                return true;
            else posXMove++;
        }

        return false;
    }

    //===================================== BISHOP CODE =====================================
    else if (pieceType == "bishop")
    {
        // ==================== Positive-gradient diagonal Check ====================
        //Top-Right-side check
        posXMove = xPos - 1;
        posYMove = yPos + 1;
        while ((posXMove >= 0) && (posXMove <= 7) && (posYMove >= 0) && (posYMove <= 7))
        {
            if ((posXMove == kingX) && (posYMove == kingY))
                return true;
            else
            {
                posXMove--;
                posYMove++;
            }
        }

        //Bottom-left-side check
        posXMove = xPos + 1;
        posYMove = yPos - 1;
        while ((posXMove >= 0) && (posXMove <= 7) && (posYMove >= 0) && (posYMove <= 7))
        {
            if ((posXMove == kingX) && (posYMove == kingY))
                return true;
            else
            {
                posXMove++;
                posYMove--;
            }
        }


        // ==================== Negative-gradient diagonal Check ====================
        //Top-left-side check
        posXMove = xPos - 1;
        posYMove = yPos - 1;
        while ((posXMove >= 0) && (posXMove <= 7) && (posYMove >= 0) && (posYMove <= 7))
        {
            if ((posXMove == kingX) && (posYMove == kingY))
                return true;
            else
            {
                posXMove--;
                posYMove--;
            }
        }

        //Bottom-Right-side check
        posYMove = yPos + 1;
        posXMove = xPos + 1;
        while ((posXMove >= 0) && (posXMove <= 7) && (posYMove >= 0) && (posYMove <= 7))
        {
            if ((posXMove == kingX) && (posYMove == kingY))
                return true;
            else
            {
                posXMove++;
                posYMove++;
            }
        }

        return false;
    }

    //===================================== KNIGHT CODE =====================================
    else if (pieceType == "knight")
    {
        // RIGHT HAND SIDE CHECK
        if (((xPos - 2) >= 0) && ((yPos + 1) <= 7) && ((xPos - 2) == kingX) && ((yPos + 1) == kingY)) // top top
            return true;

        else if (((xPos - 1) >= 0) && ((yPos + 2) <= 7) && ((xPos - 1) == kingX) && ((yPos + 2) == kingY)) // top right
            return true;

        else if (((xPos + 2) >= 0) && ((yPos + 1) <= 7) && ((xPos + 2) == kingX) && ((yPos + 1) == kingY)) // bottom bottom
            return true;
            
        else if (((xPos + 1) >= 0) && ((yPos + 2) <= 7) && ((xPos + 1) == kingX) && ((yPos + 2) == kingY)) // bottom right
            return true;
        
        
        // LEFT HAND SIDE CHECK
        else if (((xPos - 2) >= 0) && ((yPos - 1) <= 7) && ((xPos - 2) == kingX) && ((yPos - 1) == kingY)) // top top
            return true;

        else if (((xPos - 1) >= 0) && ((yPos - 2) <= 7) && ((xPos - 1) == kingX) && ((yPos - 2) == kingY)) // top left
            return true;

        else if (((xPos + 2) >= 0) && ((yPos - 1) <= 7) && ((xPos + 2) == kingX) && ((yPos - 1) == kingY)) // bottom bottom
            return true;

        else if (((xPos + 1) >= 0) && ((yPos - 2) <= 7) && ((xPos + 1) == kingX) && ((yPos - 2) == kingY)) // bottom left
            return true;
        
        return false; 
    }

    //===================================== QUEEN CODE =====================================
    else if (pieceType == "queen")
    {
        // ==================== Horizontal Check ====================
        //Right-side check
        posYMove = yPos + 1;
        while ((posYMove >= 0) && (posYMove <= 7))
        {
            
            if ((xPos == kingX) && (posYMove == kingY))
                return true;
            else posYMove++;
        }

        //Left-side check
        posYMove = yPos - 1;
        while ((posYMove >= 0) && (posYMove <= 7))
        {
            if ((xPos == kingX) && (posYMove == kingY))
                return true;
            else posYMove--;
        }


        // ==================== Vertical Check ====================
        //Top-side check
        posXMove = xPos - 1;

        while ((posXMove >= 0) && (posXMove <= 7))
        {
            if ((posXMove == kingX) && (yPos == kingY))
                return true;
            else posXMove--;
        }

        //Bottom-side check
        posXMove = xPos + 1;
        while ((posXMove >= 0) && (posXMove <= 7))
        {
            if ((posXMove == kingX) && (yPos == kingY))
                return true;
            else posXMove++;
        }



        // ==================== Positive-gradient diagonal Check ====================
        //Top-Right-side check
        posXMove = xPos - 1;
        posYMove = yPos + 1;
        while ((posXMove >= 0) && (posXMove <= 7) && (posYMove >= 0) && (posYMove <= 7))
        {
            if ((posXMove == kingX) && (posYMove == kingY))
                return true;
            else
            {
                posXMove--;
                posYMove++;
            }
        }

        //Bottom-left-side check
        posXMove = xPos + 1;
        posYMove = yPos - 1;
        while ((posXMove >= 0) && (posXMove <= 7) && (posYMove >= 0) && (posYMove <= 7))
        {
            if ((posXMove == kingX) && (posYMove == kingY))
                return true;
            else
            {
                posXMove++;
                posYMove--;
            }
        }


        // ==================== Negative-gradient diagonal Check ====================
        //Top-left-side check
        posXMove = xPos - 1;
        posYMove = yPos - 1;
        while ((posXMove >= 0) && (posXMove <= 7) && (posYMove >= 0) && (posYMove <= 7))
        {
            if ((posXMove == kingX) && (posYMove == kingY))
                return true;
            else
            {
                posXMove--;
                posYMove--;
            }
        }

        //Bottom-Right-side check
        posYMove = yPos + 1;
        posXMove = xPos + 1;
        while ((posXMove >= 0) && (posXMove <= 7) && (posYMove >= 0) && (posYMove <= 7))
        {
            if ((posXMove == kingX) && (posYMove == kingY))
                return true;
            else
            {
                posXMove++;
                posYMove++;
            }
        }

        return false;
    }

    //===================================== KING CODE =====================================
    else if (pieceType == "king")
    {
        return false;
    }

    else return false;   
}

board& board::operator--()
{
    this->operator++();

    // cout << "kingXPosMove: " << kingXPosMove << endl;
    // cout << "kingYPosMove: " << kingYPosMove << endl << endl;
    // cout << "this->whitePieces[count]->getPieceType(): " << this->whitePieces[count]->getPieceType() << endl;
    // if (kingCheckMate == true)
    //     cout << "kingCheckMate: true\n\n";
    // else cout << "kingCheckMate: false\n\n";
    // cout << "***************************************************\n";

    int kingXPos = 0, kingYPos = 0, counter = 0, check = 0;
    bool foundKing = false, flag = false;

    bool kingCheckMate = true, checkMate = true, specificPosCheck = false;
    int kingXPosMove, kingYPosMove, kingSidesMove = 0;

    if (this->sideToMove == 'w')
    {    
        while ((foundKing == false) && (check < this->numBlackPieces))
        {
            if (this->blackPieces[check]->getPieceType() == "king")
            {
                kingXPos = this->blackPieces[check]->getX();
                kingYPos = this->blackPieces[check]->getY();
                foundKing = true;
            }
            else check++;
        }

        // ===================================== Determine CheckMate BEGIN =====================================
        while ((checkMate == true) && (kingSidesMove < 8))
        {  
            int count = 0;

            //======================== RIGHT L CHECK ========================
            if (((kingXPos + 1) >= 0) && ((kingXPos + 1) <= 7) && ((kingYPos + 1) >= 0) && ((kingYPos + 1) <= 7)) //right-hand side
            {
                kingXPosMove = kingXPos + 1;
                kingYPosMove = kingYPos + 1;

                if (chessboard[kingXPosMove][kingYPosMove] == "-")
                {
                    while ((specificPosCheck == false) && (count < this->numWhitePieces))
                    {
                        kingCheckMate = this->checkIfPieceHasCheck(this->whitePieces[count]->getPieceType(), this->whitePieces[count]->getX(), this->whitePieces[count]->getY(), kingXPosMove, kingYPosMove);

                        if (kingCheckMate == true)
                        {
                            specificPosCheck = true;
                            checkMate = true;
                        }                        
                        else if (kingCheckMate == false)
                        {
                            checkMate = false;   
                            count++;
                        }   

                    }
                }

                if (checkMate == false)
                    break;

                specificPosCheck = false;
                kingSidesMove++;
                count = 0;
            }

            if (((kingYPos + 1) >= 0) && ((kingYPos + 1) <= 7)) //right-hand side
            {   
                kingXPosMove = kingXPos;
                kingYPosMove = kingYPos + 1;

                if (chessboard[kingXPosMove][kingYPosMove] == "-")
                {
                    while ((specificPosCheck == false) && (count < this->numWhitePieces))
                    {
                        kingCheckMate = this->checkIfPieceHasCheck(this->whitePieces[count]->getPieceType(), this->whitePieces[count]->getX(), this->whitePieces[count]->getY(), kingXPosMove, kingYPosMove);

                        if (kingCheckMate == true)
                        {
                            specificPosCheck = true;
                            checkMate = true;
                        }                        
                        else if (kingCheckMate == false)
                        {
                            checkMate = false;   
                            count++;
                        }  
                    }
                }

                if (checkMate == false)
                    break;

                specificPosCheck = false;
                kingSidesMove++;
                count = 0;
            }

            if (((kingXPos - 1) >= 0) && ((kingXPos - 1) <= 7) && ((kingYPos + 1) >= 0) && ((kingYPos + 1) <= 7)) //right-hand side
            {
                kingXPosMove = kingXPos - 1;
                kingYPosMove = kingYPos + 1;

                if (chessboard[kingXPosMove][kingYPosMove] == "-")
                {
                    while ((specificPosCheck == false) && (count < this->numWhitePieces))
                    {
                        kingCheckMate = this->checkIfPieceHasCheck(this->whitePieces[count]->getPieceType(), this->whitePieces[count]->getX(), this->whitePieces[count]->getY(), kingXPosMove, kingYPosMove);

                        if (kingCheckMate == true)
                        {
                            specificPosCheck = true;
                            checkMate = true;
                        }                        
                        else if (kingCheckMate == false)
                        {
                            checkMate = false;   
                            count++;
                        }  
                    }
                }

                if (checkMate == false)
                    break;

                specificPosCheck = false;
                kingSidesMove++;
                count = 0;
            }

            if (((kingXPos + 1) >= 0) && ((kingXPos + 1) <= 7)) //right-hand side
            {
                kingXPosMove = kingXPos + 1;
                kingYPosMove = kingYPos;
                
                if (chessboard[kingXPosMove][kingYPosMove] == "-")
                {
                    while ((specificPosCheck == false) && (count < this->numWhitePieces))
                    {
                        kingCheckMate = this->checkIfPieceHasCheck(this->whitePieces[count]->getPieceType(), this->whitePieces[count]->getX(), this->whitePieces[count]->getY(), kingXPosMove, kingYPosMove);

                        if (kingCheckMate == true)
                        {
                            specificPosCheck = true;
                            checkMate = true;
                        }                        
                        else if (kingCheckMate == false)
                        {
                            checkMate = false;   
                            count++;
                        }  
                    }
                }

                if (checkMate == false)
                    break;

                specificPosCheck = false;
                kingSidesMove++;
                count = 0;
            }

            
            //======================== LEFT L CHECK ========================
            if (((kingXPos - 1) >= 0) && ((kingXPos - 1) <= 7) && ((kingYPos - 1) >= 0) && ((kingYPos - 1) <= 7)) //left-hand side
            {
                kingXPosMove = kingXPos - 1;
                kingYPosMove = kingYPos - 1;
                
                if (chessboard[kingXPosMove][kingYPosMove] == "-")
                {
                    while ((specificPosCheck == false) && (count < this->numWhitePieces))
                    {
                        kingCheckMate = this->checkIfPieceHasCheck(this->whitePieces[count]->getPieceType(), this->whitePieces[count]->getX(), this->whitePieces[count]->getY(), kingXPosMove, kingYPosMove);

                        if (kingCheckMate == true)
                        {
                            specificPosCheck = true;
                            checkMate = true;
                        }                        
                        else if (kingCheckMate == false)
                        {
                            checkMate = false;   
                            count++;
                        }  
                    }
                }

                if (checkMate == false)
                    break;

                specificPosCheck = false;
                kingSidesMove++;
                count = 0;
            }

            if (((kingYPos - 1) >= 0) && ((kingYPos - 1) <= 7)) //left-hand side
            {
                kingXPosMove = kingXPos;
                kingYPosMove = kingYPos - 1;

                if (chessboard[kingXPosMove][kingYPosMove] == "-")
                {
                    while ((specificPosCheck == false) && (count < this->numWhitePieces))
                    {
                        kingCheckMate = this->checkIfPieceHasCheck(this->whitePieces[count]->getPieceType(), this->whitePieces[count]->getX(), this->whitePieces[count]->getY(), kingXPosMove, kingYPosMove);

                        if (kingCheckMate == true)
                        {
                            specificPosCheck = true;
                            checkMate = true;
                        }                        
                        else if (kingCheckMate == false)
                        {
                            checkMate = false;   
                            count++;
                        }  
                    }
                }

                if (checkMate == false)
                    break;

                specificPosCheck = false;
                kingSidesMove++;
                count = 0;                    
            }

            if (((kingXPos + 1) >= 0) && ((kingXPos + 1) <= 7) && ((kingYPos - 1) >= 0) && ((kingYPos - 1) <= 7)) //left-hand side
            {
                kingXPosMove = kingXPos + 1;
                kingYPosMove = kingYPos - 1;

                if (chessboard[kingXPosMove][kingYPosMove] == "-")
                {
                    while ((specificPosCheck == false) && (count < this->numWhitePieces))
                    {
                        kingCheckMate = this->checkIfPieceHasCheck(this->whitePieces[count]->getPieceType(), this->whitePieces[count]->getX(), this->whitePieces[count]->getY(), kingXPosMove, kingYPosMove);

                        if (kingCheckMate == true)
                        {
                            specificPosCheck = true;
                            checkMate = true;
                        }                        
                        else if (kingCheckMate == false)
                        {
                            checkMate = false;   
                            count++;
                        }  
                    }
                }

                if (checkMate == false)
                    break;

                specificPosCheck = false;
                kingSidesMove++;
                count = 0;
            }
                    
            if (((kingXPos + 1) >= 0) && ((kingXPos + 1) <= 7)) //left-hand side
            {
                kingXPosMove = kingXPos + 1;
                kingYPosMove = kingYPos;

                if (chessboard[kingXPosMove][kingYPosMove] == "-")
                {
                    while ((specificPosCheck == false) && (count < this->numWhitePieces))
                    {
                        kingCheckMate = this->checkIfPieceHasCheck(this->whitePieces[count]->getPieceType(), this->whitePieces[count]->getX(), this->whitePieces[count]->getY(), kingXPosMove, kingYPosMove);

                        if (kingCheckMate == true)
                        {
                            specificPosCheck = true;
                            checkMate = true;
                        }                        
                        else if (kingCheckMate == false)
                        {
                            checkMate = false;   
                            count++;
                        }  
                    }
                }

                if (checkMate == false)
                    break;

                specificPosCheck = false;
                kingSidesMove++;
                count = 0;
            }

            kingSidesMove = 8;
        }
        // ===================================== Determine CheckMate END =====================================
    }

    else if (this->sideToMove == 'b')
    {
        while ((foundKing == false) && (check < this->numWhitePieces))
        {
            if (this->whitePieces[check]->getPieceType() == "king")
            {
                kingXPos = this->whitePieces[check]->getX();
                kingYPos = this->whitePieces[check]->getY();
                foundKing = true;
            }
            else check++;
        }

        // ===================================== Determine CheckMate BEGIN =====================================
        while ((checkMate == true) && (kingSidesMove < 8))
        {  
            int count = 0;

            //======================== RIGHT L CHECK ========================
            if (((kingXPos + 1) >= 0) && ((kingXPos + 1) <= 7) && ((kingYPos + 1) >= 0) && ((kingYPos + 1) <= 7)) //right-hand side
            {
                kingXPosMove = kingXPos + 1;
                kingYPosMove = kingYPos + 1;

                if (chessboard[kingXPosMove][kingYPosMove] == "-")
                {
                    while ((specificPosCheck == false) && (count < this->numBlackPieces))
                    {
                        kingCheckMate = this->checkIfPieceHasCheck(this->blackPieces[count]->getPieceType(), this->blackPieces[count]->getX(), this->blackPieces[count]->getY(), kingXPosMove, kingYPosMove);

                        if (kingCheckMate == true)
                        {
                            specificPosCheck = true;
                            checkMate = true;
                        }                        
                        else if (kingCheckMate == false)
                        {
                            checkMate = false;   
                            count++;
                        }   
                    }
                }

                if (checkMate == false)
                    break;

                specificPosCheck = false;
                kingSidesMove++;
                count = 0;
            }

            if (((kingYPos + 1) >= 0) && ((kingYPos + 1) <= 7)) //right-hand side
            {   
                kingXPosMove = kingXPos;
                kingYPosMove = kingYPos + 1;

                if (chessboard[kingXPosMove][kingYPosMove] == "-")
                {
                    while ((specificPosCheck == false) && (count < this->numBlackPieces))
                    {
                        kingCheckMate = this->checkIfPieceHasCheck(this->blackPieces[count]->getPieceType(), this->blackPieces[count]->getX(), this->blackPieces[count]->getY(), kingXPosMove, kingYPosMove);

                        if (kingCheckMate == true)
                        {
                            specificPosCheck = true;
                            checkMate = true;
                        }                        
                        else if (kingCheckMate == false)
                        {
                            checkMate = false;   
                            count++;
                        }  
                    }
                }

                if (checkMate == false)
                    break;

                specificPosCheck = false;
                kingSidesMove++;
                count = 0;
            }

            if (((kingXPos - 1) >= 0) && ((kingXPos - 1) <= 7) && ((kingYPos + 1) >= 0) && ((kingYPos + 1) <= 7)) //right-hand side
            {
                kingXPosMove = kingXPos - 1;
                kingYPosMove = kingYPos + 1;

                if (chessboard[kingXPosMove][kingYPosMove] == "-")
                {
                    while ((specificPosCheck == false) && (count < this->numBlackPieces))
                    {
                        kingCheckMate = this->checkIfPieceHasCheck(this->blackPieces[count]->getPieceType(), this->blackPieces[count]->getX(), this->blackPieces[count]->getY(), kingXPosMove, kingYPosMove);

                        if (kingCheckMate == true)
                        {
                            specificPosCheck = true;
                            checkMate = true;
                        }                        
                        else if (kingCheckMate == false)
                        {
                            checkMate = false;   
                            count++;
                        }  
                    }
                }

                if (checkMate == false)
                    break;

                specificPosCheck = false;
                kingSidesMove++;
                count = 0;
            }

            if (((kingXPos + 1) >= 0) && ((kingXPos + 1) <= 7)) //right-hand side
            {
                kingXPosMove = kingXPos + 1;
                kingYPosMove = kingYPos;
                
                if (chessboard[kingXPosMove][kingYPosMove] == "-")
                {
                    while ((specificPosCheck == false) && (count < this->numBlackPieces))
                    {
                        kingCheckMate = this->checkIfPieceHasCheck(this->blackPieces[count]->getPieceType(), this->blackPieces[count]->getX(), this->blackPieces[count]->getY(), kingXPosMove, kingYPosMove);

                        if (kingCheckMate == true)
                        {
                            specificPosCheck = true;
                            checkMate = true;
                        }                        
                        else if (kingCheckMate == false)
                        {
                            checkMate = false;   
                            count++;
                        }  
                    }
                }

                if (checkMate == false)
                    break;

                specificPosCheck = false;
                kingSidesMove++;
                count = 0;
            }

            
            
            //======================== LEFT L CHECK ========================
            if (((kingXPos - 1) >= 0) && ((kingXPos - 1) <= 7) && ((kingYPos - 1) >= 0) && ((kingYPos - 1) <= 7)) //left-hand side
            {
                kingXPosMove = kingXPos - 1;
                kingYPosMove = kingYPos - 1;
                
                if (chessboard[kingXPosMove][kingYPosMove] == "-")
                {
                    while ((specificPosCheck == false) && (count < this->numBlackPieces))
                    {
                        kingCheckMate = this->checkIfPieceHasCheck(this->blackPieces[count]->getPieceType(), this->blackPieces[count]->getX(), this->blackPieces[count]->getY(), kingXPosMove, kingYPosMove);

                        if (kingCheckMate == true)
                        {
                            specificPosCheck = true;
                            checkMate = true;
                        }                        
                        else if (kingCheckMate == false)
                        {
                            checkMate = false;   
                            count++;
                        }  
                    }
                }

                if (checkMate == false)
                    break;

                specificPosCheck = false;
                kingSidesMove++;
                count = 0;
            }

            if (((kingYPos - 1) >= 0) && ((kingYPos - 1) <= 7)) //left-hand side
            {
                kingXPosMove = kingXPos;
                kingYPosMove = kingYPos - 1;

                if (chessboard[kingXPosMove][kingYPosMove] == "-")
                {
                    while ((specificPosCheck == false) && (count < this->numBlackPieces))
                    {
                        kingCheckMate = this->checkIfPieceHasCheck(this->blackPieces[count]->getPieceType(), this->blackPieces[count]->getX(), this->blackPieces[count]->getY(), kingXPosMove, kingYPosMove);

                        if (kingCheckMate == true)
                        {
                            specificPosCheck = true;
                            checkMate = true;
                        }                        
                        else if (kingCheckMate == false)
                        {
                            checkMate = false;   
                            count++;
                        }  
                    }
                }

                if (checkMate == false)
                    break;

                specificPosCheck = false;
                kingSidesMove++;
                count = 0;                    
            }

            if (((kingXPos + 1) >= 0) && ((kingXPos + 1) <= 7) && ((kingYPos - 1) >= 0) && ((kingYPos - 1) <= 7)) //left-hand side
            {
                kingXPosMove = kingXPos + 1;
                kingYPosMove = kingYPos - 1;

                if (chessboard[kingXPosMove][kingYPosMove] == "-")
                {
                    while ((specificPosCheck == false) && (count < this->numBlackPieces))
                    {
                        kingCheckMate = this->checkIfPieceHasCheck(this->blackPieces[count]->getPieceType(), this->blackPieces[count]->getX(), this->blackPieces[count]->getY(), kingXPosMove, kingYPosMove);

                        if (kingCheckMate == true)
                        {
                            specificPosCheck = true;
                            checkMate = true;
                        }                        
                        else if (kingCheckMate == false)
                        {
                            checkMate = false;   
                            count++;
                        }  
                    }
                }

                if (checkMate == false)
                    break;

                specificPosCheck = false;
                kingSidesMove++;
                count = 0;
            }
                    
            if (((kingXPos + 1) >= 0) && ((kingXPos + 1) <= 7)) //left-hand side
            {
                kingXPosMove = kingXPos + 1;
                kingYPosMove = kingYPos;

                if (chessboard[kingXPosMove][kingYPosMove] == "-")
                {
                    while ((specificPosCheck == false) && (count < this->numBlackPieces))
                    {
                        kingCheckMate = this->checkIfPieceHasCheck(this->blackPieces[count]->getPieceType(), this->blackPieces[count]->getX(), this->blackPieces[count]->getY(), kingXPosMove, kingYPosMove);

                        if (kingCheckMate == true)
                        {
                            specificPosCheck = true;
                            checkMate = true;
                        }                        
                        else if (kingCheckMate == false)
                        {
                            checkMate = false;   
                            count++;
                        }  
                    }
                }

                if (checkMate == false)
                    break;

                specificPosCheck = false;
                kingSidesMove++;
                count = 0;
            }
            
            kingSidesMove = 8;
        }
        // ===================================== Determine CheckMate END =====================================

    }
    

    if (checkMate == false)
    {
        if (this->sideToMove == 'b')
            cout << "Failed: No Checkmate of w King\n";

        else if (this->sideToMove == 'w')
            cout << "Failed: No Checkmate of b King\n";
    }

    else if (checkMate == true)
    {        
        if (this->sideToMove == 'b')
            cout << "Success: Checkmate of w King at [" << kingXPos << "," << kingYPos << "]" << endl;

        else if (this->sideToMove == 'w')
            cout << "Success: Checkmate of b King at [" << kingXPos << "," << kingYPos << "]" << endl;
    }
    
    return *this;
}