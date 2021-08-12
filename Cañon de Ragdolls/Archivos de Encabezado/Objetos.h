#include "Avatar.h"

enum identificador { Pared, Calabza, Lapida, Fantasma };

class Objetos {
public:

	Objetos(b2World* mundo, RenderWindow* ventana, float posX, float posY, float circunferia, float distancia, b2Body* cuerpo);
	Objetos(b2World* mundo, RenderWindow* ventana, float posX, float posY, float tamX, float tamY, std::string tipo);
	Objetos(b2World* mundo, RenderWindow* ventana, float posX, float posY, float circunferia);

	~Objetos();

	void Actualizar();
	void Dibujar();

	b2Body* VerBody() { return bodyBloque; }

	identificador VerID() { return ID; }

private:

	//Se usa para saber de que tipo es(colisiones)
	identificador ID;

	Texture* texBloque;

	RenderWindow* Ventana;

	b2Body* bodyBloque;
	b2World* Mundo;

	//Conectan el fantasma mediante un Joint
	b2DistanceJoint* jntFantasma;
	b2DistanceJointDef* jntdefFantasma;

	Avatar* controlBodyAvatar;
};
