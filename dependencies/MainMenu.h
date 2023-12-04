#include <SFML/Graphics.hpp>
using namespace sf;

#include <iostream>
using namespace std;

class Menu
{
  int pos;
  int len;

  Font font;
  Texture image;
  Sprite background;
  vector<Text> texts;
  RenderWindow *window;
  vector<string> options;

public:
  Menu()
  {
    window = new RenderWindow(VideoMode(1600, 900), "Data Structure Visualizer", Style::Titlebar | Style::Close);
    options = {"Data Structure Visualizer", "Linked List ", "Stack Queue", "AVL Tree", "Heap", "Quit"};
    image.loadFromFile("assets/images/background.jpg");
    font.loadFromFile("assets/fonts/font3.ttf");
    background.setTexture(image);

    pos = 0;
    len = 6;
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
        texts[i].setCharacterSize(50);
        texts[i].setOutlineColor(Color::Blue);
        texts[i].setPosition(Vector2f(180, 120 + i * 120));
      }
    }
  }

  void run_menu()
  {
    while (window->isOpen())
    {
      Event event;
      while (window->pollEvent(event))
      {
        if (event.type == Event::Closed)
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
          if (pos == 1)
            cout << pos << endl;
          else if (pos == 2)
            cout << pos << endl;
          else if (pos == 3)
            cout << pos << endl;
          else if (pos == 4)
            cout << pos << endl;
          else if (pos == 5)
            window->close();
        }
      }

      window->clear();
      window->draw(background);
      for (int i = 0; i < len; ++i)
        window->draw(texts[i]);
      window->display();
    }
  }
};

void runfoo()
{
  Menu *menu = new Menu();
  menu->run_menu();
}
