#include <SFML/Graphics.hpp>
sf::CircleShape shape (0.f);
#include <vector>
#include <iostream>
using namespace std;
using namespace sf;
int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");

//    sf::RectangleShape btn1;
//    btn1.setSize(sf::Vector2f(100, 25));
//    shape.setPosition(175, 0);
//    shape.setFillColor(sf::Color::Green);

    vector<sf::RectangleShape> bg;
    for(int r = 0; r < 10; r++){
        for(int c = 0; c < 10; c++){
            sf::RectangleShape shape;
            shape.setPosition(r*50, c*50);
            shape.setSize(sf::Vector2f(50,50));
            shape.setFillColor((r+c)%2==0?sf::Color::Black:sf::Color::White);
            bg.push_back(shape);
        }
    }

    int dir = 0;
    window.setFramerateLimit(40);
    bool isSelected = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {


                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                if (mouseX >= shape.getPosition().x && mouseX <= shape.getPosition().x + 50
                    && mouseY >= shape.getPosition().y && mouseY <= shape.getPosition().y + 50) {
                    isSelected = true;
                    shape.setFillColor(sf::Color::Blue);
                } else {
                    isSelected = false;
                    shape.setFillColor(sf::Color::Green);
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                if (isSelected) {
                    isSelected = false;
                    shape.setFillColor(sf::Color::Green);
                }
            } else if (event.type == sf::Event::MouseMoved) {
                if (isSelected) {
                    shape.setPosition(event.mouseMove.x-25, event.mouseMove.y-25);
                }

            }
        }

        window.clear();
        for(RectangleShape &s: bg){
            window.draw(s);
        }
        window.draw(shape);
//        window.draw(btn1);
        window.display();
    }
    return 0;
}

void mouseClicked(int x, int y)
{
    if(x >= 290 && x >= 390 && y>= 5 && y <= 30 )
    {
        shape.setFillColor(sf::Color::Red);
    }
}


/*
bool contains(int x, int y)
{
    int shapeX = ((int)shape.getPosition().x/50)*50;
    int shapeY = ((int)shape.getPosition().x/50)*50;
    cout << shapeX << ", " << shapeY <<
    return x == shapeX && y == shapeY;
}
*/