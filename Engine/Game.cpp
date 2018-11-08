/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd( gfx ),
	snek({ 19,19 }),
	obstacles( brd ),
	updateTimer( 0 ),
	delta_loc({ 1,0 }),
	gameIsStarted( false ),
	gameIsOver( false ),
	gameIsPaused( false ),
	pauseIsPressed( false ),
	item( brd,snek,obstacles ),
	deltaSpeed( 0.0 )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (gameIsStarted)
	{
		if (!pauseIsPressed && wnd.kbd.KeyIsPressed('P'))
		{
			pauseIsPressed = true;
			gameIsPaused = !gameIsPaused;
		}
		else
		{
			pauseIsPressed = wnd.kbd.KeyIsPressed('P');
		}

		if (!gameIsOver && !gameIsPaused)
		{	//UPDATE LOGIC
			setDeltaLoc(wnd.kbd.KeyIsPressed(VK_UP),
				wnd.kbd.KeyIsPressed(VK_DOWN),
				wnd.kbd.KeyIsPressed(VK_RIGHT),
				wnd.kbd.KeyIsPressed(VK_LEFT));
			updateSnek(delta_loc);

			//GAME OVER LOGIC
			gameIsOver = (brd.checkCollision(snek.getHeadLocation()) 
				|| snek.headInBody() 
				|| obstacles.contains(snek.getHeadLocation()));
		}
		//RESTART LOGIC
		else if (!gameIsPaused && wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			gameIsOver = false;
			gameIsPaused = false;
			delta_loc = { 1,0 };
			deltaSpeed = 0.0;
			snek.reset();
			obstacles.reset();
			item.respawn(snek, obstacles);
		}
	}
	else if (wnd.kbd.KeyIsPressed(VK_RETURN))
		gameIsStarted = true;
}


void Game::ComposeFrame()
{
	//brd.DrawBackground();
	if (gameIsStarted)
	{
		if (gameIsOver)
			SpriteCodex::DrawGameIsOverScreen(gfx, gfx.ScreenWidth / 2 - 42, gfx.ScreenHeight / 2 - 32);
		else
		{
			obstacles.draw(brd);
			item.draw(brd);
			snek.draw(brd);
		}
	}
	else {
		SpriteCodex::DrawTitleScreen(gfx, gfx.ScreenWidth/2-110, gfx.ScreenHeight/2-90);
	}
}


//HELPER METHODS
void Game::setDeltaLoc(bool up, bool down, bool right, bool left)
{
	if (up)
		delta_loc = { 0,-1 };
	else if (down)
		delta_loc = { 0,1 };
	else if (right)
		delta_loc = { 1,0 };
	else if (left)
		delta_loc = { -1,0 };
}
void Game::updateSnek(const Location& delta_loc)
{
	updateTimer++;
	if (updateTimer >= updatePeriod-(int)deltaSpeed)
	{	
		if (snek.contains(item.getLocation()))
		{
			if(deltaSpeed<=5)
				deltaSpeed+=speedFactor;
			//SNEK GROWS
			snek.grow();
			//SPawing NEW OBSTACLES
			if (snek.numberOfSegments() % 8 == 0)
			{
				obstacles.spawn(snek, item);
			}
			//RESPAWNING ITEM
			item.respawn(snek, obstacles);
		}
		updateTimer = 0;
		snek.moveBy(delta_loc);
	}
}