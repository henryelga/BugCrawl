//
// Created by Elga Jerusha Henry on 16/04/2024.
//
#include "Crawler.h"
#include <cstdlib> // For rand
#include <ctime>   // For time

//Crawler::Crawler(int bugId, pair<int, int> position, Direction direction, int size, list<pair<int,int>> path, bool alive) {
//    this->type = 'C';
//    this->id = bugId;
//    this->position = position;
//    this->direction = direction;
//    this->size = size;
//    this->path = path;
//    this->alive = alive;
//}

void Crawler::move() {
    pair<int, int> newPosition = position;
    while (isWayBlocked()) {
        direction = rand() % 4 + 1;
    }

    switch (direction) {
        case 1: // Facing North
            newPosition.second -= 1;
            break;
        case 2: // Facing East
            newPosition.first += 1;
            break;
        case 3: // Facing South
            newPosition.second += 1;
            break;
        case 4: // Facing West
            newPosition.first -= 1;
            break;
        default:
            break;
    }

    path.push_back(newPosition);
    position = newPosition;
}
