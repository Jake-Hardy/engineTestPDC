#include <curses.h>
#include <cstdarg>
#include <string>
#include <ctime> 
#include "Tile.h"

const int SCREEN_HEIGHT = 25;
const int SCREEN_WIDTH = 80;

const int MAP_HEIGHT = 250;
const int MAP_WIDTH = 400;

/* 
 * Keeps track of which map tile the top-left corner 
 * of the screen displays
 */
struct tlCorner
{
	int y;
	int x;
};

void createMap(const char *map[MAP_HEIGHT][MAP_WIDTH]);

int main()
{
	const char *map[MAP_HEIGHT][MAP_WIDTH];
	createMap(map);
	
	tlCorner tlc;

	// Center the screen on the center of the map
	tlc.y = (MAP_HEIGHT / 2) - SCREEN_HEIGHT / 2;
	tlc.x = (MAP_WIDTH / 2) - SCREEN_WIDTH / 2;
	
	Tile player;
	player = Tile("Player", "@");

	// Place the player in the middle of the screen
	player.setY(SCREEN_HEIGHT / 2);
	player.setX(SCREEN_WIDTH / 2);

	initscr();
	start_color();
	clear();
	noecho();
	cbreak();
	curs_set(0);
	wtimeout(stdscr, -1);
	keypad(stdscr, true);

	init_pair(1, COLOR_GREEN, 0);
	init_pair(2, COLOR_YELLOW, 0);
	init_pair(3, COLOR_WHITE, 0);

	bool exit = false;

	while (!exit)
	{
		for (int i = 0; i < SCREEN_HEIGHT; ++i)
		{
			for (int j = 0; j < SCREEN_WIDTH; ++j)
			{
				if (player.getY() == i && player.getX() == j)
				{
					wattron(stdscr, COLOR_PAIR(3) | A_BOLD);
					wattrset(stdscr, COLOR_PAIR(3) | A_BOLD);
				}
				else if (map[i][j] == ",")
				{
					wattron(stdscr, COLOR_PAIR(1) | A_BOLD);
					wattrset(stdscr, COLOR_PAIR(1) | A_BOLD);
				}
				else if (map[i][j] == "'")
				{
					wattron(stdscr, COLOR_PAIR(1));
					wattrset(stdscr, COLOR_PAIR(1));
				}
				else if (map[i][j] == ".")
				{
					wattron(stdscr, COLOR_PAIR(2));
					wattrset(stdscr, COLOR_PAIR(2));
				}
				
				if (player.getY() == i && player.getX() == j)
				{
					mvprintw(i, j, player.getSymbol());
				}
				else
				{
					mvprintw(i, j, map[tlc.y + i][tlc.x + j]);
				}
			}
		}

		refresh();
		
		int y = player.getY();
		int x = player.getX();
		int c = wgetch(stdscr);

		/*
		 * Check for player input. If an arrow key is pressed, 
		 * attempt to move the player. 
		 */
		switch (c)
		{
		case KEY_UP:
			if (tlc.y - 1 >= 0 && y == SCREEN_HEIGHT / 2)
			{
				tlc.y -= 1;
			}
			else if (tlc.y - 1 >= 0 && y != SCREEN_HEIGHT / 2 && y - 1 >= 0)
			{
				player.setY(y - 1);
			}
			else if (tlc.y - 1 < 0 && y - 1 >= 0)
			{
				player.setY(y - 1);
			}
			
			break;

		case KEY_DOWN:
			if (tlc.y + SCREEN_HEIGHT <= MAP_HEIGHT - 1 && y == SCREEN_HEIGHT / 2)
			{
				tlc.y += 1;
			}
			else if (tlc.y + SCREEN_HEIGHT - 1 <= MAP_HEIGHT - 1 && y != SCREEN_HEIGHT / 2 && y + 1 <= SCREEN_HEIGHT - 1)
			{
				player.setY(y + 1);
			}
			else if (tlc.y + SCREEN_HEIGHT > MAP_HEIGHT - 1 && y + 1 <= SCREEN_HEIGHT - 1)
			{
				player.setY(y + 1);
			}
			
			break;

		case KEY_LEFT:
			if (tlc.x - 1 >= 0 && x == SCREEN_WIDTH / 2)
			{
				tlc.x -= 1;
			}
			else if (tlc.x - 1 >= 0 && x != SCREEN_WIDTH / 2 && x - 1 >= 0)
			{
				player.setX(x - 1);
			}
			else if (tlc.x - 1 < 0 && x - 1 >= 0)
			{
				player.setX(x - 1);
			}
			
			break;

		case KEY_RIGHT:
			if (tlc.x + SCREEN_WIDTH <= MAP_WIDTH - 1 && x == SCREEN_WIDTH / 2)
			{
				tlc.x += 1;
			}
			else if (tlc.x + SCREEN_WIDTH - 1 <= MAP_WIDTH - 1 && x != SCREEN_WIDTH / 2 && x + 1 <= SCREEN_WIDTH - 1)
			{
				player.setX(x + 1);
			}
			else if (tlc.x + SCREEN_WIDTH > MAP_WIDTH - 1 && x + 1 <= SCREEN_WIDTH - 1)
			{
				player.setX(x + 1);
			}

			break;

		case KEY_HOME:
			exit = true;
			break;
		}
	}
	endwin();

	return 0;
}

void createMap(const char *map[MAP_HEIGHT][MAP_WIDTH])
{
	std::srand(std::time(NULL));
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			int r = std::rand() % 100;
			if (r < 30)
			{
				map[i][j] = ",";
			}
			else if (r < 60)
			{
				map[i][j] = "'";
			}
			else if (r < 100)
			{
				map[i][j] = ".";
			}
		}
	}
}