#pragma once
#include "Board.h"
class Snake {
public:
	Snake(const Location& initLoc);
	void moveBy(const Location& delta_loc);
	void grow();
	void draw(Board& brd);
	const Location& getHeadLocation() const;
	bool headInBody();
	bool contains(const Location& target) const;
	void reset();
	const int numberOfSegments() const;
private:
	class Segment {
	public:
		void initHead(const Location& loc, const Color c);
		void initBody(Color bodyColor);
		void follow(const Segment& nextSegment);
		void moveBy(const Location& delta_loc);
		const Location& getLocation() const;
		void setLocation(const Location& loc);
		void draw(Board& brd);
	private:
		Location loc;
		Color c;
	};
private:
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments;
	Location initLoc;
	static constexpr Color headColor = Colors::Yellow;
};