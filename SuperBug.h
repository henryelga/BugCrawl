//
// Created by Elga Jerusha Henry on 25/04/2024.
//

#ifndef SFML_002_SUPERBUG_H
#define SFML_002_SUPERBUG_H

#include "Bug.h"
#include <SFML/Graphics.hpp>

class SuperBug : public Bug {

public:
    SuperBug(int id, pair<int, int> position, int direction, int size) : Bug(id, position, direction, size, 0, 0) {
        this->type = "SuperBug";
        this->alive = true;
        this->path = {this->position};
    };


    void move() override;
    void moveSuperBug(sf::Keyboard::Key key);

};


#endif //SFML_002_SUPERBUG_H
