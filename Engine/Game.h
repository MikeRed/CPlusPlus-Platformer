/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void DrawBox(int x, int y, int r, int g, int b);
	void DrawEnemy(int x, int y, int r, int g, int b);
	void DrawPlayer(int x, int y, int r, int g, int b);
	void DrawDirection(int x, int y, bool forward);
	void DrawBullet(int x, int y, bool forward);
	void jump();
	bool OverlapTest(int box0x, int box0y, int box1x, int box1y);
	int ClampScreenX(int x);
	int ClampScreenY(int y);

	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	int x_enemy = 200;
	int y_enemy = gfx.ScreenHeight -9;
	bool enemy_alive = true;
	int x_mobile = 400;
	int y_mobile = gfx.ScreenHeight - 9;
	const int groundHeight = gfx.ScreenHeight - 9;
	bool grounded = true;
	bool apexReached = false;
	int bX;
	int bY;
	bool colliding = false;
	bool forward = true;
	bool bulletDirection;
	bool bulletIsFired = false;
	/********************************/
};