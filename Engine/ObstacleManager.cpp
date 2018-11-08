#include "ObstacleManager.h"

ObstacleManager::ObstacleManager(const Board& brd )
	:
	nObstacles( 0 ),
	rng( std::random_device()() ),
	xDist( 2,brd.getGridWidth()-3 ),
	yDist( 2,brd.getGridHeight()-3)
{
}

void ObstacleManager::spawn(const Snake& snek, const Item& item)
{
	if (nObstacles < nObstaclesMax)
	{
		Location newLoc;
		do {
			newLoc.x = xDist(rng);
			newLoc.y = yDist(rng);
		} while (snek.contains(newLoc) || item.contains(newLoc));
		obstacles[nObstacles].initObstacle(newLoc);
		nObstacles++;
	}
}

void ObstacleManager::draw(Board& brd)
{
	for (int i = 0; i < nObstacles; i++)
		obstacles[i].draw(brd);
}

bool ObstacleManager::contains(const Location& target) const
{
	for (int i = 0; i < nObstacles; i++)
		if (obstacles[i].getLocation() == target)
			return true;
	return false;
}

void ObstacleManager::reset()
{
	nObstacles = 0;
}

void ObstacleManager::Obstacle::draw(Board& brd)
{
	brd.DrawCell(loc, c);
}

const Location& ObstacleManager::Obstacle::getLocation() const
{
	return loc;
}

void ObstacleManager::Obstacle::initObstacle(const Location& newLoc)
{
	loc.x = newLoc.x;
	loc.y = newLoc.y;
	c = obstacleColor;
}
