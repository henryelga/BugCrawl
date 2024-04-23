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
            newPosition.second -= getHopLength();
            break;
        case 2: // Facing East
            newPosition.first += getHopLength();
            break;
        case 3: // Facing South
            newPosition.second += getHopLength();
            break;
        case 4: // Facing West
            newPosition.first -= getHopLength();
            break;
        default:
            break;
    }

    path.push_back(newPosition);
    position = newPosition;
}
