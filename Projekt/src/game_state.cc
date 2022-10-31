#include "../headers/game_state.h"


int check = 0;

Game_State::Game_State () : end_game {}, ball {}, blue_goal{}, red_goal{}, power_vec{}, player1{}, player2 {}, start{}, background {}, sprite {}, line {}, w{}, h {}, powerupamount{}, clock1{}, clock2{}, timer {}
{

}

void Game_State::cleanup()
{
  for(Powerup* &p : power_vec)
  {
    delete p; 
  }
  
    power_vec.clear();
    //kan implementeras efter att vi har en fungerande goal
}

bool overMiddle(Player player, sf::RectangleShape line)
{
    if (player.get_bounds().intersects(line.getGlobalBounds())) {
        return true;
    }
    return false;
}

void Game_State::handle_event()
{
  
  for (Powerup* &p : power_vec)
  {
    if (p->player_collision(player1) == true )
    {
      if(p->is_negative() == false)
      {
	p->ability(player1);
      }
      else
      {
	p->ability(player2);
      }
      
      power_vec.erase(remove(power_vec.begin(),power_vec.end(),p),power_vec.end());
    }
    else if (p->player_collision(player2) == true)
    {
      if(p->is_negative() == false)
      {
        p->ability(player2);
      }
      else
      {
	p->ability(player1);
      }
      
      power_vec.erase(remove(power_vec.begin(), power_vec.end(), p), power_vec.end());
    }
  }
 
}
void Game_State::spawn_powerup()
{
    int v1 = rand() % width;
    int v2 = rand() % height;
    int v3 = rand() % 10+7;
    int v4 = rand() % 4 + 1;
    if (timer.getElapsedTime().asSeconds() > 10) // var 10:de sekund spawnar en random powerup
    {
        powerupamount++;
        if (v4 == 1)
        {
            power_vec.push_back( new Buff_player_size (v1, v2, v3));
        }
        else if (v4 == 2)
        {
            power_vec.push_back(new Nerf_player_size(v1, v2, v3));
        }
        else if (v4 == 3)
        {
            power_vec.push_back(new Buff_player_speed(v1, v2, v3));
        }
        else if (v4 == 3)
        {
            power_vec.push_back(new Nerf_player_speed(v1, v2, v3));
        }
        timer.restart();
   }
   
  

}
void Game_State::render(sf::RenderWindow& target)
{
  std::string file = "res/score.ttf";
  sf::Font font{};
   if (!font.loadFromFile(file))
     {
       throw std::invalid_argument("Unable to load font");
     }
     sf::Text blue, red;
     blue = sf::Text{std::to_string(blue_goal), font, 50};
     blue.setFillColor(sf::Color::Blue);
	
     red = sf::Text{std::to_string(red_goal), font, 50};
     red.setFillColor(sf::Color::Red);

     auto blue_bounds{ blue.getGlobalBounds() };
     auto red_bounds{ red.getGlobalBounds() };

     red.setPosition(((width/2) - 100), 20);
     blue.setPosition(((width/2) + 90), 20);
    
     
  player1 = action_player1(player1);
  player2 = action_player2(player2);
  

  //Player ability cooldown
  if (player1.get_cooldown() != 0)
  {
      player1.set_cooldown(player1.get_cooldown() - 1);

      if (player1.get_cooldown() == 200)
      {
          player1.set_speed_mult(player1.get_speed_mult() - 2);
      }
  }

  if (player2.get_cooldown() != 0)
  {
      player2.set_cooldown(player2.get_cooldown() - 1);

      if (player2.get_cooldown() == 200)
      {
          player2.set_speed_mult(player2.get_speed_mult() - 2);
      }
  }
  //line.setFillColor(sf::Color::Red);
  target.draw(sprite);
  player1.draw_figure(target);
  player2.draw_figure(target);
  
  
  ball.draw_figure(target);
  
  for (Powerup* &p  : power_vec)
  {
    p->draw_figure(target);
  }
  
  
     if (blue_goal >= 3)
     {
       blue = sf::Text("Blue wins! \n" + std::to_string(red_goal) + " - " + std::to_string(blue_goal) ,font, 100);
         
         blue.setPosition((width / 4) , height/2);
         blue.setFillColor(sf::Color::Blue);
         reset();
     }
     else if (red_goal >= 3)
     {
       red = sf::Text("Red wins! \n" + std::to_string(red_goal) + " - " + std::to_string(red_goal), font, 100);
         red.setPosition((width / 4), height / 2);
         red.setFillColor(sf::Color::Red);
         reset();
     }
     target.draw(blue);
     target.draw(red);
}

void Game_State::reset()
{
  
  start = false;
  cleanup();
  check = 1;
  player1.set_radius(player1.get_radius(), check);
  player1.set_Position(width/4, height/2);
      
  check = 2;
  player2.set_radius(player2.get_radius(), check);
  player2.set_Position((width - (width/4)), height/2);
      
  check = 3;
  ball.set_radius(20, check);
  ball.set_Position((width/2), (height/2));

  
}

void Game_State::update()
{
    
  //if(!cloc.getElapsedTime().asSeconds() < 1)
    {
     
        Player player;
       
        if (player1.getCollision(ball) && clock1.getElapsedTime().asSeconds() > 0.7)
        {
            // om kollision

            //sf::Vector2f pos = player1.shape.getPosition();
            collision = true;
            ball.move(player1, collision);
            clock1.restart();
            start = true;
	    
        }

        else if (player2.getCollision(ball) && clock2.getElapsedTime().asSeconds() > 0.7)
        {
            collision = true;
            ball.move(player2, collision);
            clock2.restart();
            start = true;
        }
	
        if (start==true)
        {
            spawn_powerup();
	  ball.goal_and_wall(goal, blue_goal, red_goal);
	 
        }
	if(goal)
	  {
	    reset();
	    goal = false;
	  }
	
    }

}



int Game_State::get_next_state()
{
  if (end_game || sf::Keyboard::isKeyPressed(sf::Keyboard::L))
  {
    end_game = false;
    return menu_state;
  }
  return game_state;
}

Player Game_State::action_player1(Player player1)
{
  //Player1 ability, higher speed for 1.5 sec. 
  if (player1.get_cooldown() == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
  {
    player1.set_speed_mult(player1.get_speed_mult() + 2);
    player1.set_cooldown(300);
  }
  
  Player player = player1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
      {
        if (player1.get_position_x() <= player1.get_radius())
	  {
            player1.set_Position( player1.get_radius(),player1.get_position_y());
            if (player1.get_position_y() <= player1.get_radius()) //W
            {
                player1.set_Position(player1.get_position_x(), player1.get_radius());
                
            }
            else if(player1.get_position_y() >= h - player1.get_radius())//RangeCheck down S
            {
                player1.set_Position(player1.get_position_x(), h - player1.get_radius());
               
            }
            return player1;
	  }
	
        
        player1.set_position(-2 * player1.get_speed_mult(), 0);
      }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
      {
        if (player1.get_position_x() >= (w / 2)- player1.get_radius())//overMiddle(player, line)
        {
            player1.set_Position((w / 2) - player1.get_radius(),player1.get_position_y());
            if (player1.get_position_y() <= player1.get_radius()) //W
            {
                player1.set_Position(player1.get_position_x(), player1.get_radius());

            }
            else if (player1.get_position_y() >= h - player1.get_radius())//RangeCheck down S
            {
                player1.set_Position(player1.get_position_x(), h - player1.get_radius());

            }
            return player1;
        }
	
        /*if (overMiddle(player, line))
	  {
            return player1;
	  }*/
	
        player1.set_position(2 * player1.get_speed_mult(), 0);
      }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
      {
        if (player1.get_position_y() <= player1.get_radius())
	  {
            player1.set_Position(player1.get_position_x(), player1.get_radius());  
            if (player1.get_position_x() <= player1.get_radius()) //A
            {
                player1.set_Position(player1.get_radius(), player1.get_position_y());
            }
            else if (player1.get_position_x() >= (w / 2) - player1.get_radius())//overMiddle(player, line) //D
            {
                player1.set_Position((w / 2) - player1.get_radius(), player1.get_position_y());
            }
            return player1;
	  }
	
   
	
        player1.set_position(0, -2 * player1.get_speed_mult());
      }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
      {
        if (player1.get_position_y() >= h - player1.get_radius())//RangeCheck down
	  {
            player1.set_Position(player1.get_position_x(), h - player1.get_radius());
            if (player1.get_position_x() <= player1.get_radius()) //A
            {
                player1.set_Position(player1.get_radius(), player1.get_position_y());
            }
            else if (player1.get_position_x() >= (w / 2) - player1.get_radius())//overMiddle(player, line) //D
            {
                player1.set_Position((w / 2) - player1.get_radius(), player1.get_position_y());
            }
            return player1;
	  }
        player1.set_position(0, 2 * player1.get_speed_mult());
      }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
      {
        player1.set_position(-1 * player1.get_speed_mult(), -1 * player1.get_speed_mult());
      }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
      player1.set_position(1 * player1.get_speed_mult(), -1 * player1.get_speed_mult());
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
      {
        player1.set_position(-1 * player1.get_speed_mult(), 1 * player1.get_speed_mult());
      }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
      {
        player1.set_position(1 * player1.get_speed_mult(), 1 * player1.get_speed_mult());
      }
    
    return player1;
    
    //player2.set_position(1, 1);
}




Player Game_State::action_player2(Player player2)
{
  //Player1 ability, higher speed for 1.5 sec. 

  if (player2.get_cooldown() == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
  {
    player2.set_speed_mult(player2.get_speed_mult() + 2);
    player2.set_cooldown(300);
  }
  
  Player player = player2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      {
        if (player2.get_position_x() <= w/2 + player2.get_radius())
	  {
            player2.set_Position(w / 2 + player2.get_radius(), player2.get_position_y());
            if (player2.get_position_y() <= player2.get_radius())
            {
                player2.set_Position(player2.get_position_x(), player2.get_radius());

              
            }
            else if (player2.get_position_y() >= h - player2.get_radius())//RangeCheck down
            {
                player2.set_Position(player2.get_position_x(), h - player2.get_radius());
              
            }
            return player2;
	  }
	

        player2.set_position(-2 * player2.get_speed_mult(), 0);
      }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      {
        if (player2.get_position_x() >= w-player2.get_radius())
	  {
            player2.set_Position(w - player2.get_radius(), player2.get_position_y());
            if (player2.get_position_y() <= player2.get_radius())
            {
                player2.set_Position(player2.get_position_x(), player2.get_radius());


            }
            else if (player2.get_position_y() >= h - player2.get_radius())//RangeCheck down
            {
                player2.set_Position(player2.get_position_x(), h - player2.get_radius());

            }
            return player2;
	  }

        player2.set_position(2 * player2.get_speed_mult(), 0);
      }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      {
        if (player2.get_position_y() <= player2.get_radius())
	  {
            player2.set_Position(player2.get_position_x(), player2.get_radius());
            if (player2.get_position_x() <= w / 2 + player2.get_radius())
            {
                player2.set_Position(w / 2 + player2.get_radius(), player2.get_position_y());
            }
            else if (player2.get_position_x() >= w - player2.get_radius())
            {
                player2.set_Position(w - player2.get_radius(), player2.get_position_y());
            }
            return player2;
	  }

        player2.set_position(0, -2 * player2.get_speed_mult());
      }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      {
        if (player2.get_position_y() >= h - player2.get_radius())//RangeCheck down
	  {
            player2.set_Position(player2.get_position_x(), h-player2.get_radius());
            if (player2.get_position_x() <= w / 2 + player2.get_radius())
            {
                player2.set_Position(w / 2 + player2.get_radius(), player2.get_position_y());
            }
            else if (player2.get_position_x() >= w - player2.get_radius())
            {
                player2.set_Position(w - player2.get_radius(), player2.get_position_y());
            }
            return player2;
	  }
        player2.set_position(0, 2 * player2.get_speed_mult());
      }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      {
	if (player2.get_position_y() <= 0 && player2.get_position_x() <= w/2)
	{
	  return player2;
	}
	
        player2.set_position(-1 * player2.get_speed_mult(), -1 * player2.get_speed_mult());
      }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      player2.set_position(1 * player2.get_speed_mult(), -1 * player2.get_speed_mult());
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      {
        player2.set_position(-1 * player2.get_speed_mult(), 1 * player2.get_speed_mult());
      }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      {
        player2.set_position(1 * player2.get_speed_mult(), 1 * player2.get_speed_mult());
      }
    
    return player2;
}



void Game_State::spawn(int a , int b)
{
  w = a;
  h = b;
  
  sf::Clock clock1;
  sf::Clock clock2;
  sf::Clock timer;
  
  //int random{};
  //random = rand() % 3;
   
   reset();
  
     //background.loadFromFile("../res/wooden.jpg");
    background.loadFromFile("res/air720p.jpg");
    //background.loadFromFile("res/air1080p.jpg");
 // if (random == 0)
 //   {
 //     //background.loadFromFile("../res/wooden.jpg");
 //     background.loadFromFile("res/wooden.jpg");
 //   }
 // 
 //   if (random == 1)
 //     {
	////background.loadFromFile("../res/space.jpg");
	//background.loadFromFile("res/space.jpg");
 //     }
 //   
 //   if (random == 2)
 //     {
 //       //background.loadFromFile("../res/jungle.jpg");
	//background.loadFromFile("res/jungle.jpg");
 //     }
   //
    sprite.setTexture(background);
   
}
