#include "LinkedListViz.h"

#ifndef LINKEDQUEUE
#define LINKEDQUEUE

struct LinkedQueueVisualizer : public LinkedListVisualizer
{
    LinkedQueueVisualizer(RenderWindow *win) : LinkedListVisualizer(win)
    {
        b3->setText("Enqueue");
        b4->setText("Dequeue");
        b1->disableButton();
        b2->disableButton();
    }

    void buttonClicked(Vector2i mPos)
    {
        if (b3->isOverlap(mPos))
            append_node_viz(rand() % 500 - 500);

        else if (b4->isOverlap(mPos))
            del_head_viz();
    }
};

#endif