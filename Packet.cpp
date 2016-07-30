#include "Packet.h"
#include "Objects.h"
#include "Weapon.h"
#include "Tank.h"

Packet::Packet( packet_type type ) : m_ePacketType( type )
{	
	switch( m_ePacketType )
	{
	case packet_type::BULLET:
		m_fDamage = BULLET_DAMAGE;
		m_fSpeed = BULLET_SPEED;
		m_fShift = BULLET_SHIFT;
		m_hPacketTex = hge->Texture_Load("Resources\\bullet.png");
		m_vDir = objects->getTank( )->getCurrentWeapon( )->getDirection( );
		m_vPos = objects->getTank( )->getCurrentWeapon( )->getPosition( );
		m_vPos += m_vDir * m_fShift; 
		break;
	case packet_type::SHELL:
		m_fDamage = SHELL_DAMAGE;
		m_fSpeed = SHELL_SPEED;
		m_fShift = SHELL_SHIFT;
		m_hPacketTex = hge->Texture_Load("Resources\\shell.png");
		m_vDir = objects->getTank( )->getCurrentWeapon( )->getDirection( );
		m_vPos = objects->getTank( )->getCurrentWeapon( )->getPosition( );
		m_vPos += m_vDir * m_fShift; 
		break;
	case packet_type::ROCKET:
		m_fDamage = ROCKET_DAMAGE;
		m_fSpeed = ROCKET_SPEED;
		m_fShift = ROCKET_SHIFT;
		m_hPacketTex = hge->Texture_Load("Resources\\rocket.png");
		m_vDir = objects->getTank( )->getCurrentWeapon( )->getDirection( );
		m_vPos = objects->getTank( )->getCurrentWeapon( )->getPosition( );
		m_vPos += m_vDir * m_fShift; 
		break;
	}

	if(!prepareResources())
	{
		release();
		throw game_errors::LOAD_PACKET_SOURCES;
	}

}

Packet::~Packet(void)
{
	release( );
}

bool Packet::prepareResources()
{
	try
	{
		m_pPacketAnimated = new hgeAnimation( m_hPacketTex, 1, 10.0f, 0.0f, 0.0f, 128.0f, 128.0f ); 
	}
	catch(...)
	{
		return false;
	}
	return true;
}

void Packet::release()
{
	hge->Texture_Free( m_hPacketTex );

	delete m_pPacketAnimated;
}

void Packet::frame( )
{
	m_vPos += m_vDir * m_fSpeed * dt;	
}

void Packet::render( )
{
	if( !m_pPacketAnimated->IsPlaying( ) )
	{
		m_pPacketAnimated->Play( );
	}
	else
	{
		m_pPacketAnimated->Update( dt );
	}

	m_pPacketAnimated->SetHotSpot( 64.0f, 64.0f );
	m_pPacketAnimated->RenderEx( m_vPos.x, m_vPos.y, m_vDir.Angle( ) + M_PI_2, 0.1f ); 
}