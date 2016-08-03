#include "Objects.h"
#include "Tank.h"
#include "Monster.h"
#include "Weapon.h"
#include "Packet.h"
#include "Input.h"

Objects* Objects::instance( 0 );

Objects* Objects::getInstance( )
{
   if( instance == 0 )
	{
		instance = new Objects( );
	}
	return instance;
}

Objects::Objects( ) : m_nDeadBeast( 0 ), m_nDeadDaemon( 0 ), m_nDeadReptile( 0 ) 
{
	m_vupWeapons.resize( 3 );

	Weapon::resetTotalPacketsQuantity( );

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

		m_upTank.reset( new Tank( GAME_WIDTH / 2.0f, GAME_HEIGHT / 2.0f, TANK_HEALTH, TANK_ARMOR, TANK_SPEED,
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
			if( distanceBetweenPoints( monsterPos, packetPos ) < MONSTER_RADIUS + PACKET_RADIUS )
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
		if( ( *monster )->getHealth( ) <= 0.0f )
		{
			countDeadMonsters( ( *monster )->getType( ) );
			monster = m_vupMonsters.erase( monster );
			if( monster == m_vupMonsters.end( ) )
			{
					break;
			}
		}
		else
		{
			monster++;
		}
	}
}

void Objects::processMonsterVsTankCollision( )
{
	auto monster = m_vupMonsters.begin( );
	hgeVector tankPos = m_upTank->getPosition( );

	while( monster != m_vupMonsters.end( ) )
	{
		hgeVector monsterPos = ( *monster )->getPosition( );
		
		if( distanceBetweenPoints( monsterPos, tankPos ) < TANK_RADIUS + MONSTER_RADIUS )
		{
			float tankHealth = m_upTank->getHealth( );
			m_upTank->setHealth( tankHealth - m_upTank->getArmor( ) * ( *monster )->getDamage( ) );
			( *monster )->setPosition( monsterPos - 10.0f * ( *monster )->getDirection( ) );
			if( m_upTank->getHealth( ) < 0.0f )
			{
				attempts--;
				return;
			}
		}
		monster++;
	}
}

void Objects::processCollisions( )
{
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

		hgeVector pos( x, y );
		if( checkNeighbourMonsterPresense( pos ) ) 
		{
			continue;
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

void Objects::countDeadMonsters( monster_type type ) 
{
	switch ( type )
	{
	case monster_type::BEAST:
		m_nDeadBeast++;
		break;
	case monster_type::DAEMON:
		m_nDeadDaemon++;
		break;
	case monster_type::REPTILE:
		m_nDeadReptile++;
		break;
	}
}

bool Objects::checkNeighbourMonsterPresense( const hgeVector& pos )
{
	for(size_t i = 0; i < m_vupMonsters.size( ); i++ )
	{
		hgeVector monsterPos = m_vupMonsters[ i ]->getPosition( );
		if( distanceBetweenPoints( pos, monsterPos ) < 2 * MONSTER_RADIUS )
		{
			return true;
		}
	}
	return false;
}