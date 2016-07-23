#include "Scene.h"

Scene* Scene::instance(0);

Scene* Scene::getInstance( )
{
   static Scene* instance = new Scene( );
   return instance;
}

Scene::Scene( )
{
	h_backgroundTex = hge->Texture_Load( "Resources\\background.png" );

	// If one of the source files is not found, free all field sources and throw an error message.
	if( !prepareSources( ) || !up_background.get( ) )
	{
		release();
		throw game_errors::LOAD_SCENE_SOURCES;
	}
}

Scene::~Scene( )
{
	release( );
}

void Scene::release()
{
	hge->Texture_Free( h_backgroundTex );
	instance = 0;
}

bool Scene::prepareSources( )
{
	try
	{
		up_background.reset(new hgeSprite(h_backgroundTex, 0.0f, 0.0f, 32.0f, 32.0f));
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
		for( size_t j = 0; j < GAME_WIDTH/32; j++)
		{
			up_background->RenderStretch( tile_x, tile_y, tile_x + TILE_STEP, tile_y + TILE_STEP );
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