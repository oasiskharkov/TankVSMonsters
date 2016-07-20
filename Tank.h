#ifndef _TANK_H_
#define _TANK_H_


#include "Service.h"

class Weapon;

class Tank
{
private:
	// Health power of the tank
	float m_health;

	// Armor of the tank
	float m_armor;

	// Speed of the tank
	float m_speed;

	// Current weapon
	Weapon* m_weapon;
public:
	// Constructor
	Tank( );

	// Destructor
	~Tank( );

	// Get the health power
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
	return m_health;
}

inline float Tank::getArmor( ) const
{
	return m_armor;
}

inline float Tank::getSpeed( ) const 
{
	return m_speed;
}

void Tank::setHealth( float health )
{
	m_health = health;
}


void Tank::setArmor( float armor )
{
	m_armor = armor;
}

void Tank::setSpeed( float speed )
{
	m_speed = speed;
}

#endif

