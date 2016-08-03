#include "Monster.h"
#include "Objects.h"
#include "Tank.h"

Monster::Monster( monster_type type, float xPos, float yPos, float health, float armor, float damage, float speed,
					  const char* monster ) : m_eMonsterType( type ), m_vPos( xPos, yPos ), m_fHealth( health ),
					  m_fArmor( armor ), m_fDamage( damage ), m_fSpeed( speed ), m_fDeltaTime( 0.0f ),
					  m_pMonsterAnimated( 0 ), m_pMonsterStopped( 0 )
{
	m_hMonsterTex = hge->Texture_Load( monster );

	recalculateDirection( );

	if( !prepareResources( ) )
	{
		release( );
		throw game_errors::LOAD_MONSTER_SOURCES;
	}
}

Monster::~Monster(void)
{
	release( );
}

bool Monster::prepareResources( )
{
	try
	{
		m_pMonsterAnimated = new hgeAnimation( m_hMonsterTex, 4, 7.0f, 0.0f, 0.0f, 256.0f, 256.0f ); 
	}
	catch(...)
	{
		return false;
	}
	return true;
}

void Monster::release( )
{
	hge->Texture_Free( m_hMonsterTex );

	delete m_pMonsterAnimated;
}

void Monster::frame( ) 
{
	m_fDeltaTime += dt;
	if( m_fDeltaTime >= RECALCULATE_MONSTER_DIR_TIME )
	{
		recalculateDirection( );
		m_fDeltaTime = 0.0f;
	}
	/*hgeVector pos = m_vPos + m_vDir * m_fSpeed * dt;
	if ( checkCollisionWithAnotherMonster( pos ) ) 
	{
		return;
	}
	m_vPos = pos;*/

	m_vPos += m_vDir * m_fSpeed * dt;
}

void Monster::render( )
{
	if( m_pMonsterAnimated != nullptr )
	{
		if( !m_pMonsterAnimated->IsPlaying( ) )
		{
			m_pMonsterAnimated->Play( );
		}
		else
		{
			m_pMonsterAnimated->Update( dt );
		}

		m_pMonsterAnimated->SetHotSpot( 128.0f, 128.0f );
		m_pMonsterAnimated->RenderEx( m_vPos.x, m_vPos.y, m_vDir.Angle( ) + M_PI_2, 0.2f );
	}
	else
	{
		throw game_errors::NULL_POINTER;
	}
}

void Monster::recalculateDirection( )
{
	m_vDir = ( objects->getTank( )->getPosition( ) - m_vPos );
	m_vDir.Normalize( );
}

bool Monster::checkCollisionWithAnotherMonster( const hgeVector& pos )
{
	std::vector<std::unique_ptr<Monster>>& monsters = objects->getMonsters( );

	for( size_t i = 0; i < monsters.size( ); i++ )
	{
		if( monsters.at( i ) != 0 && this != monsters.at( i ).get( ) )
		{
			auto monsterPos = monsters.at( i )->getPosition( );
			if( Objects::distanceBetweenPoints( pos, monsterPos ) < 2 * MONSTER_RADIUS ) 
			{
				return true;
			}
		}
	}
	return false;
}