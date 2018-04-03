#include "Point.h"




void Point::changeDirWithoutTermsOfStuckSituation(Direction dir) {
	switch (dir) {
	case Direction::LEFT:
		dir_x = -1;
		dir_y = 0;
		break;
	case Direction::RIGHT:
		dir_x = 1;
		dir_y = 0;
		break;
	case Direction::UP:
		dir_x = 0;
		dir_y = -1;

		break;
	case Direction::DOWN:
		dir_x = 0;
		dir_y = 1;
		break;
	}
}
void Point::changeDir(Direction dir) {
	switch (dir) {
	case Direction::LEFT:
		if (dir_x != 1)
		{
			dir_x = -1;
			dir_y = 0;
		}
		break;
	case Direction::RIGHT:
		if (dir_x != -1)
		{
			dir_x = 1;
			dir_y = 0;
		}
		break;
	case Direction::UP:
		if (dir_y != 1)
		{
			dir_x = 0;
			dir_y = -1;
		}
		break;
	case Direction::DOWN:
		if (dir_y != -1)
		{
			dir_x = 0;
			dir_y = 1;
		}
		break;

	default: break;



	}
}


void Point::move(Direction dir, bool stuckR, bool stuckL, bool stuckU, bool stuckD)
{

	bool flag;
	flag = isStuckequaldirection(dir, stuckR, stuckL, stuckU, stuckD);
	if (!flag)
	{

		changeDir(dir);
		moveImpl();
	}
	
}

bool Point::isStuckequaldirection(Direction dir, bool stuckR,bool stuckL,bool stuckU, bool stuckD)
{
	if (dir == RIGHT&&stuckR == true)
		return true;
	if (dir == LEFT&&stuckL == true)
		return true;
	if (dir == UP&&stuckU == true)
		return true;
	if (dir == DOWN&&stuckD == true)
		return true;
	else
		return false;
}
