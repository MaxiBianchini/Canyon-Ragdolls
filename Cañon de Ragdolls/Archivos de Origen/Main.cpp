 #include "Juego.h"

#define SALIR		0
#define MENU		1
#define JUEGO		2

int main(int argc, char* args[]) {
	Juego* juego = new Juego();

	char opcion = MENU;

	while (opcion != SALIR) {
		if (opcion == MENU) opcion = juego->Menu();
		if (opcion == JUEGO) opcion = juego->Loop();
	}

	return 0;
}