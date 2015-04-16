#ifndef U_I_CURSES_H
# define U_I_CURSES_H

# include <ncurses.h>
# include <string>

class IEntity;

class UICurses
{
public:
	UICurses(void);
	UICurses(int, int, int, int);
	~UICurses(void);
	UICurses(UICurses const &src);
	UICurses&			operator=(UICurses const &rhs);

	void				init(void);

	int					getW(void) const;
	int					getH(void) const;

	void				setTitle(const std::string&);
	void				render(IEntity **entities);
	char				inputKey(void);

	std::string			readUser(void) const;
	void				notifyUser(const std::string&) const;

	bool				askContinue(void);
protected:
private:
	WINDOW				*_win;
	WINDOW				*_user;
	int					_h;
	int					_w;
	int					_y;
	int					_x;
	std::string			_title;
	void				setDefaultSize(void);
};

#endif
