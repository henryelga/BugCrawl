//
// Created by Elga Jerusha Henry on 16/04/2024.
//

#ifndef SFML_002_HOPPER_H
#define SFML_002_HOPPER_H

#include "Bug.h"

class Hopper : public Bug {
private:
    int hopLength;

public:
    void move() override; // Override the move function
    bool isWayBlocked() override; // Override the isWayBlocked function
};

#endif //SFML_002_HOPPER_H
