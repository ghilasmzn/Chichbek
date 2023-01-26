all: jeu menu graphics
jeu: jeu.c
	gcc -Wall -W -pedantic -O3 `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` jeu.c menu.c meilleurscore.c `pkg-config --libs-only-l MLV` -o jeu

menu: menu.c
	gcc -Wall -W -pedantic -O3 `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` menu.c `pkg-config --libs-only-l MLV` -o menu

graphics: graphics.h
	gcc -Wall -W -pedantic -O3 `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` graphics.h `pkg-config --libs-only-l MLV` -o graphics


