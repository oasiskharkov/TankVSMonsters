#ifndef _TANK_H_
#define _TANK_H_

#include "Service.h"

class Weapon;

class Tank
{
private:
	// Tank's current position
	hgeVector m_vPos;

	// Tank's health power
	float m_fHealth;

	// Tank's armor
	float m_fArmor;

	// Tank's speed
	float m_fSpeed;

	// Tank's direction
	float m_fDirection;

	// Tank's weapons
	std::vector<Weapon*> m_vWeapons;

	// Tank's texture
	HTEXTURE m_hTankTex;
	
	// Tank's animation
	hgeAnimation* m_pTankAnimated;

	// Tank's stopped sprite
	hgeSprite* m_pTankStopped;

	// Prepeare tank's resources
	bool prepareResources();

	// Release all allocated memory
	void release();

	// Private copy constructor
	Tank( const Tank& );

	// Private copy assignment operator
	Tank& operator = ( const Tank& );
public:
	// Constructor
	Tank( float xPos, float yPos, float health, float armor, float speed, float direction, const char* tank );

	// Destructor
	~Tank( );
	
	// Get current tank's position
	hgeVector getPosition( ) const;

	// Get tank's health power
	float getHealth( ) const;

	// Get tank's armor
	float getArmor( ) const;

	// Get tank's speed 
	float getSpeed( ) const; 

	// Get tank's direction
	float getDirection( ) const;

	// Get current tank's weapon
	Weapon* getCurrentWeapon( );

	// Set tank's weapon list
	void setWeaponList( );

	// Set tank's health power
	void setHealth( float health );

	// Set tank's armor
	void setArmor( float armor );

	// Set tank's speed
	void setSpeed( float speed );

	// Set tank's direction
	void setDirection( float direction );

	// Ghange tank's weapon
	void changeWeapon( bool clockwise = true );

	// Tank stops
	void stop( );

	// Tank moves
	void move( );

	// Tank explodes
	void explode( );

	// Tank turns
	void turn( bool toTheRight ); 
};

inline hgeVector Tank::getPosition( ) const
{
	return m_vPos;
}

inline float Tank::getHealth( ) const
{
	return m_fHealth;
}

inline float Tank::getArmor( ) const
{
	return m_fArmor;
}

inline float Tank::getSpeed( ) const 
{
	return m_fSpeed;
}

inline float Tank::getDirection( ) const
{
	return m_fDirection;
}

inline Weapon* Tank::getCurrentWeapon( )
{
	return m_vWeapons.back( );
}

inline void Tank::setHealth( float health )
{
	m_fHealth = health;
}

inline void Tank::setArmor( float armor )
{
	m_fArmor = armor;
}

inline void Tank::setSpeed( float speed )
{
	m_fSpeed = speed;
}

inline void Tank::setDirection( float direction )
{
	m_fDirection = direction;
}
	

#endif