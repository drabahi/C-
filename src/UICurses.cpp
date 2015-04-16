#include "UICurses.hpp"
#include "IEntity.hpp"
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

UICurses::UICurses(void) :
						_win(0x0),
						_user(0x0) {
	setDefaultSize();
}

UICurses::UICurses(int h, int w, int y, int x) :
											_win(0x0),
											_user(0x0),
											_h(h),
											_w(w),
											_y(y),
											_x(x) {
}

UICurses::UICurses(UICurses const &src) {
	if (this != &src)
		*this = src;
}

UICurses		&UICurses::operator=(UICurses const &rhs) {
	if (this != &rhs) {
		_win = rhs._win;
		_user = rhs._user;
		_h = rhs._h;
		_w = rhs._w;
		_y = rhs._y;
		_x = rhs._x;
		_title = rhs._title;
	}
	return (*this);
}

UICurses::~UICurses(void) {
	if (_win) {
		wborder(_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
		wrefresh(_win);
		delwin(_win);
	}
	if (_user) {
		wborder(_user, ' ', ' ', ' ',' ',' ',' ',' ',' ');
		wrefresh(_user);
		delwin(_user);
	}
	endwin();
}

int			UICurses::getW(void) const {return (_w);}
int			UICurses::getH(void) const {return (_h);}


void		UICurses::init(void) {
	_win = newwin(_h, _w, _y, _x);
	_user = newwin(1, _w - 2, _h - 1, 2);
	keypad(_win, TRUE);
	wrefresh(_win);
	refresh();
}

void		UICurses::render(IEntity **entities) {
	IEntity::sPoint		p;

	wclear(_win);
	for (int i = 0; entities[i]; ++i) {
		for (int j = 0; (p = (*entities[i])[j]).c != 'F'; ++j) {
			wattron(_win, COLOR_PAIR(p.color));
			mvwaddch(_win, p.y, p.x, p.c);
			wattroff(_win, COLOR_PAIR(p.color));
		}
	}
	wrefresh(_win);
}

char	UICurses::inputKey(void) {
	wtimeout(_win, REFRESH_TIME);
	return (wgetch(_win));
}

std::string	UICurses::readUser(void) const {
	std::string	result;
	char		str[64];

	wclear(_user);
	echo();
	curs_set(1);
	wgetstr(_user, str);
	curs_set(0);
	noecho();
	result.assign(str);
	return (result);
}

void	UICurses::notifyUser(std::string const &str) const {
	wclear(_user);
	waddstr(_user, str.c_str());
	wrefresh(_user);
	noecho();
	wgetch(_user);
}

bool	UICurses::askContinue(void) {
	static const char		message[] = "CONTINUE ? y/n";
	int						key;

	mvwaddstr(_win, _h / 2, (_w - 7) / 2, message);
	wrefresh(_win);
	while ((key = wgetch(_win)) != 'y' && key != 'n')
		;
	if (key == 'y') {
		return (true);
	} else {
		return (false);
	}
}


void	UICurses::setTitle(std::string const &title) {
	_title = std::string(title);
	box(_win, 0, 0);
	mvwaddstr(_win, 0, (_w - _title.size()) / 2, _title.c_str());
	wrefresh(_win);
}

void	UICurses::setDefaultSize(void) {
	struct winsize			ws;

	if (ioctl(0, TIOCGWINSZ, &ws) == -1) {
		return ;
	}
	_h = ws.ws_row;
	_w = ws.ws_col;
	_y = 0;
	_x = 0;
}

