#include "LinkedListViz.h"

#ifndef LINKEDSTACK
#define LINKEDSTACK

struct LinkedStackVisualizer : public LinkedListVisualizer
{
    LinkedStackVisualizer(RenderWindow *win) : LinkedListVisualizer(win)
    {
        b1->setText("Push");
        b2->setText("Pop");
        b3->disableButton();
        b4->disableButton();
    }

    void buttonClicked(Vector2i mPos)
    {
        if (b1->isOverlap(mPos))
            append_node_viz(rand() % 500 - 500);

        else if (b2->isOverlap(mPos))
            del_tail_viz();
    }
};

#endif