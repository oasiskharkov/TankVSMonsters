#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "Service.h"

class Weapon
{
private:
	// Weapon damage 
	float m_damage;

	// Shot speed 
	float m_speed;

	// Weapon type
	weapon_type m_type;

	// The number of shells
	int numberOfShells;
public:
	// Constructor
	Weapon( );

	// Destructor
	virtual ~Weapon( );

	// Weapon shots
	void shot( );
};

#endif 

