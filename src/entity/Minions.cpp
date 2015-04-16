#include "Minions.hpp"
#include <cstdlib>

Minions::Minions(int w, int h) :
	_w(w),
	_h(h - 2) {
	for (int i = 0; i < MAX_MINIONS; ++i) {
		_mesh[i].x = rand() % _w;
		_mesh[i].y = rand() % _h + 1;
		_mesh[i].c = '<';
		_mesh[i].color = 2;
		_attacks[i].x = -1;
		_attacks[i].y = -1;
		_attacks[i].c = '~';
		_attacks[i].color = 5;
	}
	for (int i = 0; i < MAX_WALL * 3 - 1; i += 3) {
		_walls[i].x = rand() % _w;
		_walls[i].y = rand() % _h + 1;
		_walls[i].c = '|';
		_walls[i].color = 4;
		_walls[i + 1].x = _walls[i].x;
		_walls[i + 1].y = _walls[i].y - 1;
		_walls[i + 1].c = '|';
		_walls[i + 1].color = 4;
		_walls[i + 2].x = _walls[i].x;
		_walls[i + 2].y = _walls[i].y + 1;
		_walls[i + 2].c = '|';
		_walls[i + 2].color = 4;
	}
	_mesh[MAX_MINIONS].c = 'F';
	_attacks[MAX_MINIONS].c = 'F';
	_walls[MAX_WALL].c = 'F';
}

Minions::Minions(Minions const &src) {
	if (this != &src)
		*this = src;
}

Minions::~Minions(void) {
}

Minions		&Minions::operator=(Minions const &rhs) {
	if (this != &rhs) {
		for (int i = 0; i < MAX_MINIONS; ++i) {
			_mesh[i] = rhs._mesh[i];
		}
		_w = rhs._w;
		_h = rhs._h;
	}
	return (*this);
}

IEntity::sPoint		&Minions::operator[](int i) {
	if (i < 0 || i >= MAX_WALL + MAX_MINIONS * 2 - 2) {
		return (_mesh[MAX_MINIONS]);
	} else if (i >= MAX_MINIONS * 2 - 2) {
		return (_walls[i - (2 * MAX_MINIONS) + 2]);
	} else if (i >= MAX_MINIONS) {
		return (_attacks[i - MAX_MINIONS]);
	}
	return (_mesh[i]);
}

void		Minions::move(int x, int y) {
	for (int i = 0; i < MAX_MINIONS; ++i) {
		if (_mesh[i].x > -1)
		{
			_mesh[i].x += x;
			_mesh[i].y += y;
			if (rand() % 100 > 95) {
				attack(_mesh[i].y * _w + _mesh[i].x);
			}
		} else {
			_mesh[i].x = _w;
			_mesh[i].y = rand() % _h + 1;
		}
		if (_attacks[i].x != -1) {
			_attacks[i].x += 2 * x;
			if (_attacks[i].x <= 1) {
				_attacks[i].x = -1;
				_attacks[i].y = -1;
			}
		}
	}
	for (int i = 0; i < MAX_WALL * 3; ++i) {
		_walls[i].x += x;
		_walls[i].y += y;
		if (_walls[i].x <= 1 && (i % 3 == 0)) {
			_walls[i].x = _w;
			_walls[i].y = rand() % _h;
			_walls[i + 1].x = _walls[i].x;
			_walls[i + 1].y = _walls[i].y - 1;
			_walls[i + 2].x = _walls[i].x;
			_walls[i + 2].y = _walls[i].y + 1;
		}
	}
}

void		Minions::refresh(void) {
	static int		calmDown = 1;
	int		r;

	calmDown++;
	calmDown %= 100;
	if (calmDown) {
		move(-1, 0);
	} else {
		r = rand() % 2;
		if (r > 1) {
			move(0, -1);
		} else {
			move(0, 1);
		}
	}
}

void		Minions::attack(int n) {
	if (n <= 0)
		return ;
	for (int i = 0; i < MAX_MINIONS; ++i) {
		if (_attacks[i].x == -1) {
			_attacks[i].x = n % _w;
			_attacks[i].y = n / _w;
			return ;
		}
	}
}

void		Minions::destroy(int n) {
	if (n >= 0 && n < MAX_MINIONS) {
		_mesh[n].x = -1;
		_mesh[n].y = -1;
	} else if (n >= MAX_MINIONS && n < MAX_MINIONS * 2 - 1) {
		_attacks[n - MAX_MINIONS].x = -1;
		_attacks[n - MAX_MINIONS].y = -1;
	} else if (n < MAX_WALL + MAX_MINIONS * 2 - 2) {
		_walls[n - MAX_MINIONS * 2 * MAX_WALL + 2].x = -1;
	}
}
