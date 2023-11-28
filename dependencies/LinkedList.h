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
    NodeObject *lastNode;
    Button *b1, *b2, *b3, *b4;
    LinkedList<NodeObject *> *nodes;

    LinkedListVisualizer(RenderWindow *win)
    {
        font.loadFromFile("assets/fonts/font2.ttf");
        nodes = new LinkedList<NodeObject *>;
        lastNode = nullptr;
        window = win;

        b1 = new Button(font);
        b1->setText("Append");
        b1->setPos(1400, 100);

        b2 = new Button(font);
        b2->setText("Prepend");
        b2->setPos(1400, 325);

        b3 = new Button(font);
        b3->setText("Pop Tail");
        b3->setPos(1400, 550);

        b4 = new Button(font);
        b4->setText("Pop Head");
        b4->setPos(1400, 775);
    }

    void randomNodes(int n, int m = 1000)
    {
        for (int i = 0; i < n; i++)
            add_node(rand() % m);
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

    void add_node_viz(int data)
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
        lastNode = obj;
    }

    void buttonClicked(int x, int y)
    {
        if (b1->isOverlap(x, y))
            add_node_viz(rand() % 500 - 500);

        else if (b2->isOverlap(x, y))
            cout << "B2 Pressed" << endl;

        else if (b3->isOverlap(x, y))
            del_tail_viz();

        else if (b4->isOverlap(x, y))
            cout << "B4 Pressed" << endl;
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
        Event event;
        while (window->pollEvent(event))
        {
            if (event.type == Event::Closed)
                window->close();

            else if (event.type == Event::MouseButtonPressed)
            {
                Vector2i pos = Mouse::getPosition();
                visualizer->buttonClicked(pos.x, pos.y);
            }
        }

        window->clear(Color(0, 0, 0));
        visualizer->visualize();
        window->display();
    }
}

#endif