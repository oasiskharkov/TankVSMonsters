#ifndef _TANK_H_
#define _TANK_H_

#include "Service.h"

class Weapon;

class Tank
{
private:
	// Tank's current position
	hgeVector m_vPos;

	// Tank's direction
	hgeVector m_vDir;

	// Tank's health power
	float m_fHealth;

	// Tank's armor
	float m_fArmor;

	// Tank's speed
	float m_fSpeed;

	// Tank's weapons
	std::vector<std::unique_ptr<Weapon>>& m_rvupWeapons;

	// Is tank moving
	bool m_bIsMoving;

	// Is tank moving back
	bool m_bIsBackMoving;

	// Tank's texture
	HTEXTURE m_hTankTex;
	
	// Tank's animation
	hgeAnimation* m_pTankAnimated;

	// Tank's stopped sprite
	hgeSprite* m_pTankStopped;

	// Prepeare tank's resources
	bool prepareResources( );

	// Release all allocated memory
	void release();

	// Tank moves
	void move( );

	// Tank stops
	void stop( );

	// Private copy constructor
	Tank( const Tank& );

	// Private copy assignment operator
	Tank& operator = ( const Tank& );
public:
	// Constructor
	Tank( float xPos, float yPos, float health, float armor, float speed, const char* tank, 
		std::vector<std::unique_ptr<Weapon>>& weapons, bool isMoving = false, bool isBackMoving = false );

	// Destructor
	~Tank( );

	// Tank's frame calculations
	void frame( );

	// Render tank
	void render( );
		
	// Get current tank's position
	hgeVector getPosition( ) const;

	// Get tank's direction
	hgeVector getDirection( ) const;

	// Get tank's health power
	float getHealth( ) const;

	// Get tank's armor
	float getArmor( ) const;

	// Get tank's speed 
	float getSpeed( ) const; 

	// Is tank moving
	bool isMoving( ) const;

	// Is tank moving back
	bool isBackMoving( ) const;

	// Get current tank's weapon
	std::unique_ptr<Weapon>& getCurrentWeapon( );

	// Set tank's position
	void setPosition( hgeVector position );

	// Set tank's direction
	void setDirection( hgeVector direction );

	// Set tank's weapon list
	void setWeaponList( );

	// Set tank's health power
	void setHealth( float health );

	// Set tank's armor
	void setArmor( float armor );

	// Set tank's speed
	void setSpeed( float speed );

	// Set tank movement
	void setMoving( bool moving = true );

	// Set tank back movement
	void setBackMoving( bool backMoving = true );
	
	// Ghange tank's weapon
	void changeWeapon( bool clockwise = true );

	// Tank turns
	void turn( bool clockwise = true ); 
};

inline hgeVector Tank::getPosition( ) const
{
	return m_vPos;
}

inline hgeVector Tank::getDirection( ) const
{
	return m_vDir;
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

inline bool Tank::isMoving( ) const
{
	return m_bIsMoving;
}

inline bool Tank::isBackMoving( ) const 
{
	return m_bIsBackMoving;
}

inline std::unique_ptr<Weapon>& Tank::getCurrentWeapon( )
{
	return m_rvupWeapons.front( );
}

inline void Tank::setPosition( hgeVector position )
{
	m_vPos = position;
}

inline void Tank::setDirection( hgeVector direction )
{
	m_vDir = direction;
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

inline void Tank::setMoving( bool moving )
{
	m_bIsMoving = moving;
}

inline void Tank::setBackMoving( bool backMoving )
{
	m_bIsBackMoving = backMoving;
}

#endif