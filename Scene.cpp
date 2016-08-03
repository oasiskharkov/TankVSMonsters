#include "Scene.h"
#include "Objects.h"
#include "Tank.h"
#include "Weapon.h"

Scene* Scene::instance( 0 );

Scene* Scene::getInstance( )
{
   if( instance == 0 )
	{
		instance = new Scene( );
	}
	return instance;
}

Scene::Scene( ) : m_fTimer( 0.0f )
{
	h_backgroundTex = hge->Texture_Load( "Resources\\background.png" );

	// If one of the source files is not found, free all scene sources and throw an error message.
	if( !prepareSources( ) || !m_upBackground.get( ) || !m_upFont.get( ) )
	{
		release( );
		throw game_errors::LOAD_SCENE_SOURCES;
	}
}

Scene::~Scene( )
{
	release( );
}

void Scene::release( )
{
	hge->Texture_Free( h_backgroundTex );

	instance = 0;
}

bool Scene::prepareSources( )
{
	try
	{
		m_upBackground.reset(new hgeSprite( h_backgroundTex, 0.0f, 0.0f, 32.0f, 32.0f ) );
		m_upFont.reset( new hgeFont( "Resources\\font1.fnt" ) );
	}
	catch(...)
	{
		return false;
	}
	return true;
}

void Scene::renderBackground( )
{
	float tile_x = 0, tile_y = 0;
	for( size_t i = 0; i < GAME_HEIGHT/32; i++ )
	{
		for( size_t j = 0; j < GAME_WIDTH/32; j++ )
		{
			m_upBackground->RenderStretch( tile_x, tile_y, tile_x + TILE_STEP, tile_y + TILE_STEP );
			tile_x += TILE_STEP;
		}
		tile_y += TILE_STEP;
		tile_x = 0.0f;
	}
}

void Scene::renderScene( )
{
	renderBackground( ); 
}

void Scene::renderFont( int a, int r, int g, int b, float scale, float x, float y, int align, const std::string& str )
{
	m_upFont->SetColor( ARGB( a, r, g, b ) );
	m_upFont->SetScale( scale );
	m_upFont->Render( x, y, align, str.c_str( ) ); 
}

void Scene::renderGameStatistics()
{
	// Show intro
	if( m_fTimer < 3.0f )
	{
		scene->renderFont( 255, 0, 255, 0, 3.0f, GAME_WIDTH / 2.0f, 30.0f, HGETEXT_CENTER, "-=SURVIVAL=-" ); 
	}

	// Show statistics
	std::string atp( "attempts: " );
	atp += std::to_string( attempts ); 
	renderFont( 255, 128, 128, 128, 1.0f, GAME_WIDTH - 140.0f, 10.0f, HGETEXT_LEFT, atp );

	std::string str( "health: ");
	int health = static_cast<int>( objects->getTank( )->getHealth( ) * 100 );
	str += std::to_string( health ); 
	renderFont( 255, 128, 128, 128, 1.0f, GAME_WIDTH - 140.0f, 40.0f, HGETEXT_LEFT, str );

	std::string timer( "timer: "); 
	timer += std::to_string( static_cast<int>(SURVIVAL_TIME) - static_cast<int>(m_fTimer) );
	timer += "s";
	renderFont( 255, 128, 128, 128, 1.0f, GAME_WIDTH - 140.0f, 70.0f, HGETEXT_LEFT, timer );

	std::string bst( "beasts: ") ;
	bst += std::to_string( objects->getDeadBeastQuantity( ) ); 
	renderFont( 255, 128, 128, 128, 1.0f, 10.0f, 10.0f, HGETEXT_LEFT, bst );

	std::string dmn( "daemons: ");
	dmn += std::to_string( objects->getDeadDaemonQuantity( ) ); 
	renderFont( 255, 128, 128, 128, 1.0f, 10.0f, 40.0f, HGETEXT_LEFT, dmn );

	std::string rpt( "reptiles: "); 
	rpt += std::to_string( objects->getDeadReptileQuantity( ) );
	renderFont( 255, 128, 128, 128, 1.0f, 10.0f, 70.0f, HGETEXT_LEFT, rpt );

	std::string blt( "bullets: ");
	blt += std::to_string( Weapon::getBulletsQuantity( ) );
	renderFont( 255, 128, 128, 128, 1.0f, 10.0f, GAME_HEIGHT - 90.0f, HGETEXT_LEFT, blt );

	std::string shl( "shells: ");
	shl += std::to_string( Weapon::getShellsQuantity( ) );
	renderFont( 255, 128, 128, 128, 1.0f, 10.0f, GAME_HEIGHT - 60.0f, HGETEXT_LEFT, shl );

	std::string rct( "rockets: ");
	rct += std::to_string( Weapon::getRocketsQuantity( ) );
	renderFont( 255, 128, 128, 128, 1.0f, 10.0f, GAME_HEIGHT - 30.0f, HGETEXT_LEFT, rct );
}