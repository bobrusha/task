#include <list>
#include "bomb.h"
#include "block.h"
using namespace std;

//global variables------
int wW = 540, wH = 460;
const int border = 20;
const int maxsteps = ((wW - border)/ step);
const int max_num_lvls = 4;

unsigned int textures[30];
unsigned int NUM_LVL = 0;
//---------------------
//MENU


//--------------------
//game's objects

screen scrn;

list <enemy> enemies;
list <brick> bricks;
list <bomb> bombs;

hero Main (scrn);
portal lvlup ( 0, 0, 0, 0, scrn);

list <enemy>::iterator pos;

//-----------------------
int calculateCoordinates (int x)
{
		x *= step;
        x += 10;
		return x;
}
//-----------------------

int lvls[max_num_lvls][13][15] =
{
	{
		{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
		{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 2, 2, 0 },
		{ 4, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 4 },
		{ 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
		{ 4, 0, 0, 0, 0, 2, 0, 2, 3, 2, 0, 2, 0, 0, 4 },
		{ 4, 0, 2, 2, 0, 2, 2, 0, 0, 2, 0, 0, 0, 0, 4 },
		{ 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4 },
		{ 4, 2, 0, 0, 2, 0, 2, 0, 2, 2, 0, 0, 2, 2, 4 },
		{ 4, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 4 },
		{ 4, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 4 },
		{ 4, 0, 0, 0, 0, 0, 3, 2, 0, 0, 0, 0, 0, 0, 4 },
		{ 4, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 4 },
		{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 }
	},
	{
		{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
		{ 4, 0, 2, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 4 },
		{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 4 },
		{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4 },
		{ 4, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 4 },
		{ 4, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 4 },
		{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 4 },
		{ 4, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 4 },
		{ 4, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 4 },
		{ 4, 0, 0, 2, 0, 0, 3, 2, 0, 0, 2, 2, 0, 0, 4 },
		{ 4, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
		{ 4, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 3, 4 },
		{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 }
	},
	{
		{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
		{ 4, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 0, 0, 2, 4 },
		{ 4, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 4 },
		{ 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 4 },
		{ 4, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 4 },
		{ 4, 0, 2, 3, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 4 },
		{ 4, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
		{ 4, 0, 0, 0, 0, 0, 0, 2, 0, 0, 3, 2, 0, 0, 4 },
		{ 4, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 4 },
		{ 4, 0, 2, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 4 },
		{ 4, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 4 },
		{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 3, 2, 0, 4 },
		{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 }
	},
	{
		{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
		{ 4, 0, 0, 0, 0, 2, 0, 2, 2, 0, 0, 0, 0, 2, 4 },
		{ 4, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 4 },
		{ 4, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 4 },
		{ 4, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4 },
		{ 4, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 4 },
		{ 4, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 4 },
		{ 4, 2, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 4 },
		{ 4, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 4 },
		{ 4, 2, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 0, 4 },
		{ 4, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 3, 0, 4 },
		{ 4, 2, 2, 0, 2, 2, 2, 0, 2, 0, 2, 0, 2, 2, 4 },
		{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 }
	}
};

void createLevel ()
{
        scrn.clearScreen();
		bricks.clear();
		enemies.clear();
		bombs.clear();

		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				switch ( lvls[NUM_LVL][i][j])
				{
					case 2:
					{
						bricks.push_back(brick (calculateCoordinates(j - 1), calculateCoordinates(j), calculateCoordinates(i-1), calculateCoordinates(i), scrn));
					}
					break;
					case 3:
					{
						enemies.push_back(enemy (calculateCoordinates(j - 1), calculateCoordinates(j), calculateCoordinates(i-1), calculateCoordinates(i), scrn));
					}
					break;
				}
			}
		}

		lvlup = portal (10, 50, 410, 450, scrn);
		Main = hero (scrn);
}


void levelUp()
{
	++NUM_LVL;
	createLevel();
}
void startNewGame()
{
	NUM_LVL = 0;
	createLevel();
}

/*
void boom (int);
void enemyMotion(int);
*/
//-----------------------------------
void bomb::damage(sf::RenderWindow& window, sf::Sprite& sprFire)
{

	if (scrn.getArrayElement(calculateIndex(b),calculateIndex(l)+1) != 4)
	{
		for (int i=0; i <= dst; ++i)
		{
			if (scrn.getArrayElement(calculateIndex(b), calculateIndex(l)+i) == 2 )
			{
				if (first)
				{
					bricks.remove(brick(l+i*step, r+(i*step), b, t, scrn));
					scrn.setArrayElement(0, calculateIndex(b), calculateIndex(l)+i);
				}
				break;
			}
			if (scrn.getArrayElement(calculateIndex(b), calculateIndex(l)+i) == 3)
			{
				enemies.remove( enemy ( l + i*step, r + i*step, b, t, scrn) );
				scrn.setArrayElement(0, calculateIndex(b), calculateIndex(l) + i);
			}
			sprFire.setPosition(sf::Vector2f(l + i*step, b));
			window.draw(sprFire);
		}
	}
	if (scrn.getArrayElement(calculateIndex(b), calculateIndex(l)-1) != 4)
	{
		for (int i=0; i <= dst; ++i)
		{
			if (scrn.getArrayElement(calculateIndex(b), calculateIndex(l) - i) == 2 && first)
			{
				if(first)
				{
					bricks.remove(brick( l - i*step, r - i*step, b, t, scrn));
					scrn.setArrayElement(0, calculateIndex(b), calculateIndex(l) - i);
				}
				break;
			}
			if (scrn.getArrayElement(calculateIndex(b), calculateIndex(l) - i - 1) == 3 )
			{
				enemies.remove( enemy (l-i*step, r-i*step, b, t, scrn) );
				scrn.setArrayElement(0, calculateIndex(b), calculateIndex(l) - i - 1);
			}
			sprFire.setPosition(sf::Vector2f(l- i*step, b));
			window.draw(sprFire);
		}
	}
	if (scrn.getArrayElement(calculateIndex(b)+1, calculateIndex(l)) != 4 )
	{
		for (int i=0; i <= dst; ++i)
		{
			if (scrn.getArrayElement(calculateIndex(b)+i, calculateIndex(l)) == 2  && first)
			{
				if(first)
				{
					bricks.remove(brick(l, r, b+i*step, t+i*step, scrn));
					scrn.setArrayElement(0, calculateIndex(b)+i, calculateIndex(l));
				}
				break;
			}
			if (scrn.getArrayElement(calculateIndex(b)+i, calculateIndex(l)) == 3)
			{
				enemies.remove( enemy (l, r, b+i*step, t+i*step, scrn) );
				scrn.setArrayElement(0, calculateIndex(b)+i, calculateIndex(l));
			}
			sprFire.setPosition(sf::Vector2f(l, b+ i*step));
			window.draw(sprFire);
		}
	}
	if (scrn.getArrayElement(calculateIndex(b)-1, calculateIndex(l)) != 4)
	{
		for (int i = 0; i <= dst; i++)
		{
			if (scrn.getArrayElement(calculateIndex(b)-i, calculateIndex(l)) == 2)
			{
				if (first)
				{
					bricks.remove(brick (l, r, b-i*step, t-i*step, scrn));
					scrn.setArrayElement(0, calculateIndex(b)-i, calculateIndex(l));
				}
				break;
			}
			if (scrn.getArrayElement(calculateIndex(b)-i, calculateIndex(l)) == 3)
			{
				enemies.remove (enemy (l, r, b-i*step, t-i*step, scrn));
				scrn.setArrayElement (0, calculateIndex(b)-i, calculateIndex(l));
			}
			sprFire.setPosition(sf::Vector2f(l , b - i*step));
			window.draw(sprFire);
		}
	}
	if (first)
	{
		first = false;
	}
	return;
}

list <list<bomb>::iterator> lst_iter;

void eventsInMenu (sf::Event &event, sf::RenderWindow &window, bool & in_menu, int txt1_x,int txt1_y, int txt2_x, int txt2_y)
{
	switch(event.type)
	{
		case sf::Event::Closed:
		{
			window.close();
		}
		break;
		case sf::Event::MouseButtonPressed:
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i mPos = sf::Mouse::getPosition(window);
				if ( mPos.x >= txt1_x && mPos.x <= (500) && mPos.y >= txt1_y && mPos.y <= (txt1_y+100) )
				{
					in_menu = false;
					startNewGame();
				}

				if ( mPos.x >= txt2_x && mPos.x <= (500) && mPos.y >= txt2_y && mPos.y <= (txt2_y+100) )
				{
					window.close();
				}
			}
		}
		break;
	}
}

void eventsInGame(sf::Event &event, sf::RenderWindow &window)
{
	switch (event.type)
	{
	case sf::Event::Closed:
		{
			window.close();
		}
		break;
	//========================================================================================= Keyboard
	case sf::Event::KeyPressed:
		{
			switch (event.key.code)
			{
			case (sf::Keyboard::Left):
				Main.MoveL(scrn, lvlup);
				break;
			case (sf::Keyboard::Right):
				Main.MoveR(scrn, lvlup);
				break;
			case (sf::Keyboard::Up):
				Main.MoveU(scrn, lvlup);
				break;
			case (sf::Keyboard::Down):
				Main.MoveD(scrn, lvlup);
				break;
			case (sf::Keyboard::Space):
				bombs.push_back(bomb (Main.l, Main.r, Main.b, Main.t));
				break;
			case (sf::Keyboard::E):
			{
				scrn.print();
			}
			break;
			case (sf::Keyboard::Escape):
				{
					window.close();
				}
			break;
			case (sf::Keyboard::A):
			{
				//NUM_LVL++;
				enemies.clear();
				//scrn.clearScreen();
			}
			break;
			}
		}
	}
}

void eventsAfterLosing(sf::Event &event, sf::RenderWindow &window, bool &in_menu)
{
	switch(event.type)
	{
	case sf::Event::MouseButtonPressed:
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i mPos = sf::Mouse::getPosition(window);
				if ( mPos.x >= 100 && mPos.x <= 200 && mPos.y >= 250 && mPos.y <= 350 )
				{
					scrn.setRun(true);
					in_menu = true;
				}

				if ( mPos.x >= 250 && mPos.x <= 350 && mPos.y >= 250 && mPos.y <= 300 )
				{
					window.close();
				}
			}
		}
	}
}
void eventsAfterWin(sf::Event &event, sf::RenderWindow &window, bool &in_menu, int x1, int y1, int x2, int y2)
{
	switch(event.type)
	{
	case sf::Event::MouseButtonPressed:
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i mPos = sf::Mouse::getPosition(window);
				if ( mPos.x >= x1 && mPos.x <= 500 && mPos.y >= y1 && mPos.y <= y1 + 100 )
				{
					scrn.setRun(true);
					in_menu = true;
				}

				if ( mPos.x >= x2 && mPos.x <= 500 && mPos.y >= y2 && mPos.y <= y2 + 100)
				{
					window.close();
				}
			}
		}
	}
}
void getText(sf::Text & txt, sf::Font & font,char* str, int x, int y, int size)
{
	txt.setFont(font); 
	txt.setString(str);
	txt.setColor(sf::Color::Black);
	txt.setPosition(x,y);
	txt.setCharacterSize(size);
}

void youWin (sf::Text & txt, sf::Font & font)
{
	txt.setFont(font); // font is a sf::Font

				// set the string to display
	txt.setString("You win !!!");
	txt.setColor(sf::Color::Black);
	txt.setPosition(100,100);
	txt.setCharacterSize(72);
}

int main ( int argc, char** argv)
{
	sf::RenderWindow window(sf::VideoMode(wW, wH), "MyDynablaster", sf::Style::Titlebar);

	sf::Clock clock;

	//==================================================================================================== Textures for objects
	
	sf::Texture texMainHero;
	texMainHero.loadFromFile("main_hero.png");
	sf::Sprite sprMainHero;
	sprMainHero.setTexture(texMainHero);

	sf::Texture texBrick;
	texBrick.loadFromFile("brick.png");
	sf::Sprite sprBrick;
	sprBrick.setTexture(texBrick);

	sf::Texture texEnemy;
	texEnemy.loadFromFile("enemy.png");
	sf::Sprite sprEnemy;
	sprEnemy.setTexture(texEnemy);

	sf::Texture texBomb;
	texBomb.loadFromFile("bomb.png");
	sf::Sprite sprBomb;
	sprBomb.setTexture(texBomb);

	sf::Texture texPortal;
	texPortal.loadFromFile("portal.png");
	sf::Sprite sprPortal;
	sprPortal.setTexture(texPortal);

	sf::Texture texFire;
	texFire.loadFromFile("fire.png");
	sf::Sprite sprFire;
	sprFire.setTexture(texFire);

	sf::Font font;
	if (!font.loadFromFile("font.ttf"))
	{
		return 3;
   	}

	
	//-----------------------------------------------------------------------------------------------Boolean variables	
	bool lvl_is_completed = false;
	bool in_menu = true;
	bool gamer_lose = false;
	// -----------------------------------------------------------------------------------------------Game
	while (window.isOpen())
    {
		sf::Event event;

		while ( in_menu)
		{
			window.clear(sf::Color::White);

			sf::Text txt1, txt2;
			const int txt1_x = 100, txt1_y=100;

			txt1.setFont(font);
			txt1.setString("Start game");
			txt1.setColor(sf::Color::Black);
			txt1.setPosition(txt1_x, txt1_y);
			txt1.setCharacterSize(72);
			window.draw(txt1);

			const int txt2_x = 100, txt2_y=180;
			txt2.setFont(font);
			txt2.setString("Exit");
			txt2.setColor(sf::Color::Black);
			txt2.setPosition(txt2_x,txt2_y);
			txt2.setCharacterSize(72);
			window.draw(txt2);

			window.display();
			while ( window.pollEvent(event))
			{
				eventsInMenu( event, window, in_menu, txt1_x, txt1_y, txt2_x, txt2_y);
			}
			
		}

		while ( window.pollEvent(event) )
		{
			if(scrn.getRun())
			{
				eventsInGame(event, window);
			}
			else
			{
				if(gamer_lose)
				{
					eventsAfterLosing (event, window, in_menu);
				}
				else
				{
					eventsAfterWin (event, window, in_menu, 100, 150, 100, 250);
				}
			}
		}

		//--------------------------------------------------------------------------------------------------------------------Draw
		window.clear(sf::Color::White);

		if (scrn.getRun() == true)
		{
			sprPortal.setPosition(sf::Vector2f(lvlup.l, lvlup.b));
			window.draw(sprPortal);

				if (! bricks.empty())
				{
					for (list<brick>::iterator i = bricks.begin(); i != bricks.end(); ++i)
					{
						sprBrick.setPosition(sf::Vector2f(i->l, i->b));
						window.draw(sprBrick);
					}
				}
				if (! enemies.empty())
				{

					sf::Time elapsed1 = clock.getElapsedTime();

					if (elapsed1.asSeconds() >= 0.5f)
					{
						for (list<enemy>::iterator i = enemies.begin(); i != enemies.end(); ++i)
						{

							i->motion(scrn, Main);
						}
						sf::Time elapsed1 = clock.restart();
					}
					for (list<enemy>::iterator i = enemies.begin(); i != enemies.end(); ++i)
					{	
						sprEnemy.setPosition(sf::Vector2f(i->l, i->b));
						window.draw(sprEnemy);
					}
				}
				if ( !bombs.empty())
				{
					for (list<bomb>::iterator i = bombs.begin(); i != bombs.end(); ++i)
					{
						sprBomb.setPosition(sf::Vector2f(i->l, i->b));

						if ( (i->clock).getElapsedTime().asSeconds() >= 3.0)
						{
							i->damage(window, sprFire);
							if ( (i->clock).getElapsedTime().asSeconds() > 5.0)
							{
								lst_iter.push_back(i);
							}

						}
						window.draw(sprBomb);
					}
				}
				sprMainHero.setPosition (sf::Vector2f (Main.l, Main.b));
				window.draw (sprMainHero);

				if ( enemies.empty() && Main.b == lvlup.b && Main.r ==lvlup.r)
				{
					std::cout<<NUM_LVL<<std::endl;
					if ( NUM_LVL < max_num_lvls -1)
					{
						levelUp();
					}
					else
					{
						std::cout<<"I'm here"<< std::endl;
						scrn.setRun(false); 
					}
				}
			}
			else
			{
				bricks.clear();
				bombs.clear();
				enemies.clear();
				scrn.clearScreen();
				scrn.setRun(false);

				sf::Text txt1, txt2, txt3, txt4;

				if ( NUM_LVL >= max_num_lvls - 1)
				{
					getText(txt1, font, "You Win!!", 100, 50, 72);
					window.draw(txt1);

					getText(txt2, font, "Back in menu", 100, 150, 72);
					window.draw(txt2);

					getText(txt3, font, "Exit", 100, 250, 72);
					window.draw(txt3);
				}
				else
				{
					gamer_lose = true;

					getText(txt1, font, "You lose", 100, 50, 72);
					window.draw(txt1);

					getText(txt2, font, "Try again?", 100, 150, 72);
					window.draw(txt2);

					getText(txt3, font, "Yes", 100, 250, 72);
					window.draw(txt3);

					getText(txt4, font, "No", 250, 250, 72);
					window.draw(txt4);
				}
			}

			window.display();
			
			if ( bombs.size() != 0)
			{ 
				for (list<list<bomb>::iterator>::iterator i = lst_iter.begin(); i != lst_iter.end(); ++i)
				{
					bombs.remove( *(*i));
				}
				lst_iter.clear();
			}
	} //while (window.isOpen())

    return 0;
}