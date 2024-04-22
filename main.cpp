#include <SFML/Graphics.hpp>

sf::CircleShape shape(0.f);

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Board.h"
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"

using namespace std;
using namespace sf;

int main() {
    ifstream fin("bugs.txt");
    ofstream fout("bugs_life_history_date_time.txt");
    cout << "Sample Board" << endl;
    Board board;

    int choice;

    do {
        // Display menu
        cout << "Menu Items" << endl;
        cout << "1. Initialize Bug Board (load data from file)" << endl;
        cout << "2. Display all Bugs" << endl;
        cout << "3. Find a Bug (given an id)" << endl;
        cout << "4. Tap the Bug Board (causes move all, then fight/eat)" << endl;
        cout << "5. Display Life History of all Bugs (path taken)" << endl;
        cout << "6. Exit: Write Life History of all Bugs to file" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                board.intializeBugs(fin);
                break;
            case 2:
                board.displayAllBugs();
                break;
            case 3:
                int bugId;
                cout << "Enter Bug ID to find: ";
                cin >> bugId;
                board.findaBug(bugId);
                break;
            case 4:
                board.tapBoard();
                board.displayAllBugs();
                break;
            case 5:
                board.displayLifeHistory();
                break;
            case 6:
                board.writeLifeHistory(fout);
                cout << "Life history written to file." << endl;
                break;
            case 7:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        cout << endl;

    } while (choice != 7);

    fin.close(); // Close input file stream
    fout.close(); // Close output file stream


    return 0;
}

