//
// Created by Elga Jerusha Henry on 24/04/2024.
//

#include "Teleporter.h"

void Teleporter::move() {
    pair<int, int> newPosition = position;

    newPosition.first = rand() % 10;
    newPosition.second = rand() % 10;

    path.push_back(newPosition);
    position = newPosition;
}
