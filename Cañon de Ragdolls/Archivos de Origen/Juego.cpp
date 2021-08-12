#include "Juego.h"

#define SALIR		0
#define MENU		1
#define JUEGO		2

Juego::Juego() {
	Fps = 60.f;
	TiempoFrame = 1.f / Fps;

	Ventana = new RenderWindow(VideoMode(1200, 700), "TP Final: Cañon de Ragdolls");
	Ventana->setFramerateLimit(Fps);

	Procesador = new Colisionador(); //Listener de Colisiones

	SetZoom();
	CargarImagenes(); 

	IniciarFisicas(); 
	Colisiones(); 

	Salir = 1;

	Reiniciar = false;
	GanarNivel = false;

	Nivel = 0;
	ContRagdolls = 0;
	DibujarRagdolls = 0;
	ContRagdollsDisparados = 0;

	Paredes[0] = new Objetos(Mundo, Ventana, 50.f, 100.f, 100.f, 5.f, "Paredes");
	Paredes[1] = new Objetos(Mundo, Ventana, 0.f, 50.f, 5.f, 100.f, "Paredes");
	Paredes[2] = new Objetos(Mundo, Ventana, 100.f, 50.f, 5.f, 100.f, "Paredes");
	Paredes[3] = new Objetos(Mundo, Ventana, 50.f, 0.f, 100.f, 5.f, "Paredes");

	Cañon = new Canon(Mundo, Ventana, 5.f, 96.7f, 5.12f, 5.9f);
}

//Destructor
Juego::~Juego() {

}

//Asigna el Listener al Mundo Fisico
void Juego::Colisiones() {
	Mundo->SetContactListener(Procesador);
}

//Crea el Mundo de Box2D
void Juego::IniciarFisicas() {

	Mundo = new b2World(b2Vec2(0.f, 9.8f));

	///PARA EL SFML RENDERER  
	debugRender = new SFMLRenderer(Ventana);
	debugRender->SetFlags(UINT_MAX);
	Mundo->SetDebugDraw(debugRender);
}

void Juego::SetZoom() {

	Camara = new View;
	Camara->setSize({ 100.f, 100.f });
	Camara->setCenter({ 50.f, 50.f });

	Ventana->setView(*Camara);
}

//Carga los Carteles y Botones
void Juego::CargarImagenes() {

	//Fondo del Loop
	texFondoJuego = new Texture();
	texFondoJuego->loadFromFile("Imagenes/Fondos/Juego.png");

	spFondoJuego = new Sprite(*texFondoJuego);
	spFondoJuego->scale(0.085f, 0.15f);

	//Fondo del Menu
	texFondoMenu = new Texture();
	texFondoMenu->loadFromFile("Imagenes/Fondos/Menu.png");

	spFondoMenu = new Sprite(*texFondoMenu);
	spFondoMenu->scale(0.085f, 0.15f);

	//Cartel del Titulo
	texTitulo = new Texture();
	texTitulo->loadFromFile("Imagenes/Carteles/Titulo.png");

	spTitulo = new Sprite(*texTitulo);
	spTitulo->setScale(0.06f, 0.06f);
	spTitulo->setPosition(50.f - ((texTitulo->getSize().x / 12) / 2.7f), 20);

	//Cartel de Nuevo Juego
	texJugar = new Texture();
	texJugar->loadFromFile("Imagenes/Carteles/Juego Nuevo.png");

	spJugar = new Sprite(*texJugar);
	spJugar->setScale(0.06f, 0.06f);
	spJugar->setPosition(50.f - ((texJugar->getSize().x / 12) / 2.5f), 40);

	//Cartel de Salir
	texSalir = new Texture();
	texSalir->loadFromFile("Imagenes/Carteles/Salir.png");

	spSalir = new Sprite(*texSalir);
	spSalir->setScale(0.06f, 0.06f);
	spSalir->setPosition(50.f - ((texSalir->getSize().x / 12) / 2.5f), 50);

	//Boton de Siguiente Nivel
	texSiguienteNivel = new Texture();
	texSiguienteNivel->loadFromFile("Imagenes/Carteles/Siguiente Level.png");

	spSiguienteNivel = new Sprite(*texSiguienteNivel);
	spSiguienteNivel->setScale(0.06f, 0.06f);
	spSiguienteNivel->setPosition(50.f - ((texSiguienteNivel->getSize().x / 12) / 2.5f), 50);

	//Cartel de Nivel Superado
	texNivelSuperado = new Texture();
	texNivelSuperado->loadFromFile("Imagenes/Carteles/Level Superado.png");

	spNivelSuperado = new Sprite(*texNivelSuperado);
	spNivelSuperado->setScale(0.06f, 0.06f);
	spNivelSuperado->setPosition(50.f - ((texNivelSuperado->getSize().x / 12) / 2.5f), 40.f);

	//Cartel de Juego Superado
	texJuegoGanado = new Texture();
	texJuegoGanado->loadFromFile("Imagenes/Carteles/Juego Terminado.png");

	spJuegoGanado = new Sprite(*texJuegoGanado);
	spJuegoGanado->setScale(0.06f, 0.06f);
	spJuegoGanado->setPosition(50.f - ((texJuegoGanado->getSize().x / 12) / 2.5f), 35.f);

	//Cartel de Game Over
	texGameOver = new Texture();
	texGameOver->loadFromFile("Imagenes/Carteles/Game Over.png");

	spGameOver = new Sprite(*texGameOver);
	spGameOver->setScale(0.06f, 0.06f);
	spGameOver->setPosition(50.f - ((texGameOver->getSize().x / 12) / 2.5f), 40.f);

	//Boton de Reiniciar
	texRestart = new Texture();
	texRestart->loadFromFile("Imagenes/Carteles/Reiniciar.png");

	spRestart = new Sprite(*texRestart);
	spRestart->setScale(0.06f, 0.06f);
	spRestart->setPosition(50.f - ((texRestart->getSize().x / 12) / 2.5f), 50);
}

//LOOP PRINCIPAL
char Juego::Loop(void) {
	GanarNivel = false;

	while (Salir == 2 ) {

		Ventana->clear();

		Event evento;
		while (Ventana->pollEvent(evento)) {

			switch (evento.type) {

			case Event::Closed:
				Ventana->close(); Salir = SALIR;
				break;
				
			case Event::MouseButtonPressed:

				//Si tengo 5 Ragdolls en pantalla y quiere uno mas, permitimos la eliminacion de uno
				if (ContRagdolls == 5) {
					EliminarRagdoll = true;
					ContRagdolls = 0; 
				}

				if (EliminarRagdoll) Ragdolls[ContRagdolls]->~Ragdoll(); //Eliminacion del Ragdoll
				
				//Creacion del nuevo Ragdoll
				Ragdolls[ContRagdolls] = new Ragdoll(Mundo, Ventana, Cañon->VerX() + 3, Cañon->VerY() - 8, 0.5f);
				Ragdolls[ContRagdolls]->Fuerzas(FuerzaDisparo(), Cañon->VerA());

				ContRagdolls++;
				ContRagdollsDisparados++;
				break;
			}
		}

		Actualizar();
		Dibujar();
	}

	return Salir;
}

//Loop Secundario, carga los menús
char Juego::Menu(void) {

	Ventana->clear();

	Ventana->draw(*spFondoMenu);

	switch (Nivel) {//Carga los carteles y botones segun el nivel
	case 0:
		Ventana->draw(*spTitulo);
		Ventana->draw(*spJugar);
		Ventana->draw(*spSalir);
		break;

	case 1:
		if (GanarNivel) {//Si ganó el nivel 1, carga estos elementos
			Ventana->draw(*spSiguienteNivel);
			Ventana->draw(*spNivelSuperado);
		}
		else {//si no ganó el nivel, carga estos elementos
			Ventana->draw(*spGameOver);
			Ventana->draw(*spRestart);
		}
		break;

	case 2:
		if (GanarNivel) {//Si ganó el nivel 2, carga estos elementos
			Ventana->draw(*spJuegoGanado);
			Ventana->draw(*spSalir);
		}
		else {//si no ganó el nivel, carga estos elementos
			Ventana->draw(*spGameOver);
			Ventana->draw(*spRestart);
		}
		break;
	}

	Ventana->display();

	Event evento;
	while (Salir == 1) {
		while (Ventana->pollEvent(evento)) {
			if (evento.type == Event::MouseMoved) { //Obtiene la posicion del mouse
				x = evento.mouseMove.x / 12;
				y = evento.mouseMove.y / 7;
			}

			switch (evento.type) {
			case Event::MouseButtonPressed:

				switch (Nivel) { //Segun lo que presione, puede, Salir del juego, Reintentar el nivel o ir al Siguiente Nivel
				case 0:
					sprite_Rect = spJugar->getGlobalBounds();
					if (Click(sprite_Rect)) {
						Salir = JUEGO;

						Nivel++;
						CargarLevel();
					}
					else {
						sprite_Rect = spSalir->getGlobalBounds();
						if (Click(sprite_Rect)) Salir = SALIR;
					}
					break;

				case 1:
					if (GanarNivel) {
						sprite_Rect = spSiguienteNivel->getGlobalBounds();
						if (Click(sprite_Rect)) {
							Salir = JUEGO;

							Nivel++;
							CargarLevel();
						}
					}
					else {
						sprite_Rect = spRestart->getGlobalBounds();
						if (Click(sprite_Rect)) {

							Reiniciar = true;

							Salir = JUEGO;
							CargarLevel();
						}
					}
					break;

				case 2:
					if (GanarNivel) {
						sprite_Rect = spSalir->getGlobalBounds();
						if (Click(sprite_Rect)) Salir = SALIR;
					}
					else {
						sprite_Rect = spRestart->getGlobalBounds();
						if (Click(sprite_Rect)) {

							Reiniciar = true;

							Salir = JUEGO;
							CargarLevel();
						}
					}
					break;
				}
				break;

			case Event::Closed:
				Salir = SALIR;
				break;
			}
		}
	}

	return Salir;
}


//Carga los Elemntos del juego (Estantes, Lapidas, Calabaza, Fantasmas)
void Juego::CargarLevel() {
	
	if (Nivel == 1){
		if (Reiniciar == true) { //En caso de haber perdido elimina los elementos existenes y se reinician las variables

			for (int i = 0; i < 4; i++) {
				Estantes[i]->~Objetos();
				Elementos[i]->~Objetos();
			}

			for (int i = 0; i < DibujarRagdolls; i++) Ragdolls[i]->~Ragdoll();
			
			ContRagdolls = 0;
			DibujarRagdolls = 0;
			EliminarRagdoll = false;
			ContRagdollsDisparados = 0;

			Reiniciar = false;
		}

		Estantes[0] = new Objetos(Mundo, Ventana, 40.f, 85.f, 15.f, 20.f, "Paredes");
		Estantes[1] = new Objetos(Mundo, Ventana, 40.f, 15.f, 15.f, 20.f, "Paredes");
		Estantes[2] = new Objetos(Mundo, Ventana, 40.f, 55.f, 15.f, 5.f, "Paredes");
		Estantes[3] = new Objetos(Mundo, Ventana, 80.f, 55.f, 15.f, 5.f, "Paredes");
	
		Elementos[0] = new Objetos(Mundo, Ventana, 80.f, 50.f, 3.f);
		Elementos[1] = new Objetos(Mundo, Ventana, 38.f, 55.f, 5.f, 10.f, "Lapida");
		Elementos[2] = new Objetos(Mundo, Ventana, 40.f, 75.f, 5.f, 60.f, Paredes[3]->VerBody());
		Elementos[3] = new Objetos(Mundo, Ventana, 65.f, 35.f, 5.f, 25.f, Paredes[3]->VerBody());
	}
	else if (Nivel == 2) {//Al pasar de nivel elimina los elementos existenes y se reinician las variables

		for (int i = 0; i < 4; i++) {
			Estantes[i]->~Objetos();
			Elementos[i]->~Objetos();
		}

		for (int i = 0; i < DibujarRagdolls; i++) Ragdolls[i]->~Ragdoll();

		ContRagdolls = 0;
		DibujarRagdolls = 0;
		EliminarRagdoll = false;
		ContRagdollsDisparados = 0;

		Estantes[0] = new Objetos(Mundo, Ventana, 40.f, 85.f, 15.f, 20.f, "Paredes");
		Estantes[1] = new Objetos(Mundo, Ventana, 40.f, 15.f, 15.f, 20.f, "Paredes");
		Estantes[2] = new Objetos(Mundo, Ventana, 40.f, 55.f, 15.f, 5.f, "Paredes");
		Estantes[3] = new Objetos(Mundo, Ventana, 90.f, 55.f, 15.f, 5.f, "Paredes");

		Elementos[0] = new Objetos(Mundo, Ventana, 92.f, 50.f, 3.f);
		Elementos[1] = new Objetos(Mundo, Ventana, 85.f, 45.f, 5.f, 10.f, "Lapida");
		Elementos[2] = new Objetos(Mundo, Ventana, 40.f, 35.f, 5.f, 15.f, Estantes[1]->VerBody());
		Elementos[3] = new Objetos(Mundo, Ventana, 40.f, 60.f, 5.f, 2.f, Estantes[2]->VerBody());
	}
}

//Realiza las actualizaciones de los distintos elementos
void Juego::Actualizar() {

	//Obtenemos la posicion del mouse
	posMouse = Mouse::getPosition(*Ventana);
	posMouseToCoords = Ventana->mapPixelToCoords(posMouse);

	Cañon->Grados(posMouseToCoords); //Respecto a la posicion del mouse le damos los grados al cañon

	if (DibujarRagdolls <= 4) DibujarRagdolls = ContRagdolls;

	//Actualizacion general de los elementos del juego
	for (int i = 0; i < 4; i++) Elementos[i]->Actualizar();
	for (int i = 0; i < 4; i++) Paredes[i]->Actualizar();
	for (int i = 0; i < 4; i++) Estantes[i]->Actualizar();
	
	for (int i = 0; i < DibujarRagdolls; i++) Ragdolls[i]->Actualizar();

	Cañon->Actualizar();

	// Condicion para ganar
	for (int i = 0; i < DibujarRagdolls; i++) {

		if (Ragdolls[i]->VerWin()) {

			Salir = MENU;
			GanarNivel = true;
		}
	}

	//Condicion para perder
	if (ContRagdollsDisparados == 16) Salir = MENU;

	Mundo->Step(TiempoFrame, 8, 8);
	Mundo->ClearForces();
	Mundo->DrawDebugData();
}

//Realiza el dibujado de los elementos del juego
void Juego::Dibujar() {

	//Ventana->draw(*spFondoJuego);

	for (int i = 0; i < 4; i++) Elementos[i]->Dibujar();
	for (int i = 0; i < 4; i++) Paredes[i]->Dibujar();
	for (int i = 0; i < 4; i++) Estantes[i]->Dibujar();
	
	for (int i = 0; i < DibujarRagdolls; i++) Ragdolls[i]->Dibujar();
	
	Cañon->Dibujar();

	Ventana->display();
}

//Calcula la fuerza segun la distancia que hay entre el cañon y el mouse
float Juego::FuerzaDisparo() {
	posMouse = Mouse::getPosition(*Ventana);
	posMouseToCoords = Ventana->mapPixelToCoords(posMouse);

	float VectorX = posMouseToCoords.x - Cañon->VerX();
	float VectorY = posMouseToCoords.y - Cañon->VerY();

	float DistanciaDisparo = sqrt((pow(VectorX, 2) + pow(VectorY, 2)));
	float FuerzaDisp = DistanciaDisparo * 50.f;

	return FuerzaDisp;
}

//Verifica que al hacer click la posicion del mouse este sobre el boton
bool Juego::Click(FloatRect sprite_Rect) {

	largo = sprite_Rect.left + sprite_Rect.width;
	alto = sprite_Rect.top + sprite_Rect.height;

	if ((x > sprite_Rect.left&& x <= largo) && (y > sprite_Rect.top&& y <= alto)) return true;
	else return false;
}
