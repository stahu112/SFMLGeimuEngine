#include "Character_Candy.h"
#include "States\Playing_State.h"

#include <algorithm>

Character_Candy::UniqueStats Character_Candy::getUniqueStats() const
{
	return uniqueStats;
}

void Character_Candy::update(float dt)
{	
	//TODO REFACTOR
	if (velocity.x > 0)
	{
		if (currentAnim != &m_animations.at(AnimationID::RunR)) m_animations.at(AnimationID::RunR).reset();
		setCurrentAnim(AnimationID::RunR);
		spriteSheet.setTexture(Resource_Holder::get().getTexture(Texture_Name::spritesheet));
	}
	else if (velocity.x < 0)
	{
		if (currentAnim != &m_animations.at(AnimationID::RunL)) m_animations.at(AnimationID::RunL).reset();
		setCurrentAnim(AnimationID::RunL);
		spriteSheet.setTexture(Resource_Holder::get().getTexture(Texture_Name::spritesheet1));
	}
	else
	{
		setCurrentAnim(AnimationID::Idle);
	}

	if (flags.falling || flags.jumping) Physics::applyGravity(*this, dt);
	else { velocity.y = 0; }

	velocity.x = Physics::approach(goalVelocity.x, velocity.x, dt);
	//velocity.y = Physics::approach(goalVelocity.y, velocity.y, dt);

	setPosition(Position + velocity*dt);

	bot = Position.y + size.y;
	left = Position.x;
	right = (Position.x + size.x);
	top = Position.y;

	expPos = Position + velocity * dt;

	topLeft = (sf::Vector2i((int)left / 32, (int)top / 32));
	topRight = (sf::Vector2i((int)right / 32, (int)top / 32));
	botLeft = (sf::Vector2i((int)left / 32, (int)bot / 32));
	botRight = (sf::Vector2i((int)right / 32, (int)bot / 32));
	//Left = sf::Vector2i(topLeft.x, topLeft.y + 1);
	//Right = sf::Vector2i(topRight.x, topRight.y + 1);

	tiles.clear();

	tiles.push_back(topLeft);
	if (std::find(tiles.begin(), tiles.end(), topRight) == tiles.end()) tiles.push_back(topRight);
	if (std::find(tiles.begin(), tiles.end(), botLeft) == tiles.end()) tiles.push_back(botLeft);
	if (std::find(tiles.begin(), tiles.end(), botRight) == tiles.end()) tiles.push_back(botRight);
	//if (std::find(tiles.begin(), tiles.end(), Right) == tiles.end()) tiles.push_back(Right);
	//if (std::find(tiles.begin(), tiles.end(), Left) == tiles.end()) tiles.push_back(Left);

	updateAnim();
	getSprite().setPosition(Position);
}

void Character_Candy::setCurrentAnim(AnimationID id)
{
	currentAnim = &m_animations.at(id);
}

void Character_Candy::updateAnim()
{
	spriteSheet.setTextureRect(currentAnim->getFrame());
	spriteSheet.setScale(
		size.x / spriteSheet.getLocalBounds().width,
		size.y / spriteSheet.getLocalBounds().height
	);
}

Character_Candy::Character_Candy()
{
	setBaseStats("Candy",1250,1);
	spriteSheet.setTexture(Resource_Holder::get().getTexture(Texture_Name::spritesheet));
	mass = 75;
	size = { 32,32 };
	spriteSheet.setScale(
		size.x / spriteSheet.getLocalBounds().width,
		size.y / spriteSheet.getLocalBounds().height
	);
	
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
