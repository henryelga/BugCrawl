//
// Created by Elga Jerusha Henry on 16/04/2024.
//

#include <utility>
#include <list>
#include <string>

using namespace std;

#ifndef SFML_002_BUG_H
#define SFML_002_BUG_H

enum class Direction {
    North, East, South, West
};

class Bug {
protected:
    string type;
    int id{};
    pair<int, int> position;
    int direction{};
//    Direction direction;
    int size{};
    int hopLength{};
public:
    int getHopLength() const;

protected:
    bool alive{};
    list<pair<int, int>> path;

public:
//    Bug(int id, const pair<int, int> position, int direction, int size, int hopLength){
//        this->alive = true;
//        this->path.push_back(position);
//    };
    Bug(int id, const pair<int, int> position, int direction, int size, int hopLength)
            : id(id), position(position), direction(direction), size(size), hopLength(hopLength) {
        this->alive = true;
        this->path.push_back(position);
    };


    virtual void move() = 0;

    virtual bool isWayBlocked();

    virtual ~Bug();

    const string &getType() const { return type; };
    int getId() const { return id; };
    const pair<int, int> &getPosition() const { return position; };
    int getDirection() const { return direction; };
    int getSize() const { return size; };
    bool isAlive() const { return alive; };
    const list<pair<int, int>> &getPath() const { return path; };
    // destructor
};

#endif //SFML_002_BUG_H
