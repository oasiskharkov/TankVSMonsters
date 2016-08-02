#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "Service.h"

class Weapon
{
private:
	// Weapon's type
	weapon_type m_eWeaponType;

	// Weapon's position
	hgeVector m_vPos;

	// Weapon's direction
	hgeVector m_vDir;

	// Bullets quantity
	static int s_nBullets;

	// Shells quantity 
	static int s_nShells;
	
	// Rockets quantity
	static int s_nRockets;

	// Weapon's texture
	HTEXTURE m_hWeaponTex;

	// Weapon's stopped sprite
	hgeSprite* m_pWeapon;

	// Prepeare weapon's resources
	bool prepareResources();

	// Release all allocated memory
	void release();

	// Private copy constructor
	Weapon( const Weapon& );

	// Private copy assignment operator
	Weapon& operator = ( const Weapon& );
public:
	// Constructor
	Weapon( weapon_type type, const char* weapon );

	// Destructor
	~Weapon( );

	// Weapon frame calculations
	void frame( ); 

	// Render weapon
	void render( );

	// Weapon shots
	void shot( );

	// Get current weapon's position
	hgeVector getPosition( ) const;

	// Get weapon's direction
	hgeVector getDirection( ) const;

	// Get total bullets quantity
	static int getBulletsQuantity( );

	// Get total shells quantity
	static int getShellsQuantity( );

	// Get total rockets quantity
	static int getRocketsQuantity( );

	// Set weapon's position
	void setPosition( hgeVector position );

	// Set weapon's direction
	void setDirection( hgeVector direction );

	// Reset total packets quantity to nil
	static void resetTotalPacketsQuantity( );
};

inline hgeVector Weapon::getPosition( ) const
{
	return m_vPos;
}

inline hgeVector Weapon::getDirection( ) const
{
	return m_vDir;
}

inline void Weapon::setPosition( hgeVector position )
{
	m_vPos = position;
}

inline void Weapon::setDirection( hgeVector direction )
{
	m_vDir = direction;
}

inline int Weapon::getBulletsQuantity( )
{
	return s_nBullets;
}

inline int Weapon::getShellsQuantity( )
{
	return s_nShells;
}

inline int Weapon::getRocketsQuantity( )
{
	return s_nRockets;
}

inline void Weapon::resetTotalPacketsQuantity( )
{
	s_nBullets = s_nShells = s_nRockets = 0;
}


#endif 

