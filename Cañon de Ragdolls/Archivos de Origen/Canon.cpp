#include "Canon.h"

Canon::Canon(b2World* mundo, RenderWindow* ventana, float posX, float posY, float tamX, float tamY) {

	Ventana = ventana;
	Mundo = mundo;

	//Carga la Imagen del Cañon
	texCanon = new Texture();
	texCanon->loadFromFile("Imagenes/Objetos/Cañon.png");

	//Crea el Body
	bodyCanon = Box2DHelper::CreateRectangularStaticBody(Mundo, tamX, tamY);
	bodyCanon->SetTransform(b2Vec2(posX, posY), 0.0f);

	//Crea un Avatar
	controlBodyAvatar = new Avatar(bodyCanon, new Sprite(*texCanon));
}

//destructor del Cañon
Canon::~Canon() {

}

//Actualiza los elementos del Cañon
void Canon::Actualizar() {
	controlBodyAvatar->Actualizar();
}

//Dibuja el Cañon
void Canon::Dibujar() {
	controlBodyAvatar->Dibujar(*Ventana);
}

//Le da la inclinacion al Cañon
void Canon::Grados(Vector2f vector) {

	if (atan2f(vector.y - bodyCanon->GetPosition().y, vector.x - bodyCanon->GetPosition().x) < Deg2Rad(-65))	bodyCanon->SetTransform(bodyCanon->GetPosition(), Deg2Rad(-65));
	else if (atan2f(vector.y - bodyCanon->GetPosition().y, vector.x - bodyCanon->GetPosition().x) > Deg2Rad(0))	bodyCanon->SetTransform(bodyCanon->GetPosition(), Deg2Rad(0));
	else bodyCanon->SetTransform(bodyCanon->GetPosition(), atan2f(vector.y - bodyCanon->GetPosition().y, vector.x - bodyCanon->GetPosition().x));
}
