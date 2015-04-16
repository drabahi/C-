#ifndef LASER_H
# define LASER_H

# include "IEntity.hpp"
class IEntity;

class Laser : public IEntity
{
public:
	Laser(void);
	~Laser(void);
	Laser(Laser const &src);
	Laser&	operator=(Laser const &rhs);

	virtual IEntity::sPoint	&operator[](int);
	virtual void			move(int w, int h);
	virtual void			refresh(void);
	virtual void			attack(int n);
	virtual void			destroy(int);

	void					setW(int w);
	void					shot(int x, int y);
protected:
private:

	sPoint		_mesh[MAX_LASER + 1];
	int			_w;
};

#endif
