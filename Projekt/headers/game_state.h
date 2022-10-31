#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SFML/Graphics.hpp>
#include"../headers/state.h"
#include "../headers/graphics.h"

class Game_State : public State
{
private:
  bool end_game;
  bool collision = false;
  bool goal = false;
	void cleanup();
	Ball ball;
	int blue_goal;
	int red_goal;
  std::vector<Powerup*> power_vec;
	Player player1;
	Player player2;
	bool start;
	sf::Texture background;
	sf::Sprite sprite;
	sf::RectangleShape line;
	int w, h, powerupamount;
	sf::Clock clock1,clock2,timer;
	void spawn_powerup();
	void reset();

	  
public:
	Game_State();
	void handle_event()override;
	void update() override;
	void render(sf::RenderWindow& target)override;
	int get_next_state()override;
	Player action_player2(Player player2);
	Player action_player1(Player player1);
	void spawn(int,int);
};

#endif
