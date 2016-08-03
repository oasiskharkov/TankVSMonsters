#include "Weapon.h"
#include "Objects.h"
#include "Tank.h"
#include "Packet.h"

int Weapon::s_nBullets( 0 );

int Weapon::s_nShells( 0 );

int Weapon::s_nRockets( 0 );

Weapon::Weapon( weapon_type type, const char* weapon ) : m_eWeaponType( type ), m_pWeapon( 0 ) 
{
	m_hWeaponTex = hge->Texture_Load( weapon );

	if( !prepareResources( ) )
	{
		release( );
		throw game_errors::LOAD_WEAPON_SOURCES;
	}
}

Weapon::~Weapon( )
{
	release( );
}

bool Weapon::prepareResources( )
{
	try
	{
		m_pWeapon = new hgeSprite( m_hWeaponTex, 0.0f, 0.0f, 256.0f, 256.0f ); 
	}
	catch(...)
	{
		return false;
	}
	return true;
}

void Weapon::release( )
{
	hge->Texture_Free( m_hWeaponTex );

	delete m_pWeapon;
}

void Weapon::frame( )
{
	setPosition( objects->getTank( )->getPosition( ) );
	setDirection( objects->getTank( )->getDirection( ) );
}

void Weapon::render( )
{
	if ( m_pWeapon != nullptr )
	{
		m_pWeapon->SetHotSpot( 128.0f, 128.0f );
		m_pWeapon->RenderEx( m_vPos.x, m_vPos.y, m_vDir.Angle( ) + M_PI_2, 0.3f);
	}
	else
	{
		throw game_errors::NULL_POINTER;
	}
}

void Weapon::shot( )
{
	Packet* packet;
	switch( m_eWeaponType )
	{
	case weapon_type::MACHINE_GUN:
		s_nBullets++;
		packet = new Packet( packet_type::BULLET, BULLET_DAMAGE, BULLET_SPEED, BULLET_SHIFT, "Resources\\bullet.png" );
		break;
	case weapon_type::CANNON:
		s_nShells++;
		packet = new Packet( packet_type::SHELL, SHELL_DAMAGE, SHELL_SPEED, SHELL_SHIFT, "Resources\\shell.png" );
		break;
	case weapon_type::ROCKET_LAUNCHER:
		s_nRockets++;
		packet = new Packet( packet_type::ROCKET, ROCKET_DAMAGE, ROCKET_SPEED, ROCKET_SHIFT, "Resources\\rocket.png" );
		break;
	};

	objects->getPackets( ).push_back( static_cast<std::unique_ptr<Packet>>( packet ) );
}