#include "SFMLRenderer.h"

class Avatar {
public:

	Avatar(b2Body* bodyCuerpo, Sprite* spCuerpo);

	~Avatar();

	void Actualizar();
	void Dibujar(RenderWindow& RW);

private:

	float Rad2Deg(float radianes) { return radianes * 180 / 3.14f; } //Pasa de Radianes a Grados

	Sprite* spAvatar;

	b2Body* bodyAvatar;

	b2World* Mundo;

	b2Vec2 bodyPos;
};