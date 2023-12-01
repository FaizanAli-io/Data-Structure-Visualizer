#include "../Structures.h"
#include "../GraphicObjects.h"

#ifndef STACKQUEUE
#define STACKQUEUE

struct StackQueueVisualizer
{
    const float animationSpeed = 2.5;

    Font font;
    Clock clock;
    BoxObject **stack;
    BoxObject **queue;
    RenderWindow *window;
    Button *b1, *b2, *b3, *b4;
    int headS, headQ, tailQ, size;

    StackQueueVisualizer(RenderWindow *win) : window(win), headS(0), headQ(0), tailQ(0), size(10)
    {
        font.loadFromFile("assets/fonts/font2.ttf");

        stack = new BoxObject *[size];
        queue = new BoxObject *[size];
        for (int i = 0; i < size; i++)
        {
            stack[i] = nullptr;
            queue[i] = nullptr;
        }

        b1 = new Button(font);
        b1->setText("Push");
        b1->setPos(Vector2f(1200, 25));

        b2 = new Button(font);
        b2->setText("Pop");
        b2->setPos(Vector2f(1200, 250));

        b3 = new Button(font);
        b3->setText("Enqueue");
        b3->setPos(Vector2f(1200, 475));

        b4 = new Button(font);
        b4->setText("Dequeue");
        b4->setPos(Vector2f(1200, 700));
    }

    Vector2f getStackPosition(int x) { return Vector2f(75, 800 - 80 * x); }

    Vector2f getQueuePosition(int x) { return Vector2f(525, 800 - 80 * x); }

    void addStackViz(int data)
    {
        stack[headS] = new BoxObject(font);
        stack[headS]->setText(to_string(data));
        stack[headS]->setPos(getStackPosition(headS++));
    }

    void addQueueViz(int data)
    {
        queue[headQ] = new BoxObject(font);
        queue[headQ]->setText(to_string(data));
        queue[headQ]->setPos(getQueuePosition(headQ));
        headQ = (headQ + 1) % size;
    }

    void remStackViz()
    {
        delete stack[--headS];
        stack[headS] = nullptr;
    }

    void remQueueViz()
    {
        delete queue[tailQ];
        queue[tailQ] = nullptr;
        tailQ = (tailQ + 1) % size;
    }

    void buttonClicked(Vector2i mPos)
    {
        if (b1->isOverlap(mPos))
            addStackViz(rand() % 1000);
        else if (b2->isOverlap(mPos))
            remStackViz();
        else if (b3->isOverlap(mPos))
            addQueueViz(rand() % 1000);
        else if (b4->isOverlap(mPos))
            remQueueViz();
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
        for (int i = 0; i < size; i++)
        {
            if (stack[i] != nullptr)
                stack[i]->draw(window);
            if (queue[i] != nullptr)
                queue[i]->draw(window);
        }

        b1->draw(window);
        b2->draw(window);
        b3->draw(window);
        b4->draw(window);
    }
};

#endif