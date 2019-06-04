#include "Board.h"

Board::Board(Graphics & gfx)
	:
	gfx(gfx)
{
}

int Board::Clamp(Location & loc)
{
	if (loc.x > width)
	{
		loc.x = width;
		return 1;
	} else if (loc.x < 0)
	{
		loc.x = 0;
		return 1;
	} else if (loc.y > height)
	{
		loc.y = height;
		return 1;
	} else if (loc.y < 0)
	{
		loc.y = 0;
		return 1;
	}
	return 0;
}

void Board::DrawCell( const Location & loc, Color c)
{
	gfx.DrawRectDim(loc.x * dimension, loc.y * dimension, dimension, dimension, c);
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

int Board::GetDimension() const
{
	return dimension;
}
void Board::Initialize()
{
	Location newLoc;
	std::uniform_int_distribution<int> X_DISTRIBUTION(0, GetGridWidth() - 1);
	std::uniform_int_distribution<int> Y_DISTRIBUTION(0, GetGridHeight() - 1);
	newLoc.x = X_DISTRIBUTION(rng);
	newLoc.y = Y_DISTRIBUTION(rng);
	bit.setLoc(newLoc);
}

void Board::DrawBorders(Color c) {
	Location border;
	border.y = GetGridWidth() + 1;
	for (int i = 0; i <= GetGridWidth()+1; i++) {
		border.x = i;
		DrawCell(border, c);
	}
	border.x = GetGridWidth() + 1;
	for (int i = 0; i <= GetGridHeight()+1; i++) {
		border.y = i;
		DrawCell(border, c);
	}
}
Board::Apple& Board::getApple()
{
	return bit;
}

Board::Apple::Apple()
{
	c = Board::appleColor;
	loc.x = 0;
	loc.y = 0;
}

void Board::Apple::Draw(Board& brd) {
	brd.DrawCell(loc, c);
}

int Board::Apple::Apple_Collision(Location & head)
{
	if (this->loc.x == head.x &&
		this->loc.y == head.y) {
		return 1;
	}
	return 0;
}

Location & Board::Apple::getLoc()
{
	return loc;
}

void Board::Apple::setLoc(Location & newLoc)
{
	loc.x = newLoc.x;
	loc.y = newLoc.y;
}
