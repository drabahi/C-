#ifndef MINIONS_H
# define MINIONS_H

# include "IEntity.hpp"
class IEntity;

class Minions : public IEntity
{
public:
	Minions(int, int);
	~Minions(void);
	Minions(Minions const &src);
	Minions&	operator=(Minions const &rhs);
	virtual IEntity::sPoint	&operator[](int);
	virtual void			move(int w, int h);
	virtual void			refresh(void);
	virtual void			attack(int n);
	virtual void			destroy(int);

protected:
private:
	Minions(void);

	sPoint		_mesh[MAX_MINIONS + 1];
	sPoint		_attacks[MAX_MINIONS + 1];
	sPoint		_walls[MAX_WALL * 3 + 1];
	int			_w;
	int			_h;
};

#endif
