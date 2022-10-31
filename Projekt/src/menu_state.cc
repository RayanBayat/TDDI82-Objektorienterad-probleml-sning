#include "../headers/menu_state.h"

Menu_State::Menu_State()
  :  play{ false }, start {}, end {}, font {}, background {}, sprite {}
{
  std::string file = "res/sfont.ttf";
  //std::string file = "res/sfont.ttf";
    if (!font.loadFromFile(file))
        throw std::invalid_argument("Unable to load font");
    start = sf::Text{ "Press <Enter> to start", font, 40 };
    start.setFillColor(sf::Color::Black);
    end = sf::Text{ "Press <Shift> to exit", font, 40 };
    end.setFillColor(sf::Color::Black);
}

void Menu_State::handle_event()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		play = true;
    }
   
}

void Menu_State::update()
{
}

void Menu_State::render(sf::RenderWindow& target)
{
    target.draw(sprite);
    auto bounds{ start.getGlobalBounds() };
    auto size{ target.getSize() };

    start.setPosition((size.x - bounds.width) / 2,
        (size.y - bounds.height) / 3);

    target.draw(start);
    end.setPosition((size.x - bounds.width) / 2,
        (size.y - bounds.height) / 3 *2-20);
    target.draw(end);
   
}

int Menu_State::get_next_state()
{
    if (play)
    {
        play = false;
        return 1;
    }
    else
    {
        return 0;
    }
}

void Menu_State::spawn(int,int)
{
    background.loadFromFile("res/start720p.jpg");
    sprite.setTexture(background);
}
