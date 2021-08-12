#include "Colisionador.h"

class Juego {
public:
	Juego();
	~Juego();

	char Menu(void);
	char Loop(void);

private:

	RenderWindow* Ventana;

	View* Camara;

	b2World* Mundo;

	Ragdoll* Ragdolls[5];

	Objetos* Paredes[4];
	Objetos* Estantes[4];
	Objetos* Elementos[4];

	Canon* Cañon;

	float Fps, TiempoFrame;

	SFMLRenderer* debugRender;

	//Funciones varias
	void CargarImagenes();
	void IniciarFisicas();
	void SetZoom();

	void Colisiones();

	void Actualizar();
	void Dibujar();

	float FuerzaDisparo();
	void CargarLevel();

	bool Click(FloatRect sprite_Rect);

	//Algunas variables
	char Salir;

	float x, y;
	float alto, largo;

	bool Reiniciar;
	bool GanarNivel;
	bool EliminarRagdoll;
	
	int Nivel;
	int ContRagdolls;
	int DibujarRagdolls;
	int ContRagdollsDisparados;
	
	Vector2i posMouse;
	Vector2f posMouseToCoords;

	FloatRect sprite_Rect;

	Colisionador *Procesador;

	//Fondos del juego y menu
	Texture* texFondoMenu;
	Sprite* spFondoMenu;

	Texture* texFondoJuego;
	Sprite* spFondoJuego;

	//Carteles y botones
	Texture* texTitulo;
	Sprite* spTitulo;

	Texture* texJugar; 
	Sprite* spJugar;

	Texture* texSalir;  
	Sprite* spSalir;

	Texture* texRestart;
	Sprite* spRestart;

	Texture* texGameOver;
	Sprite* spGameOver;

	Texture* texJuegoGanado; 
	Sprite* spJuegoGanado;

	Texture* texNivelSuperado;
	Sprite* spNivelSuperado;

	Texture* texSiguienteNivel; 
	Sprite* spSiguienteNivel;
};
