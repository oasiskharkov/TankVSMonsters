#include "Objects.h"
#include "Tank.h"
#include "Monster.h"
#include "Weapon.h"
#include "Packet.h"

Objects* Objects::instance( 0 );

Objects* Objects::getInstance( )
{
   static Objects* instance = new Objects( );
   return instance;
}

Objects::Objects( ) : oldWKeyState( true ), oldQKeyState( true )
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

		m_upTank.reset( new Tank( GAME_WIDTH / 2.0f, GAME_HEIGHT / 2.0f, 1.0f, 1.0f, 50.0f,
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

void Objects::renderObjects( )
{
	renderTank( );
	renderWeapon( );
}

void Objects::frameTank( )
{
	m_upTank->frame( );
}

void Objects::frameWeapon( )
{
	m_upTank->getCurrentWeapon( )->frame( );
}

void Objects::frameObjects( ) 
{
	processInput( );

	frameTank( );
	frameWeapon( );
}

void Objects::processInput( )
{	
	// Handle 'LEFT ARROW' key press
	if( hge->Input_GetKeyState( HGEK_LEFT ) ) 
	{
		m_upTank->turn( false );
	}

	// Handle 'RIGHT ARROW' key press
	if( hge->Input_GetKeyState( HGEK_RIGHT ) )
	{
		m_upTank->turn( );
	}

	// Handle 'UP ARROW' key press
	hge->Input_GetKeyState( HGEK_UP ) ? m_upTank->setMoving( ) : m_upTank->setMoving( false );  
	
	// Handle 'DOWN ARROW' key press
	hge->Input_GetKeyState( HGEK_DOWN ) ? m_upTank->setBackMoving( ) : m_upTank->setBackMoving( false );

	// Handle 'Q' key press
	if( !oldQKeyState && hge->Input_GetKeyState( HGEK_Q ) )
	{
		m_upTank->changeWeapon( false );
	}
	oldQKeyState = hge->Input_GetKeyState( HGEK_Q );

	// Handle 'W' key press
	if( !oldWKeyState && hge->Input_GetKeyState( HGEK_W ) )
	{
		m_upTank->changeWeapon( );
	}
	oldWKeyState = hge->Input_GetKeyState( HGEK_W );
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


