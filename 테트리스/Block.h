#pragma once
#define BLACK "\x1b[48;2;0;0;0m"
#define RED "\x1b[48;2;256;0;0m"
#define ORANGE "\x1b[48;2;256;128;0m"
#define YELLOW "\x1b[48;2;256;256;0m"
#define GREEN "\x1b[48;2;0;256;0m"
#define SKY_BLUE "\x1b[48;2;0;192;256m"
#define BLUE "\x1b[48;2;0;0;256m"
#define PURPLE "\x1b[48;2;128;0;128m"
#define WHITE "\x1b[48;2;256;256;256m"

enum Color
{
	Black = 0,
	Red,
	Orange,
	Yellow,
	Green,
	Sky_blue,
	Blue,
	Purple,
	White
};

class Block
{
private:
	int x;
	int y;
	Color color;
public:
	Block();
	Block(int x, int y, Color color);
	int getX() { return x; };
	void setX(int x) { this->x = x; };
	int getY() { return y; };
	void setY(int y) { this->y = y; };
	Color getColor() { return color; };
	void setColor(Color color) { this->color = color; };
	void print(int x, int y);
};
