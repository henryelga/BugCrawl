//
// Created by Elga Jerusha Henry on 16/04/2024.
//
#include "Hopper.h"
#include <cstdlib> // For rand
#include <ctime>   // For time

void Hopper::move() {
    pair<int, int> newPosition = position;
    while (isWayBlocked()) {
        srand(time(nullptr));
        direction = rand() % 4 + 1;
    }

    switch (direction) {
        case 1: // Facing North
            newPosition.second += hopLength;
            break;
        case 2: // Facing East
            newPosition.first += hopLength;
            break;
        case 3: // Facing South
            newPosition.second -= hopLength;
            break;
        case 4: // Facing West
            newPosition.first -= hopLength;
            break;
        default:
            break;
    }

    path.push_back(newPosition);
    position = newPosition;
}
