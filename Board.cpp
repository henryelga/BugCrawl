#include "Board.h"
#include "Crawler.h"
#include "Hopper.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <thread>

using namespace this_thread;
using namespace chrono;


void Board::intializeBugs(ifstream &fin) {

    if (fin.good()) {
        string line;

        while (getline(fin, line)) {
            parseLine(line);
        }
        fin.close();
        cout << "Bug Board Initialized" << endl;
    } else
        cout << "Unable to open file, or file is empty.";
}

void Board::parseLine(const string &strLine) {
    stringstream strStream(strLine);

    const char DELIMITER = ';';

    string bug_type;
    getline(strStream, bug_type, DELIMITER);
    string strTemp;
    int bug_id;
    int x;
    int y;
    int direction;
    int size;
    int hopLength;
    Bug *temp;
    try {
        getline(strStream, strTemp, DELIMITER);
        bug_id = stoi(strTemp);

        getline(strStream, strTemp, DELIMITER);
        x = stoi(strTemp);

        getline(strStream, strTemp, DELIMITER);
        y = stoi(strTemp);

        getline(strStream, strTemp, DELIMITER);
        direction = stoi(strTemp);

        getline(strStream, strTemp, DELIMITER);
        size = stoi(strTemp);
        pair<int, int> position = make_pair(x, y);
        if (bug_type == "C") {
            temp = new Crawler(bug_id, position, direction, size);
        } else if (bug_type == "H") {
            getline(strStream, strTemp, DELIMITER);
            hopLength = stoi(strTemp);
            temp = new Hopper(bug_id, position, direction, size, hopLength);
        }
        bugs_vector.push_back(temp);
        cells[x][y].push_back(temp);
    }
    catch (invalid_argument const &e) {
        cout << "Bad input: invalid_argument thrown" << '\n';
    }
    catch (out_of_range const &e) {
        cout << "Integer overflow: out_of_range thrown" << '\n';
    }
}

void Board::printBug(const Bug *bug) {
    const pair<int, int> &pos = bug->getPosition();
    int x = pos.first;
    int y = pos.second;

    int direction = bug->getDirection();
    string dir;
    switch (direction) {
        case 1:
            dir = "North";
            break;
        case 2:
            dir = "East";
            break;
        case 3:
            dir = "South";
            break;
        case 4:
            dir = "West";
            break;
        default:
            dir = "Unknown";
            break;
    }

    string alive = (bug->isAlive()) ? "Alive" : "Dead";

    cout << bug->getId() << " " <<
         bug->getType() << " (" <<
         x << "," << y << ") " <<
         bug->getSize() << " " <<
         dir;

    if (bug->getType() == "Hopper") {
        cout << " " << bug->getHopLength();
    }

    cout << " " << alive << endl;
}


void Board::displayAllBugs() const {
    for (const Bug *bug: bugs_vector) {
        printBug(bug);
    }
}

void Board::findaBug(int id) const {
    bool found = false;
    for (const Bug *bug: bugs_vector) {
        if (bug->getId() == id) {
            cout << "Bug Found" << endl;
            found = true;
            printBug(bug);
        }
    }
    if (!found) {
        cout << "Bug Id: " << id << " Not found" << endl;
    }
}

void Board::tapBoard() {
    for (Bug *bug: bugs_vector) {
        vector<Bug *> &v = cells[bug->getPosition().first][bug->getPosition().second];
        v.erase(remove(v.begin(), v.end(), bug));
        bug->move();
        cells[bug->getPosition().first][bug->getPosition().second].push_back(bug);

    }
    cout << "Bug Board Tapped!" << endl;

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (!cells[i][j].empty()) {
                for (Bug *bug: cells[i][j]) {
                    sort(cells[i][j].begin(), cells[i][j].end(), [](Bug *a, Bug *b) {
                        return a->getSize() > b->getSize();
                    });
                }
                Bug *bigBug = cells[i][j][0];
                for (int k = 1; k < cells[i][j].size(); k++) {
                    Bug *tempBug = cells[i][j][k];
                    if (tempBug->isAlive()) {
                        bigBug->setSize(bigBug->getSize() + tempBug->getSize());
                        tempBug->setAlive(false);
                        cout << "Killed " << tempBug->getId() << endl;
                    }

                }
            }
        }
    }
}

void Board::displayLifeHistory() {
    for (Bug *bug: bugs_vector) {
        const list<pair<int, int>> &path = bug->getPath();

        cout << bug->getId() << " " <<
             bug->getType() << " Path: ";
        for (const pair<int, int> &pos: path) {
            cout << "(" << pos.first << "," << pos.second << ") ";
        }
        cout << (bug->isAlive() ? "Alive" : "Dead") << endl;
    }
}

void Board::writeLifeHistory(ofstream &fout) {
    for (Bug *bug: bugs_vector) {
        const list<pair<int, int>> &path = bug->getPath();

        fout << bug->getId() << " " <<
             bug->getType() << " Path: ";
        for (const pair<int, int> &pos: path) {
            fout << "(" << pos.first << "," << pos.second << ") ";
        }
        fout << (bug->isAlive() ? "Alive" : "Dead") << endl;
    }
    cout << "done" << endl;
}

void Board::displayAllCells() {
    // Display all cells
    cout << "Displaying all Cells:" << endl;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cout << "(" << i << "," << j << "): ";
            if (cells[i][j].empty()) {
                cout << "empty";
            } else {
                for (Bug *bug: cells[i][j]) {
                    if (bug->isAlive()) {
                        cout << bug->getType() << " " << bug->getId();
                        cout << " ";
                    }
                }
            }
            cout << " " << endl;
        }
    }
}

void Board::runStimulation() {
    cout << "Running Stimulation" << endl;
    bool gameRunning = true;
    while (gameRunning) {
        tapBoard();
        int bugCount = 0;
        Bug *winner;
        for (Bug *bug: bugs_vector) {
            if (bug->isAlive()) {
                bugCount++;
                winner = bug;
            }
        }
        if (bugCount == 1) {
            cout << "Winner: Bug " << winner->getId() << "!" << endl;
            gameRunning = false;
        } else {
//            sleep_for(seconds(1));
        }

    }
}



