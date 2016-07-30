#include "Tank.h"
#include "Objects.h"

Tank::Tank( float xPos, float yPos, float health, float armor, float speed, const char* tank,
			  std::vector<std::unique_ptr<Weapon>>& weapons,  bool isMoving, bool isBackMoving ) 
	: m_vPos( xPos, yPos ), m_vDir( 0.0f, -1.0f ), m_fHealth( health ), m_fArmor( armor ), m_fSpeed( speed ),
	m_rvupWeapons( weapons ), m_bIsMoving ( isMoving ), m_bIsBackMoving( isBackMoving ),
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
		m_pTankAnimated = new hgeAnimation( m_hTankTex, 3, 10.0f, 0.0f, 0.0f, 256.0f, 256.0f ); 
		m_pTankStopped = new hgeSprite( m_hTankTex, 0.0f, 0.0f, 256.0f, 256.0f );
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
		std::rotate( m_rvupWeapons.begin( ), m_rvupWeapons.begin( ) + 1, m_rvupWeapons.end( ) );
	}
	else
	{
		std::rotate( m_rvupWeapons.rbegin( ), m_rvupWeapons.rbegin( ) + 1, m_rvupWeapons.rend( ) );
	}
}

void Tank::frame( ) 
{
	hgeVector vTemp;
	hgeVector vSpeed;
	if( m_bIsMoving )
	{
		vSpeed = m_vDir * m_fSpeed;
	
	}
	else if( m_bIsBackMoving )
	{
		hgeVector vDirBar( m_vDir );
		vDirBar.Rotate( M_PI );
		vSpeed = vDirBar * m_fSpeed;
	}

	if( m_bIsMoving || m_bIsBackMoving )
	{
		vTemp = m_vPos + vSpeed * dt;
		if( Objects::isObjectOnScreen( vTemp ) )
		{
			m_vPos = vTemp; 
		}			 
	}
}

void Tank::render( )
{
	m_bIsMoving ? move( ) : stop( );
}

void Tank::move( )
{
	if( !m_pTankAnimated->IsPlaying( ) )
	{
		m_pTankAnimated->Play( );
	}
	else
	{
		m_pTankAnimated->Update( dt );
	}

	m_pTankAnimated->SetHotSpot( 128.0f, 128.0f );
	m_pTankAnimated->RenderEx( m_vPos.x, m_vPos.y, m_vDir.Angle( ) + M_PI_2, 0.3f );
}

void Tank::stop( )
{
	m_pTankStopped->SetHotSpot( 128.0f, 128.0f );
	m_pTankStopped->RenderEx( m_vPos.x, m_vPos.y, m_vDir.Angle( ) + M_PI_2, 0.3f );
}

void Tank::turn( bool clockwise )
{
	float angle = clockwise ? dt * TANK_ANGLE_VELOCITY : - dt * TANK_ANGLE_VELOCITY;
	
	if ( m_bIsBackMoving )
	{
		angle = -angle;
	}

	m_vDir.Rotate( angle );
}

