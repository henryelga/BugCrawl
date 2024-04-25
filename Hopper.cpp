//
// Created by Elga Jerusha Henry on 16/04/2024.
//
#include "Hopper.h"
#include <cstdlib> // For rand
#include <ctime>   // For time

void Hopper::move() {
    pair<int, int> newPosition = position;
    while (isWayBlocked()) {

        direction = rand() % 4 + 1;
    }

    switch (direction) {
        case 1: // North
            newPosition.second -= getHopLength();
            break;
        case 2: // East
            newPosition.first += getHopLength();
            break;
        case 3: // South
            newPosition.second += getHopLength();
            break;
        case 4: // West
            newPosition.first -= getHopLength();
            break;
        default:
            break;
    }

    // if hopper hops less than 0, pick the maximum numb
    // if hopper hops more than 9, pick the minimum num
    newPosition.first = max(0, min(newPosition.first, 9));
    newPosition.second = max(0, min(newPosition.second, 9));


    path.push_back(newPosition);
    position = newPosition;
}
