#ifndef BACKGROUND_H
# define BACKGROUND_H

# include "IEntity.hpp"
class IEntity;

class Background : public IEntity
{
public:
	Background(int, int);
	~Background(void);
	Background(Background const &src);
	Background&	operator=(Background const &rhs);

	virtual IEntity::sPoint	&operator[](int);
	virtual void			move(int w, int h);
	virtual void			refresh(void);
	virtual void			attack(int n);
	virtual void			destroy(int);

protected:
private:
	Background(void);

	sPoint		_mesh[MAX_BACKGROUND * 5 + 1];
	int			_w;
	int			_h;
};

#endif
