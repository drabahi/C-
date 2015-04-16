#ifndef GAME_H
# define GAME_H
# define MAX_ENTITIES 8

# include "UICurses.hpp"
class UICurses;

class Game
{
public:
	Game(void);
	~Game(void);
	Game(Game const &src);
	Game&	operator=(Game const &rhs);

	int			getW(void) const;
	int			getH(void) const;

	void		init(void);
	bool		loop(void);

	int			checkConflict(void);
protected:
private:
	enum eGame {
		END = 0,
		CONTINUE
	};

	enum eEntities {
		SHIP = 0,
		BACKGROUND,
		MINIONS
	};

	void		addEntity(IEntity *e);

	UICurses	_ui;
	IEntity		*_e[MAX_ENTITIES + 1];
	int			_score;
	int			_time;
	int			_lives;
};

#endif
