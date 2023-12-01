#include "Dependencies/LinkMenu.cpp"
#include "Dependencies/Visualizers/LinkedListViz.h"
#include "Dependencies/Visualizers/LinkedStackViz.h"
#include "Dependencies/Visualizers/LinkedQueueViz.h"
#include "Dependencies/Visualizers/ArrayStackQueueViz.h"

void forLinkedList(int mode = 0)
{
    LinkedListVisualizer *visualizer;

    RenderWindow *window = new RenderWindow(VideoMode(1600, 900), "Linked List");

    if (mode == 0)
        visualizer = new LinkedListVisualizer(window);
    else if (mode == 1)
        visualizer = new LinkedStackVisualizer(window);
    else if (mode == 2)
        visualizer = new LinkedQueueVisualizer(window);

    visualizer->randomNodes(8);

    while (window->isOpen())
    {
        Vector2i worldPos = window->getPosition();
        worldPos.y += 30;

        Vector2i mousePos = Mouse::getPosition() - worldPos;
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
        Vector2i worldPos = window->getPosition();
        worldPos.y += 30;

        Vector2i mousePos = Mouse::getPosition() - worldPos;
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