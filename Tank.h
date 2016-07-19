#ifndef _TANK_H_
#define _TANK_H_

#include "Weapon.h"

class Tank
{
private:
	// Health power of the tank
	double m_health;

	// Armor of the tank
	double m_armor;

	// Speed of the tank
	double m_speed;

	// Current weapon
	Weapon* m_weapon;

public:
	// Constructor
	Tank( );

	// Destructor
	~Tank( );
};

#endif

