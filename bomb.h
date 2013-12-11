#ifndef _BOMB_H_
#define _BOMB_H_

#include "hero.h"
#include "enemy.h"

int i;
void boom (int);

class bomb
{
public:
	int l, r, b, t, dst;
	bool isburned, first;
	sf::Clock clock;
	sf::Time elapsed;

	bomb (): l(0), r(0), b(0), t(0), dst(0){}
	bomb ( int _l, int _r, int _b, int _t):	l(_l), r(_r), b(_b), t(_t), dst(3), isburned(false), first(true)
	{
		i = 0;
		elapsed = clock.restart();
	}
	void damage (sf::RenderWindow&, sf::Sprite&);
};

bool operator == (const bomb& x1, const bomb& x2)
{
	return (x1.l == x2.l && x1.b ==x2.b );
}

#endif