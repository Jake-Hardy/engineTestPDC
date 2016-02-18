#ifndef Tile_H
#define Tile_H

class Tile
{
public:
	Tile();
	Tile(const char *name, const char *symbol);
	const char *getName();
	void setName(const char *name);
	const char *getSymbol();
	void setSymbol(const char *symbol);
	int getY();
	void setY(int y);
	int getX();
	void setX(int x);

private:
	const char *name;
	const char *symbol;
	int y;
	int x;
};

#endif