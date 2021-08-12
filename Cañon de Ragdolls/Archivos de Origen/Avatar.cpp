#include "Avatar.h"

Avatar::Avatar(b2Body* bodyCuerpo, Sprite* spCuerpo) : bodyAvatar(bodyCuerpo), spAvatar(spCuerpo) {//Se encarga de calcular el tamaño de la imagen y adaptarlo al body

	bodyPos = bodyAvatar->GetPosition();

	spAvatar->setOrigin(spAvatar->getTexture()->getSize().x / 2.f, spAvatar->getTexture()->getSize().y / 2.f);

	spAvatar->setPosition(bodyPos.x, bodyPos.y);
	spAvatar->setRotation(Rad2Deg(bodyAvatar->GetAngle()));

	b2AABB dimension;

	dimension.upperBound = b2Vec2(-FLT_MAX, FLT_MAX);
	dimension.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);

	for (b2Fixture* F = bodyAvatar->GetFixtureList(); F; F = F->GetNext()) {
		dimension = F->GetAABB(0);
	}

	spAvatar->setScale(dimension.GetExtents().x * 2 / spAvatar->getTexture()->getSize().x, dimension.GetExtents().y * 2 / spAvatar->getTexture()->getSize().y);
}

//Destructor
Avatar::~Avatar() {

}

//Actualiza las imagenes segun el body
void Avatar::Actualizar() {
	bodyPos = bodyAvatar->GetPosition();

	spAvatar->setPosition(bodyPos.x, bodyPos.y);
	spAvatar->setRotation(Rad2Deg(bodyAvatar->GetAngle()));
}

//Dibuja el objeto 
void Avatar::Dibujar(RenderWindow& Ventana) {
	Ventana.draw(*spAvatar);
}
