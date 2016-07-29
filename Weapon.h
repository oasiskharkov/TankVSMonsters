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

	// The number of packets
	int m_nNumberOfPackets;

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

	// Set weapon's position
	void setPosition( hgeVector position );

	// Set weapon's direction
	void setDirection( hgeVector direction );
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

#endif 

