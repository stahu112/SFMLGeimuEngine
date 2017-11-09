#include "Character_Candy.h"
#include "States\Playing_State.h"

#define DEGTORAD 0.01745329252;

void Character_Candy::input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x = -1;
	}
	else
	{			
		velocity.x = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		velocity.y = -1;
	}
	else
	{
		velocity.y = 0;
	}

	if (InputHandler::checkDown(sf::Keyboard::LControl))
	{
		if (velocity.x != 0) slide = true;
		else crouch = true;
	}
	else if (InputHandler::checkUp(sf::Keyboard::LControl))
	{
		slide = false;
		crouch = false;
	}

}

void Character_Candy::update(float dt)
{

	input();

	sf::Vector2f pos = sf::Vector2f(body->GetPosition().x * 32 - 16, body->GetPosition().y * 32 - 32);

	b2Vec2 vel = body->GetLinearVelocity();

	if (goalVelocity.x > 0) { changeAnim(AnimationID::RunR); sprite.setTexture(Resource_Holder::get().getTexture(Texture_Name::spritesheet)); }
	else if (goalVelocity.x < 0) { changeAnim(AnimationID::RunL); sprite.setTexture(Resource_Holder::get().getTexture(Texture_Name::spritesheet1)); }
	else { changeAnim(AnimationID::Idle); }

	float velChange = goalVelocity.x - vel.x;
	float force = body->GetMass() * velChange / dt;
	body->ApplyForce(b2Vec2(force, 0), body->GetWorldCenter(), true);

	if (currentState == CState::Jump && !inAir) jump();
	if (currentState == CState::Catapult && !inAir) catapult();

	setPosition(pos);

	processStates();

	std::cout << (int)currentState << std::endl;

	sprite.setPosition(pos);

	updateAnim();
}

void Character_Candy::processStates()
{

	switch (currentState)
	{
	case CState::Idle:
		if (velocity.x > 0)
		{
			currentState = CState::RunR;
		}
		if (velocity.x < 0)
		{
			currentState = CState::RunL;
		}

		if (crouch)
		{
			currentState = CState::Crouch;
		}

		if (velocity.y < 0)
		{
			currentState = CState::Jump;
		}
		break;

	case CState::RunR:
		goalVelocity.x = 5;

		if (velocity.x == 0)
		{
			currentState = CState::Idle;
			goalVelocity.x = 0;
		}

		if (slide)
		{
			currentState = CState::Slide;
		}

		if (velocity.x < 0)
		{
			currentState = CState::RunL;
		}

		if (velocity.y < 0)
		{
			currentState = CState::Jump;
		}
		break;

	case CState::RunL:
		goalVelocity.x = -5;

		if (velocity.x == 0)
		{
			currentState = CState::Idle;
			goalVelocity.x = 0;
		}

		if (slide)
		{
			currentState = CState::Slide;
		}

		if (velocity.x > 0)
		{
			currentState = CState::RunR;
		}

		if (velocity.y < 0)
		{
			currentState = CState::Jump;
		}
		break;

	case CState::Jump:
		if (body->GetLinearVelocity().y > 0) currentState = CState::Dive;
		break;

	case CState::Dive:
		if (body->GetLinearVelocity().y == 0)
		{
			currentState = CState::Idle;
		}
		break;

	case CState::Slide:
		body->SetTransform(body->GetPosition(), 90 * 0.01745329252);
		if (velocity.x == 0) currentState = CState::Idle;
		if (body->GetLinearVelocity().x != 0 && velocity.y < 0)
		{
			currentState = CState::Catapult;
		}
		break;

	case CState::Crouch:
		if (!crouch) currentState = CState::Idle;
		body->SetTransform(body->GetPosition(), 90 * 0.01745329252);
		break;

	case CState::Catapult:
		if (body->GetLinearVelocity().y > 0) currentState = CState::Dive;
		break;
	}

	if (inAir)
	{
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x + goalVelocity.x*0.2, body->GetLinearVelocity().y));
	}
	else if (velocity.x == 0) goalVelocity.x = 0;
	if ((currentState != CState::Catapult ||
		currentState != CState::Jump ||
		currentState != CState::Dive) &&
		body->GetLinearVelocity().y == 0)
	{
		inAir = false;
	}
	if (currentState != CState::Slide && currentState != CState::Crouch) body->SetTransform(body->GetPosition(), 0);
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
	b2BodyDef bodyDef;

	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(Position.x/32, Position.y/32);

	body = boxWorldPtr->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.35, 0.95);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.1f;

	body->CreateFixture(&fixtureDef);
	body->SetFixedRotation(true);
	body->SetGravityScale(2);

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

	initAnimations();
}

void Character_Candy::jump()
{
	if (!inAir)
	{
		float impulse = body->GetMass() * 10;
		body->ApplyLinearImpulse(b2Vec2(0, -impulse), body->GetWorldCenter(), true);
		inAir = true;
	}
}

void Character_Candy::catapult()
{
	if (!inAir)
	{
		float impulse = body->GetMass() * 12;
		body->ApplyLinearImpulse(b2Vec2(0, -impulse), body->GetWorldCenter(), true);
		inAir = true;
	}
}
