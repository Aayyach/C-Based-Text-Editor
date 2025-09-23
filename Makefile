typer: typer.c
	gcc typer.c -o typer -Wall -Wextra -pedantic -std=c99
gui: gui.c
	gcc gui.c -o gui `pkg-config --cflags --libs gtk4`