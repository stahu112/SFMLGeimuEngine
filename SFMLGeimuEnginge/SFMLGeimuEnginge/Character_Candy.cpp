#include "Character_Candy.h"
#include "States\Playing_State.h"

void Character_Candy::update(float dt)
{	
	//TODO REFACTOR
	if (velocity.x > 0)
	{
		if (currentAnim != &m_animations.at(AnimationID::RunR)) m_animations.at(AnimationID::RunR).reset();
		setCurrentAnim(AnimationID::RunR);
		sprite.setTexture(Resource_Holder::get().getTexture(Texture_Name::spritesheet));
	}
	else if (velocity.x < 0)
	{
		if (currentAnim != &m_animations.at(AnimationID::RunL)) m_animations.at(AnimationID::RunL).reset();
		setCurrentAnim(AnimationID::RunL);
		sprite.setTexture(Resource_Holder::get().getTexture(Texture_Name::spritesheet1));
	}
	else
	{
		setCurrentAnim(AnimationID::Idle);
	}

	sf::Vector2f pos = sf::Vector2f(body->GetPosition().x*32 - 16, body->GetPosition().y*32 - 32);

	setPosition(pos);

	std::cout << body->GetLocalCenter().x << "   " << body->GetLocalCenter().y << "  ";

	std::cout << Position.x << "  " << Position.y << std::endl;

	sprite.setPosition(pos);
	updateAnim();
}

void Character_Candy::setCurrentAnim(AnimationID id)
{
	currentAnim = &m_animations.at(id);
}

void Character_Candy::updateAnim()
{
	sprite.setTextureRect(currentAnim->getFrame());
	sprite.setScale(
		size.x / sprite.getLocalBounds().width,
		size.y / sprite.getLocalBounds().height
	);
}

Character_Candy::Character_Candy(State::Playing & state)
{
	sprite.setTexture(Resource_Holder::get().getTexture(Texture_Name::spritesheet));
	mass = 75;
	size = { 32,64 };
	sprite.setScale(
		size.x / sprite.getLocalBounds().width,
		size.y / sprite.getLocalBounds().height
	);

	boxWorldPtr = state.getWorld();

	b2BodyDef bodyDef;

	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(10,10);

	body = boxWorldPtr->CreateBody(&bodyDef);
	
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox( 0.5, 1);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.1f;
	
	body->CreateFixture(&fixtureDef);

	Animation RunRAnim;
	RunRAnim.addFrames({ 0,0,20,38}, 0.1f);
	RunRAnim.addFrames({ 20,0,20,38 }, 0.1f);
	RunRAnim.addFrames({ 40,0,20,38 }, 0.1f);
	RunRAnim.addFrames({ 60,0,20,38 }, 0.1f);
	RunRAnim.addFrames({ 0,38,20,38 }, 0.1f);
	RunRAnim.addFrames({ 20,38,20,38 }, 0.1f);
	m_animations.insert(std::make_pair(AnimationID::RunR, RunRAnim));

	Animation RunLAnim;
	RunLAnim.addFrames({ 60,0,20,38 }, 0.1f);
	RunLAnim.addFrames({ 40,0,20,38 }, 0.1f);
	RunLAnim.addFrames({ 20,0,20,38 }, 0.1f);
	RunLAnim.addFrames({ 0,0,20,38 }, 0.1f);
	RunLAnim.addFrames({ 60,38,20,38 }, 0.1f);
	RunLAnim.addFrames({ 40,38,20,38 }, 0.1f);
	m_animations.insert(std::make_pair(AnimationID::RunL, RunLAnim));

	Animation Idle;
	Idle.addFrames({ 0,0,20,38 }, 0.f);
	m_animations.insert(std::make_pair(AnimationID::Idle, Idle));

	setCurrentAnim(AnimationID::Idle);
}
