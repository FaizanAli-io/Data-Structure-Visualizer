#include <SFML/Graphics.hpp>
#include <memory>
using namespace sf;

#include "Structures.h"
#include "Utilities.h"

#ifndef CLASS
#define CLASS

struct Arrow
{
    RectangleShape line;
    CircleShape triangle;

    void set(Vector2f beg, Vector2f end)
    {
        Vector2f dirVector = (end - beg) * 0.6f;
        int angleBetween = angleInDegrees(dirVector.x, dirVector.y);
        float arrowLength = magnitude(dirVector.x, dirVector.y);

        line.setPosition(beg);
        line.setFillColor(Color::Green);
        line.setSize(Vector2f(arrowLength, 8.f));

        float r = 40.f;
        triangle.setRadius(r);
        triangle.setOrigin(r, r);
        triangle.setPointCount(3);
        triangle.setOutlineThickness(-4.f);
        triangle.setFillColor(Color::Green);
        triangle.setOutlineColor(Color::Yellow);
        triangle.setPosition(beg + dirVector);

        line.rotate(angleBetween);
        triangle.rotate(angleBetween + 90);
    }

    void draw(RenderWindow &win)
    {
        win.draw(line);
        win.draw(triangle);
    }
};

struct NodeObject
{
    Text text;
    Arrow pointer;
    CircleShape shape;

    NodeObject(Font &font)
    {
        float r = 100.f;
        shape.setRadius(r);
        shape.setOrigin(r, r);
        shape.setPointCount(100);
        shape.setOutlineThickness(-4.f);
        shape.setFillColor(Color::Blue);
        shape.setOutlineColor(Color::Red);

        text.setFont(font);
        text.setCharacterSize(72);
        text.setFillColor(Color::Magenta);
    }

    void setText(string value)
    {
        text.setString(value);

        Vector2f textSize = text.getGlobalBounds().getSize();
        text.setOrigin(textSize.x * 0.5, textSize.y * 0.75);
    }

    void setPos(int x, int y)
    {
        shape.setPosition(x, y);
        text.setPosition(x, y);
    }

    void setArrow(Vector2f dst)
    {
        Vector2f src = shape.getPosition();
        pointer.set(src, dst);
    }

    void draw(RenderWindow &win)
    {
        pointer.draw(win);
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
    NodeObject *lastNode;
    LinkedList<NodeObject *> *nodes;

    LinkedListVisualizer()
    {
        font.loadFromFile("assets/fonts/font2.ttf");
        nodes = new LinkedList<NodeObject *>;
        lastNode = nullptr;
    }

    void add_node(int data)
    {
        NodeObject *obj = new NodeObject(font);
        int i = nodes->getLength();
        obj->setText(to_string(data));

        int row = i / 5;
        int col = i % 5;

        if (row % 2 == 0)
            obj->setPos(325 * col + 150, 300 * row + 150);
        else
            obj->setPos(-325 * col + 1450, 300 * row + 150);

        if (lastNode != nullptr)
            lastNode->setArrow(obj->shape.getPosition());

        nodes->append(obj);
        lastNode = obj;
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

    for (int i = 0; i < 15; i++)
        viz.add_node(i * i * 10);

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