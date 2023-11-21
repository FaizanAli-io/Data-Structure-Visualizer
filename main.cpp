#include "Graphic Objects/ListNode.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!");
    sf::CircleShape shape(150.f);
    shape.setPointCount(100);
    shape.setOutlineThickness(-10.f);
    shape.setOutlineColor(sf::Color::Red);
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(25, 25);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(shape);
        window.display();
    }
}