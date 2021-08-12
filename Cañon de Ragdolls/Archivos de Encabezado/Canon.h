#include "Objetos.h"

class Canon {
public:

	Canon(b2World* mundo, RenderWindow* ventana, float posX, float posY, float tamX, float tamY);
	~Canon();

	void Actualizar();
	void Dibujar();

	void Grados(Vector2f vector);

	//Se usan para darle los valores al Ragdoll
	float VerX() { return bodyCanon->GetPosition().x; }
	float VerY() { return bodyCanon->GetPosition().y; }
	float VerA() { return bodyCanon->GetAngle(); }

private:

	Texture* texCanon;

	RenderWindow* Ventana;

	b2Body* bodyCanon;
	b2World* Mundo;

	Avatar* controlBodyAvatar;

	float Deg2Rad(float grados) { return grados * 3.14f / 180; } //Pasa de Grados a Radianes
};