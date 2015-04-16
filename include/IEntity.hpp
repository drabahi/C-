#ifndef I_ENTITY_H
# define I_ENTITY_H

# define REFRESH_TIME 16
# define TIME_INVUL 100
# define MAX_LASER 8
# define MAX_MINIONS 24
# define SHIP_SIZE 15
# define MAX_ERASER 10
# define MAX_BACKGROUND 30
# define MAX_WALL 20

/*
        COLOR_BLACK   0
        COLOR_RED     1
        COLOR_GREEN   2
        COLOR_YELLOW  3
        COLOR_BLUE    4
        COLOR_MAGENTA 5
        COLOR_CYAN    6
        COLOR_WHITE   7
*/

class IEntity
{
public:
	struct		sPoint {
		char	c;
		int		x;
		int		y;
		int		color;
	};

	enum eShip {
		USUAL = 0,
		RAY
	};
	virtual ~IEntity(void){}
	virtual IEntity::sPoint	&operator[](int) = 0;
	virtual void			move(int x, int y) = 0;
	virtual void			refresh(void) = 0;
	virtual void			attack(int) = 0;
	virtual void			destroy(int) = 0;
protected:
private:
};

#endif
