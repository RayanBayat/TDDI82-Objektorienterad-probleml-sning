#include "../headers/graphics.h"
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;

Figure::Figure ()  :shape {}, position_x{150}, position_y{150}, radius{5}
{
}

Figure::Figure(int pos_x, int pos_y, float rad): shape {}, position_x{pos_x}, position_y{pos_y}, radius{rad}
{
  shape.setRadius(radius);
  shape.setFillColor(sf::Color::Green);
  shape.setPosition(position_x,position_y);
}

void Figure::set_radius(float rad, int check)
{
  if (check == 1){
    shape.setFillColor(sf::Color::Red);
  }
  if (check == 2){
    shape.setFillColor(sf::Color::Blue);
  }
  if (check == 3){
    shape.setFillColor(sf::Color::Black);
  }
  shape.setRadius(rad);
  radius = rad;
  shape.setOrigin(rad, rad);
}

sf::FloatRect Figure::get_bounds ()
{
  return shape.getGlobalBounds();
}

int Figure::get_position_x()
{
  sf::Vector2f pos = shape.getPosition();
  return pos.x;
}

int Figure::get_position_y()
{
  sf::Vector2f pos = shape.getPosition();
  return pos.y;
}



float Figure::get_radius ()
{
  return radius;
}

void Figure::draw_figure(RenderWindow& window)
{
  window.draw(shape);
}





Moving_Figure::Moving_Figure (int pos_x, int pos_y, float rad, int vel_x, int vel_y):Figure(pos_x, pos_y, rad), velocity_x {vel_x}, velocity_y{vel_y}
{
  
}

void Moving_Figure::move(Player player, bool collision)
{
  // sf::Vector2f ball_pos = this->shape.getPosition();
  
//  int zero = 0;
  if (collision)
  {

      double a, b;
      a = static_cast<double>(this->get_position_x()) - static_cast<double>(player.get_position_x());
      b = static_cast<double>(this->get_position_y()) - static_cast<double>(player.get_position_y());

      //
      //// Om bollen är till höger om spelaren
      if (this->get_position_x() > player.get_position_x())
      {
          // this->set_Position(player.get_radius() + this->get_radius() + player.get_position_x(),this->get_position_y());&& this->get_position_y() > player.get_position_y()

           /*std::cout << "Skillnad i x led mellan bollen och spelaren : " << a << "\n"
               << "Skillnad i y led mellan bollen och spelaren : " << b;*/
          if (a > b * 2)
          {
              this->set_velocity_x(-1 * velocity_x);
              this->set_velocity_y(velocity_y);
          }
          else
          {
              this->set_velocity_x(-1 * velocity_x);
              this->set_velocity_y(-1 * velocity_y);
          }

      }

      // Om bollen är till vänster om spelaren
      if (this->get_position_x() < player.get_position_x())
      {
          if (a > 2 * b)
          {
              this->set_velocity_x(-1 * velocity_x);
              this->set_velocity_y(-1 * velocity_y);
          }
          else
          {
              this->set_velocity_x(-1 * velocity_x);
              this->set_velocity_y(velocity_y);


          }

      }

      //std::cout << "Boll hastighet x: " << get_velocity_x() << "\n"
      //    << "Boll hastighet y: " << get_velocity_y() << "\n";
      // system("cls");
  }


  
  //this->set_position(get_velocity_x(), get_velocity_y());
  
}

void Moving_Figure::set_position(int x, int y) //Två av samma funktion?
{
  
  shape.setPosition(get_position_x() + x, get_position_y() +  y);
}
void Moving_Figure::set_Position(int x, int y)
{
  
    shape.setPosition(x, y);
}

void Moving_Figure::goal_and_wall(bool & goal, int & blue_goal, int & red_goal)
{
    sf::Vector2f ball_pos = this->shape.getPosition();
    if (ball_pos.x == ((this->radius)))
    {
        //  Blå MÅL
        if (ball_pos.y >= (height / 3) && ball_pos.y <= (height - (height / 3)))
        {
	  this->set_radius(40, 1);
	  blue_goal++;
	
	  goal = true; 
        }
        this->set_velocity_x(-velocity_x);
    }
    if (ball_pos.x <= ((this->radius)))
    {
        //  Blå MÅL
        if (ball_pos.y >= (height / 3) && ball_pos.y <= (height - (height / 3)))
        {
            this->set_radius(40, 1);
	     blue_goal++;
	     
	    goal = true;
        }

        //this->set_Position((this->radius) - 1, this->get_position_y());
        this->set_velocity_x(-velocity_x);
    }
    if (ball_pos.x == width - ((this->radius)))
    {
        //  Röd MÅL
        if (ball_pos.y >= (height / 3) && ball_pos.y <= (height - (height / 3)))
        {
            this->set_radius(30, 2);
	     red_goal++;
	     
	    goal = true;
        }

        this->set_velocity_x(-velocity_x);
    }

    if (ball_pos.x >= width - ((this->radius)))
    {
        //  Röd MÅL
        if (ball_pos.y >= (height / 3) && ball_pos.y <= (height - (height / 3)))
        {
            this->set_radius(30, 2);
	    red_goal++;
	    
	    goal = true;
        }

        //this->set_Position(width - (this->radius), this->get_position_y());
        this->set_velocity_x(-velocity_x);
    }
    if (ball_pos.y == ((this->radius)))
    {
        this->set_velocity_y(-velocity_y);
    }
    if (ball_pos.y <= ((this->radius)))
    {
        this->set_Position(this->get_position_x(), (this->radius));
        this->set_velocity_y(-velocity_y);
    }
    if (ball_pos.y == height - (this->radius))
    {
        this->set_velocity_y(-velocity_y);
    }
    if (ball_pos.y >= height - (this->radius))
    {
        this->set_Position(this->get_position_x(), height - (this->radius));
        this->set_velocity_y(-velocity_y);
    }
    this->set_velocity_x(get_velocity_x());
    this->set_velocity_y(get_velocity_y());
  
}



int Moving_Figure::get_velocity_x()
{
    
    return velocity_x;
}

int Moving_Figure::get_velocity_y()
{
  
     return velocity_y;
}

void Moving_Figure::set_velocity_x(int x)
{
    velocity_x = x;
    shape.setPosition(get_position_x() + x, get_position_y());
}

void Moving_Figure::set_velocity_y(int y)
{
  velocity_y = y;
    shape.setPosition(get_position_x(), get_position_y() + y);
}


int Ball::get_velocity_x()
{
  return velocity_x;
}

int Ball::get_velocity_y()
{
  return velocity_y;
}

void Ball::set_velocity_x(double x)
{
  velocity_x = x;
  shape.setPosition(get_position_x() + x, get_position_y());
}

void Ball::set_velocity_y(double y)
{
  velocity_y = y;
  shape.setPosition(get_position_x(), get_position_y() + y);
}

Player::Player () : Moving_Figure(0, 0, 30, 30, 30), speed_mult {4}, cooldown {300}
{
  
}

int Player::get_speed_mult ()
{
  return speed_mult;
}

int Player::get_cooldown ()
{
  return cooldown;
}

void Player::set_speed_mult (double speed)
{
  speed_mult = speed;
  return;
}

void Player::set_cooldown (int cd)
{
  cooldown = cd;
  return;
}

bool Player::getCollision( Ball ball )
{
  double xs = (static_cast<double>(this->get_position_x()) - static_cast<double>(ball.get_position_x()));
  double ys = (static_cast<double>(this->get_position_y()) - static_cast<double>(ball.get_position_y()));
    double distan =((xs * xs) + (ys * ys));
    double distance = sqrt(distan);
    if ((static_cast<double>(this->radius) + static_cast<double>(ball.get_radius())) >= distance)
    {
  
        return true;
        /*std::cout << "Spelare 1 position x: " << player1.get_position_x() << "\n" << "Spelare 1 position y: " << player1.get_position_y()
            << "\n" << "Spelare 1 radie: " << player1.get_radius();*/
       
    }
    return false;
 
}

Powerup::Powerup (int pos_x, int pos_y, float rad, bool negative_effect) :Figure( pos_x, pos_y, rad), negative_effect{negative_effect}
{
  
}

bool Powerup::player_collision (Player & p)
{
  if ((*this).get_bounds().intersects(p.get_bounds()))
  {
    return true;
  }
  return false;
}

bool Powerup::is_negative() const
{
  return negative_effect;
}

Buff_player_size::Buff_player_size(int pos_x, int pos_y, float rad): Powerup {pos_x, pos_y, rad, false}
{
  
}

void Buff_player_size::ability (Player & p)
{

  if (p.get_radius() < 60)
  {
    p.set_radius(p.get_radius() + 5, 0);
  }
  return;
}

Nerf_player_size::Nerf_player_size(int pos_x, int pos_y, float rad): Powerup {pos_x, pos_y, rad, true}
{
  
}

void Nerf_player_size::ability (Player & p)
{
  if(p.get_radius() > 6)
  {
    p.set_radius(p.get_radius() - 5, 0);
  }
  return;
}


Buff_player_speed::Buff_player_speed(int pos_x, int pos_y, float rad): Powerup {pos_x, pos_y, rad, false}
{
  
}

void Buff_player_speed::ability (Player & p)
{
  if(p.get_speed_mult() < 10)
  {
    p.set_speed_mult(p.get_speed_mult() + 1);
  }
  return;
}

Nerf_player_speed::Nerf_player_speed(int pos_x, int pos_y, float rad): Powerup {pos_x, pos_y, rad, true}
{
  
}

void Nerf_player_speed::ability (Player & p)
{
  if(p.get_speed_mult() > 3)
  {
    p.set_speed_mult(p.get_speed_mult() - 1);
  }
  return;
}
