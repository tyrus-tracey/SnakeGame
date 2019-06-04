#pragma once
#include "Graphics.h"
#include "Location.h"
#include <assert.h>
#include <random>

class Board {
private:
	class Apple
	{
	public:
		Apple();
		void Draw(Board& brd);
		int Apple_Collision(Location& head);
		Location& getLoc();
		void setLoc(Location& newLoc);
	private:
		Location loc;
		Color c;
	};

public:
	Board(Graphics& gfx);
	int Clamp(Location& loc);
	void DrawCell( const Location& loc, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;
	int GetDimension() const;
	void DrawBorders(Color c);
	void Initialize();
	Apple& getApple();
private:
	Apple bit = Apple();
	static constexpr int dimension = 20;
	static constexpr int width = 25;
	static constexpr int height = 25;
	static constexpr Color appleColor = Colors::Blue;
	std::random_device rd;
	std::mt19937 rng{ rd() };
	
	Graphics& gfx;

};