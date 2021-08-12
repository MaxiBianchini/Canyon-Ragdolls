#include "Objetos.h"

Objetos::Objetos(b2World* mundo, RenderWindow* ventana, float posX, float posY, float tamX, float tamY, std::string tipo) {
	Ventana = ventana;
	Mundo = mundo;

	texBloque = new Texture();

	//Dependiendo del tipo se crean un body distinto
	if (tipo == "Paredes") {
		texBloque->loadFromFile("Imagenes/Objetos/Paredes.png");

		//Crea el Body
		bodyBloque = Box2DHelper::CreateRectangularStaticBody(Mundo, tamX, tamY);
		bodyBloque->SetTransform(b2Vec2(posX, posY), 0.0f);

		ID = identificador::Pared; //Identificador para colisiones
	}
	else if (tipo == "Lapida") {

		texBloque->loadFromFile("Imagenes/Objetos/Lapida.png");

		//Crea el Body
		bodyBloque = Box2DHelper::CreateRectangularDynamicBody(Mundo, tamX, tamY, 2.f, 0.01f, 0.1f);
		bodyBloque->SetTransform(b2Vec2(posX, posY), 0.0f);

		ID = identificador::Lapida; //Identificador para colisiones
	}
	
	bodyBloque->SetUserData(this); //Carga el User Data

	controlBodyAvatar = new Avatar(bodyBloque, new Sprite(*texBloque));
}

//Usa un constructor diferente porque necesita distintos datos
Objetos::Objetos(b2World* mundo, RenderWindow* ventana, float posX, float posY, float circunferia) {
	Ventana = ventana;
	Mundo = mundo;

	texBloque = new Texture();
	texBloque->loadFromFile("Imagenes/Objetos/Calabaza.png");

	//Crea el Body
	bodyBloque = Box2DHelper::CreateCircularDynamicBody(Mundo, circunferia, 1.f, 0.01f, 0.1f);
	bodyBloque->SetTransform(b2Vec2(posX, posY), 0.0f);

	ID = identificador::Calabza; //Identificador para colisiones
	bodyBloque->SetUserData(this); //Carga el User Data

	controlBodyAvatar = new Avatar(bodyBloque, new Sprite(*texBloque));
}

//Usa un constructor diferente porque necesita distintos datos
Objetos::Objetos(b2World* mundo, RenderWindow* ventana, float posX, float posY, float circunferia, float distancia, b2Body *cuerpo) {

	Ventana = ventana;
	Mundo = mundo;

	texBloque = new Texture();
	texBloque->loadFromFile("Imagenes/Objetos/Fantasma.png");

	//Crea el Body
	bodyBloque = Box2DHelper::CreateCircularDynamicBody(Mundo, circunferia, 1.f, 0.1f, 0.1f);
	bodyBloque->SetTransform(b2Vec2(posX, posY), 0.0f);

	ID = identificador::Fantasma; //Identificador para colisiones
	bodyBloque->SetUserData(this); //Carga el User Data

	//Crea el Joint y lo une al body que se le paso como parametro en el contructor
	Box2DHelper::CreateDistanceJoint(Mundo, cuerpo, b2Vec2(posX, cuerpo->GetPosition().y), bodyBloque, b2Vec2(bodyBloque->GetPosition().x, bodyBloque->GetPosition().y - 2.f), distancia, 0.2f, 0.2f);

	controlBodyAvatar = new Avatar(bodyBloque, new Sprite(*texBloque));
}

//Destructor 
Objetos::~Objetos() {

	Mundo->DestroyBody(bodyBloque);
}

//Actualiza las imagenes segun el body
void Objetos::Actualizar() {
	controlBodyAvatar->Actualizar();
}

//Dibuja el objeto
void Objetos::Dibujar() {
	controlBodyAvatar->Dibujar(*Ventana);
}
