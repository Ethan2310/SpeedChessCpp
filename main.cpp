#include<iostream>
#include<string>

#include"solver.h"

using namespace std;

int main()
{
    // if (boardOne.checkIfPieceHasCheck("pawn", 1, 7, 7, 6) == true)
    //     cout << "Found king\n";
    // else cout << "King not found\n";

    // board boardOne("game4.txt");
    // boardOne.operator--();

    // board boardTwo("game2.txt");
    // boardTwo.operator--();
    
    // board boardThree("game3.txt");
    // boardThree.operator--();
    
    // board boardFour("game1.txt");
    // boardFour.operator--();
    

    solver board("list.txt");

    return 0;
}