#include "Laser.hpp"

Laser::Laser(void) {
	for (int i = 0; i < MAX_LASER; ++i) {
		_mesh[i].x = -1;
		_mesh[i].y = -1;
		_mesh[i].c = '-';
		_mesh[i].color = 3;
	}
}

Laser::Laser(Laser const &src) {
	if (this != &src)
		*this = src;
}

Laser::~Laser(void) {
}

void		Laser::setW(int w) {_w = w;}

Laser		&Laser::operator=(Laser const &rhs) {
	if (this != &rhs) {
		for (int i = 0; i < MAX_LASER; ++i) {
			_mesh[i] = rhs._mesh[i];
		}
		_w = rhs._w;
	}
	return (*this);
}

IEntity::sPoint		&Laser::operator[](int i) {
	if (i < 0 || i >= MAX_LASER) {
		return (_mesh[MAX_LASER]);
	}
	return (_mesh[i]);
}

void		Laser::move(int x, int y) {
	(void)y;
	for (int i = 0; _mesh[i].c != 'F' && i < MAX_LASER; ++i) {
		if (_mesh[i].x == -1)
			continue ;
		_mesh[i].x += x;
		if (_mesh[i].x >= _w) {
			_mesh[i].x = -1;
		}
	}
}

void		Laser::shot(int x, int y) {
	for (int i = 0; i < MAX_LASER; ++i) {
		if (_mesh[i].x == -1) {
			_mesh[i].x = x;
			_mesh[i].y = y;
			return ;
		}
	}
}

void		Laser::refresh(void) {
	move(1, 0);
}

void		Laser::attack(int n) {
	(void)n;
	/*MAKE EXPLOSIONS !*/
}

void		Laser::destroy(int n) {
	if (n >= 0 && n < MAX_LASER) {
		_mesh[n].x = -1;
		_mesh[n].y = -1;
	}
}
