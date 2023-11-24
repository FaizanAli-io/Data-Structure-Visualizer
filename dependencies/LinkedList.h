#include <SFML/Graphics.hpp>
#include "Structures.h"
using namespace sf;

#ifndef CLASS
#define CLASS

struct NodeObject
{
    Text text;
    Font font;
    CircleShape shape;

    NodeObject()
    {
        float r = 100.f;
        shape.setRadius(r);
        shape.setOrigin(r, r);
        shape.setPointCount(100);
        shape.setFillColor(Color::Blue);
        shape.setOutlineThickness(-4.f);
        shape.setOutlineColor(Color::Red);

        font.loadFromFile("assets/fonts/font2.ttf");

        text.setFont(font);
        text.setCharacterSize(72);
        text.setFillColor(Color::Magenta);
    }

    void setText(string value)
    {
        text.setString(value);
    }

    void setPos(int x, int y)
    {
        Vector2f textSize = text.getGlobalBounds().getSize();
        text.setOrigin(textSize.x * 0.5, textSize.y * 0.75);
        shape.setPosition(x, y);
        text.setPosition(x, y);
    }

    void draw(RenderWindow &win)
    {
        win.draw(shape);
        win.draw(text);
    }
};

struct LinkedListVisualizer
{
    DoublyLinkedCircularList<NodeObject> nodes;

    void add_node(int data)
    {
        nodes.print();
        int i = nodes.getLength();
        cout << i << endl;

        NodeObject obj;
        obj.setText(to_string(data));
        obj.setPos(i * 200 + 100, 100);

        nodes.append(obj);
    }

    void visualize(RenderWindow &win)
    {
        if (!nodes.isEmpty())
        {
            cout << "here 1\n";
            ListNode<NodeObject> *cur = nodes.getHead();
            do
            {
                cout << "here 2\n";
                cur->data.draw(win);
                cur = cur->next;
            } while (cur != nodes.getHead());
        }
    }
};

void foo()
{

    RenderWindow window(VideoMode(1600, 900), "Linked List");

    LinkedListVisualizer viz;

    for (int i = 0; i < 25; i++)
    {
        cout << "here " << i << "\n";
        viz.add_node(i * 10);
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::Black);
        viz.visualize(window);
        window.display();
    }
}

#endif