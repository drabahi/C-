#include "Eraser.hpp"

Eraser::Eraser(void) {
	for (int i = 0; i < MAX_ERASER; ++i) {
		_mesh[i].x = -1;
		_mesh[i].y = -1;
		_mesh[i].c = '=';
		_mesh[i].color = 3;
	}
}

Eraser::Eraser(Eraser const &src) {
	if (this != &src)
		*this = src;
}

Eraser::~Eraser(void) {
}

void		Eraser::setW(int w) {_w = w;}

Eraser		&Eraser::operator=(Eraser const &rhs) {
	if (this != &rhs) {
		for (int i = 0; i < MAX_ERASER; ++i) {
			_mesh[i] = rhs._mesh[i];
		}
		_w = rhs._w;
	}
	return (*this);
}

IEntity::sPoint		&Eraser::operator[](int i) {
	if (i < 0 || i > MAX_ERASER) {
		return (_mesh[MAX_ERASER]);
	}
	return (_mesh[MAX_ERASER - i]);
}

void		Eraser::move(int x, int y) {
	(void)y;
	for (int i = 0; _mesh[i].c != 'F' && i < MAX_ERASER; ++i) {
		if (_mesh[i].x == -1)
			continue ;
		_mesh[i].x += x;
		if (_mesh[i].x >= _w) {
			_mesh[i].x = -1;
		}
	}
}

void		Eraser::shot(int x, int y) {
	if (_mesh[0].x != -1)
		return ;
	for (int i = 0; i < MAX_ERASER; ++i) {
		_mesh[i].x = x + i;
		_mesh[i].y = y;
	}
}

void		Eraser::refresh(void) {
	move(1, 0);
}

void		Eraser::attack(int n) {
	(void)n;
	/*MAKE EXPLOSIONS !*/
}

void		Eraser::destroy(int n) {
	if (n >= 0 && n <= MAX_ERASER) {
		_mesh[MAX_ERASER - n].x = -1;
		_mesh[MAX_ERASER - n].y = -1;
	}
}
