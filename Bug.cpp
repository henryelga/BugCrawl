//
// Created by Elga Jerusha Henry on 16/04/2024.
//

#include "Bug.h"

Bug::~Bug() {}

int Bug::getHopLength() const {
    return hopLength;
}

//bool Bug::isWayBlocked() {
//    int x = position.first;
//    int y = position.second;
//
//    // x = 0
//    if (x == 0) {
//        if (y == 0) {
//            if (direction == 1 || direction == 4) {
//                return true;
//            }
//        } else if (y == 9) {
//            if (direction == 3 || direction == 4) {
//                return true;
//            }
//        } else if (direction == 4) {
//            return true;
//        }
//    }
//
//    //x = 9
//    if (x == 9) {
//        if (y == 0) {
//            if (direction == 1 || direction == 2) {
//                return true;
//            }
//        } else if (y == 9) {
//            if (direction == 3 || direction == 2) {
//                return true;
//            }
//        } else if (direction == 2) {
//            return true;
//        }
//    }
//
//    //y = 0
//    if (y == 0 && direction == 1) {
//        return true;
//    }
//
//    //y = 9
//    if (y == 9 && direction == 3) {
//        return true;
//    }
//    return false;
//}

//bool Bug::isWayBlocked() {
//    int x = position.first;
//    int y = position.second;
//
//    // Check if the bug is at the edge of the board and cannot move in the current direction
//    if ((x == 0 || y == 0) && (direction == 1 || direction == 4)) {
//        // Bug is at the left edge and moving North or West
//        return true;
//    } else if (x == 9 && (direction == 1 || direction == 2)) {
//        // Bug is at the right edge and moving East or South
//        return true;
//    } else if (y == 0 && direction == 4) {
//        // Bug is at the bottom edge and moving West
//        return true;
//    } else if (y == 9 && direction == 3) {
//        // Bug is at the top edge and moving South
//        return true;
//    }
//
//    // If none of the above conditions match, the way is not blocked
//    return false;
//}

bool Bug::isWayBlocked() {
    int x = position.first;
    int y = position.second;

    switch (direction) {
        case 1: // North
            return (y == 0);
        case 2: // East
            return (x == 9);
        case 3: // South
            return (y == 9);
        case 4: // West
            return (x == 0);
        default:
            return false;
    }
}

void Bug::setSize(int size) {
    Bug::size = size;
}

void Bug::setAlive(bool alive) {
    Bug::alive = alive;
}

void Bug::setEatenBy(int eatenBy) {
    Bug::eatenBy = eatenBy;
}

void Bug::setPosition(pair<int, int> pair) {
Bug::position = pair;
}


