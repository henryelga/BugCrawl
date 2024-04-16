//
// Created by Elga Jerusha Henry on 16/04/2024.
//
#include "Crawler.h"
#include <cstdlib> // For rand
#include <ctime>   // For time

void Crawler::move() {
    pair<int, int> newPosition = position;
    if (direction == Direction::North) {
        newPosition.second += 1;
    } else if (direction == Direction::South) {
        newPosition.second -= 1;
    } else if (direction == Direction::East) {
        newPosition.first += 1;
    } else if (direction == Direction::West) {
        newPosition.first -= 1;
    }

    path.push_back(newPosition);
    position = newPosition;
}

bool Crawler::isWayBlocked() {
    int x = position.first;
    int y = position.second;

    // x = 0
    if(x == 0){
        if(y == 0){
            if(direction == Direction::North || direction == Direction::West){
                return true;
            }
        }
        else if(y == 9){
            if(direction == Direction::South || direction == Direction::West){
                return true;
            }
        }
        else if(direction == Direction::West){
            return true;
        }
    }

    //x = 9
    if(x == 9){
        if(y == 0){
            if(direction == Direction::North || direction == Direction::East){
                return true;
            }
        }
        else if(y == 9){
            if(direction == Direction::South || direction == Direction::East){
                return true;
            }
        }
        else if(direction == Direction::East){
            return true;
        }
    }

    //y = 0
    if(y == 0 && direction == Direction::North){
        return true;
    }

    //y = 9
    if(y == 9 && direction == Direction::South){
        return true;
    }
    return false;
}


