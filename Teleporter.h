//
// Created by Elga Jerusha Henry on 24/04/2024.
//

#ifndef SFML_002_TELEPORTER_H
#define SFML_002_TELEPORTER_H


#include "Bug.h"

class Teleporter : public Bug {

public:
    Teleporter(int id,
            pair<int, int> position,
            int direction,
            int size): Bug(id, position, direction, size, 0, 0){
        this->type = "Teleporter";
        this->alive = true;
        this->path = {this->position};
    };


    void move() override;

};


#endif //SFML_002_TELEPORTER_H
