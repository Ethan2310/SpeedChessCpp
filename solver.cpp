#include "solver.h"

solver::solver(string games)
{
    ifstream boardList, countList;
    string line;

    // ===================== Count total number of boards BEGIN =====================
    this->numGames = 0;

    countList.open(games.c_str());

    while (getline(countList, line))
        this->numGames++;

    countList.close();
    // ===================== Count total number of boards END =====================


    // ===================== Count total number of boards BEGIN =====================
    boardList.open(games.c_str());

    string * boardArray = new string[numGames];
    int * priorityArray = new int[numGames];
    int counter = 0;


    boards = new board*[numGames];
    for (int k = 0; k < numGames; k++)
        boards[k] = NULL;


    while (getline(boardList, line))
    {
        string boardName, priority;
        int boardPriority;

        istringstream boardInfo(line);
        getline(boardInfo, boardName, ',');
        boardArray[counter] = boardName;
        
        getline(boardInfo, priority, ',');
        stringstream convertToInt(priority);
        convertToInt >> boardPriority;
        priorityArray[counter] = boardPriority;

        counter++;
    }


    for (int k = 0; k < numGames; k++)
        boards[k] = new board(boardArray[k]);

   for (int i = 0; i < numGames - 1; i++)
    {
        for (int j = i + 1; j < numGames; j++)
        {
            if (priorityArray[i] > priorityArray[j])
            {
                int intTemp = priorityArray[i];
                string stringTemp = boardArray[i];

                priorityArray[i] = priorityArray[j];
                priorityArray[j] = intTemp;

                boardArray[i] = boardArray[j];
                boardArray[j] = stringTemp;
            }
        }
    }

    board ** tempArr = new board*[numGames];

    for (int k = 0; k < numGames; k++)
        tempArr[k] = NULL;

    
    for (int k = 0; k < numGames; k++)
    {
        tempArr[k] = new board(boardArray[k]);
        cout << "[" << priorityArray[k] << "] ";
        tempArr[k]->operator--();
    }

    // cout << "===================================================\n";
    // for (int k = 0; k < numGames; k++)
    //     delete tempArr[k];
    // delete [] tempArr;
    // tempArr = NULL;
    // cout << "===================================================\n";

    boardList.close();
    delete [] boardArray;
    delete [] priorityArray;
}

solver::~solver()
{
    for (int k = 0; k < numGames; k++)
        delete boards[k];
    delete [] boards;
    boards = NULL;

    cout << "Num Boards Deleted: " << this->numGames << endl;
}