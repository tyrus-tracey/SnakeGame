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
#include "Snake.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd( gfx )
{
	brd.Initialize();
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::control(Location& loc)
{
	if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
		loc.x = 1;
		loc.y = 0;
	} else if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
		loc.x = -1;
		loc.y = 0;
	} else if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
		loc.x = 0;
		loc.y = 1;
	} else if (wnd.kbd.KeyIsPressed(VK_UP)) {
		loc.x = 0;
		loc.y = -1;
	}
}

void Game::UpdateModel()
{
	control(input);
	if (wnd.kbd.KeyIsPressed(VK_CONTROL)) {
		player.Grow();
	}

	FRAME_COUNT++;
	if (FRAME_COUNT >= FRAME_LIMITER) {
		FRAME_COUNT = 0;
		player.MoveBy(input);

		if (player.Snake_Collision() == 1 ||
			brd.Clamp(player.getHeadLoc()) == 1) {
			//GAME OVER//
			player.~Snake();
			Bordercolor = Colors::Red;
		}

		player.Consume(brd);
	}
}

void Game::ComposeFrame()
{
	std::uniform_int_distribution<int> ColorDist( 0, 255 );
	player.Limiter(brd);
	brd.DrawBorders(Bordercolor);
	player.Draw(brd);
	brd.getApple().Draw(brd);
}
