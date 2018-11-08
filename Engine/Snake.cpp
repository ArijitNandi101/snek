#include "Snake.h"
#include "Location.h"

Snake::Snake(const Location& initLoc)
{
	constexpr int nBodyColors = 4;
	constexpr Color bodyColors[nBodyColors] = 
	{
		{20, 100, 32},
		{20, 130, 48},
		{20, 160, 48},
		{20, 130, 48}
	};
	for (int i = 0; i < nSegmentsMax; i++) {
		segments[i].initBody(bodyColors[ i%nBodyColors ]);
	}
	this -> initLoc = initLoc;
	reset();
}

void Snake::moveBy(const Location& delta_loc)
{
	for (int i = nSegments-1; i > 0; i--)
		segments[i].follow(segments[i - 1]);
	segments[0].moveBy(delta_loc);
}

void Snake::grow()
{
	if (nSegments < nSegmentsMax)
	{
		nSegments++;
	}
}

void Snake::draw(Board& brd)
{
	for (int i = 0; i < nSegments; i++)
		segments[i].draw(brd);
}

void Snake::Segment::initHead(const Location& loc, const Color c)
{
	this -> loc = loc;
	this -> c = c;
}

void Snake::Segment::initBody( Color bodyColor )
{	
	c = bodyColor;
}

void Snake::Segment::follow(const Segment & nextSegment)
{	
	loc = nextSegment.getLocation();
}

void Snake::Segment::moveBy(const Location & delta_loc)
{	
	loc.add(delta_loc);
}

const Location& Snake::Segment::getLocation() const
{
	return loc;
}

void Snake::Segment::setLocation(const Location& loc)
{
	this -> loc = loc;
}

void Snake::Segment::draw(Board & brd)
{
	brd.DrawCell(loc, c);
}

const Location& Snake::getHeadLocation() const
{
	return segments[0].getLocation();
}

bool Snake::headInBody()
{
	for (int i = 1; i < nSegments; i++) {
		if (segments[0].getLocation() == segments[i].getLocation())
			return true;
	}
	return false;
}

bool Snake::contains(const Location & target) const
{
	for(int i = 0 ;i < nSegments; i++)
	{
		if (segments[i].getLocation() == target)
			return true;
	}
	return false;
}

void Snake::reset()
{
	nSegments = 1;
	segments[0].initHead(initLoc, headColor);
	while (nSegments < 3)
	{
		grow();
		moveBy({ 1,0 });
	}
}

const int Snake::numberOfSegments() const
{
	return nSegments;
}
