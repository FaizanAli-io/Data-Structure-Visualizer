#include "Dependencies/LinkMenu.cpp"
#include "Dependencies/LinkedList.h"
#include <memory>

namespace test {
	class testAction : public gmenu::Action {
	public:
		bool start() {
			return true;
		}
	};
}
//Action will link

int main() {
	sf::RenderWindow w( sf::VideoMode( 800, 600 ), "Welcome", sf::Style::Close);
	std::vector<gmenu::MenuItem> itemList;
	std::string text[4] = { "Linked List", "Stack / Queue","AVL Tree", "Heap" };
	gmenu::MenuItem item;
	sf::Font font;
	font.loadFromFile( "assets/fonts/font1.ttf" );
	gmenu::Style style( font, font );
	style.layout = gmenu::Layout::TitleLeft|gmenu::Layout::ItemLeft;
	style.TitleColor = sf::Color::White;
	style.ItemColor = sf::Color::Cyan;
	style.Selected = sf::Color::Yellow;
	style.PaddingTitle.top = 250;
	style.PaddingItems.top = 30;
	style.PaddingItems.left = -100;
	for ( int i = 0; i < 4; ++i ) {
		item.title = text[i];
		item.action = std::make_shared < test::testAction>();
		itemList.push_back( item );
	}
	gmenu::Menu menu( w, "Welcome", itemList, style );
	menu.createMenu();
    return 0;
}


