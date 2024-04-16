//
// Created by Elga Jerusha Henry on 16/04/2024.
//

#include <utility>
#include <list>

using namespace std;

#ifndef SFML_002_BUG_H
#define SFML_002_BUG_H

enum class Direction { North, East, South, West };

class Bug {
protected:
    int id;
    pair<int, int> position;
//    int direction;
    Direction direction;
    int size;
    bool alive;
    list<pair<int,int>> path;

public:
    virtual void move() = 0;
    virtual bool isWayBlocked() = 0;
    virtual ~Bug();  // destructor
};

#endif //SFML_002_BUG_H
