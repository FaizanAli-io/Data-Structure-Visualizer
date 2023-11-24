#include <SFML/Graphics.hpp>
#include "Structures.h"
using namespace sf;

#ifndef CLASS
#define CLASS

struct NodeObject
{
    Text text;
    CircleShape shape;

    NodeObject(Font &font)
    {
        float r = 100.f;
        shape.setRadius(r);
        shape.setOrigin(r, r);
        shape.setPointCount(100);
        shape.setFillColor(Color::Blue);
        shape.setOutlineThickness(-4.f);
        shape.setOutlineColor(Color::Red);

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

ostream &operator<<(ostream &out, NodeObject &obj)
{
    string s = obj.text.getString();
    return out << s;
}

struct LinkedListVisualizer
{
    Font font;
    LinkedList<NodeObject *> *nodes;

    LinkedListVisualizer()
    {
        font.loadFromFile("assets/fonts/font2.ttf");
        nodes = new LinkedList<NodeObject *>;
    }

    void add_node(int data)
    {
        NodeObject *obj = new NodeObject(font);
        int i = nodes->getLength();
        obj->setText(to_string(data));
        obj->setPos(i * 300 + 150, 150);
        nodes->append(obj);
    }

    void visualize(RenderWindow &win)
    {
        ListNode<NodeObject *> *cur = nodes->getHead();
        while (cur != nullptr)
        {
            cur->data->draw(win);
            cur = cur->next;
        }
    }
};

void foo()
{

    RenderWindow window(VideoMode(1600, 900), "Linked List");

    LinkedListVisualizer viz;

    for (int i = 0; i < 25; i++)
        viz.add_node((i + 1) * 10);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();

        window.clear(Color::Black);
        viz.visualize(window);
        window.display();
    }
}

#endif