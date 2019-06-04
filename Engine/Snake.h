#pragma once
#include "board.h"

class Snake 
{
private:
	class Segment 
	{
	public:
		void InitHead(const Location& in_loc);
		void InitBody();
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Limiter(Board& brd);
		void Draw(Board& brd) const;
		int Segment_Collision(Segment& head);
		Location& getLoc();
	private:
		Location loc;
		Color c;
	};

public:
	Snake(const Location& loc);
	~Snake();
	void MoveBy(const Location& delta_loc);
	void Grow();
	void Limiter(Board& brd);
	void Draw(Board& brd) const;
	int Snake_Collision();
	Location& getHeadLoc();
	void Consume(Board& brd);

private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::Green;
	static constexpr int MaxSize = 100;
	int size = 1;
	Segment segments[MaxSize];
};