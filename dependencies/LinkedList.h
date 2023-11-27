#include <SFML/Graphics.hpp>
using namespace sf;

#include "Structures.h"
#include "Utilities.h"

#ifndef CLASS
#define CLASS

struct Arrow
{
    RectangleShape line;
    CircleShape triangle;

    Arrow()
    {
        float r = 30.f;
        triangle.setRadius(r);
        triangle.setOrigin(r, r);
        triangle.setPointCount(3);
        triangle.setOutlineThickness(-3.f);

        line.setFillColor(Color(0, 255, 0));
        triangle.setFillColor(Color(0, 255, 0));
        triangle.setOutlineColor(Color(255, 255, 0));
    }

    void set(Vector2f beg, Vector2f end)
    {
        Vector2f dirVector = (end - beg) * 0.6f;
        float arrowLength = magnitude(dirVector.x, dirVector.y);
        int angleBetween = angleInDegrees(dirVector.x, dirVector.y);

        line.setPosition(beg);
        triangle.setPosition(beg + dirVector);
        line.setSize(Vector2f(arrowLength, 6.f));

        line.setRotation(angleBetween);
        triangle.setRotation(angleBetween + 90);
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
        float r = 80.f;
        shape.setRadius(r);
        shape.setOrigin(r, r);
        shape.setPointCount(100);
        shape.setOutlineThickness(-4.f);
        shape.setFillColor(Color(0, 0, 255));
        shape.setOutlineColor(Color(255, 0, 0));

        text.setFont(font);
        text.setCharacterSize(72);
        text.setFillColor(Color(255, 0, 255));
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

    void setAllAlpha(int i)
    {
        Color col = shape.getFillColor();
        col.a = i;
        shape.setFillColor(col);

        col = shape.getOutlineColor();
        col.a = i;
        shape.setOutlineColor(col);

        col = text.getFillColor();
        col.a = i;
        text.setFillColor(col);
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
    Clock clock;
    NodeObject *lastNode;
    LinkedList<NodeObject *> *nodes;

    LinkedListVisualizer()
    {
        font.loadFromFile("assets/fonts/font2.ttf");
        nodes = new LinkedList<NodeObject *>;
        lastNode = nullptr;
    }

    NodeObject *add_node(int data)
    {
        NodeObject *obj = new NodeObject(font);
        obj->setText(to_string(data));
        int i = nodes->getLength();
        int row = i / 5;
        int col = i % 5;

        if (row % 2 == 0)
            obj->setPos(250 * col + 100, 250 * row + 100);
        else
            obj->setPos(-250 * col + 1100, 250 * row + 100);

        if (lastNode != nullptr)
            lastNode->setArrow(obj->shape.getPosition());
        obj->setArrow(Vector2f(1100, 1100));

        nodes->append(obj);
        lastNode = obj;
        return obj;
    }

    void add_node_viz(int data, RenderWindow &win)
    {
        NodeObject *obj = add_node(data);

        int i = 0;
        while (i < 255)
        {
            if (clock.getElapsedTime() >= seconds(0.01))
            {
                i++;
                clock.restart();
                obj->setAllAlpha(i);
            }

            win.clear();
            visualize(win);
            win.display();
        }
    }

    void del_tail_viz(RenderWindow &win)
    {
        NodeObject *obj = nodes->getTail()->data;

        int i = 255;
        while (i >= 0)
        {
            if (clock.getElapsedTime() >= seconds(0.01))
            {
                i--;
                clock.restart();
                obj->setAllAlpha(i);
            }

            win.clear();
            visualize(win);
            win.display();
        }

        nodes->removeTail();
        obj = nodes->getTail()->data;
        obj->setArrow(Vector2f(1100, 1100));
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

    for (int i = 0; i < 12; i++)
        viz.add_node(rand() % 1000);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;

            case Event::KeyPressed:
                if (Keyboard::isKeyPressed(Keyboard::Return))
                    viz.add_node_viz(rand() % 1000, window);
                if (Keyboard::isKeyPressed(Keyboard::BackSpace))
                    viz.del_tail_viz(window);
                break;

            default:
                break;
            }
        }

        window.clear(Color(0, 0, 0));
        viz.visualize(window);
        window.display();
    }
}

#endif