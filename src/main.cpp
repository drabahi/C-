#include "Game.hpp"

int		main(void) {
	Game	g;

	g.init();
	while (g.loop()) {
		g.init();
	}
	return (0);
}
