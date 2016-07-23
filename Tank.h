#ifndef _TANK_H_
#define _TANK_H_

#include "Service.h"

class Weapon;

class Tank
{
private:
	// Tank's current X position
	float m_fXPos;

	// Tank's current Y posititon
	float m_fYPos;

	// Tank's health power
	float m_fHealth;

	// Tank's armor
	float m_fArmor;

	// Tank's speed
	float m_fSpeed;

	// Tank's current weapon
	Weapon* m_pWeapon;

	// Tank's texture
	HTEXTURE m_hTankTex;
	
	// Tank's animation
	hgeAnimation* m_pTankAnimated;

	// Tank's stopped sprite
	hgeSprite* m_pTankStopped;

public:
	// Constructor
	Tank( );

	// Destructor
	~Tank( );

	// Get  health power
	float getHealth( ) const;

	// Get the armor
	float getArmor( ) const;

	// Get the speed 
	float getSpeed( ) const; 

	// Set health power
	void setHealth( float health );

	// Set armor
	void setArmor( float armor );

	// Set speed
	void setSpeed( float speed );

	// Ghange the weapon
	void changeWeapon( );

	// Tank stops
	void stop( );

	// Tank moves
	void move( );

	// Tank explodes
	void explode( );

	// Tank turns
	void turn( bool toTheRight ); 
};

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

#endif


// std::rotate ( vec.rbegin() , vec.rbegin()+1 , vec.rend() ) ;