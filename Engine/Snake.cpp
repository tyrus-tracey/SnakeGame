#include "Snake.h"
#include <iostream>
#include <assert.h>
#include <math.h>

Snake::Snake(const Location & loc)
{
	segments[0].InitHead(loc);
}

Snake::~Snake() {
	this->size = 0;
}

void Snake::MoveBy(const Location & delta_loc)
{
	for (int i = size - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	if (size < MaxSize)
	{
		size++;
		int LAST_POSITION = size - 1;
		segments[LAST_POSITION].InitBody();
		segments[LAST_POSITION].Follow(segments[LAST_POSITION - 1]);
	} 
}

void Snake::Draw(Board & brd) const
{
	for (int i = 0; i < size; i++)
	{
		segments[i].Draw(brd);
	}
}

int Snake::Snake_Collision()
{
	int i = 1;
	for (i; i < size; i++) {
		if (segments[i].Segment_Collision(segments[0]) == 1) {
			return 1;
		}
	}
	return 0;
}

void Snake::Consume(Board& brd)
{
	if (brd.getApple().getLoc().x == getHeadLoc().x &&
		brd.getApple().getLoc().y == getHeadLoc().y) {
		brd.Initialize();
		Grow();
	}
}

void Snake::Limiter(Board& brd)
{
	for (int i = 0; i < size; i++)
	{
		segments[i].Limiter(brd);
	}
}

Location & Snake::getHeadLoc()
{
	return segments[0].getLoc();
}

Location& Snake::Segment::getLoc() {
	return loc;
}

void Snake::Segment::InitHead(const Location & in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody()
{
	c = Snake::bodyColor;
}

void Snake::Segment::Follow(const Segment & next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location & delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) <= 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Limiter(Board & brd)
{
	brd.Clamp(loc);
}

void Snake::Segment::Draw(Board & brd) const
{
	assert(loc.x >= 0 && loc.x <= brd.GetGridWidth());
	assert(loc.y >= 0 && loc.y <= brd.GetGridHeight());
	brd.DrawCell(loc, c);
}

int Snake::Segment::Segment_Collision(Segment& head){
	if (this->loc.x == head.loc.x && 
		this->loc.y == head.loc.y) {
		return 1;
	}
	return 0;
}




