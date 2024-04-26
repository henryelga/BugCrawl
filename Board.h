//
// Created by Elga Jerusha Henry on 16/04/2024.
//

#ifndef SFML_002_BOARD_H
#define SFML_002_BOARD_H

#include <vector>
#include "Bug.h"

using namespace std;

class Board {
private:
//    vector<vector<vector<Bug*>>> cells; //columns -- rows -- list of bugs
//    vector<vector<Bug*>> cells;
    vector<vector<vector<Bug*>>> cells;
    vector<Bug *> bugs_vector;

public:
    // vector of 100 cells --  vector of bugs

public:
//    Board();
//    ~Board();

//    Board():cells(10, vector<Bug*>(10, nullptr)){}
    Board() : cells(10, vector<vector<Bug*>>(10)) {}

    void intializeBugs(ifstream &fin);
    void parseLine(const string &strLine);
    void displayAllBugs() const;
    void findaBug(int id) const;
    void tapBoard();
    void displayLifeHistory();
    void writeLifeHistory(ofstream &fout);
    void displayAllCells();


    static void printBug(const Bug *bug) ;

    void runStimulation();

    void displayAllBugsSFML();

    int countAliveBugs();

    void tapBoard(vector<Bug *> &bugs);

    void tapBoard(const vector<Bug *> &bugs);
};

#endif //SFML_002_BOARD_H
