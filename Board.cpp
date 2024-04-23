#include "Board.h"
#include "Crawler.h"
#include "Hopper.h"
#include <iostream>
#include <sstream>
#include <fstream>


void Board::intializeBugs(ifstream &fin) {

    if (fin.good()) {
        string line;

        while (getline(fin, line)) {
            parseLine(line);
        }
        fin.close();
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

    try {

        if (bug_type == "C") {
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

            bugs_vector.push_back(new Crawler(bug_id, position, direction, size));

        } else if (bug_type == "H") {
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

            getline(strStream, strTemp, DELIMITER);
            hopLength = stoi(strTemp);

            pair<int, int> position = make_pair(x, y);

            bugs_vector.push_back(new Hopper(bug_id, position, direction, size, hopLength));

        }

    }
    catch (std::invalid_argument const &e) {
        cout << "Bad input: std::invalid_argument thrown" << '\n';
    }
    catch (std::out_of_range const &e) {
        cout << "Integer overflow: std::out_of_range thrown" << '\n';
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
        bug->move();
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
    for (auto bug: bugs_vector) {
        auto position = bug->getPosition();
        int x = position.first;
        int y = position.second;
        if (x >= 0 && x < 10 && y >= 0 && y < 10) { // Check if bug's position is within the board bounds
            cells[x][y].push_back(bug);
        }
    }

    // Display all cells
    cout << "Displaying all Cells:" << endl;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cout << "(" << i << "," << j << "): ";
            if (cells[i][j].empty()) {
                cout << "empty";
            } else {
                for (Bug *bug: cells[i][j]) {
                    cout << bug->getType() << " " << bug->getId();
                    cout << " ";
                }
            }
            cout << " " << endl;
        }
    }
}



