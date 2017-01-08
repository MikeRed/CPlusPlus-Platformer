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
	gfx( wnd )
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

	if (wnd.kbd.KeyIsPressed(VK_UP) && grounded)
	{
		grounded = false;
	}

	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		y_mobile = y_mobile + 2;
	}

	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		x_mobile = x_mobile - 2;
		forward = false;
	}

	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		x_mobile = x_mobile + 2;
		forward = true;
	}
	if (!bulletIsFired)
	{
		if (wnd.kbd.KeyIsPressed(VK_SPACE))
		{
			bulletIsFired = true;
			bulletDirection = forward;
			if (forward)
				bX = x_mobile + 8;
			else
				bX = x_mobile - 8;
			bY = y_mobile;
		}
	}

	if (!grounded)
		jump();

	if (OverlapTest(bX, bY, x_enemy, y_enemy))
		enemy_alive = false;
	
	x_mobile = ClampScreenX(x_mobile);
	y_mobile = ClampScreenY(y_mobile);
}

void Game::jump()
{
	if (!apexReached && y_mobile > gfx.ScreenHeight - 50)
		y_mobile -= 2;
	else
		apexReached = true;

	if (apexReached && y_mobile < groundHeight)
		y_mobile += 2;

	if (y_mobile == groundHeight)
	{
		grounded = true;
		apexReached = false;
	}
		

}

void Game::ComposeFrame()
{	
	DrawPlayer(x_mobile, y_mobile, 255, 255, 255);
	
	DrawDirection(x_mobile, y_mobile, forward);

	if (bulletIsFired)
	{
		if (bulletDirection)
		{
			if (bX + 2 <= gfx.ScreenWidth - 1)
			{
				DrawBullet(bX, bY, bulletDirection);
				bX += 8;
			}

			else
				bulletIsFired = false;
		}
		else
		{
			if (bX - 2 >= 1)
			{
				DrawBullet(bX, bY, bulletDirection);
				bX -= 8;
			}
			else
				bulletIsFired = false;
		}
	}

	if (enemy_alive)
		DrawEnemy(x_enemy, y_enemy, 255, 0, 0);
}

void Game::DrawBox(int x, int y, int r, int g, int b)
{
	gfx.PutPixel(-5 + x,  y    , r, g, b);
	gfx.PutPixel(-4 + x,  y    , r, g, b);
	gfx.PutPixel(-3 + x,  y    , r, g, b);
	gfx.PutPixel( 3 + x,  y    , r, g, b);
	gfx.PutPixel( 4 + x,  y    , r, g, b);
	gfx.PutPixel( 5 + x,  y    , r, g, b);
	gfx.PutPixel( x    ,  3 + y, r, g, b);
	gfx.PutPixel( x    ,  4 + y, r, g, b);
	gfx.PutPixel( x    ,  5 + y, r, g, b);
	gfx.PutPixel( x    , -5 + y, r, g, b);
	gfx.PutPixel( x    , -4 + y, r, g, b);
	gfx.PutPixel( x    , -3 + y, r, g, b);
}

void Game::DrawEnemy(int x, int y, int r, int g, int b)
{

	gfx.PutPixel(8 + x, y + 8, r, g, b);
	gfx.PutPixel(7 + x, y + 8, r, g, b);
	gfx.PutPixel(6 + x, y + 8, r, g, b);
	gfx.PutPixel(5 + x, y + 8, r, g, b);
	gfx.PutPixel(4 + x, y + 8, r, g, b);
	gfx.PutPixel(3 + x, y + 8, r, g, b);
	gfx.PutPixel(2 + x, y + 8, r, g, b);
	gfx.PutPixel(1 + x, y + 8, r, g, b);
	gfx.PutPixel(-8 + x, y + 8, r, g, b);
	gfx.PutPixel(-7 + x, y + 8, r, g, b);
	gfx.PutPixel(-6 + x, y + 8, r, g, b);
	gfx.PutPixel(-5 + x, y + 8, r, g, b);
	gfx.PutPixel(-4 + x, y + 8, r, g, b);
	gfx.PutPixel(-3 + x, y + 8, r, g, b);
	gfx.PutPixel(-2 + x, y + 8, r, g, b);
	gfx.PutPixel(-1 + x, y + 8, r, g, b);
	gfx.PutPixel(x, y + 8, r, g, b);

	gfx.PutPixel(8 + x, y - 8, r, g, b);
	gfx.PutPixel(7 + x, y - 8, r, g, b);
	gfx.PutPixel(6 + x, y - 8, r, g, b);
	gfx.PutPixel(5 + x, y - 8, r, g, b);
	gfx.PutPixel(4 + x, y - 8, r, g, b);
	gfx.PutPixel(3 + x, y - 8, r, g, b);
	gfx.PutPixel(2 + x, y - 8, r, g, b);
	gfx.PutPixel(1 + x, y - 8, r, g, b);
	gfx.PutPixel(-8 + x, y - 8, r, g, b);
	gfx.PutPixel(-7 + x, y - 8, r, g, b);
	gfx.PutPixel(-6 + x, y - 8, r, g, b);
	gfx.PutPixel(-5 + x, y - 8, r, g, b);
	gfx.PutPixel(-4 + x, y - 8, r, g, b);
	gfx.PutPixel(-3 + x, y - 8, r, g, b);
	gfx.PutPixel(-2 + x, y - 8, r, g, b);
	gfx.PutPixel(-1 + x, y - 8, r, g, b);
	gfx.PutPixel(x, y - 8, r, g, b);

	gfx.PutPixel(x + 8, y - 1, r, g, b);
	gfx.PutPixel(x + 8, y - 2, r, g, b);
	gfx.PutPixel(x + 8, y - 3, r, g, b);
	gfx.PutPixel(x + 8, y - 4, r, g, b);
	gfx.PutPixel(x + 8, y - 5, r, g, b);
	gfx.PutPixel(x + 8, y - 6, r, g, b);
	gfx.PutPixel(x + 8, y - 7, r, g, b);
	gfx.PutPixel(x + 8, y - 8, r, g, b);
	gfx.PutPixel(x + 8, y + 0, r, g, b);
	gfx.PutPixel(x + 8, y + 1, r, g, b);
	gfx.PutPixel(x + 8, y + 2, r, g, b);
	gfx.PutPixel(x + 8, y + 3, r, g, b);
	gfx.PutPixel(x + 8, y + 4, r, g, b);
	gfx.PutPixel(x + 8, y + 5, r, g, b);
	gfx.PutPixel(x + 8, y + 6, r, g, b);
	gfx.PutPixel(x + 8, y + 7, r, g, b);
	gfx.PutPixel(x + 8, y + 8, r, g, b);

	gfx.PutPixel(x - 8, y - 1, r, g, b);
	gfx.PutPixel(x - 8, y - 2, r, g, b);
	gfx.PutPixel(x - 8, y - 3, r, g, b);
	gfx.PutPixel(x - 8, y - 4, r, g, b);
	gfx.PutPixel(x - 8, y - 5, r, g, b);
	gfx.PutPixel(x - 8, y - 6, r, g, b);
	gfx.PutPixel(x - 8, y - 7, r, g, b);
	gfx.PutPixel(x - 8, y - 8, r, g, b);
	gfx.PutPixel(x - 8, y + 0, r, g, b);
	gfx.PutPixel(x - 8, y + 1, r, g, b);
	gfx.PutPixel(x - 8, y + 2, r, g, b);
	gfx.PutPixel(x - 8, y + 3, r, g, b);
	gfx.PutPixel(x - 8, y + 4, r, g, b);
	gfx.PutPixel(x - 8, y + 5, r, g, b);
	gfx.PutPixel(x - 8, y + 6, r, g, b);
	gfx.PutPixel(x - 8, y + 7, r, g, b);
	gfx.PutPixel(x - 8, y + 8, r, g, b);
}

void Game::DrawPlayer(int x, int y, int r, int g, int b)
{

	gfx.PutPixel( 8 + x, y + 8, r, g, b);
	gfx.PutPixel( 7 + x, y + 8, r, g, b);
	gfx.PutPixel( 6 + x, y + 8, r, g, b);
	gfx.PutPixel( 5 + x, y + 8, r, g, b);
	gfx.PutPixel( 4 + x, y + 8, r, g, b);
	gfx.PutPixel( 3 + x, y + 8, r, g, b);
	gfx.PutPixel( 2 + x, y + 8, r, g, b);
	gfx.PutPixel( 1 + x, y + 8, r, g, b);
	gfx.PutPixel(-8 + x, y + 8, r, g, b);
	gfx.PutPixel(-7 + x, y + 8, r, g, b);
	gfx.PutPixel(-6 + x, y + 8, r, g, b);
	gfx.PutPixel(-5 + x, y + 8, r, g, b);
	gfx.PutPixel(-4 + x, y + 8, r, g, b);
	gfx.PutPixel(-3 + x, y + 8, r, g, b);
	gfx.PutPixel(-2 + x, y + 8, r, g, b);
	gfx.PutPixel(-1 + x, y + 8, r, g, b);
	gfx.PutPixel(     x, y + 8, r, g, b);

	gfx.PutPixel(8 + x, y - 8, r, g, b);
	gfx.PutPixel(7 + x, y - 8, r, g, b);
	gfx.PutPixel(6 + x, y - 8, r, g, b);
	gfx.PutPixel(5 + x, y - 8, r, g, b);
	gfx.PutPixel(4 + x, y - 8, r, g, b);
	gfx.PutPixel(3 + x, y - 8, r, g, b);
	gfx.PutPixel(2 + x, y - 8, r, g, b);
	gfx.PutPixel(1 + x, y - 8, r, g, b);
	gfx.PutPixel(-8 + x, y - 8, r, g, b);
	gfx.PutPixel(-7 + x, y - 8, r, g, b);
	gfx.PutPixel(-6 + x, y - 8, r, g, b);
	gfx.PutPixel(-5 + x, y - 8, r, g, b);
	gfx.PutPixel(-4 + x, y - 8, r, g, b);
	gfx.PutPixel(-3 + x, y - 8, r, g, b);
	gfx.PutPixel(-2 + x, y - 8, r, g, b);
	gfx.PutPixel(-1 + x, y - 8, r, g, b);
	gfx.PutPixel(x, y - 8, r, g, b);

	gfx.PutPixel(x + 8, y - 1, r, g, b);
	gfx.PutPixel(x + 8, y - 2, r, g, b);
	gfx.PutPixel(x + 8, y - 3, r, g, b);
	gfx.PutPixel(x + 8, y - 4, r, g, b);
	gfx.PutPixel(x + 8, y - 5, r, g, b);
	gfx.PutPixel(x + 8, y - 6, r, g, b);
	gfx.PutPixel(x + 8, y - 7, r, g, b);
	gfx.PutPixel(x + 8, y - 8, r, g, b);
	gfx.PutPixel(x + 8, y + 0, r, g, b);
	gfx.PutPixel(x + 8, y + 1, r, g, b);
	gfx.PutPixel(x + 8, y + 2, r, g, b);
	gfx.PutPixel(x + 8, y + 3, r, g, b);
	gfx.PutPixel(x + 8, y + 4, r, g, b);
	gfx.PutPixel(x + 8, y + 5, r, g, b);
	gfx.PutPixel(x + 8, y + 6, r, g, b);
	gfx.PutPixel(x + 8, y + 7, r, g, b);
	gfx.PutPixel(x + 8, y + 8, r, g, b);

	gfx.PutPixel(x - 8, y - 1, r, g, b);
	gfx.PutPixel(x - 8, y - 2, r, g, b);
	gfx.PutPixel(x - 8, y - 3, r, g, b);
	gfx.PutPixel(x - 8, y - 4, r, g, b);
	gfx.PutPixel(x - 8, y - 5, r, g, b);
	gfx.PutPixel(x - 8, y - 6, r, g, b);
	gfx.PutPixel(x - 8, y - 7, r, g, b);
	gfx.PutPixel(x - 8, y - 8, r, g, b);
	gfx.PutPixel(x - 8, y + 0, r, g, b);
	gfx.PutPixel(x - 8, y + 1, r, g, b);
	gfx.PutPixel(x - 8, y + 2, r, g, b);
	gfx.PutPixel(x - 8, y + 3, r, g, b);
	gfx.PutPixel(x - 8, y + 4, r, g, b);
	gfx.PutPixel(x - 8, y + 5, r, g, b);
	gfx.PutPixel(x - 8, y + 6, r, g, b);
	gfx.PutPixel(x - 8, y + 7, r, g, b);
	gfx.PutPixel(x - 8, y + 8, r, g, b);

}

void Game::DrawDirection(int x, int y, bool forward) 
{
	if (forward)
	{
		gfx.PutPixel(x + 4, y,     255, 0, 0);
		gfx.PutPixel(x + 3, y + 1, 255, 0, 0);
		gfx.PutPixel(x + 3, y - 1, 255, 0, 0);
		gfx.PutPixel(x + 2, y + 2, 255, 0, 0);
		gfx.PutPixel(x + 2, y - 2, 255, 0, 0);
		gfx.PutPixel(x + 1, y + 3, 255, 0, 0);
		gfx.PutPixel(x + 1, y - 3, 255, 0, 0);
		gfx.PutPixel(x,     y + 4, 255, 0, 0);
		gfx.PutPixel(x,     y - 4, 255, 0, 0);

		gfx.PutPixel(x + 5, y,     255, 0, 0);
		gfx.PutPixel(x + 4, y + 1, 255, 0, 0);
		gfx.PutPixel(x + 4, y - 1, 255, 0, 0);
		gfx.PutPixel(x + 3, y + 2, 255, 0, 0);
		gfx.PutPixel(x + 3, y - 2, 255, 0, 0);
		gfx.PutPixel(x + 2, y + 3, 255, 0, 0);
		gfx.PutPixel(x + 2, y - 3, 255, 0, 0);
		gfx.PutPixel(x + 1, y + 4, 255, 0, 0);
		gfx.PutPixel(x + 1, y - 4, 255, 0, 0);
		gfx.PutPixel(x,     y + 5, 255, 0, 0);
		gfx.PutPixel(x,     y - 5, 255, 0, 0);

		gfx.PutPixel(x + 6, y,     255, 0, 0);
		gfx.PutPixel(x + 5, y + 1, 255, 0, 0);
		gfx.PutPixel(x + 5, y - 1, 255, 0, 0);
		gfx.PutPixel(x + 4, y + 2, 255, 0, 0);
		gfx.PutPixel(x + 4, y - 2, 255, 0, 0);
		gfx.PutPixel(x + 3, y + 3, 255, 0, 0);
		gfx.PutPixel(x + 3, y - 3, 255, 0, 0);
		gfx.PutPixel(x + 2, y + 4, 255, 0, 0);
		gfx.PutPixel(x + 2, y - 4, 255, 0, 0);
		gfx.PutPixel(x + 1, y + 5, 255, 0, 0);
		gfx.PutPixel(x + 1, y - 5, 255, 0, 0);
		gfx.PutPixel(x,     y + 6, 255, 0, 0);
		gfx.PutPixel(x,     y - 6, 255, 0, 0);

		gfx.PutPixel(x + 7, y,     255, 0, 0);
		gfx.PutPixel(x + 6, y + 1, 255, 0, 0);
		gfx.PutPixel(x + 6, y - 1, 255, 0, 0);
		gfx.PutPixel(x + 5, y + 2, 255, 0, 0);
		gfx.PutPixel(x + 5, y - 2, 255, 0, 0);
		gfx.PutPixel(x + 4, y + 3, 255, 0, 0);
		gfx.PutPixel(x + 4, y - 3, 255, 0, 0);
		gfx.PutPixel(x + 3, y + 4, 255, 0, 0);
		gfx.PutPixel(x + 3, y - 4, 255, 0, 0);
		gfx.PutPixel(x + 2, y + 5, 255, 0, 0);
		gfx.PutPixel(x + 2, y - 5, 255, 0, 0);
		gfx.PutPixel(x + 1, y + 6, 255, 0, 0);
		gfx.PutPixel(x + 1, y - 6, 255, 0, 0);
		gfx.PutPixel(x,     y + 7, 255, 0, 0);
		gfx.PutPixel(x,     y - 7, 255, 0, 0);

	}
	else
	{
		gfx.PutPixel(x - 4, y,     255, 0, 0);
		gfx.PutPixel(x - 3, y + 1, 255, 0, 0);
		gfx.PutPixel(x - 3, y - 1, 255, 0, 0);
		gfx.PutPixel(x - 2, y + 2, 255, 0, 0);
		gfx.PutPixel(x - 2, y - 2, 255, 0, 0);
		gfx.PutPixel(x - 1, y + 3, 255, 0, 0);
		gfx.PutPixel(x - 1, y - 3, 255, 0, 0);
		gfx.PutPixel(x,     y + 4, 255, 0, 0);
		gfx.PutPixel(x,     y - 4, 255, 0, 0);

		gfx.PutPixel(x - 5, y, 255, 0, 0);
		gfx.PutPixel(x - 4, y + 1, 255, 0, 0);
		gfx.PutPixel(x - 4, y - 1, 255, 0, 0);
		gfx.PutPixel(x - 3, y + 2, 255, 0, 0);
		gfx.PutPixel(x - 3, y - 2, 255, 0, 0);
		gfx.PutPixel(x - 2, y + 3, 255, 0, 0);
		gfx.PutPixel(x - 2, y - 3, 255, 0, 0);
		gfx.PutPixel(x - 1, y + 4, 255, 0, 0);
		gfx.PutPixel(x - 1, y - 4, 255, 0, 0);
		gfx.PutPixel(x,     y + 5, 255, 0, 0);
		gfx.PutPixel(x,     y - 5, 255, 0, 0);

		gfx.PutPixel(x - 6,     y, 255, 0, 0);
		gfx.PutPixel(x - 5, y + 1, 255, 0, 0);
		gfx.PutPixel(x - 5, y - 1, 255, 0, 0);
		gfx.PutPixel(x - 4, y + 2, 255, 0, 0);
		gfx.PutPixel(x - 4, y - 2, 255, 0, 0);
		gfx.PutPixel(x - 3, y + 3, 255, 0, 0);
		gfx.PutPixel(x - 3, y - 3, 255, 0, 0);
		gfx.PutPixel(x - 2, y + 4, 255, 0, 0);
		gfx.PutPixel(x - 2, y - 4, 255, 0, 0);
		gfx.PutPixel(x - 1, y + 5, 255, 0, 0);
		gfx.PutPixel(x - 1, y - 5, 255, 0, 0);
		gfx.PutPixel(x,     y + 6, 255, 0, 0);
		gfx.PutPixel(x,     y - 6, 255, 0, 0);

		gfx.PutPixel(x - 7, y,     255, 0, 0);
		gfx.PutPixel(x - 6, y + 1, 255, 0, 0);
		gfx.PutPixel(x - 6, y - 1, 255, 0, 0);
		gfx.PutPixel(x - 5, y + 2, 255, 0, 0);
		gfx.PutPixel(x - 5, y - 2, 255, 0, 0);
		gfx.PutPixel(x - 4, y + 3, 255, 0, 0);
		gfx.PutPixel(x - 4, y - 3, 255, 0, 0);
		gfx.PutPixel(x - 3, y + 4, 255, 0, 0);
		gfx.PutPixel(x - 3, y - 4, 255, 0, 0);
		gfx.PutPixel(x - 2, y + 5, 255, 0, 0);
		gfx.PutPixel(x - 2, y - 5, 255, 0, 0);
		gfx.PutPixel(x - 1, y + 6, 255, 0, 0);
		gfx.PutPixel(x - 1, y - 6, 255, 0, 0);
		gfx.PutPixel(x,     y + 7, 255, 0, 0);
		gfx.PutPixel(x,     y - 7, 255, 0, 0);
	}
}

void Game::DrawBullet(int x, int y, bool bulletDirection)
{
	if (bulletDirection)
	{
		gfx.PutPixel(x, y - 1, 255, 0, 0);
		gfx.PutPixel(x + 1, y - 1, 255, 0, 0);
		gfx.PutPixel(x + 2, y - 1, 255, 0, 0);
		gfx.PutPixel(x + 1, y - 2, 255, 0, 0);
		gfx.PutPixel(x + 1, y, 255, 0, 0);
	}
	else
	{
		gfx.PutPixel(x, y - 1, 255, 0, 0);
		gfx.PutPixel(x - 1, y - 1, 255, 0, 0);
		gfx.PutPixel(x - 2, y - 1, 255, 0, 0);
		gfx.PutPixel(x - 1, y - 2, 255, 0, 0);
		gfx.PutPixel(x - 1, y, 255, 0, 0);
	}
}

bool Game::OverlapTest(int box0x, int box0y, int box1x, int box1y)
{
	const int left_box0 = box0x - 8;
	const int right_box0 = box0x + 8;
	const int top_box0 = box0y - 8;
	const int bottom_box0 = box0y + 8;

	const int left_box1 = box1x - 8;
	const int right_box1 = box1x + 8;
	const int top_box1 = box1y - 8;
	const int bottom_box1 = box1y + 8;
	
	return
		left_box0 <= right_box1 &&
		right_box0 >= left_box1 &&
		top_box0 <= bottom_box1 &&
		bottom_box0 >= top_box1;
}

int Game::ClampScreenX(int x)
{
	const int left = x - 8;
	const int right = x + 8;
	if (left < 0)
		return 8;
	else if (right >= gfx.ScreenWidth)
		return gfx.ScreenWidth - 9;
	else
		return x;
}

int Game::ClampScreenY(int y)
{
	const int top = y - 8;
	const int bottom = y + 8;
	if (top < 0)
		return 8;
	else if (bottom >= gfx.ScreenHeight)
		return gfx.ScreenHeight - 9;
	else
		return y;
}
