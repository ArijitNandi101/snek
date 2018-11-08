#pragma once
#include "Board.h"
#include "Snake.h"
#include "Item.h"
#include <random>

class ObstacleManager {
public:
	ObstacleManager(const Board& brd);
	void spawn(const Snake& snek, const Item& item);
	void draw(Board& brd);
	bool contains(const Location& target) const;
	void reset();
private:
	class Obstacle {
	public:
		Location loc;
		Color c;
	public:
		void draw(Board& brd);
		const Location& getLocation() const;
		void initObstacle(const Location& newLoc);
	};
private:
	static constexpr int nObstaclesMax = 100;
	static constexpr Color obstacleColor = Colors::LightGray;
	Obstacle obstacles[100];
	int nObstacles;
	std::mt19937 rng;
	std::uniform_int_distribution<int> xDist;
	std::uniform_int_distribution<int> yDist;
};