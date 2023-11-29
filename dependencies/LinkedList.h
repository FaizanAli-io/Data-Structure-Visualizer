#include <SFML/Graphics.hpp>
using namespace sf;

#include "Structures.h"
#include "GraphicObjects.h"

#ifndef LINKEDLIST
#define LINKEDLIST

struct LinkedListVisualizer
{
    Font font;
    Clock clock;
    RenderWindow *window;
    Button *b1, *b2, *b3, *b4;
    LinkedList<NodeObject *> *nodes;

    LinkedListVisualizer(RenderWindow *win)
    {
        font.loadFromFile("assets/fonts/font2.ttf");
        nodes = new LinkedList<NodeObject *>;
        window = win;

        b1 = new Button(font);
        b1->setText("Append");
        b1->setPos(1200, 25);

        b2 = new Button(font);
        b2->setText("Prepend");
        b2->setPos(1200, 250);

        b3 = new Button(font);
        b3->setText("Pop Tail");
        b3->setPos(1200, 475);

        b4 = new Button(font);
        b4->setText("Pop Head");
        b4->setPos(1200, 700);
    }

    void randomNodes(int n, int m = 1000)
    {
        for (int i = 0; i < n; i++)
            append_node(rand() % m);
    }

    NodeObject *append_node(int data)
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

        if (!nodes->isEmpty())
        {
            NodeObject *lastNode = nodes->getTail()->data;
            if (lastNode != nullptr)
                lastNode->setArrow(obj->shape.getPosition());
        }
        obj->setArrow(Vector2f(1100, 1100));

        nodes->append(obj);
        return obj;
    }

    NodeObject *prepend_node(int data)
    {
        NodeObject *next = nodes->getHead()->data;
        NodeObject *obj = new NodeObject(font);
        obj->setText(to_string(data));

        Vector2f nextPos = next->shape.getPosition();

        int row = (nextPos.y - 100) / 250;
        int colPos = (row % 2 == 0)
                         ? nextPos.x - 250
                         : nextPos.x + 250;
        obj->setPos(colPos, nextPos.y);
        obj->setArrow(nextPos);

        nodes->prepend(obj);
        return obj;
    }

    void append_node_viz(int data)
    {
        NodeObject *obj = append_node(data);

        int i = 0;
        while (i < 255)
        {
            if (clock.getElapsedTime() >= seconds(0.01))
            {
                i++;
                clock.restart();
                obj->setAllAlpha(i);
            }

            window->clear();
            visualize();
            window->display();
        }
    }

    void prepend_node_viz(int data)
    {
        NodeObject *obj = prepend_node(data);

        int i = 0;
        while (i < 255)
        {
            if (clock.getElapsedTime() >= seconds(0.01))
            {
                i++;
                clock.restart();
                obj->setAllAlpha(i);
            }

            window->clear();
            visualize();
            window->display();
        }
    }

    void del_tail_viz()
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

            window->clear();
            visualize();
            window->display();
        }

        nodes->removeTail();
        obj = nodes->getTail()->data;
        obj->setArrow(Vector2f(1100, 1100));
    }

    void del_head_viz()
    {
        NodeObject *obj = nodes->getHead()->data;

        int i = 255;
        while (i >= 0)
        {
            if (clock.getElapsedTime() >= seconds(0.01))
            {
                i--;
                clock.restart();
                obj->setAllAlpha(i);
            }

            window->clear();
            visualize();
            window->display();
        }

        nodes->removeHead();
    }

    void buttonClicked(int x, int y)
    {
        if (b1->isOverlap(x, y))
            append_node_viz(rand() % 500 - 500);

        else if (b2->isOverlap(x, y))
            prepend_node_viz(rand() % 500 - 500);

        else if (b3->isOverlap(x, y))
            del_tail_viz();

        else if (b4->isOverlap(x, y))
            del_head_viz();
    }

    void buttonHover(int x, int y)
    {
        b1->setNormalColor();
        b2->setNormalColor();
        b3->setNormalColor();
        b4->setNormalColor();

        if (b1->isOverlap(x, y))
            b1->setHoverColor();

        else if (b2->isOverlap(x, y))
            b2->setHoverColor();

        else if (b3->isOverlap(x, y))
            b3->setHoverColor();

        else if (b4->isOverlap(x, y))
            b4->setHoverColor();
    }

    void visualize()
    {
        ListNode<NodeObject *> *cur = nodes->getHead();
        while (cur != nullptr)
        {
            cur->data->draw(window);
            cur = cur->next;
        }

        b1->draw(window);
        b2->draw(window);
        b3->draw(window);
        b4->draw(window);
    }
};

void foo()
{

    RenderWindow *window = new RenderWindow(VideoMode(1600, 900), "Linked List");

    LinkedListVisualizer *visualizer = new LinkedListVisualizer(window);

    visualizer->randomNodes(12);

    while (window->isOpen())
    {
        Vector2i worldPos = window->getPosition();
        worldPos.y += 30;

        Vector2i pos = Mouse::getPosition() - worldPos;
        visualizer->buttonHover(pos.x, pos.y);

        Event event;
        while (window->pollEvent(event))
        {
            if (event.type == Event::Closed)
                window->close();

            else if (event.type == Event::MouseButtonPressed)
                visualizer->buttonClicked(pos.x, pos.y);
        }

        window->clear(Color(0, 0, 0));
        visualizer->visualize();
        window->display();
    }
}

#endif