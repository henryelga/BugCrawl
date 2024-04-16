//
// Created by Elga Jerusha Henry on 16/04/2024.
//

#ifndef SFML_002_CRAWLER_H
#define SFML_002_CRAWLER_H

#include "Bug.h"

class Crawler : public Bug {
public:
    void move() override;
    bool isWayBlocked() override;
};

#endif //SFML_002_CRAWLER_H
