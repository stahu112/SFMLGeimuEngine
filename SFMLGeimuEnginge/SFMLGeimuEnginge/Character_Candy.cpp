#include "Character_Candy.h"
#include "States\Playing_State.h"
#include "ColFilters.h"
#include "UtilFunc.h"

#define DEGTORAD 0.01745329252;

bool once = false;

float timer = 0;

void Character_Candy::input(float dt)
{
	if (onGround)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			jump();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			goalVelocity.x = 5;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			goalVelocity.x = -5;
		}
		else 
		{
			goalVelocity.x = 0;
		}
	}
	else
	{
		if (wallR && !falling)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				if (goalVelocity.x < -5) goalVelocity.x = -5;
				goalVelocity.x -= dt * 10;
			}
			else
			{
				goalVelocity.x += dt * 10; 
				if (goalVelocity.x > 0) goalVelocity.x = 0;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				float impulse = body->GetMass();
				goalVelocity.x = -5;
				body->ApplyLinearImpulse(b2Vec2(-3, -impulse * 30), body->GetWorldCenter(), true);
				wallDone = false;
			}
		}

		if (wallL && !falling)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				if (goalVelocity.x > 5) goalVelocity.x = 5;
				goalVelocity.x += dt * 10;
			}
			else
			{
				goalVelocity.x -= dt * 10;
				if (goalVelocity.x < 0) goalVelocity.x = 0; 
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				float impulse = body->GetMass();
				goalVelocity.x = 5;
				body->ApplyLinearImpulse(b2Vec2(3, -impulse * 30), body->GetWorldCenter(), true);
				wallDone = false;

			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (goalVelocity.x > 5) goalVelocity.x = 5;
			goalVelocity.x += dt * 20;
		}
		else
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (goalVelocity.x < -5) goalVelocity.x = -5;
			goalVelocity.x -= dt * 20;
		}
		else
		{
			if (goalVelocity.x < 0) { goalVelocity.x += dt * 10; if (goalVelocity.x > 0) goalVelocity.x = 0; }
			else if (goalVelocity.x > 0) { goalVelocity.x -= dt * 10; if (goalVelocity.x < 0) goalVelocity.x = 0; }
		}
	}
}

void Character_Candy::update(float dt)
{

	input(dt);

	sf::Vector2f pos = sf::Vector2f(body->GetPosition().x * 32 - 16, body->GetPosition().y * 32 - 32);

	vel = body->GetLinearVelocity();

	if (vel.y < -10) vel.y = -10;

	processStates(dt);

	if (goalVelocity.x > 0) 
	{
		changeAnim(AnimationID::RunR);
		sprite.setTexture(Resource_Holder::get().getTexture(Texture_Name::spritesheet));
	}
	
	else if (goalVelocity.x < 0)
	{ 
		changeAnim(AnimationID::RunL);
		sprite.setTexture(Resource_Holder::get().getTexture(Texture_Name::spritesheet1));
	}
	else { changeAnim(AnimationID::Idle); }

	vel.x = Utils::approach(goalVelocity.x, vel.x, dt);

	//GROUND CONTACTS
	//#############################
	if (numContacts > 0)
	{
		onGround = true;
		falling = false;
	}
	else
	{
		onGround = false;
	}

	//WALL CONTACTS
	//#############################

	body->SetLinearVelocity(vel);
	
	if (numWallRContacts > 0)
	{
		wallR = true;
		if (numWallRContacts == 1)
		{	
			wallR = false;
			pullUp(dt);
		}
	}
	else
	{
		wallR = false;
		wallDone = true;
	}

	if (numWallLContacts > 0)
	{
		wallL = true;
		if (numWallLContacts == 1)
		{
			wallL = false;
			pullUp(dt);
		}
	}
	else
	{
		wallL = false;
		wallDone = true;
	}

	if (wallL || wallR)
	{
		wallJump(dt);
	}
	else
	{
		timer = 0;
	}

	std::cout << "numContacts" << numContacts << " numWallL" << numWallLContacts << " numWallR" << numWallRContacts << std::endl;
	 
	setPosition(pos);

	//std::cout << onGround << std::endl;

	updateAnim();
	sprite.setPosition(pos);

}

void Character_Candy::processStates(float dt)
{

	switch (currentState)
	{
	case CState::Idle:
		if (vel.x > 0)
		{
			currentState = CState::RunR;
		}
		if (vel.x < 0)
		{
			currentState = CState::RunL;
		}

		if (vel.y < 0)
		{
			currentState = CState::Jump;
		}
		break;

	case CState::RunR:

		if (vel.x == 0)
		{
			currentState = CState::Idle;
		}

		if (vel.x < 0)
		{
			currentState = CState::RunL;
		}

		if (vel.y < 0)
		{
			currentState = CState::Jump;
		}
		break;

	case CState::RunL:

		if (vel.x == 0)
		{
			currentState = CState::Idle;
		}

		if (vel.x > 0)
		{
			currentState = CState::RunR;
		}

		if (vel.y < 0)
		{
			currentState = CState::Jump;
		}
		break;

	case CState::Jump:
	
		if (vel.y > 0)
		{
			currentState = CState::Dive;
		}
		break;

	case CState::Dive:
		
		if (vel.y == 0)
		{
			currentState = CState::Idle;
		}
		break;

	case CState::WallJumpL:
		
		if (vel.y > 0)
		{
			currentState = CState::Dive;
		}
		else if (vel.y < 0)
		{
			currentState = CState::Jump;
		}
		break;

	case CState::WallJumpR:

		if (vel.y > 0)
		{
			currentState = CState::Dive;
		}
		else if (vel.y < 0)
		{
			currentState = CState::Jump;
		}
		break;

	}

	if (!onGround && numWallLContacts > 1) currentState = CState::WallJumpL;
	if (!onGround && numWallRContacts > 1) currentState = CState::WallJumpR;
}

void Character_Candy::setCurrentAnim()
{
	animation = &m_animations.at(currentAnim);
}

void Character_Candy::changeAnim(AnimationID anim)
{
	if (currentAnim != anim)
	{
		animation->reset();
		currentAnim = anim;
		setCurrentAnim();
	}
}

void Character_Candy::updateAnim()
{
	sprite.setTextureRect(animation->getFrame());
	sprite.setScale(
		size.x / sprite.getLocalBounds().width,
		size.y / sprite.getLocalBounds().height
	);
}

void Character_Candy::createRigidBody()
{
	//BODYDEF
	b2BodyDef bodyDef;

	//FIXTURES
	b2FixtureDef fixtureDef;
	b2FixtureDef sensorLowFix;
	b2FixtureDef sensorLWallFix;
	b2FixtureDef sensorRWallFix;

	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(Position.x/32, Position.y/32);

	body = boxWorldPtr->CreateBody(&bodyDef); 
	
	//0,8 1,9
	//0,4 0,95


	//MAIN BOX
	b2Vec2 vert[8];
	vert[0].Set(-0.4, 0.94);
	vert[1].Set(-0.35, 0.95);
	vert[2].Set(0.35, 0.95);
	vert[3].Set(0.4, 0.94);
	vert[4].Set(0.4, -0.94);
	vert[5].Set(0.35, -0.95);
	vert[6].Set(-0.35, -0.95);
	vert[7].Set(-0.4, -0.94);

	//SETBOX
	b2PolygonShape dynamicBox;
	dynamicBox.Set(vert, 8);

	//dynamicBox.SetAsBox(0.3, 0.750);

	//SET FIXUTRE
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.f;

	body->CreateFixture(&fixtureDef);

	//SET ROTATION AND GRAV SCALE
	body->SetFixedRotation(true);
	body->SetGravityScale(2.25);

	b2PolygonShape sensorLow;
	sensorLow.SetAsBox(0.39, 0.05, b2Vec2(Position.x/32, Position.y/32 + 0.95), 0);

	sensorLowFix.shape = &sensorLow;
	sensorLowFix.isSensor = true;
	
	b2PolygonShape sensorRWall;

	sensorRWall.SetAsBox(0.05, 0.51, b2Vec2(Position.x / 32 + 0.41, Position.y / 32 + 0.42), 0);

	sensorRWallFix.shape = &sensorRWall;
	sensorRWallFix.isSensor = true;

	b2PolygonShape sensorLWall;

	sensorLWall.SetAsBox(0.05, 0.51, b2Vec2(Position.x / 32 - 0.41, Position.y / 32 + 0.42), 0);

	sensorLWallFix.shape = &sensorLWall;
	sensorLWallFix.isSensor = true;

	b2Fixture* footSensorFixture = body->CreateFixture(&sensorLowFix);
	footSensorFixture->SetUserData((void*)3);

	b2Fixture* WallLFixture = body->CreateFixture(&sensorLWallFix);
	WallLFixture->SetUserData((void*)2);

	b2Fixture* WallRFixture = body->CreateFixture(&sensorRWallFix);
	WallRFixture->SetUserData((void*)1);
}

void Character_Candy::initAnimations()
{
	Animation RunRAnim;
	RunRAnim.addFrames({ 0,0,20,38 }, 0.1f);
	RunRAnim.addFrames({ 20,0,20,38 }, 0.1f);
	RunRAnim.addFrames({ 40,0,20,38 }, 0.1f);
	RunRAnim.addFrames({ 60,0,20,38 }, 0.1f);
	RunRAnim.addFrames({ 0,38,20,38 }, 0.1f);
	RunRAnim.addFrames({ 20,38,20,38 }, 0.1f);
	addAnimations(AnimationID::RunR, RunRAnim);

	Animation RunLAnim;
	RunLAnim.addFrames({ 60,0,20,38 }, 0.1f);
	RunLAnim.addFrames({ 40,0,20,38 }, 0.1f);
	RunLAnim.addFrames({ 20,0,20,38 }, 0.1f);
	RunLAnim.addFrames({ 0,0,20,38 }, 0.1f);
	RunLAnim.addFrames({ 60,38,20,38 }, 0.1f);
	RunLAnim.addFrames({ 40,38,20,38 }, 0.1f);
	addAnimations(AnimationID::RunL, RunLAnim);

	Animation Idle;
	Idle.addFrames({ 0,0,20,38 }, 0.f);
	addAnimations(AnimationID::Idle, Idle);

	setCurrentAnim();
}

void Character_Candy::addAnimations(AnimationID id, Animation & animation)
{
	m_animations.insert(std::make_pair(id, animation));
}

Character_Candy::Character_Candy(State::Playing & state)
{
	sprite.setTexture(Resource_Holder::get().getTexture(Texture_Name::spritesheet));
	size = { 32,64 };
	sprite.setScale(
		size.x / sprite.getLocalBounds().width,
		size.y / sprite.getLocalBounds().height
	);

	boxWorldPtr = state.getWorld();

	createRigidBody();

	force = body->GetMass() * 5;

	initAnimations();
}

void Character_Candy::jump()
{
	float impulse = body->GetMass() * 5;
	body->ApplyLinearImpulse(b2Vec2(0, -impulse), body->GetWorldCenter(), true);
}

void Character_Candy::wallJump(float dt)
{
	if (wallDone && !falling)
	{
		timer += dt;

		if (timer < 20.f * dt && !onGround)
		{
			body->SetLinearVelocity(b2Vec2(vel.x, 0));
		}
		else
		{
			falling = true;
		}
	}
}

void Character_Candy::pullUp(float dt)
{
	if (!onGround)
	{
		body->SetLinearVelocity(b2Vec2(vel.x, 0));
		
		float impulse = body->GetMass() * 5;

		body->ApplyLinearImpulse(b2Vec2(0.7 * force, -impulse), body->GetWorldCenter(), true);
	}
}

