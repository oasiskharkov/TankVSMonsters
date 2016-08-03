#include "Packet.h"
#include "Objects.h"
#include "Weapon.h"
#include "Tank.h"

Packet::Packet( packet_type type, float damage, float speed, float shift, const char* packet ) :
	m_ePacketType( type ), m_fDamage( damage ), m_fSpeed( speed ), m_fShift ( shift ) 
{	
	m_hPacketTex = hge->Texture_Load( packet );
	m_vDir = objects->getTank( )->getCurrentWeapon( )->getDirection( );
	m_vPos = objects->getTank( )->getCurrentWeapon( )->getPosition( );
	m_vPos += m_vDir * m_fShift; 

	if( !prepareResources( ) )
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
	if( m_pPacketAnimated != nullptr )
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
		m_pPacketAnimated->RenderEx( m_vPos.x, m_vPos.y, m_vDir.Angle( ) + M_PI_2, 0.17f ); 
	}
	else 
	{
		throw game_errors::NULL_POINTER;
	}
}