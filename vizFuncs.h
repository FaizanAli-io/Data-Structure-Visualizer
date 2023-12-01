#include "Dependencies/LinkMenu.cpp"
#include "Dependencies/Visualizers/LinkedListViz.h"
#include "Dependencies/Visualizers/LinkedStackViz.h"
#include "Dependencies/Visualizers/LinkedQueueViz.h"

void forLinkedList()
{
    RenderWindow *window = new RenderWindow(VideoMode(1600, 900), "Linked List");

    LinkedListVisualizer *visualizer = new LinkedListVisualizer(window);

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

void forLinkedStack()
{
    RenderWindow *window = new RenderWindow(VideoMode(1600, 900), "Linked List");

    LinkedStackVisualizer *visualizer = new LinkedStackVisualizer(window);

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

void forLinkedQueue()
{
    RenderWindow *window = new RenderWindow(VideoMode(1600, 900), "Linked List");

    LinkedQueueVisualizer *visualizer = new LinkedQueueVisualizer(window);

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