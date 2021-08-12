#include "Ragdoll.h"

Ragdoll::Ragdoll(b2World* mundo, RenderWindow* ventana, float posX, float posY, float tam) {

	Ventana = ventana;
	Mundo = mundo;

	win = false;
	restar = false;

	//Tamaño de las partes del cuerpo. PD: para editar el tamaño del Ragdoll solo editar el tamaño de la cabeza

	// Cabeza y Pecho
	float TamCabeza  = tam ;
	float TamPechoX  = TamCabeza * 2;
	float TamPechoY  = TamCabeza * 4;

	//Brazos
	float TamBrazoX	 = TamCabeza * 0.7f;
	float TamBrazoY	 = TamCabeza * 3;

	float TamAnteBrazoX = TamCabeza * 0.7f;
	float TamAnteBrazoY = TamCabeza * 3;

	float TamMano = TamCabeza;

	//Piernas
	float TamPiernaX = TamCabeza * 0.83f;
	float TamPiernaY = TamCabeza * 3.3f;

	float TamAntePiernaX = TamCabeza * 0.83f;
	float TamAntePiernaY = TamCabeza * 3.3f;

	float TamPie = TamCabeza;

	//Body del Ragdoll
	bodyRagdolls[0] = Box2DHelper::CreateCircularDynamicBody(Mundo, TamCabeza, TamCabeza, 0.2f, 0.1f);						//Cabeza
	bodyRagdolls[1] = Box2DHelper::CreateRectangularDynamicBody(Mundo, TamPechoX, TamPechoY, 2.f, 0.2f, 0.1f);				//Pecho

	//Brazo Derecho Completo
	bodyRagdolls[2] = Box2DHelper::CreateRectangularDynamicBody(Mundo, TamBrazoX, TamBrazoY, 2.f, 0.2f, 0.1f);				//Brazo Derecho
	bodyRagdolls[3] = Box2DHelper::CreateRectangularDynamicBody(Mundo, TamAnteBrazoX, TamAnteBrazoY, 2.f, 0.2f, 0.1f);		//AnteBrazo Derecho
	bodyRagdolls[4] = Box2DHelper::CreateRectangularDynamicBody(Mundo, TamMano, TamMano, 2.f, 0.2f, 0.1f);					//Mano Derecha

	//Brazo Izquierdo Completo
	bodyRagdolls[5] = Box2DHelper::CreateRectangularDynamicBody(Mundo, TamBrazoX, TamBrazoY, 2.f, 0.2f, 0.1f);				//Brazo Izquierdo
	bodyRagdolls[6] = Box2DHelper::CreateRectangularDynamicBody(Mundo, TamAnteBrazoX, TamAnteBrazoY, 2.f, 0.2f, 0.1f);		//AnteBrazo Izquierdo
	bodyRagdolls[7] = Box2DHelper::CreateRectangularDynamicBody(Mundo, TamMano, TamMano, 2.f, 0.2f, 0.1f);					//Mano Izquierda

	//Pierna Derehca Completa
	bodyRagdolls[8] = Box2DHelper::CreateRectangularDynamicBody(Mundo, TamPiernaX, TamPiernaY, 2.f, 0.2f, 0.1f);			//Pierna Derecha
	bodyRagdolls[9] = Box2DHelper::CreateRectangularDynamicBody(Mundo, TamAntePiernaX, TamAntePiernaY, 2.f, 0.2f, 0.1f);	//AntePierna Derecha
	bodyRagdolls[10] = Box2DHelper::CreateRectangularDynamicBody(Mundo, TamPie, TamPie, 2.f, 0.2f, 0.1f);					//Pie Derecho
	
	//Pierna Izquierda Completa
	bodyRagdolls[11] = Box2DHelper::CreateRectangularDynamicBody(Mundo, TamPiernaX, TamPiernaY, 2.f, 0.2f, 0.1f);			//Pierna Izquierda
	bodyRagdolls[12] = Box2DHelper::CreateRectangularDynamicBody(Mundo, TamAntePiernaX, TamAntePiernaY, 2.f, 0.2f, 0.1f);	//AntePierna Izquierda
	bodyRagdolls[13] = Box2DHelper::CreateRectangularDynamicBody(Mundo, TamPie, TamPie, 2.f, 0.2f, 0.1f);					//pie izquierda


	//Posiciones de las partes del cuerpo
	
	// Cabeza y Pecho
	float PosCabezaX = posX;
	float PosCabezaY = posY;

	float PosPechoX   = PosCabezaX;
	float PosPechoY   = PosCabezaY + (TamCabeza / 2) + (TamPechoY / 2) + 0.2f;

	//Brazos
	float PosBrazoDX = PosCabezaX + (TamPechoX / 2) + (TamBrazoX / 2) + 0.2f;
	float PosBrazoIX = PosCabezaX - (TamPechoX / 2) - (TamBrazoX / 2) - 0.2f;
	float PosBrazoY = PosCabezaY + (TamCabeza / 2) + (TamBrazoY / 2) + 0.2f;

	//AnteBrazos
	float PosAnteBrazoDX = PosBrazoDX;
	float PosAnteBrazoIX = PosBrazoIX;
	float PosAnteBrazoY = PosBrazoY + (TamBrazoY / 2) + (TamAnteBrazoY / 2) + 0.2f;
	
	//Manos
	float PosManoDX = PosBrazoDX;
	float PosManoIX = PosBrazoIX;
	float PosManoY = PosAnteBrazoY + (TamAnteBrazoY / 2) + (TamMano / 2) + 0.2f;

	//Piernas
	float PosPiernaDX = PosCabezaX + ((TamPechoX / 2) / 2);
	float PosPiernaIX = PosCabezaX - ((TamPechoX / 2) / 2);
	float PosPiernaY  = PosPechoY + (TamPechoY / 2) + (TamPiernaY / 2) + 0.2f;

	//AntePiernas
	float PosAntePiernaDX = PosPiernaDX;
	float PosAntePiernaIX = PosPiernaIX;
	float PosAntePiernaY = PosPiernaY + (TamPiernaY / 2) + (TamAntePiernaY / 2) + 0.2f;

	//Pies
	float PosPieDX = PosPiernaDX;
	float PosPieIX = PosPiernaIX;
	float PosPieY = PosAntePiernaY + (TamAntePiernaY / 2) + (TamPie / 2) + 0.2f;


	//Posicion de los elementos
	bodyRagdolls[0]->SetTransform(b2Vec2(PosCabezaX, PosCabezaY), 0.f);				//Cabeza
	bodyRagdolls[1]->SetTransform(b2Vec2(PosPechoX, PosPechoY), 0.f);				//Pecho

	bodyRagdolls[2]->SetTransform(b2Vec2(PosBrazoDX, PosBrazoY), 0.f);				//Brazo Derecho
	bodyRagdolls[3]->SetTransform(b2Vec2(PosAnteBrazoDX, PosAnteBrazoY), 0.f);		//AnteBrazo Derecho
	bodyRagdolls[4]->SetTransform(b2Vec2(PosManoDX, PosManoY), 0.f);				//Mano Derecha

	bodyRagdolls[5]->SetTransform(b2Vec2(PosBrazoIX, PosBrazoY), 0.f);				//Brazo Izquierdo
	bodyRagdolls[6]->SetTransform(b2Vec2(PosAnteBrazoIX, PosAnteBrazoY), 0.f);		//AnteBrazo Izquierdo
	bodyRagdolls[7]->SetTransform(b2Vec2(PosManoIX, PosManoY), 0.f);				//Mano Izquierda

	bodyRagdolls[8]->SetTransform(b2Vec2(PosPiernaDX, PosPiernaY), 0.f);			//Pierna Derecha
	bodyRagdolls[9]->SetTransform(b2Vec2(PosAntePiernaDX, PosAntePiernaY), 0.f);	//AntePierna Derecha
	bodyRagdolls[10]->SetTransform(b2Vec2(PosPieDX, PosPieY), 0.f);					//Pie Derecho

	bodyRagdolls[11]->SetTransform(b2Vec2(PosPiernaIX, PosPiernaY), 0.f);			//Pierna Izquierda
	bodyRagdolls[12]->SetTransform(b2Vec2(PosAntePiernaIX, PosAntePiernaY), 0.f);	//AntePierna Izquierda
	bodyRagdolls[13]->SetTransform(b2Vec2(PosPieIX, PosPieY), 0.f);					//Pie Izquierdo
	
	for (int i = 0; i < 14; i++)	bodyRagdolls[i]->SetUserData(this); //Cargamos el User Data

	CargarImagenes();
	Vinculador();

	//Resortes

	//Cabeza con Torso
	Box2DHelper::CreateDistanceJoint(Mundo, bodyRagdolls[0], bodyRagdolls[0]->GetPosition(), bodyRagdolls[1], bodyRagdolls[1]->GetPosition(), 0.25f, 4.f, 0.1f);
	
	/////////////////////////
	//Torso con Brazo Derecho
	Box2DHelper::CreateDistanceJoint(Mundo, bodyRagdolls[1], b2Vec2(PosPechoX + (TamPechoX / 2) - 0.1f, PosPechoY - (TamPechoY / 2) + 0.1f), bodyRagdolls[2], b2Vec2(PosBrazoDX - (TamBrazoX / 2) + 0.1f, PosBrazoY - (TamBrazoY / 2) + 0.1f), 0.15f, 5.f, 0.3f);

	//Brazo con AnteBrazo Derecho
	Box2DHelper::CreateDistanceJoint(Mundo, bodyRagdolls[2], b2Vec2(PosBrazoDX, PosBrazoY + (TamBrazoY / 2) - 0.1f), bodyRagdolls[3], b2Vec2(PosAnteBrazoDX, PosAnteBrazoY - (TamAnteBrazoY / 2) + 0.1f), 0.15f, 5.f, 0.3f);

	//AnteBrazo con Mano Derecho
	Box2DHelper::CreateDistanceJoint(Mundo, bodyRagdolls[3], b2Vec2(PosAnteBrazoDX, PosAnteBrazoY + (TamAnteBrazoY / 2) - 0.1f), bodyRagdolls[4], b2Vec2(PosManoDX, PosManoY - (TamMano / 2) + 0.1f), 0.15f, 5.f, 0.3f);

	////////////////////////////
	//Torso con Brazo Izquierdo
	Box2DHelper::CreateDistanceJoint(Mundo, bodyRagdolls[1], b2Vec2(PosPechoX - (TamPechoX / 2) + 0.1f, PosPechoY - (TamPechoY / 2) + 0.1f), bodyRagdolls[5], b2Vec2(PosBrazoIX + (TamBrazoX / 2) - 0.1f, PosBrazoY - (TamBrazoY / 2) + 0.1f), 0.15f, 5.f, 0.3f); 
	
	//Brazo con AnteBrazo Izquierdo
	Box2DHelper::CreateDistanceJoint(Mundo, bodyRagdolls[5], b2Vec2(PosBrazoIX, PosBrazoY + (TamBrazoY / 2) - 0.1f), bodyRagdolls[6], b2Vec2(PosAnteBrazoIX, PosAnteBrazoY - (TamAnteBrazoY / 2) + 0.1f), 0.15f, 5.f, 0.3f);

	/// AnteBrazo con Mano Izquierda
	Box2DHelper::CreateDistanceJoint(Mundo, bodyRagdolls[6], b2Vec2(PosAnteBrazoIX, PosAnteBrazoY + (TamAnteBrazoY / 2) - 0.1f), bodyRagdolls[7], b2Vec2(PosManoIX, PosManoY - (TamMano / 2) + 0.1f), 0.15f, 5.f, 0.3f);

	///////////////////////////
	//Torso con Pierna Derecha
	Box2DHelper::CreateDistanceJoint(Mundo, bodyRagdolls[1], b2Vec2(PosPechoX + ((TamPechoX / 2) / 2), PosPechoY + (TamPechoY / 2) - 0.1f), bodyRagdolls[8], b2Vec2(PosPiernaDX, PosPiernaY - (TamPiernaY / 2) + 0.1f), 0.15f, 5.f, 0.3f);
	
	//Pierna con AntePierna Derecha
	Box2DHelper::CreateDistanceJoint(Mundo, bodyRagdolls[8], b2Vec2(PosPiernaDX, PosPiernaY + (TamPiernaY / 2) - 0.1f), bodyRagdolls[9], b2Vec2(PosAntePiernaDX, PosAntePiernaY - (TamAntePiernaY / 2) + 0.1f), 0.15f, 5.f, 0.3f);

	//AntePierna con Pie Derecho
	Box2DHelper::CreateDistanceJoint(Mundo, bodyRagdolls[9], b2Vec2(PosAntePiernaDX, PosAntePiernaY + (TamAntePiernaY / 2) - 0.1f), bodyRagdolls[10], b2Vec2(PosPieDX, PosPieY - (TamPie / 2) + 0.1f), 0.15f, 5.f, 0.3f);

	////////////////////////////
	//Torso con Pierna Izquierda	
	Box2DHelper::CreateDistanceJoint(Mundo, bodyRagdolls[1], b2Vec2(PosPechoX - ((TamPechoX / 2) / 2), PosPechoY + (TamPechoY / 2) - 0.1f), bodyRagdolls[11], b2Vec2(PosPiernaIX, PosPiernaY - (TamPiernaY / 2) + 0.1f), 0.15f, 5.f, 0.3f); 
	
	//Pierrna con AntePierna Izquierda
	Box2DHelper::CreateDistanceJoint(Mundo, bodyRagdolls[11], b2Vec2(PosPiernaIX, PosPiernaY + (TamPiernaY / 2) - 0.1f), bodyRagdolls[12], b2Vec2(PosAntePiernaIX, PosAntePiernaY - (TamAntePiernaY / 2) + 0.1f), 0.15f, 5.f, 0.3f);

	//AntePierna con Pie Izqwuierdo
	Box2DHelper::CreateDistanceJoint(Mundo, bodyRagdolls[12], b2Vec2(PosAntePiernaIX, PosAntePiernaY + (TamAntePiernaY / 2) - 0.1f), bodyRagdolls[13], b2Vec2(PosPieIX, PosPieY - (TamPie / 2) + 0.1f), 0.15f, 5.f, 0.3f);
}

//Carga las imagenes del Ragdoll
void Ragdoll::CargarImagenes() {

	//Cabeza
	texRagdolls[0] = new Texture();
	texRagdolls[0]->loadFromFile("Imagenes/Ragdoll/Cabeza.png");
	spRagdolls[0] = new Sprite(*texRagdolls[0]);

	//Torso
	texRagdolls[1] = new Texture();
	texRagdolls[1]->loadFromFile("Imagenes/Ragdoll/Torso.png");
	spRagdolls[1] = new Sprite(*texRagdolls[1]);

	//Brazo Derecho
	texRagdolls[2] = new Texture();
	texRagdolls[2]->loadFromFile("Imagenes/Ragdoll/BrazoD.png");
	spRagdolls[2] = new Sprite(*texRagdolls[2]);

	texRagdolls[3] = new Texture();
	texRagdolls[3]->loadFromFile("Imagenes/Ragdoll/AnteBrazoD.png");
	spRagdolls[3] = new Sprite(*texRagdolls[3]);

	texRagdolls[4] = new Texture();
	texRagdolls[4]->loadFromFile("Imagenes/Ragdoll/ManoD.png");
	spRagdolls[4] = new Sprite(*texRagdolls[4]);

	//Brazo Izquierdo
	texRagdolls[5] = new Texture();
	texRagdolls[5]->loadFromFile("Imagenes/Ragdoll/BrazoI.png");
	spRagdolls[5] = new Sprite(*texRagdolls[5]);

	texRagdolls[6] = new Texture();
	texRagdolls[6]->loadFromFile("Imagenes/Ragdoll/AnteBrazoI.png");
	spRagdolls[6] = new Sprite(*texRagdolls[6]);

	texRagdolls[7] = new Texture();
	texRagdolls[7]->loadFromFile("Imagenes/Ragdoll/ManoI.png");
	spRagdolls[7] = new Sprite(*texRagdolls[7]);

	//Pierna Derecha
	texRagdolls[8] = new Texture();
	texRagdolls[8]->loadFromFile("Imagenes/Ragdoll/PiernaD.png");
	spRagdolls[8] = new Sprite(*texRagdolls[8]);

	texRagdolls[9] = new Texture();
	texRagdolls[9]->loadFromFile("Imagenes/Ragdoll/AntePiernaD.png");
	spRagdolls[9] = new Sprite(*texRagdolls[9]);

	texRagdolls[10] = new Texture();
	texRagdolls[10]->loadFromFile("Imagenes/Ragdoll/PieD.png");
	spRagdolls[10] = new Sprite(*texRagdolls[10]);

	//Pierna Izquierda
	texRagdolls[11] = new Texture();
	texRagdolls[11]->loadFromFile("Imagenes/Ragdoll/PiernaI.png");
	spRagdolls[11] = new Sprite(*texRagdolls[11]);

	texRagdolls[12] = new Texture();
	texRagdolls[12]->loadFromFile("Imagenes/Ragdoll/AntePiernaI.png");
	spRagdolls[12] = new Sprite(*texRagdolls[12]);

	texRagdolls[13] = new Texture();
	texRagdolls[13]->loadFromFile("Imagenes/Ragdoll/PieI.png");
	spRagdolls[13] = new Sprite(*texRagdolls[13]);
}

//Destructor
Ragdoll::~Ragdoll() {

	for (int i = 0; i < 14; i++) Mundo->DestroyBody(bodyRagdolls[i]);
}

//Actualiza las imagenes segun el body
void Ragdoll::Actualizar() {

	for (int i = 0; i < 14; i++) {

		spRagdolls[i]->setPosition(bodyRagdolls[i]->GetPosition().x, bodyRagdolls[i]->GetPosition().y);
		spRagdolls[i]->setRotation(Rad2Deg(bodyRagdolls[i]->GetAngle()));
	}
}

//Dibuja el Ragdoll
void Ragdoll::Dibujar() {
	for (int i = 0; i < 14; i++) Ventana->draw(*spRagdolls[i]);
}

//Se encarga de calcular el tamaño de la imagen y adaptarlo al body de cada parte del Ragdoll
void Ragdoll::Vinculador() {

	for (int i = 0; i < 14; i++) {

		spRagdolls[i]->setOrigin(texRagdolls[i]->getSize().x / 2.f, texRagdolls[i]->getSize().y / 2.f);
		spRagdolls[i]->setPosition(bodyRagdolls[i]->GetPosition().x, bodyRagdolls[i]->GetPosition().y);
		spRagdolls[i]->setRotation(Rad2Deg(bodyRagdolls[i]->GetAngle()));

		b2AABB dimension;

		dimension.upperBound = b2Vec2(-FLT_MAX, FLT_MAX);
		dimension.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);

		for (b2Fixture* F = bodyRagdolls[i]->GetFixtureList(); F != NULL; F = F->GetNext()) {
			dimension = F->GetAABB(0);
		}

		spRagdolls[i]->setScale(dimension.GetExtents().x * 2 / texRagdolls[i]->getSize().x, dimension.GetExtents().y * 2 / texRagdolls[i]->getSize().y);
	}
}

//Aplica la fuerza de impulso al Ragdoll
void Ragdoll::Fuerzas(float fuerza, float radianes) {

	for (int i = 0; i < 14; i++) bodyRagdolls[i]->ApplyForceToCenter(b2Vec2(fuerza * cos(radianes), fuerza * sin(radianes)), false);
}

