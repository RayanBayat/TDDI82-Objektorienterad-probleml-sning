#ifndef MENU_STATE_H
#define MENU_STATE_H
#include "../headers/state.h"
#include <SFML/Graphics.hpp>

class Menu_State : public State
{
private:
	bool play;
	sf::Text start,end;
	sf::Font font{};
	sf::Texture background;
	sf::Sprite sprite;
public:
	Menu_State();

	 virtual void handle_event()override;
	 void update() override;
	 void render(sf::RenderWindow& target)override ;
	 int get_next_state()override;
	 void spawn(int,int);
};


#endif
