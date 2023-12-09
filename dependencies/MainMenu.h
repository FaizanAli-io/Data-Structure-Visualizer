#include "Visualizers.h"

#ifndef MAINMENU
#define MAINMENU

class MainMenu
{
    int pos;
    int len;

    Font font;
    Texture image;
    Sprite background;
    vector<Text> texts;
    RenderWindow *window;
    vector<string> options;
    Visualizers *allVisualizers;

public:
    MainMenu()
    {
        window = new RenderWindow(VideoMode(1600, 900), "Data Structure Visualizer", Style::Titlebar | Style::Close);

        allVisualizers = new Visualizers(window);

        options = {
            "Data Structure Visualizer",
            "Linked List",
            "Linked Stack",
            "Priority Queue",
            "Array Stack Queue",
            "Balanced Tree",
            "Min Max Heap",
            "Quit Program",
        };

        image.loadFromFile("assets/images/background.jpg");
        font.loadFromFile("assets/fonts/font3.ttf");
        background.setTexture(image);

        pos = 1;
        len = options.size();
        texts.resize(len);

        for (int i = 0; i < len; ++i)
        {
            texts[i].setFont(font);
            texts[i].setString(options[i]);
            texts[i].setFillColor(Color::Red);

            if (i == 0)
            {
                texts[i].setCharacterSize(120);
                texts[i].setOutlineThickness(4);
                texts[i].setPosition(Vector2f(40, 40));
                texts[i].setOutlineColor(Color::Magenta);
            }

            else
            {
                texts[i].setCharacterSize(60);
                texts[i].setOutlineColor(Color::Blue);

                if (i <= len / 2)
                    texts[i].setPosition(Vector2f(120, 120 + i * 120));
                else
                    texts[i].setPosition(Vector2f(920, 120 + (i - len / 2) * 120));
            }
        }

        texts[pos].setOutlineThickness(4);
    }

    void run()
    {
        while (window->isOpen())
        {
            Event event;
            while (window->pollEvent(event))
            {
                if (event.type == Event::Closed | Keyboard::isKeyPressed(Keyboard::Escape))
                    window->close();

                if (Keyboard::isKeyPressed(Keyboard::Down))
                {
                    texts[pos].setOutlineThickness(0);
                    pos = (++pos >= len) ? 1 : pos;
                    texts[pos].setOutlineThickness(4);
                }

                if (Keyboard::isKeyPressed(Keyboard::Up))
                {
                    texts[pos].setOutlineThickness(0);
                    pos = (--pos <= 0) ? len - 1 : pos;
                    texts[pos].setOutlineThickness(4);
                }

                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    if (pos == 7)
                        window->close();
                    else
                        allVisualizers->showStructure(pos - 1);
                }
            }

            window->clear(Color(0, 0, 0));
            window->draw(background);
            for (int i = 0; i < len; ++i)
                window->draw(texts[i]);
            window->display();
        }
    }
};

#endif
