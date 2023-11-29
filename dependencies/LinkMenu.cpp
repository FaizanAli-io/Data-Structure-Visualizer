#include "LinkMenu.h"

namespace gmenu
{

	/*==================================================*
	 *				public functions					*
	 *===================================================*/

	void Menu::setTitle(std::string title)
	{
		menuTitle = title;
	}

	void Menu::setMenuItems(std::vector<MenuItem> items)
	{
		menuItems = items;
	}

	/*
	This function constains the main event loop for the menu
	The actions performed : drawMenu() -> pollEvent() -> prefromAction()
	*/
	void Menu::createMenu()
	{
		setMenu();
		bool cont = true;
		while (window.isOpen() && cont)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				else if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Up)
					{
						currently_selected_item = (currently_selected_item + menuItems.size() - 1) % (menuItems.size());
					}
					else if (event.key.code == sf::Keyboard::Down)
					{
						currently_selected_item = (currently_selected_item + 1) % (menuItems.size());
					}
					else if (event.key.code == sf::Keyboard::Return)
					{
						cont = menuItems.at(currently_selected_item).action->start();
					}
				}
			} // while( pollEvent )

			window.clear();
			drawMenu();
			window.display();
		} // while window open
	}	  // create menu

	/*==================================================*
	 *				Private Functions					*
	 *===================================================*/

	/* Utility function */
	void Menu::writeText(std::string str, sf::Font font, unsigned int size, float x, float y, const sf::Color &color)
	{
		sf::Text text;
		text.setString(str);
		text.setFont(font);
		text.setFillColor(color);
		text.setCharacterSize(size);
		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.width / 2.0f, 0);
		if (x - textRect.width / 2.0f < 0)
		{
			// std::cout << x << " " << textRect.width / 2.0f;
			x = textRect.width / 2 + style.PaddingTitle.left;
		}
		if (x + textRect.width / 2.0f > window.getSize().x)
		{
			// std::cout << x << " " << textRect.width / 2.0f;
			x = window.getSize().x - textRect.width / 2 + style.PaddingTitle.left;
		}
		text.setPosition(sf::Vector2f(x, y));
		window.draw(text);
	} // writeText(...)

	void Menu::setMenu()
	{

		std::cout << "screen size:" << window.getSize().x << " " << window.getSize().y << std::endl;

		/* Setting title of menu */
		{
			/* Small scope just to be able to freely use the variable names */
			float offset_coefficient = 0.5;
			if (style.layout & Layout::TitleCentre)
				offset_coefficient = 0.5;
			else if (style.layout & Layout::TitleLeft)
				offset_coefficient = 0.25;
			else if (style.layout & Layout::TitleRight)
				offset_coefficient = 0.75;
			float x = (float)window.getSize().x * offset_coefficient, y = style.PaddingTitle.top;
			title_location.x = (x + style.PaddingTitle.left);
			title_location.y = y;
			std::cout << "title_location:" << title_location.x << " " << title_location.y << offset_coefficient << std::endl;
		}

		unsigned int menu_screen_height = (int)window.getSize().y - title_location.y + style.PaddingItems.top;
		std::cout << "Screen hieght" << menu_screen_height << std::endl;
		unsigned int block_height = (int)menu_screen_height / menuItems.size() * style.MenuItemScaleFactor;

		float offset_coefficient = 0.5;
		if (style.layout & Layout::ItemCentre)
			offset_coefficient = 0.5;
		else if (style.layout & Layout::ItemLeft)
			offset_coefficient = 0.25;
		else if (style.layout & Layout::ItemRight)
			offset_coefficient = 0.75;

		float x = (float)window.getSize().x * offset_coefficient + style.PaddingItems.left;
		float y = ((float)window.getSize().y) - 0.75 * menu_screen_height + block_height * 1 / 8;
		/* Calculating Menu item locations */
		for (int8_t i = 0; i < menuItems.size(); ++i)
		{
			coordinates crd;
			crd.x = x;
			crd.y = y;
			item_location.push_back(crd);
			std::cout << "menu location:" << x << " " << y << offset_coefficient << std::endl;
			y += block_height;
		}

	} // setMenu()

	void Menu::drawMenu()
	{
		writeText(menuTitle, style.ItemFont, style.TitleFontSize, title_location.x, title_location.y, style.TitleColor);
		sf::Color color = style.ItemColor;
		for (int i = 0; i < menuItems.size(); ++i)
		{
			if (i == currently_selected_item)
			{
				color = style.Selected;
			}
			writeText(menuItems[i].title, style.ItemFont, style.ItemFontSize, item_location[i].x, item_location[i].y, color);
			color = style.ItemColor;
		}

	} // drawMenu()

} // namespace sui

namespace test
{
	class testAction : public gmenu::Action
	{
	public:
		bool start()
		{
			return true;
		}
	};
}

void mainMenuFunc()
{
	sf::RenderWindow w(sf::VideoMode(1600, 900), "Welcome", sf::Style::Close);
	std::vector<gmenu::MenuItem> itemList;
	std::string text[4] = {"Linked List", "Stack / Queue", "AVL Tree", "Heap"};
	gmenu::MenuItem item;
	sf::Font font;
	font.loadFromFile("assets/fonts/font1.ttf");
	gmenu::Style style(font, font);
	style.layout = gmenu::Layout::TitleLeft | gmenu::Layout::ItemLeft;
	style.TitleColor = sf::Color::White;
	style.ItemColor = sf::Color::Cyan;
	style.Selected = sf::Color::Yellow;
	style.PaddingTitle.top = 10;
	style.PaddingItems.top = 50;
	style.PaddingItems.left = 200;
	for (int i = 0; i < 4; ++i)
	{
		item.title = text[i];
		itemList.push_back(item);
	}
	gmenu::Menu menu(w, "Welcome", itemList, style);
	menu.createMenu();
}