#include "Tank.h"

Tank::Tank( float xPos, float yPos, float health, float armor, float speed, const char* tank ) 
	: m_vPos( xPos, yPos ), m_vDir( 0.0f, -1.0f ), m_fHealth( health ), m_fArmor( armor ), m_fSpeed( speed ),
	m_pTankAnimated( 0 ), m_pTankStopped( 0 ) 
{
	m_hTankTex = hge->Texture_Load( tank );

	if( !prepareResources( ) )
	{
		release( );
		throw game_errors::LOAD_TANK_SOURCES;
	}
}

Tank::~Tank( )
{
	release( );
}

bool Tank::prepareResources( )
{
	try
	{
		//m_pTankAnimated = new hgeAnimation()
		//m_pTankStopped = new hgeSpite()
	}
	catch(...)
	{
		return false;
	}
	return true;
}

void Tank::release( )
{
	hge->Texture_Free( m_hTankTex );

	delete m_pTankAnimated;
	delete m_pTankStopped;
}

void Tank::changeWeapon( bool clockwise )
{
	if( clockwise ) 
	{
		std::rotate( m_vWeapons.rbegin( ), m_vWeapons.rbegin( ) + 1, m_vWeapons.rend( ) );
	}
	else
	{
		std::rotate( m_vWeapons.begin( ), m_vWeapons.begin( ) + 1, m_vWeapons.end( ) );
	}
}