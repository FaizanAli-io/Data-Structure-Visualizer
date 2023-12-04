#include "Dependencies/LinkMenu.cpp"
#include "Dependencies/Visualizers/LinkedListViz.h"
#include "Dependencies/Visualizers/LinkedStackViz.h"
#include "Dependencies/Visualizers/LinkedQueueViz.h"
#include "Dependencies/Visualizers/ArrayStackQueueViz.h"
#include "Dependencies/Visualizers/AutoBalanceTreeVIz.h"

Vector2i trueMousePos(RenderWindow *win)
{
    return Mouse::getPosition() - win->getPosition() - Vector2i(0, 30);
}

void forLinkedList(int mode = 0)
{
    RenderWindow *window = new RenderWindow(VideoMode(1600, 900), "Linked List");

    LinkedListVisualizer *visualizer;

    if (mode == 0)
        visualizer = new LinkedListVisualizer(window);
    else if (mode == 1)
        visualizer = new LinkedStackVisualizer(window);
    else if (mode == 2)
        visualizer = new LinkedQueueVisualizer(window);

    while (window->isOpen())
    {
        Vector2i mousePos = trueMousePos(window);
        visualizer->buttonHover(mousePos);

        Event event;
        while (window->pollEvent(event))
        {
            if (event.type == Event::Closed)
                window->close();

            else if (event.type == Event::MouseButtonPressed)
                visualizer->buttonClicked(mousePos);
        }

        window->clear(Color(0, 0, 0));
        visualizer->visualize();
        window->display();
    }
}

void forStackQueue()
{
    RenderWindow *window = new RenderWindow(VideoMode(1600, 900), "Stack Queue");

    StackQueueVisualizer *visualizer = new StackQueueVisualizer(window);

    while (window->isOpen())
    {
        Vector2i mousePos = trueMousePos(window);
        visualizer->buttonHover(mousePos);

        Event event;
        while (window->pollEvent(event))
        {
            if (event.type == Event::Closed)
                window->close();

            else if (event.type == Event::MouseButtonPressed)
                visualizer->buttonClicked(mousePos);
        }

        window->clear(Color(0, 0, 0));
        visualizer->visualize();
        window->display();
    }
}

void forTree()
{
    RenderWindow *window = new RenderWindow(VideoMode(1600, 900), "Stack Queue");

    AutoBalanceTreeVisualizer *visualizer = new AutoBalanceTreeVisualizer(window);

    while (window->isOpen())
    {
        Vector2i mousePos = trueMousePos(window);
        visualizer->buttonHover(mousePos);

        Event event;
        while (window->pollEvent(event))
        {
            if (event.type == Event::Closed)
                window->close();

            else if (event.type == Event::MouseButtonPressed)
                visualizer->buttonClicked(mousePos);
        }

        window->clear(Color(0, 0, 0));
        visualizer->visualize();
        window->display();
    }
}