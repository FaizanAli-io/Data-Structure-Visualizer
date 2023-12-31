#include "../Structures.h"
#include "../GraphicObjects.h"

#ifndef LINKEDLIST
#define LINKEDLIST

struct LinkedListVisualizer
{
    const float updateSpeed = 0.01;
    const float animationSpeed = 3;
    const Vector2f NullSpot = Vector2f(1100, 1100);

    Font font;
    Clock clock;
    int head, tail;
    RenderWindow *window;
    Button *b1, *b2, *b3, *b4;
    LinkedList<NodeObject *> *nodes;

    LinkedListVisualizer(RenderWindow *win, bool initializeRand = true) : window(win), tail(0), head(-1)
    {
        font.loadFromFile("assets/fonts/font2.ttf");
        nodes = new LinkedList<NodeObject *>;

        b1 = new Button(font);
        b1->setText("Append");
        b1->setPos(Vector2f(1200, 25));

        b2 = new Button(font);
        b2->setText("Prepend");
        b2->setPos(Vector2f(1200, 250));

        b3 = new Button(font);
        b3->setText("Pop Tail");
        b3->setPos(Vector2f(1200, 475));

        b4 = new Button(font);
        b4->setText("Pop Head");
        b4->setPos(Vector2f(1200, 700));

        if (initializeRand)
        {
            int n = rand() % 10;
            for (int i = 0; i < n; i++)
                append_node(rand() % 1000);
        }
    }

    Vector2f setPositionFromIndex(int i)
    {
        int row = i / 5;
        int col = i % 5;

        if (row % 2 == 0)
            return Vector2f(250 * col + 100, 250 * row + 100);
        else
            return Vector2f(-250 * col + 1100, 250 * row + 100);
    }

    NodeObject *append_node(int data)
    {
        NodeObject *obj = new NodeObject(font);

        obj->setData(data);
        obj->setPos(setPositionFromIndex(tail++));
        obj->setArrow(NullSpot, 1);

        if (!nodes->isEmpty())
        {
            NodeObject *lastNode = nodes->getTail()->data;
            if (lastNode != nullptr)
                lastNode->setArrow(obj->shape.getPosition(), 1);
        }

        nodes->append(obj);
        return obj;
    }

    NodeObject *prepend_node(int data)
    {
        NodeObject *obj = new NodeObject(font);

        obj->setData(data);
        obj->setPos(setPositionFromIndex(head--));
        obj->setArrow(nodes->getHead()->data->shape.getPosition(), 1);

        nodes->prepend(obj);
        return obj;
    }

    void animation(NodeObject *obj, bool fadein)
    {
        int i = fadein ? 0 : 255;
        while ((fadein && i < 255) || (!fadein && i > 0))
        {
            Event event;
            while (window->pollEvent(event))
                if (event.type == Event::Closed)
                    window->close();

            if (clock.getElapsedTime() >= seconds(updateSpeed))
            {
                i += animationSpeed * (fadein ? 1 : -1);
                clock.restart();
                obj->setAllAlpha(i);
            }

            window->clear();
            visualize();
            window->display();
        }
    }

    void append_node_viz(int data)
    {
        NodeObject *obj = append_node(data);
        animation(obj, true);
    }

    void prepend_node_viz(int data)
    {
        NodeObject *obj = prepend_node(data);
        animation(obj, true);
    }

    void del_tail_viz()
    {
        NodeObject *obj = nodes->getTail()->data;
        animation(obj, false);

        tail--;
        nodes->removeTail();
        obj = nodes->getTail()->data;
        obj->setArrow(NullSpot, 1);
    }

    void del_head_viz()
    {
        NodeObject *obj = nodes->getHead()->data;
        animation(obj, false);

        head++;
        nodes->removeHead();
    }

    virtual void buttonClicked(Vector2i mPos)
    {
        if (b1->isOverlap(mPos))
            append_node_viz(rand() % 500);

        else if (b2->isOverlap(mPos))
            prepend_node_viz(rand() % 500);

        else if (b3->isOverlap(mPos))
            del_tail_viz();

        else if (b4->isOverlap(mPos))
            del_head_viz();
    }

    void buttonHover(Vector2i mPos)
    {
        b1->setNormalColor();
        b2->setNormalColor();
        b3->setNormalColor();
        b4->setNormalColor();

        if (b1->isOverlap(mPos))
            b1->setHoverColor();

        else if (b2->isOverlap(mPos))
            b2->setHoverColor();

        else if (b3->isOverlap(mPos))
            b3->setHoverColor();

        else if (b4->isOverlap(mPos))
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

#endif