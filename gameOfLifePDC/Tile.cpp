#include "Tile.h"

Tile::Tile()
{
	name = "Player";
	symbol = "";
}

Tile::Tile(const char *name, const char *symbol)
{
	this->name = name;
	this->symbol = symbol;
}

const char *Tile::getName()
{
	return this->name;
}

void Tile::setName(const char *name)
{
	this->name = name;
}

const char *Tile::getSymbol()
{
	return this->symbol;
}

void Tile::setSymbol(const char *symbol)
{
	this->symbol = symbol;
}

int Tile::getY()
{
	return this->y;
}

void Tile::setY(int y)
{
	this->y = y;
}

int Tile::getX()
{
	return this->x;
}

void Tile::setX(int x)
{
	this->x = x;
}