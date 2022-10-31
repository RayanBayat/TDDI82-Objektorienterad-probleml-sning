#ifndef STATE_H
#define STATE_H
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <vector>
#include<vector>
#include <cmath>

#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics.hpp>

#include "graphics.h"
int const width{ 1280 };
int const height{ 720 };
const int menu_state{ 0 };
const int game_state{ 1 };

class State
{
private:

public:
	virtual ~State() = default;
	virtual void handle_event() = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderWindow& target) = 0;
	virtual int get_next_state() = 0;
	virtual void spawn(int, int) = 0;
};


#endif
