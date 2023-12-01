#include "menu.hpp"
#include "LinkedList.h"
Menu::Menu(){
  window = new sf::RenderWindow();
  winclose = new sf::RectangleShape();
  font = new sf::Font();
  image = new sf::Texture();
  bg = new sf::Sprite();

  set_values();
}



void Menu::set_values(){
  window->create(sf::VideoMode(1280,720), "Data Structure Visualizer ", sf::Style::Titlebar | sf::Style::Close);
  window->setPosition(sf::Vector2i(0,0));

  pos = 0;
  pressed = theselect = false;
  font->loadFromFile("assets/fonts/font1.ttf");
  image->loadFromFile("assets/fonts/hmm.jpg");

  bg->setTexture(*image);

  pos_mouse = {0,0};
  mouse_coord = {0, 0};

  options = {"Data Structure Visualizer", "Linked List ", "Stack_Queue", "AVL","Heap","Quit"};
  texts.resize(6);
  coords = {{590,40},{610,191},{590,282},{600,370},{623,457},{660,550}};//cordinates of texts(calculated via getpos)
  sizes = {40,45,44,44,43,46};//Set your size of text

  for (std::size_t i{}; i < texts.size(); ++i){
   texts[i].setFont(*font); 
   texts[i].setString(options[i]); 
   texts[i].setCharacterSize(sizes[i]);
   texts[i].setOutlineColor(sf::Color::Blue);
   texts[i].setPosition(coords[i]);
   texts[i].setFillColor(sf::Color::Red);
  }
  texts[1].setOutlineThickness(4);
  pos = 1;

  winclose->setSize(sf::Vector2f(23,26));
  winclose->setPosition(1178,39);
  winclose->setFillColor(sf::Color::Transparent);

}

void Menu::loop_events(){
  sf::Event event;
  while(window->pollEvent(event)){
    if( event.type == sf::Event::Closed){
      window->close();
    }

    pos_mouse = sf::Mouse::getPosition(*window);
    mouse_coord = window->mapPixelToCoords(pos_mouse);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed){
      if( pos < 5){
        ++pos;
        pressed = true;
        texts[pos].setOutlineThickness(4);
        texts[pos - 1].setOutlineThickness(0);
        pressed = false;
        theselect = false;
      }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed){
      if( pos > 1){
        --pos;
        pressed = true;
        texts[pos].setOutlineThickness(4);
        texts[pos + 1].setOutlineThickness(0);
        pressed = false;
        theselect = false;
      }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect){
      theselect = true;
       if( pos == 5){
        window->close();
        }
      
       else if(pos == 1)
        {
           foo();
        }
        else if (pos==2)
        {
          //different functions; for stack
        }
        else if (pos==3)
        {

        }
      
      
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
      if(winclose->getGlobalBounds().contains(mouse_coord)){
        //std::cout << "Close the window!" << '\n';
        window->close();
      }
    }
  }
}

void Menu::draw_all(){
  window->clear();
  window->draw(*bg);
  for(auto t : texts){
   window->draw(t); 
  }
  window->display();
}

void Menu::run_menu(){
  while(window->isOpen()){
    loop_events();
    draw_all();
  }
}

void runfoo()
{
  Menu * menu = new Menu();
  menu->run_menu();
  
}
