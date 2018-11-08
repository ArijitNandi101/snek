#pragma once
#include "Graphics.h"
#include "Location.h"
#include <Assert.h>
class Board {
private:
	static constexpr int dimention = 20;
	static constexpr int width = Graphics::ScreenWidth/dimention;
	static constexpr int height = Graphics::ScreenHeight/dimention;
	static constexpr Color backgroundColor = Colors::LightGray;
	Graphics& gfx;
public:
	Board(Graphics&);
	void DrawCell(const Location&, Color);
	int getGridWidth() const;
	int getGridHeight() const;
	void DrawBackground();
	bool checkCollision(Location nextHeadLoc);
};