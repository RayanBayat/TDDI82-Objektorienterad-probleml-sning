#ifndef AIRHOCKEY_GRAPHICS_H
#define AIRHOCKEY_GRAPHICS_H
#include <SFML/Graphics.hpp>
#include"../headers/state.h"

class Figure
{
public:
  Figure();
  Figure (int pos_x, int pos_y, float rad);
  
  virtual ~Figure() = default;
  
  void set_radius(float radius, int check); 
  int get_position_x();
  int get_position_y();
  void draw_figure(sf::RenderWindow& window);
  
  float get_radius ();
  sf::FloatRect get_bounds ();
    
protected:
  // sf::Texture texture;
  sf::CircleShape shape;
  int position_x;
  int position_y;
  float radius;
  //sf::Texture texture;
  //sf::Sprite sprite;
};

class Player;

class Moving_Figure : public Figure
{
public:
  Moving_Figure(int pos_x, int pos_y, float rad, int vel_x, int vel_y);

  Moving_Figure () = default;
  void move(Player player, bool collision);
  void goal_and_wall(bool & goal, int & blue_goal, int & red_goal);
  void set_position(int x, int y);
  void set_Position(int x, int y);
  int get_velocity_x();
  int get_velocity_y();
  void set_velocity_x(int);
  void set_velocity_y(int);
  void set_colour();
  
protected:
  int velocity_x = -8;
  int velocity_y = -4;
  
};

class Ball : public Moving_Figure
{
private:
  
public:
  int get_velocity_x();
  int get_velocity_y();
  void set_velocity_x(double);
  void set_velocity_y(double);
};

class Player : public Moving_Figure
{
public:
  Player ();
  
  int get_speed_mult ();
  int get_cooldown ();
  void set_speed_mult(double speed);
  void set_cooldown (int cd);
  bool getCollision (Ball ball);
  
private:
  int speed_mult;
  int cooldown;
};

class Powerup : public Figure
{
public:
  Powerup (int pos_x, int pos_y, float rad, bool negative_effect);
  
  bool player_collision (Player & p);
  virtual void ability (Player & p) = 0;
  bool is_negative () const;
protected:
  const bool negative_effect;
};


class Buff_player_size : public Powerup
{
public:
  Buff_player_size(int pos_x, int pos_y, float rad);
  void ability (Player &p) override;
};

class Nerf_player_size : public Powerup
{
public:
  Nerf_player_size(int pos_x, int pos_y, float rad);
  void ability (Player &p) override;
};

class Buff_player_speed : public Powerup
{
public:
  Buff_player_speed(int pos_x, int pos_y, float rad);
  void ability (Player &p) override;
};

class Nerf_player_speed : public Powerup
{
public:
  Nerf_player_speed(int pos_x, int pos_y, float rad);
  void ability (Player &p) override;
};

#endif //AIRHOCKEY_GRAPHICS_H
