#include "Canon.h"

class Ragdoll
{
public:
	Ragdoll(b2World* mundo, RenderWindow* ventana, float posX, float posY, float tam);
	~Ragdoll();

	void Actualizar();
	void Dibujar();
	
	void Fuerzas(float fuerza, float grados);

	void Win() { win = true; } //Funcion que es llamada con la colision del Ragdoll y una Calabaza
	bool VerWin() { return win; }

private:

	Sprite* spRagdolls[14];
	Texture* texRagdolls[14];

	b2Body* bodyRagdolls[14];

	b2DistanceJoint* jntRagdoll[13];
	b2DistanceJointDef* jntdefRagdoll[13];

	RenderWindow* Ventana;

	b2World* Mundo;

	bool win;
	bool restar;

	void CargarImagenes();
	void Vinculador();

	float Rad2Deg(float grados) { return grados * 180 / 3.14f; } //Pasa de Radianes a Grados
};