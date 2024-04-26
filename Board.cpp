#include "Board.h"
#include "Crawler.h"
#include "Hopper.h"
#include "Teleporter.h"
#include "SuperBug.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <thread>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

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
        } else if (bug_type == "T") {
            temp = new Teleporter(bug_id, position, direction, size);
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
            if (cells[i][j].size() > 1) {
                sort(cells[i][j].begin(), cells[i][j].end(), [](Bug *a, Bug *b) {
                    // return a->getSize() > b->getSize();
                    if (a->getSize() > b->getSize()) {
                        return true;
                    } else if (a->getSize() == b->getSize()) {
                        // Choose random bug
                        return rand() % 2 == 0;
                    } else {
                        return false;
                    }
                });
                Bug *bigBug = cells[i][j][0];
                for (int k = 1; k < cells[i][j].size(); k++) {
                    Bug *tempBug = cells[i][j][k];
                    if (tempBug->isAlive()) {
                        bigBug->setSize(bigBug->getSize() + tempBug->getSize());
                        tempBug->setAlive(false);
                        tempBug->setEatenBy(bigBug->getId());
                        cout << "Killed " << tempBug->getId() << endl;
                    }

                }
            }
        }
    }

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
    }
}

void Board::tapBoard(vector<Bug *> &bugs) {
    for (Bug *bug: bugs) {
        vector<Bug *> &v = cells[bug->getPosition().first][bug->getPosition().second];
        v.erase(remove(v.begin(), v.end(), bug), v.end());
        bug->move();
        cells[bug->getPosition().first][bug->getPosition().second].push_back(bug);
    }
    cout << "Bug Board Tapped!" << endl;

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (cells[i][j].size() > 1) {
                sort(cells[i][j].begin(), cells[i][j].end(), [](Bug *a, Bug *b) {
                    // return a->getSize() > b->getSize();
                    if (a->getSize() > b->getSize()) {
                        return true;
                    } else if (a->getSize() == b->getSize()) {
                        // Choose random bug
                        return rand() % 2 == 0;
                    } else {
                        return false;
                    }
                });
                Bug *bigBug = cells[i][j][0];
                for (int k = 1; k < cells[i][j].size(); k++) {
                    Bug *tempBug = cells[i][j][k];
                    if (tempBug->isAlive()) {
                        bigBug->setSize(bigBug->getSize() + tempBug->getSize());
                        tempBug->setAlive(false);
                        tempBug->setEatenBy(bigBug->getId());
                        cout << "Killed " << tempBug->getId() << endl;
                    }
                }
            }
        }
    }

    int bugCount = 0;
    Bug *winner;
    for (Bug *bug: bugs) {
        if (bug->isAlive()) {
            bugCount++;
            winner = bug;
        }
    }
    if (bugCount == 1) {
        cout << "Winner: Bug " << winner->getId() << "!" << endl;
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
        if (bug->isAlive()) {
            cout << "Alive!" << endl;
        } else {
            cout << "Eaten by " << bug->getEatenBy() << endl;
        }
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
        if (bug->isAlive()) {
            fout << "Alive!" << endl;
        } else {
            fout << "Eaten by " << bug->getEatenBy() << endl;
        }

    }
    cout << "Written life history of all bugs to .txt file" << endl;
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

    while (countAliveBugs() > 1) {
        tapBoard();
        sleep_for(seconds(1));
    }

}

int Board::countAliveBugs() {
    int bugCount = 0;
    for (Bug *bug: bugs_vector) {
        if (bug->isAlive()) {
            bugCount++;
        }
    }
    return bugCount;
}

void Board::displayAllBugsSFML() {
    const int tileSize = 90;

    // SFML window
    sf::RenderWindow window(sf::VideoMode(900, 900), "Bug Simulation");

    // Super-Bug controlled by arrow keys
    int superBugX = 0;
    int superBugY = 0;

    // Bug textures
    sf::Texture crawlerTexture;
    crawlerTexture.loadFromFile("crawler.png");
    crawlerTexture.setSmooth(true);

    sf::Texture hopperTexture;
    hopperTexture.loadFromFile("hopper.png");
    hopperTexture.setSmooth(true);

    sf::Texture teleporterTexture;
    teleporterTexture.loadFromFile("teleporter.png");
    teleporterTexture.setSmooth(true);

    sf::Texture superBugTexture;
    superBugTexture.loadFromFile("superBug.png");
    superBugTexture.setSmooth(true);

    // Sprites
    sf::Sprite crawlerSprite(crawlerTexture);
    sf::Sprite hopperSprite(hopperTexture);
    sf::Sprite teleporterSprite(teleporterTexture);
    sf::Sprite superBugSprite(superBugTexture);

    // Sprites Sizes
    crawlerSprite.setScale(tileSize / static_cast<float>(crawlerTexture.getSize().x),
                           tileSize / static_cast<float>(crawlerTexture.getSize().y));

    hopperSprite.setScale(tileSize / static_cast<float>(hopperTexture.getSize().x),
                          tileSize / static_cast<float>(hopperTexture.getSize().y));

    teleporterSprite.setScale(tileSize / static_cast<float>(teleporterTexture.getSize().x),
                              tileSize / static_cast<float>(teleporterTexture.getSize().y));

    superBugSprite.setScale(tileSize / static_cast<float>(superBugTexture.getSize().x),
                            tileSize / static_cast<float>(superBugTexture.getSize().y));

    SuperBug superBug(0, pair<int, int>(), 0, 0);
    superBug.setSize(10);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Mouse Clicks
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    tapBoard(bugs_vector);
                }
            }

            // Move super-bug
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    superBug.moveSuperBug(sf::Keyboard::Left);
                } else if (event.key.code == sf::Keyboard::Right) {
                    superBug.moveSuperBug(sf::Keyboard::Right);
                } else if (event.key.code == sf::Keyboard::Up) {
                    superBug.moveSuperBug(sf::Keyboard::Up);
                } else if (event.key.code == sf::Keyboard::Down) {
                    superBug.moveSuperBug(sf::Keyboard::Down);
                }
                superBugSprite.setPosition(superBug.getPosition().first * tileSize,
                                           superBug.getPosition().second * tileSize);
                cout << "Super Bug: " << superBug.getPosition().first << "," << superBug.getPosition().second
                     << ", Size: " << superBug.getSize() << endl;
            }
        }

        window.clear();

        // Board Pattern
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
                tile.setPosition(i * tileSize, j * tileSize);

                // Tile Colours
                if ((i + j) % 2 == 0) {
                    tile.setFillColor(sf::Color(34, 139, 34)); // Dark Green
                } else {
                    tile.setFillColor(sf::Color(204, 255, 204)); // Light Green
                }
                window.draw(tile);

                // Render bugs
                const vector<Bug *> &bugs = cells[i][j];
                for (const Bug *bug: bugs) {
                    if (bug->isAlive()) {
                        // Set sprite based on bug type
                        if (bug->getType() == "Crawler") {
                            crawlerSprite.setPosition(i * tileSize, j * tileSize);
                            window.draw(crawlerSprite);
                        } else if (bug->getType() == "Hopper") {
                            hopperSprite.setPosition(i * tileSize, j * tileSize);
                            window.draw(hopperSprite);
                        } else if (bug->getType() == "Teleporter") {
                            teleporterSprite.setPosition(i * tileSize, j * tileSize);
                            window.draw(teleporterSprite);
                        } else {
                            // Unknown bug type
                            cout << "Unknown bug type: " << bug->getType() << endl;
                        }
                    }
                }
            }
        }

        // Draw super-bug
        vector<Bug *> &bugsAtSuperBugPos = cells[superBug.getPosition().first][superBug.getPosition().second];
        for (Bug *bug: bugsAtSuperBugPos) {
            if (bug->isAlive() && bug->getType() != "SuperBug") {
                superBug.setSize(superBug.getSize() + bug->getSize());
                bug->setAlive(false);
                bug->setEatenBy(superBug.getId());
                cout << "Super Bug ate Bug " << bug->getId() << endl;
            }
        }
        window.draw(superBugSprite);

        // Display the window
        window.display();
    }
}