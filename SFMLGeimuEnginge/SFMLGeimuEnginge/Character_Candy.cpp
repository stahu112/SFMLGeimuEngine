#include "Character_Candy.h"
#include "States\Playing_State.h"
#include "ColFilters.h"
#include "UtilFunc.h"

#define DEGTORAD 0.01745329252;

bool once = false, debug = false;
bool canDo = false;

float timer = 0, timer1 = 0;
float timerGround = 0;

void Character_Candy::input(float dt)
{
	if (onGround)
	{
		if ((wallR || wallL) && !falling)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				pullUp(dt);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				pullUp(dt);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			jump(dt);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			goalVelocity.x = speedX;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			goalVelocity.x = -speedX;
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				pullUp(dt);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				wallJump(dt, 1);
			}
		}

		if (wallL && !falling)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				pullUp(dt);
			}
		
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				wallJump(dt, 0);
			}
		}
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !wallR)
		{
			if (goalVelocity.x > speedX) goalVelocity.x = speedX;
			goalVelocity.x += dt * 13;
		}
		else
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !wallL)
		{
			if (goalVelocity.x < -speedX) goalVelocity.x = -speedX;
			goalVelocity.x -= dt * 13;
		}
		else
		{
			if (goalVelocity.x < 0) { goalVelocity.x += dt * 16; if (goalVelocity.x > 0) goalVelocity.x = 0; }
			else if (goalVelocity.x > 0) { goalVelocity.x -= dt * 16; if (goalVelocity.x < 0) goalVelocity.x = 0; }
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) debug = true;
}

//Forcefully change position "BLINK"
void Character_Candy::changePosition(b2Vec2 newPos)
{
	body->SetTransform(b2Vec2(newPos),0);
	Position = sf::Vector2f(newPos.x, newPos.y);
}

//UPDATE
void Character_Candy::update(float dt)
{

	input(dt);

	sf::Vector2f pos = sf::Vector2f(body->GetPosition().x * 32 - 16, body->GetPosition().y * 32 - 32);

	Position = pos;

	vel = body->GetLinearVelocity();

	//if (body->GetLinearVelocity().y < -8) body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -8));

	processStates(dt);

	vel.x = Utils::approach(goalVelocity.x, vel.x, dt);

	//GROUND CONTACTS
	//#############################
	if (numContacts > 0)
	{
		onGround = true;
		falling = false;
		canDo = false;
	}
	else
	{
		onGround = false;
	}

	if (onGround)
	{
		timerGround += dt;
	}
	else
	{
		timerGround = 0;
	}

	//WALL CONTACTS
	//#############################

	body->SetLinearVelocity(vel);

	if (numWallRContacts > 0)
	{
		wallR = true;
	}
	else
	{
		wallR = false;
		wallDone = true;
	}

	if (numWallLContacts > 0)
	{
		wallL = true;
	}
	else
	{
		wallL = false;
		wallDone = true;
	}

	if (!wallL && !wallR)
	{
		timer = 0;
		timer1 = 0;
		once = false;
	}

	//std::cout << "numContacts" << numContacts << " numWallL" << numWallLContacts << " numWallR" << numWallRContacts << std::endl;
	 

	if (vel.y > 0)
	{
		body->SetGravityScale(4);
	}
	else
	{
		body->SetGravityScale(2.25);
	}

	if (vel.y < -10)
	{
		body->SetLinearVelocity(b2Vec2(vel.x, -10));
	}

	if (vel.y > 16)
	{
		body->SetLinearVelocity(b2Vec2(vel.x, 16));
	}

	setPosition(pos);

	//std::cout << onGround << std::endl;

	updateAnim();
	sprite.setPosition(pos);

	if (debug) debugData();

}

//PROCESS PLAYER STATES
void Character_Candy::processStates(float dt)
{

	switch (currentState)
	{
	case CState::Idle:
		if (body->GetLinearVelocity().x > 0.2)
		{
			currentState = CState::RunR;
		}
		if (body->GetLinearVelocity().x < -0.2)
		{
			currentState = CState::RunL;
		}

		if (!onGround)
		{
			currentState = CState::Jump;
		}
		break;

	case CState::RunR:

		if (body->GetLinearVelocity().x == 0)
		{
			currentState = CState::Idle;
		}

		if (!onGround)
		{
			currentState = CState::Jump;
		}
		break;

	case CState::RunL:

		if (body->GetLinearVelocity().x == 0)
		{
			currentState = CState::Idle;
		}

		if (!onGround)
		{
			currentState = CState::Jump;
		}
		break;

	case CState::Jump:
	
		if (body->GetLinearVelocity().y > 0.1)
		{
			currentState = CState::Dive;
		}
		break;

	case CState::Dive:
		
		if (onGround)
		{
			currentState = CState::Idle;
		}
		break;

	case CState::WallJumpL:
		
		if (body->GetLinearVelocity().y > 0.1)
		{
			currentState = CState::Dive;
		}
		else if (wallDone)
		{
			currentState = CState::Jump;
		}
		break;

	case CState::WallJumpR:

		if (body->GetLinearVelocity().y > 0.1)
		{
			currentState = CState::Dive;
		}
		else if (wallDone)
		{
			currentState = CState::Jump;
		}
		break;

	}

	if (!onGround && numWallLContacts > 0) currentState = CState::WallJumpL;
	if (!onGround && numWallRContacts > 0) currentState = CState::WallJumpR;
}

//ANIMATION MANAGING
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
	if (body->GetLinearVelocity().x > 0.1)
	{
		changeAnim(AnimationID::RunR);
		sprite.setTexture(Resource_Holder::get().getTexture(Texture_Name::spritesheet1));
	}

	else if (body->GetLinearVelocity().x < -0.1)
	{
		changeAnim(AnimationID::RunL);
		sprite.setTexture(Resource_Holder::get().getTexture(Texture_Name::spritesheet));
	}
	else { changeAnim(AnimationID::Idle); }

	sprite.setTextureRect(animation->getFrame());
	sprite.setScale(
		size.x / sprite.getLocalBounds().width,
		size.y / sprite.getLocalBounds().height
	);
}

//Create body and sensors for player
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

	b2CircleShape shape;
	shape.m_radius = 0.2;
	shape.m_p.x = -0.15;

	b2CircleShape shape1;
	shape1.m_radius = 0.2;
	shape1.m_p.x = 0.15;

	b2FixtureDef shapef;
	b2FixtureDef shape1f;

	shapef.shape = &shape;
	shape1f.shape = &shape1;

	shapef.density = 1;
	shape1f.density = 1;

	shapef.friction = 0;
	shape1f.friction = 0;

	//MAIN BOX
	b2Vec2 vert[8];
	vert[0].Set(-0.35, 0.80);
	vert[1].Set(-0.28, 0.95);
	vert[2].Set(0.28, 0.95);
	vert[3].Set(0.35, 0.80);
	vert[4].Set(0.35, -0.80);
	vert[5].Set(0.28, -0.95);
	vert[6].Set(-0.28, -0.95);
	vert[7].Set(-0.35, -0.80);

	//SETBOX
	b2PolygonShape dynamicBox;
	dynamicBox.Set(vert, 8);

	//dynamicBox.SetAsBox(0.3, 0.750);

	//SET FIXUTRE
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.f;

	body->CreateFixture(&fixtureDef);
	body->CreateFixture(&shapef);
	body->CreateFixture(&shape1f);

	//SET ROTATION AND GRAV SCALE
	body->SetFixedRotation(true);
	body->SetGravityScale(2.25);

	//GroundSensor
	b2PolygonShape sensorLow;
	sensorLow.SetAsBox(0.32, 0.08, b2Vec2(Position.x/32, Position.y/32 + 0.95), 0);

	sensorLowFix.shape = &sensorLow;
	sensorLowFix.isSensor = true;
	
	//RightWallActions
	b2PolygonShape sensorRWall;

	sensorRWall.SetAsBox(0.05, 0.40, b2Vec2(Position.x / 32 + 0.35, Position.y / 32 + 0.4f), 0);

	sensorRWallFix.shape = &sensorRWall;
	sensorRWallFix.isSensor = true;

	//LeftWallActions
	b2PolygonShape sensorLWall;

	sensorLWall.SetAsBox(0.05, 0.40, b2Vec2(Position.x / 32 - 0.35, Position.y / 32 + 0.4f), 0);

	sensorLWallFix.shape = &sensorLWall;
	sensorLWallFix.isSensor = true;
	
	b2Fixture* footSensorFixture = body->CreateFixture(&sensorLowFix);
	footSensorFixture->SetUserData((void*)"GroundSensor");

	b2Fixture* WallLFixture = body->CreateFixture(&sensorLWallFix);
	WallLFixture->SetUserData((void*)"WallL");

	b2Fixture* WallRFixture = body->CreateFixture(&sensorRWallFix);
	WallRFixture->SetUserData((void*)"WallR");
}

//Initialize animations
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
	Idle.addFrames({ 0,0,20,38 }, 0.1f);
	addAnimations(AnimationID::Idle, Idle);

	setCurrentAnim();
}

//Add an animation to anim map
void Character_Candy::addAnimations(AnimationID id, Animation & animation)
{
	m_animations.insert(std::make_pair(id, animation));
}

//Constructor
Character_Candy::Character_Candy(State::Playing & state)
{
	sprite.setTexture(Resource_Holder::get().getTexture(Texture_Name::spritesheet));
	size = { 32,64 };
	sprite.setScale(
		size.x / sprite.getLocalBounds().width,
		size.y / sprite.getLocalBounds().height
	);

	speedX = 5;

	boxWorldPtr = state.getWorld();

	createRigidBody();

	force = body->GetMass() * 5;

	initAnimations();
}

//Variables displayed
void Character_Candy::debugData()
{
	sf::Text text;

	std::string linVelX, linVelY,
		velX, velY,
		x, y,
		onGroundS,
		wallRS,
		wallLS,
		wallDoneS,
		onceS,
		stateS,
		animS;


	text.setFont(Resource_Holder::get().getFont(Font_Name::Powerfull));

	text.setScale(0.2, 0.2);

	x = std::to_string((int)body->GetPosition().x);
	y = std::to_string((int)body->GetPosition().y);

	onGroundS = std::to_string(onGround);
	wallRS = std::to_string(wallR);
	wallLS = std::to_string(wallL);
	wallDoneS = std::to_string(wallDone);
	onceS = std::to_string(once);

	stateS = std::to_string((int)currentState);

	animS = std::to_string((int)currentAnim);

	linVelX = std::to_string((int)body->GetLinearVelocity().x);
	linVelY = std::to_string((int)body->GetLinearVelocity().y);
	
	velX = std::to_string((int)vel.x);
	velY = std::to_string((int)vel.y);

	text.setString("STATE: " + stateS + "\n\nANIM: " + animS + "\n\nX: " + x + "\t\tY: " + y + "\n\nVEL X: " + velX + "\t\tVEL Y:" + velY + "\n\nLIN VEL X: " + linVelX + "\t\tLIN VEL Y: " + linVelY + "\n\nGROUND: " + onGroundS + "\n\nWALL L : " + wallLS + "\t\tWALL R : " + wallRS +"\n\nWALL DONE : " + wallDoneS + "\t\tONCE: " + onceS);

	text.setFillColor(sf::Color(0, 0, 0, 255));

	text.setPosition(Display::getView().getCenter().x, Display::getView().getCenter().y - 5);

	Display::draw(text);

}

//COMMANDS
void Character_Candy::jump(float dt)
{
	float impulse = body->GetMass() * 6;
	body->ApplyLinearImpulse(b2Vec2(0, -impulse), body->GetWorldCenter(), true);
}


//WALLJUMP
void Character_Candy::wallJump(float dt, bool right)
{
	if (wallDone && !falling && canDo)
	{
		float impulse = body->GetMass();
		if(right) goalVelocity.x = -speedX;
		else goalVelocity.x = speedX;
		if (right) body->ApplyLinearImpulse(b2Vec2(-3, -impulse * 40), body->GetWorldCenter(), true);
		else body->ApplyLinearImpulse(b2Vec2(3, -impulse * 40), body->GetWorldCenter(), true);
		wallDone = false;
	}

	if (timer1 > 0.2f) canDo = true;
}

//WALLRUN UP
void Character_Candy::pullUp(float dt)
{
	if (!falling)
	{
		timer1 += dt;

		float impulse = body->GetMass();

		if (!once)
		{
			body->SetLinearVelocity(b2Vec2(vel.x, 0));
			once = true;
		}

		if (vel.y < -5.5)
		{
			body->SetLinearVelocity(b2Vec2(vel.x, -5.5));
		}

		if (timer1 < 0.3f) body->ApplyLinearImpulse(b2Vec2(0, -impulse), body->GetWorldCenter(), true);
		else if (timer1 > 0.5f) body->SetLinearVelocity(b2Vec2(vel.x, 2));
	}
}

