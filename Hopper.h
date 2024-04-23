//
// Created by Elga Jerusha Henry on 16/04/2024.
//

#ifndef SFML_002_HOPPER_H
#define SFML_002_HOPPER_H

#include "Bug.h"

class Hopper : public Bug {
protected:
    int hopLength{};

public:
    Hopper(int id,
            pair<int, int> position,
            int direction,
            int size, int hopLength): Bug(id, position, direction, size, hopLength){
        this->type = "Hopper";
        this->alive = true;
        this->path = {this->position};
    };

    void move() override; // Override the move function
};

#endif //SFML_002_HOPPER_H
