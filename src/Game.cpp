#include "Game.hpp"
#include "IEntity.hpp"
#include "Ship.hpp"
#include "Minions.hpp"
#include "Background.hpp"
#include <ncurses.h>
#include <time.h>
#include <string>
#include <cstdlib>
#include <ctime>

Game::Game(void) :
	_score(0),
	_time(0),
	_lives(5) {

	std::srand(std::time(0));

	initscr();
	clear();
	noecho();
	cbreak();
	raw();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_GREEN, COLOR_BLACK);
	init_pair(7, COLOR_BLACK, COLOR_BLACK);
	init_pair(8, COLOR_WHITE, COLOR_BLACK);

	_ui.init();
	_ui.setTitle("|*Space coon*|");
	_e[SHIP] = 0x0;
}

void	Game::init(void) {
	int		w;
	int		h;

	w = _ui.getW();
	h = _ui.getH();
	for (int i = 0; i < MAX_ENTITIES; ++i) {
		if (_e[i] == 0x0) {
			break ;
		} else {
			delete _e[i];
			_e[i] = 0x0;
		}
	}
	addEntity(new Ship(w, h));
	addEntity(new Background(w, h));
	addEntity(new Minions(w, h));
	_score = 0;
	_time = 0;
	_lives = 5;
}

Game::Game(Game const &src) {
	if (this != &src)
		*this = src;
}

Game::~Game(void) {
	curs_set(1);
	endwin();
	for (int i = 0; i < MAX_ENTITIES; ++i) {
		if (_e[i] == 0x0) {
			break ;
		} else {
			delete _e[i];
		}
	}
}

int			Game::getW(void) const {return (_ui.getW());}
int			Game::getH(void) const {return (_ui.getH());}

Game		&Game::operator=(Game const &rhs) {
	if (this != &rhs) {
		_ui = rhs._ui;
		for (int i = 0; i < MAX_ENTITIES + 1; ++i) {
			_e[i] = rhs._e[i];
		}
		_score = rhs._score;
		_time = rhs._time;
		_lives = rhs._lives;
	}
	return (*this);
}

void		Game::addEntity(IEntity *e) {
	for (int i = 0; i < MAX_ENTITIES; ++i) {
		if (!_e[i]) {
			_e[i] = e;
			_e[i + 1] = 0x0;
			return ;
		}
	}
}

bool		Game::loop(void) {
	char	key;
	int		invul;
	clock_t	t;
	clock_t	tmp;

	invul = TIME_INVUL;
	t = clock();
	_ui.render(_e);
	while (true) {
		key = _ui.inputKey();
		if (key == 27) {
			break ;
		} else if (key == 'w') {
			_e[SHIP]->move(0, -1);
		} else if (key == 'a') {
			_e[SHIP]->move(-1, 0);
		} else if (key == 's') {
			_e[SHIP]->move(0, 1);
		} else if (key == 'd') {
			_e[SHIP]->move(1, 0);
		} else if (key == ' ') {
			_e[SHIP]->attack(IEntity::USUAL);
		} else if (key == 'r') {
			_e[SHIP]->attack(IEntity::RAY);
		} else if (key == 'e') {
			_ui.notifyUser("STOP");
		}
		if ((tmp = clock() - t) > REFRESH_TIME) {
			if (invul > 0) {
				invul--;
			}
			_time += REFRESH_TIME;
			_e[SHIP]->refresh();
			_e[MINIONS]->refresh();
			_e[BACKGROUND]->refresh();
			_ui.render(_e);
			_ui.setTitle("|Score: " + std::to_string(_score)
						+ " |Time: " + std::to_string(_time / 1000)
						+ " |Lives: " + std::to_string(_lives));
			if (checkConflict() == END && !invul) {
				_lives--;
				if (_lives <= 0) {
					_ui.notifyUser("YOU LOST !");
					break ;
				} else {
					invul = TIME_INVUL;
				}
			}
			t = tmp;
		}
	}
	_ui.notifyUser("Final score: "+ std::to_string(_score));
	return (_ui.askContinue());
}

int			Game::checkConflict(void) {
	IEntity::sPoint		a;
	IEntity::sPoint		b;
	int					result;

	result = CONTINUE;
	for (int i = 0; i < SHIP_SIZE + MAX_LASER + MAX_ERASER - 2; ++i) {
		a = (*_e[SHIP])[i];
		if (a.c == 'F' || a.x == -1) {
			if (i < SHIP_SIZE) {
				i = SHIP_SIZE - 1;
			}
			continue ;
		}
		for (int j = 0; j < MAX_MINIONS * 2 + MAX_WALL; ++j) {
			b = (*_e[MINIONS])[j];
			if (b.c == 'F' || b.x == -1) {
				continue ;
			}
			if ((a.x == b.x || a.x == b.x - 1) && a.y == b.y) {
				if (i < SHIP_SIZE) {
					_e[SHIP]->destroy(i);
					_e[MINIONS]->destroy(j);
					result = END;
				} else {
					_score++;
					_e[SHIP]->destroy(i);
					_e[MINIONS]->destroy(j);
				}
			}
		}
	}
	return (result);
}
