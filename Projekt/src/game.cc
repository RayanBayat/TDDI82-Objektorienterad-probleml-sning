#include "../headers/game.h"

#include "../headers/state.h"
#include "../headers/menu_state.h"
#include "../headers/game_state.h"



void Game::Handle_events()
{
    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            window.close();
            running = false;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
        {
            window.close();
            running = false;
        }
        states.at(current_state)->handle_event();
    }
}

Game::Game(int const width, int const height, std::string title): w{width}, h{height}, window{ sf::VideoMode(width, height), title, sf::Style::Close }, states{}, running{true}, current_state{0}, event {}
{
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);
  //Lägger in alla states som ska vara med i map med motsvarande nyckel
  states.insert (std::pair<int,
		 std::unique_ptr<State>>({ menu_state,std::make_unique<Menu_State>() }));
  states.insert(std::pair<int,
		std::unique_ptr<State>>({ game_state,std::make_unique<Game_State>() }));
  
}

void Game::Start()
{
    states.at(menu_state)->spawn(w, h);
    states.at(game_state)->spawn(w,h);
    
    sf::Image icon;
    icon.loadFromFile ("res/icon.png"); // File/Image/Pixel
    if (!icon.loadFromFile("res/icon.png"))
        throw std::invalid_argument("Unable to load icon");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    while (running) {
       
            states.at(current_state)->update();
          
        
      Handle_events();
      window.clear();
      states.at(current_state)->render(window);
     // std::cout << clock.getElapsedTime().asSeconds() << "\n";
    
      
      current_state = states.at(current_state)->get_next_state();



      window.display();

    }
}
