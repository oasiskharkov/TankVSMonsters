#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "Service.h"

class Monster
{
private:
	// Monster's type
	monster_type m_eMonsterType;

	// Current monster's position
	hgeVector m_vPos;

	// Monster's health power
	float m_fHealth;

	// Monster's armor
	float m_fArmor;

	// Monster's damage
	float m_fDamage;

	// Monster's speed
	float m_fSpeed;

	// Monster's direction
	float m_fDirection;

	// Monster's texture
	HTEXTURE m_hMonsterTex;
	
	// Monster's animation
	hgeAnimation* m_pMonsterAnimated;

	// Monster's stopped sprite
	hgeSprite* m_pMonsterStopped;

	// Prepeare monster's resources
	bool prepareResources();

	// Release all allocated memory
	void release();

	// Private copy constructor
	Monster( const Monster& );

	// Private copy assignment operator
	Monster& operator = ( const Monster& );
public:
	// Constructor
	Monster( monster_type type, float xPos, float yPos, float health, float armor, float damage, 
		float speed, float direction, const char* monster );

	// Destructor
	virtual ~Monster( );
		
	// Get monster's type
	monster_type getType( ) const;

	// Get monster's health
	float getHealth( ) const;

	// Get monster's armor
	float getArmor( ) const;

	// Get monster's damage
	float getDamage( ) const;

	// Get monster's speed
	float getSpeed( ) const;

	// Get monster's direction
	float getDirection( ) const;
	
	// Set monster's health
	void setHealth( float health );

	// Set monster's armor
	void setArmor( float armor );

	// Set monster's damage
	void setDamage( float damage );

	// Set monster's speed
	void setSpeed( float speed );

	// Set monster's direction
	void setDirection( float direction );
};

inline monster_type Monster::getType( ) const
{
	return m_eMonsterType;
}

inline float Monster::getHealth( ) const
{
	return m_fHealth;
}

inline float Monster::getArmor( ) const
{
	return m_fArmor;
}

inline float Monster::getDamage( ) const
{
	return m_fDamage;
}

inline float Monster::getSpeed( ) const
{
	return m_fSpeed;
}

inline float Monster::getDirection( ) const
{
	return m_fDirection;
}

inline void Monster::setHealth( float health )
{
	m_fHealth = health;
}

inline void Monster::setArmor( float armor )
{
	m_fArmor = armor;
}
	
inline void Monster::setDamage( float damage )
{
	m_fDamage = damage;
}

void Monster::setSpeed( float speed )
{
	m_fSpeed = speed;
}

void Monster::setDirection( float direction )
{
	m_fDirection = direction;
}

#endif