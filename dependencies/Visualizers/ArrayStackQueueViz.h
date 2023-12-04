#include "../Structures.h"
#include "../GraphicObjects.h"

#ifndef STACKQUEUE
#define STACKQUEUE

struct StackQueueVisualizer
{
    const float updateSpeed = 0.01;
    const float animationSpeed = 5;

    Font font;
    Clock clock;
    BoxObject **stack;
    BoxObject **queue;
    RenderWindow *window;
    Button *b1, *b2, *b3, *b4;
    Label *headLabelS, *headLabelQ, *tailLabelQ;
    int headS, headQ, tailQ, size;

    Vector2f getStackPosition() { return Vector2f(50, 800 - 80 * headS); }

    Vector2f getQueuePosition(int x) { return Vector2f(600, 800 - 80 * x); }

    StackQueueVisualizer(RenderWindow *win) : window(win), headS(0), headQ(0), tailQ(0), size(8)
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

        headLabelS = new Label(font, "Stack Head");
        headLabelQ = new Label(font, "Queue Head");
        tailLabelQ = new Label(font, "Queue Tail");

        setLabels();
    }

    void setLabels()
    {
        Vector2f src = getStackPosition() + Vector2f(150, -60);
        Vector2f dst = src + Vector2f(0, 100);
        Vector2f offset = Vector2f(0, -30);
        headLabelS->set(src, dst, offset);

        src = getQueuePosition(headQ) + Vector2f(-200, 40);
        dst = src + Vector2f(150, 0);
        offset = Vector2f(60, -60);
        headLabelQ->set(src, dst, offset);

        src = getQueuePosition(tailQ) + Vector2f(500, 40);
        dst = src + Vector2f(-150, 0);
        offset = Vector2f(-60, -60);
        tailLabelQ->set(src, dst, offset);
    }

    void animation(BoxObject *obj, bool fadein)
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

    void addStackViz(int data)
    {
        if (headS >= size)
            return;

        stack[headS] = new BoxObject(font);
        stack[headS]->setText(to_string(data));
        stack[headS]->setPos(getStackPosition());
        animation(stack[headS], true);
        headS++;
    }

    void addQueueViz(int data)
    {
        if (headQ == tailQ && queue[headQ] != nullptr)
            return;

        queue[headQ] = new BoxObject(font);
        queue[headQ]->setText(to_string(data));
        queue[headQ]->setPos(getQueuePosition(headQ));
        animation(queue[headQ], true);
        headQ = (headQ + 1) % size;
    }

    void remStackViz()
    {
        if (headS <= 0)
            return;

        animation(stack[--headS], false);
        delete stack[headS];
        stack[headS] = nullptr;
    }

    void remQueueViz()
    {
        if (headQ == tailQ && queue[tailQ] == nullptr)
            return;

        animation(queue[tailQ], false);
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
        setLabels();
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

        headLabelS->draw(window);
        headLabelQ->draw(window);
        tailLabelQ->draw(window);
    }
};

#endif