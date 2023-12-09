#include "Visualizers/LinkedListViz.h"
#include "Visualizers/LinkedStackViz.h"
#include "Visualizers/LinkedQueueViz.h"
#include "Visualizers/ArrayStackQueueViz.h"
#include "Visualizers/AutoBalanceTreeViz.h"

Vector2i trueMousePos(RenderWindow *win)
{
    return Mouse::getPosition() - win->getPosition() - Vector2i(0, 30);
}

struct Visualizers
{
    RenderWindow *window;
    LinkedListVisualizer *linkedlist;
    LinkedStackVisualizer *linkedstack;
    LinkedQueueVisualizer *linkedqueue;
    StackQueueVisualizer *stackqueue;
    AutoBalanceTreeVisualizer *balancetree;

    Visualizers(RenderWindow *window)
    {
        this->window = window;
        linkedlist = new LinkedListVisualizer(window);
        linkedstack = new LinkedStackVisualizer(window);
        linkedqueue = new LinkedQueueVisualizer(window);
        stackqueue = new StackQueueVisualizer(window);
        balancetree = new AutoBalanceTreeVisualizer(window);
    }

    void buttonHover(int mode, Vector2i pos)
    {
        switch (mode)
        {
        case 0:
            linkedlist->buttonHover(pos);
            break;
        case 1:
            linkedstack->buttonHover(pos);
            break;
        case 2:
            linkedqueue->buttonHover(pos);
            break;
        case 3:
            stackqueue->buttonHover(pos);
            break;
        case 4:
            balancetree->buttonHover(pos);
            break;
        case 5:
            cout << "HEAP" << endl;
            break;
        default:
            break;
        }
    }

    void buttonClick(int mode, Vector2i pos)
    {
        switch (mode)
        {
        case 0:
            linkedlist->buttonClicked(pos);
            break;
        case 1:
            linkedstack->buttonClicked(pos);
            break;
        case 2:
            linkedqueue->buttonClicked(pos);
            break;
        case 3:
            stackqueue->buttonClicked(pos);
            break;
        case 4:
            balancetree->buttonClicked(pos);
            break;
        case 5:
            cout << "HEAP" << endl;
            break;
        default:
            break;
        }
    }

    void displayVisualizer(int mode)
    {
        switch (mode)
        {
        case 0:
            linkedlist->visualize();
            break;
        case 1:
            linkedstack->visualize();
            break;
        case 2:
            linkedqueue->visualize();
            break;
        case 3:
            stackqueue->visualize();
            break;
        case 4:
            balancetree->visualize();
            break;
        case 5:
            cout << "HEAP" << endl;
            break;
        default:
            break;
        }
    }

    void showStructure(int mode)
    {
        while (window->isOpen())
        {
            Vector2i mousePos = trueMousePos(window);
            this->buttonHover(mode, mousePos);

            Event event;
            while (window->pollEvent(event))
            {
                if (event.type == Event::Closed | Keyboard::isKeyPressed(Keyboard::BackSpace))
                    return;

                else if (event.type == Event::MouseButtonPressed)
                    this->buttonClick(mode, mousePos);
            }

            window->clear(Color(0, 0, 0));
            this->displayVisualizer(mode);
            window->display();
        }
    }
};