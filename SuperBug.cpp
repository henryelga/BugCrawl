//
// Created by Elga Jerusha Henry on 25/04/2024.
//

#include <SFML/Window/Keyboard.hpp>
#include "SuperBug.h"

void SuperBug::move() {
    // Implement the default move logic here, similar to the Crawler::move() function
}

void SuperBug::moveSuperBug(sf::Keyboard::Key key) {
    pair<int, int> newPosition = position;

    // Update position based on arrow key input
    if (key == sf::Keyboard::Left) {
        newPosition.first = max(position.first - 1, 0);
    } else if (key == sf::Keyboard::Right) {
        newPosition.first = min(position.first + 1, 9);
    } else if (key == sf::Keyboard::Up) {
        newPosition.second = max(position.second - 1, 0);
    } else if (key == sf::Keyboard::Down) {
        newPosition.second = min(position.second + 1, 9);
    }

    // Check if the new position is within the board boundaries
    if (newPosition.first >= 0 && newPosition.first < 10 && newPosition.second >= 0 && newPosition.second < 10) {
        path.push_back(newPosition);
        position = newPosition;
    }
}
