#ifndef ERASER_H
# define ERASER_H

# include "IEntity.hpp"
class IEntity;

class Eraser : public IEntity
{
public:
	Eraser(void);
	~Eraser(void);
	Eraser(Eraser const &src);
	Eraser&	operator=(Eraser const &rhs);

	virtual IEntity::sPoint	&operator[](int);
	virtual void			move(int w, int h);
	virtual void			refresh(void);
	virtual void			attack(int n);
	virtual void			destroy(int);

	void					setW(int w);
	void					shot(int x, int y);
protected:
private:

	sPoint		_mesh[MAX_ERASER + 1];
	int			_w;
};

#endif
