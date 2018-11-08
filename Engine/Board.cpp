#include "Board.h"

Board::Board(Graphics& gfx)
	:
	gfx( gfx )
{	
}

void Board::DrawCell(const Location & loc, Color c)
{	
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	gfx.DrawRectDim(loc.x*dimention+1, loc.y*dimention+1, dimention-2, dimention-2, c);
}

int Board::getGridWidth() const
{
	return width;
}

int Board::getGridHeight() const
{
	return height;
}

void Board::DrawBackground()
{
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			DrawCell({ x,y }, backgroundColor);
}

bool Board::checkCollision(Location nextHeadLoc)
{
	if (nextHeadLoc.x < 0 || nextHeadLoc.x >= width
		|| nextHeadLoc.y < 0 || nextHeadLoc.y >= height)
		return true;
	return false;
}
