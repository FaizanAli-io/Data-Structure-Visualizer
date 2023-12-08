#include "LinkedListViz.h"

#ifndef LINKEDQUEUE
#define LINKEDQUEUE

struct LinkedQueueVisualizer : public LinkedListVisualizer
{
    const int animationFrames = 50;

    LinkedQueueVisualizer(RenderWindow *win) : LinkedListVisualizer(win, false)
    {
        b1->enabled = false;
        b2->enabled = false;
        b3->setText("Enqueue");
        b4->setText("Dequeue");
    }

    void buttonClicked(Vector2i mPos)
    {
        if (b3->isOverlap(mPos))
            enqueue_viz(rand() % 500);

        else if (b4->isOverlap(mPos))
            del_head_viz();

        setNewPositions();
    }

    void enqueue_viz(int data)
    {
        NodeObject *obj = new NodeObject(font);

        obj->setData(data);
        obj->setPos(setPositionFromIndex(-1));
        nodes->appendPriority(obj);
    }

    void movementLoop()
    {
        int i = 0;
        while (i < animationFrames)
        {
            Event event;
            while (window->pollEvent(event))
                if (event.type == Event::Closed)
                    window->close();

            ListNode<NodeObject *> *cur;
            if (clock.getElapsedTime() >= seconds(updateSpeed))
            {
                cur = nodes->getHead();
                while (cur != nullptr)
                {
                    cur->data->moveBody();
                    cur = cur->next;
                }

                clock.restart();
                i++;
            }

            window->clear();
            visualize();
            window->display();
        }

        finalizePosition();
    }

    void finalizePosition()
    {
        ListNode<NodeObject *> *cur = nodes->getHead();
        while (cur != nullptr)
        {
            cur->data->setPos(cur->data->nextPos);

            if (cur->next != nullptr)
            {
                Vector2f nextNodePos = cur->next->data->shape.getPosition();
                cur->data->setArrow(nextNodePos, 1);
            }

            cur = cur->next;
        }
    }

    void setNewPositions()
    {
        ListNode<NodeObject *> *cur = nodes->getHead();
        for (int i = 0; cur != nullptr; cur = cur->next, i++)
        {
            Vector2f newPos = setPositionFromIndex(i);
            cur->data->setNextPos(newPos, animationFrames);
        }

        movementLoop();
    }
};

#endif