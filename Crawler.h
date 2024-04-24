//
// Created by Elga Jerusha Henry on 16/04/2024.
//

#ifndef SFML_002_CRAWLER_H
#define SFML_002_CRAWLER_H

#include <string>
#include "Bug.h"

class Crawler : public Bug {

public:
    Crawler(int id,
            pair<int, int> position,
            int direction,
            int size): Bug(id, position, direction, size, 0, 0){
        this->type = "Crawler";
        this->alive = true;
        this->path = {this->position};
    };


    void move() override;

};

#endif //SFML_002_CRAWLER_H
