#ifndef _MONSTER_H_
#define _MONSTER_H_

class Monster
{
private:
	// Health power of the monster
	float m_health;

	// Armor of the monster
	float m_armor;

	// Damage that could cause a monster
	float m_damage;

	// Speed of the monster
	float m_speed;
public:
	// Constructor
	Monster( );

	// Destructor
	virtual ~Monster( );

	// Get monster's health
	float getHealth( ) const;

	// Get monster's armor
	float getArmor( ) const;

	// Get monster's damage
	float getDamage( ) const;

	// Get monster's speed
	float getSpeed( ) const;

	// Set monster's health
	void setHealth( float health );

	// Set monster's armor
	void setArmor( float armor );

	// Set monster's damage
	void setDamage( float damage );

	// Set monster's speed
	void setSpeed( float speed );
};

float Monster::getHealth( ) const
{
	return m_health;
}

float Monster::getArmor( ) const
{
	return m_armor;
}

float Monster::getDamage( ) const
{
	return m_damage;
}

float Monster::getSpeed( ) const
{
	return m_speed;
}

void Monster::setHealth( float health )
{
	m_health = health;
}

void Monster::setArmor( float armor )
{
	m_armor = armor;
}
	
void Monster::setDamage( float damage )
{
	m_damage = damage;
}

void Monster::setSpeed( float speed )
{
	m_speed = speed;
}

#endif