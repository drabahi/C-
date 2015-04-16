#include "Ship.hpp"

Ship::Ship(int w, int h) :
	_w(w),
	_h(h - 2) {
	_origin.x = _w / 2;
	_origin.y = _h / 2;
	_l.setW(_w);
	_e.setW(_w);
	_invul = false;
	create();
}

Ship::Ship(Ship const &src) {
	if (this != &src)
		*this = src;
}

Ship::~Ship(void) {
}

Ship		&Ship::operator=(Ship const &rhs) {
	if (this != &rhs) {
		for (int i = 0; i < SHIP_SIZE; ++i) {
			_mesh[i] = rhs._mesh[i];
		}
	}
	return (*this);
}

IEntity::sPoint		&Ship::operator[](int i) {
	if (i > SHIP_SIZE + MAX_LASER + MAX_ERASER - 1) {
		return (_mesh[SHIP_SIZE]);
	} else if (i >= SHIP_SIZE + MAX_LASER) {
		return (_e[i - SHIP_SIZE - MAX_LASER]);
	} else if (i >= SHIP_SIZE) {
		return (_l[i - SHIP_SIZE]);
	}
	return (_mesh[i]);
}

void		Ship::create(void) {
	static const char	shipSym[SHIP_SIZE + 1] = "~>-+-  [O}~>-+-";
	static const int	shipCol[SHIP_SIZE + 1] = {	3, 1, 1, 1, 2,
													1, 1, 3, 8, 3,
													3, 1, 1, 1, 2};

	for (int i = 0; i < SHIP_SIZE; ++i) {
		_mesh[i].x = _origin.x + (i % (SHIP_SIZE / 3));
		_mesh[i].y = _origin.y + (i / (SHIP_SIZE / 3));
		_mesh[i].c = shipSym[i];
		_mesh[i].color = shipCol[i];
	}
	_mesh[SHIP_SIZE].c = 'F';
}

void		Ship::setInvul(bool n) {
	if (n) {
		_invul = true;
		_mesh[0].color = 5;
		_mesh[7].color = 5;
		_mesh[8].c = 'X';
		_mesh[8].color = 5;
		_mesh[9].color = 5;
		_mesh[10].color = 5;
	} else {
		_mesh[0].color = 3;
		_mesh[7].color = 3;
		_mesh[8].color = 8;
		_mesh[8].c = 'O';
		_mesh[9].color = 3;
		_mesh[10].color = 3;
		_invul = false;
	}
}

void		Ship::move(int x, int y) {
	if (_origin.x + 5 + x > _w
		|| _origin.x + x < 1
		|| _origin.y + 2 + y > _h
		|| _origin.y + y < 1)
		return ;
	_origin.x += x;
	_origin.y += y;
	for (int i = 0; i < SHIP_SIZE; ++i) {
		_mesh[i].x += x;
		_mesh[i].y += y;
	}
}

void		Ship::refresh(void) {
	static int		timeInvul = 0;

	if (_invul) {
		timeInvul++;
	}
	if (timeInvul > TIME_INVUL) {
		timeInvul = 0;
		setInvul(false);
	}
	_l.refresh();
	_e.refresh();
}

void		Ship::attack(int n) {
	static int	alt = 0;

	if (_invul)
		return ;
	if (n == USUAL) {
		if (alt == 0) {
			_l.shot(_origin.x + 3, _origin.y);
		} else if (alt == 1) {
			_l.shot(_origin.x + 3, _origin.y + 2);
		}
		alt = (alt + 1) % 2;
	} else if (n == RAY) {
		_e.shot(_origin.x + 3, _origin.y + 1);
	}
}

void		Ship::destroy(int n) {
	if (n >= SHIP_SIZE + MAX_LASER) {
		_e.destroy(n - SHIP_SIZE - MAX_LASER - 1);
	} else if (n >= SHIP_SIZE) {
		_l.destroy(n - SHIP_SIZE);
	} else {
		setInvul(true);
	}
}
