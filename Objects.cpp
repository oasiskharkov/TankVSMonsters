#include "Objects.h"
#include "Tank.h"
#include "Monster.h"
#include "Weapon.h"
#include "Packet.h"
#include "Input.h"

Objects* Objects::instance( 0 );

Objects* Objects::getInstance( )
{
   static Objects* instance = new Objects( );
   return instance;
}

Objects::Objects( )
{
	m_vupMonsters.resize( 10 );
	m_vupWeapons.resize( 3 );

	prepareObjects( );
}

Objects::~Objects( )
{
	release( );
}

void Objects::release( )
{
	instance = 0;
}

void Objects::prepareObjects( )
{
	try
	{
		m_vupWeapons.at( 0 ).reset( new Weapon( weapon_type::MACHINE_GUN, "Resources\\tower1.png" ) );
		m_vupWeapons.at( 1 ).reset( new Weapon( weapon_type::CANNON, "Resources\\tower2.png" ) );
		m_vupWeapons.at( 2 ).reset( new Weapon( weapon_type::ROCKET_LAUNCHER, "Resources\\tower3.png" ) );

		m_upTank.reset( new Tank( GAME_WIDTH / 2.0f, GAME_HEIGHT / 2.0f, 1.0f, 1.0f, TANK_SPEED,
			"Resources\\tank.png", m_vupWeapons ) );

	}
	catch(const game_errors& error)
	{
		release( );
		throw error;
	}
	catch(...)
	{
		release( );
		throw game_errors::UNKNOWN_ERROR;
	}
}

void Objects::renderTank( ) 
{
	m_upTank->render( );
}

void Objects::renderWeapon( )
{
	m_upTank->getCurrentWeapon( )->render( );
}

void Objects::renderPackets( )
{
	for(size_t i = 0; i < m_vupPackets.size( ); i++ )
	{
		m_vupPackets[i]->render( );
	}
}

void Objects::renderObjects( )
{
	renderTank( );
	renderWeapon( );
	renderPackets( );
}

void Objects::frameTank( )
{
	m_upTank->frame( );
}

void Objects::frameWeapon( )
{
	m_upTank->getCurrentWeapon( )->frame( );
}

void Objects::framePackets( )
{
	auto packet = m_vupPackets.begin( );
	while( packet != m_vupPackets.end( ) )
	{
		if( !isObjectOnScreen( (*packet)->getPosition( ) ) )
		{
			( *packet ).reset( nullptr );
			packet = m_vupPackets.erase( packet );
			if( packet == m_vupPackets.end( ) )
			{
				break;
			}
		}
		( *packet )->frame( );
		packet++;
	}
}

void Objects::frameObjects( ) 
{
	Input::handleTankControlKeys( );

	frameTank( );
	frameWeapon( );
	framePackets( );
}

bool Objects::isObjectOnScreen( hgeVector center )
{
	return !(center.x < 0 || center.x > GAME_WIDTH || center.y < 0 || center.y > GAME_HEIGHT);
}

float Objects::getAngleInRadians( float vx, float vy )
{
	if( vx >= 0.0f && vy < 0.0f )
	{
		return atan( vx / -vy );
	}
	else if( vx >= 0 && vy >= 0 )
	{
		return M_PI - atan( vx / vy );
	}
	else if( vx < 0 && vy >= 0 )
	{
		return M_PI + atan( -vx / vy );
	}
	else
	{
		return 2 * M_PI - atan ( vx / vy );
	}
}


