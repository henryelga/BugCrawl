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
    srand(time(nullptr));

    int choice;

    do {
        // Display menu
        cout << "Menu Items" << endl;
        cout << "1. Initialize Bug Board (load data from file)" << endl;
        cout << "2. Display all Bugs" << endl;
        cout << "3. Find a Bug (given an id)" << endl;
        cout << "4. Tap the Bug Board (causes move all, then fight/eat)" << endl;
        cout << "5. Display Life History of all Bugs (path taken)" << endl;
        cout << "6. Display all Cells listing their Bugs " << endl;
        cout << "7. Run Stimulation (generates a tap every second)" << endl;
        cout << "8. Display GUI" << endl;
        cout << "9. Exit" << endl;
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
                break;
            case 5:
                board.displayLifeHistory();
                break;
            case 6:
                board.displayAllCells();
                break;
            case 7:
                board.runStimulation();
                break;
            case 8:
                board.displayAllBugsSFML();
                break;
            case 9:
                board.writeLifeHistory(fout);
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        cout << endl;

    } while (choice != 9);

    fin.close(); // Close input file stream
    fout.close(); // Close output file stream


    return 0;
}

