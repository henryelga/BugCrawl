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
    int eatenBy;
public:
    int getHopLength() const;

protected:
    bool alive{};
    list<pair<int, int>> path;

public:
    Bug(int id, const pair<int, int> position, int direction, int size, int hopLength, int eatenBy)
            : id(id), position(position), direction(direction), size(size), hopLength(hopLength), eatenBy(eatenBy) {
        this->alive = true;
        this->path.push_back(position);
    }

    void setEatenBy(int eatenBy);;


    virtual void move() = 0;

    virtual bool isWayBlocked();

    virtual ~Bug();

    const string &getType() const { return type; };
    int getId() const { return id; };
    const pair<int, int> &getPosition() const { return position; };
    int getDirection() const { return direction; };
    int getSize() const { return size; };
    int getEatenBy() const { return eatenBy; };
    bool isAlive() const { return alive; };
    const list<pair<int, int>> &getPath() const { return path; };

    void setSize(int size);
    void setAlive(bool alive);
};

#endif //SFML_002_BUG_H
