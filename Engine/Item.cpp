#include "Item.h"
#include "ObstacleManager.h"

Item::Item(const Board& brd, const Snake& snek, const ObstacleManager& obstacles)
	:
	rng( std::random_device()() ),
	xDist(0,brd.getGridWidth()-1),
	yDist(0,brd.getGridHeight()-1),
	loc({ 0,0 }),
	c(itemColor)
	
{
	respawn(snek, obstacles);
}

void Item::respawn(const Snake& snek, const ObstacleManager& obstacles)
{
	do {
		loc.x = xDist(rng);
		loc.y = yDist(rng);
	} while (snek.contains(loc) || obstacles.contains(loc));
}

void Item::draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

const Location& Item::getLocation() const
{
	return loc;
}

bool Item::contains(const Location& target) const
{
	if (loc == target)
		return true;
	return false;
}
