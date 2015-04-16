#include "Background.hpp"
#include <cstdlib>

Background::Background(int w, int h) :
	_w(w),
	_h(h - 2) {
	for (int i = 0; i < MAX_BACKGROUND * 5 - 1; i += 5) {
		_mesh[i].x = rand() % _w;
		_mesh[i].y = rand() % _h;
		_mesh[i].c = '+';
		_mesh[i].color = 7;
		_mesh[i + 1].x = _mesh[i].x;
		_mesh[i + 1].y = _mesh[i].y - 1;
		_mesh[i + 1].c = '|';
		_mesh[i + 1].color = 7;
		_mesh[i + 2].x = _mesh[i].x + 1;
		_mesh[i + 2].y = _mesh[i].y;
		_mesh[i + 2].c = '-';
		_mesh[i + 2].color = 7;
		_mesh[i + 3].x = _mesh[i].x;
		_mesh[i + 3].y = _mesh[i].y + 1;
		_mesh[i + 3].c = '|';
		_mesh[i + 3].color = 7;
		_mesh[i + 4].x = _mesh[i].x - 1;
		_mesh[i + 4].y = _mesh[i].y;
		_mesh[i + 4].c = '-';
		_mesh[i + 4].color = 7;
	}
	_mesh[MAX_BACKGROUND * 5].c = 'F';
}

Background::Background(Background const &src) {
	if (this != &src)
		*this = src;
}

Background::~Background(void) {
}

Background		&Background::operator=(Background const &rhs) {
	if (this != &rhs) {
		for (int i = 0; i < MAX_BACKGROUND; ++i) {
			_mesh[i] = rhs._mesh[i];
		}
		_w = rhs._w;
	}
	return (*this);
}

IEntity::sPoint		&Background::operator[](int i) {
	if (i < 0 || i >= MAX_BACKGROUND * 5) {
		return (_mesh[MAX_BACKGROUND * 5]);
	}
	return (_mesh[i]);
}

void		Background::move(int x, int y) {
	(void)y;
	for (int i = 0; _mesh[i].c != 'F' && i < MAX_BACKGROUND * 5; ++i) {
		_mesh[i].x += x;
		if (_mesh[i].x <= 1 && _mesh[i].c == '+') {
			_mesh[i].x = _w;
			_mesh[i].y = rand() % _h;
			_mesh[i + 1].x = _mesh[i].x;
			_mesh[i + 1].y = _mesh[i].y - 1;
			_mesh[i + 2].x = _mesh[i].x + 1;
			_mesh[i + 2].y = _mesh[i].y;
			_mesh[i + 3].x = _mesh[i].x;
			_mesh[i + 3].y = _mesh[i].y + 1;
			_mesh[i + 4].x = _mesh[i].x - 1;
			_mesh[i + 4].y = _mesh[i].y;
		}
	}
}

void		Background::refresh(void) {
	move(-1, 0);
}

void		Background::attack(int n) {
	(void)n;
}

void		Background::destroy(int n) {
	(void)n;
}
