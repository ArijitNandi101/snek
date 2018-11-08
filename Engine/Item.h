#pragma once
#include "Board.h"
#include "Snake.h"
#include <random>
class ObstacleManager;

class Item {
public:
	Item(const Board& brd, const Snake& snek, const ObstacleManager& obstacles);
	void respawn(const Snake& snek, const ObstacleManager& obstacles);
	void draw(Board& brd) const;
	const Location& getLocation() const;
	bool contains(const Location& target) const;
private:
	static constexpr Color itemColor = Colors::Red;
	std::mt19937 rng;
	std::uniform_int_distribution<int> xDist;
	std::uniform_int_distribution<int> yDist;
	Location loc;
	Color c;
};