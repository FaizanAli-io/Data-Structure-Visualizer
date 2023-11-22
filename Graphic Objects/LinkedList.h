#include <SFML/Graphics.hpp>
#include "../Data Structures.h"
using namespace sf;

#ifndef CLASS
#define CLASS

class NodeObject
{
public:
    Text text;
    Font font;
    CircleShape shape;

    NodeObject()
    {
        shape.setRadius(100.f);
        shape.setPointCount(100);
        shape.setFillColor(Color::Blue);
        shape.setOutlineThickness(-4.f);
        shape.setOutlineColor(Color::Red);

        font.loadFromFile("assets/fonts/font1.ttf");
        text.setFont(font);
        text.setString("sexy");
        text.setCharacterSize(24);
        text.setFillColor(Color::Green);
    }

    void setPos(int x, int y)
    {
        shape.setPosition(x, y);
    }

    void setText(string text)
    {
    }

    void draw(RenderWindow &win)
    {
        win.draw(shape);
        win.draw(text);
    }
};

class LinkedListVisualizer
{
};

void foo()
{
    // DoublyLinkedCircularList<int> obj;
    // obj.append(10);
    // obj.append(20);
    // obj.append(30);
    // obj.append(40);

    RenderWindow window(VideoMode(1600, 900), "Linked List");

    NodeObject *circles = new NodeObject[20];

    for (int i = 0; i < 20; i++)
        circles[i].setPos(i * 100, i * 50);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::Black);

        for (int i = 0; i < 1; i++)
            circles[i].draw(window);

        window.display();
    }
}

#endif