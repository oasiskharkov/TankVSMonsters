#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include "Service.h"

class Tank;
class Monster;
class Weapon;
class Packet;

class Objects
{
private:
	// Unique pointer to the Tank
	std::unique_ptr<Tank> m_upTank;

	// Container with unique pointers to the monsters
	std::vector<std::unique_ptr<Monster>> m_vupMonsters;
	
	// Container with unique pointers to the weapons
	std::vector<std::unique_ptr<Weapon>> m_vupWeapons;

	// Container with unique pointers to the packets
	std::vector<std::unique_ptr<Packet>> m_vupPackets;

	// Render tank
	void renderTank( );
	
	// Render all monsters
	void renderMonsters( );

	// Render current weapon
	void renderWeapon( );

	// Render all packets
	void renderPackets( );

	// Tank's frame calculations
	void frameTank( );

	// Monsters' frame calculations
	void frameMonsters( );

	// Weapon frame calculations
	void frameWeapon( );

	// Packet's frame calculations
	void framePackets( );

	// Prepare game objects
	void prepareObjects( );

	// Release all allocated memory
	void release();

	// Private constructor
	Objects( );

	// Scene instance
	static Objects* instance;
public:
	// Destructor
	~Objects( ) ;

	// Get Objects instance
	static Objects* getInstance( );

	// Render all game objects
	void renderObjects( );

	// Frame all game objects
	void frameObjects( );	

	// Get unique pointer to the tank
	std::unique_ptr<Tank>& getTank( );

	// Get container with unique pointers to the monsters
	std::vector<std::unique_ptr<Monster>>& getMonsters( );

	// Get container with unique pointers to the weapons
	std::vector<std::unique_ptr<Weapon>>& getWeapons( );

	// Get container with unique pointers to the packets
	std::vector<std::unique_ptr<Packet>>& getPackets( );

	// Get direction in radians
	static float getAngleInRadians( float vx, float vy );
	
	// Check is object on screen
	static bool isObjectOnScreen( hgeVector center ); 
};

inline std::unique_ptr<Tank>& Objects::getTank( )
{
	return m_upTank;
}

inline std::vector<std::unique_ptr<Monster>>& Objects::getMonsters( )
{
	return m_vupMonsters;
}

inline std::vector<std::unique_ptr<Weapon>>& Objects::getWeapons( )
{
	return m_vupWeapons;
}
	
inline std::vector<std::unique_ptr<Packet>>& Objects::getPackets( )
{
	return m_vupPackets;
}

#endif