#ifndef SHIP_H
# define SHIP_H

# include "IEntity.hpp"
class IEntity;
# include "Laser.hpp"
class Laser;
# include "Eraser.hpp"
class Eraser;

class Ship : public IEntity
{
public:
	Ship(int, int);
	~Ship(void);
	Ship(Ship const &src);
	Ship&			operator=(Ship const &rhs);
	virtual IEntity::sPoint	&operator[](int);
	virtual void			move(int x, int y);
	virtual void			refresh(void);
	virtual void			attack(int n);
	virtual void			destroy(int);

protected:
private:
	Ship(void);

	void		create(void);
	void		setInvul(bool);

	sPoint		_mesh[SHIP_SIZE + 1];
	sPoint		_origin;

	int			_w;
	int			_h;

	bool		_invul;

	Laser		_l;
	Eraser		_e;
};

#endif
