#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include"../headers/state.h"

class Game
{
private:
  //Variaber
  int w, h;
  sf::RenderWindow window;
  std::map<int, std::unique_ptr<State>> states;
  bool running;
  int current_state;
  
  sf::Event event;
  
  
  //funktioner
  void Handle_events();
  
public:
  //destruktor och konstruktor
  Game(int height, int width, std::string title);
  ~Game() = default;
  

  
  void Start();
  
};
#endif
