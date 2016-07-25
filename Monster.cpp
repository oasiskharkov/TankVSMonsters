#include "Monster.h"


Monster::Monster( monster_type type, float xPos, float yPos, float health, float armor, float damage, float speed, float direction,
					  const char* monster ) : m_eMonsterType( type ), m_vPos( xPos, yPos ), m_fHealth( health ), m_fArmor( armor ), 
					  m_fDamage( damage ), m_fSpeed( speed ), m_fDirection( direction ), m_pMonsterAnimated( 0 ), m_pMonsterStopped( 0 )
{
	m_hMonsterTex = hge->Texture_Load( monster );

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
		//m_pTankAnimated = new hgeAnimation()
		//m_pTankStopped = new hgeSpite()
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
	delete m_pMonsterStopped;
}
