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

void Objects::renderMonsters( )
{
	for(size_t i = 0; i < m_vupMonsters.size( ); i++ )
	{
		m_vupMonsters[ i ]->render( );
	}
}

void Objects::renderObjects( )
{
	renderTank( );
	renderWeapon( );
	renderMonsters( ); 
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

void Objects::frameMonsters( )
{
	createMonsters( );

	auto monster = m_vupMonsters.begin( );
	while( monster != m_vupMonsters.end( ) )
	{
		if( ( *monster )->getHealth( ) <= 0.0f )
		{
			( *monster ).reset( nullptr );
			monster = m_vupMonsters.erase( monster );
			if( monster == m_vupMonsters.end( ) )
			{
				break;
			}
		}
		( *monster )->frame( );
		monster++;
	}
}

void Objects::framePackets( )
{
	auto packet = m_vupPackets.begin( );
	while( packet != m_vupPackets.end( ) )
	{
		if( !isObjectOnScreen( ( *packet )->getPosition( ) ) )
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

	processCollisions( );

	frameTank( );
	frameWeapon( );
	frameMonsters( );
	framePackets( );
}

void Objects::processMonsterVsMonsterCollision( )
{

}

void Objects::processMonsterVsPacketCollision( )
{
	auto monster = m_vupMonsters.begin( );
	while( monster != m_vupMonsters.end( ) )
	{
		hgeVector monsterPos = ( *monster )->getPosition( );
		auto packet = m_vupPackets.begin( );
		while( packet != m_vupPackets.end( ) )
		{
			hgeVector packetPos = ( *packet )->getPosition( );
			if( distanceBetweenPoints( monsterPos, packetPos ) < PACKET_MONSTER_SHIFT )
			{
				float monsterHealth = ( *monster )->getHealth( );
				( *monster )->setHealth( monsterHealth - ( *monster )->getArmor( ) * ( *packet )->getDamage( ) );
				( *packet ).reset( nullptr );
				packet = m_vupPackets.erase( packet );
				if( packet == m_vupPackets.end( ) )
				{
					break;
				}
			}
			packet++;
		}
		monster++;
	}
}

void Objects::processMonsterVsTankCollision( )
{

}

void Objects::processCollisions( )
{
	processMonsterVsMonsterCollision( );
	processMonsterVsPacketCollision( );
	processMonsterVsTankCollision( );
}

void Objects::createMonsters( )
{
	while( m_vupMonsters.size( ) < MAX_MONSTER_COUNT )
	{
		float x, y;
		int choicePos = hge->Random_Int( 1, 4 );
		int choiceType = hge->Random_Int( 1, 3 ); 

		switch( choicePos )
		{
		case 1:
			x = -50.0f;
			y = hge->Random_Float( 0.0f, static_cast<float>( GAME_HEIGHT ) );
			break;
		case 2:
			x = static_cast<float>( GAME_WIDTH ) + 50.0f;
			y = hge->Random_Float( 0.0f, static_cast<float>( GAME_HEIGHT ) );
			break;
		case 3:
			x = hge->Random_Float( 0.0f, static_cast<float>( GAME_WIDTH ) );
			y = -50.0f;
			break;
		case 4:
			x = hge->Random_Float( 0.0f, static_cast<float>( GAME_WIDTH ) );
			y = static_cast<float>( GAME_HEIGHT ) + 50.0f;
			break;
		}

		switch( choiceType )
		{
		case 1:
			m_vupMonsters.push_back(static_cast<std::unique_ptr<Monster>>(
				new Monster( monster_type::BEAST, x, y, BEAST_HEALTH, 
					BEAST_ARMOR, BEAST_DAMAGE, BEAST_SPEED, "Resources\\beast.png" ) ) );
			break;
		case 2:
			m_vupMonsters.push_back(static_cast<std::unique_ptr<Monster>>(
				new Monster( monster_type::DAEMON, x, y, DAEMON_HEALTH, 
					DAEMON_ARMOR, DAEMON_DAMAGE, DAEMON_SPEED, "Resources\\daemon.png" ) ) );
			break;
		case 3:
			m_vupMonsters.push_back(static_cast<std::unique_ptr<Monster>>(
				new Monster( monster_type::REPTILE, x, y, REPTILE_HEALTH, 
					REPTILE_ARMOR, REPTILE_DAMAGE, REPTILE_SPEED, "Resources\\reptile.png" ) ) );
			break;
		}
	}
}

float Objects::distanceBetweenPoints( const hgeVector& v1, const hgeVector& v2 )
{
	return sqrt( ( v2.x - v1.x ) * ( v2.x - v1.x ) + ( v2.y - v1.y ) * ( v2.y - v1.y ) ); 
}

bool Objects::isObjectOnScreen( const hgeVector& center )
{
	return !( center.x < 0 || center.x > GAME_WIDTH || center.y < 0 || center.y > GAME_HEIGHT );
}
