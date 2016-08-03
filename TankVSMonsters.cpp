#include "Service.h"
#include "Objects.h"
#include "Scene.h"
#include "Input.h"
#include "Tank.h"

HGE* hge = 0;
Objects* objects = 0;
Scene* scene = 0;
unsigned short attempts = 5;
bool toExit = true;
float dt;

void ShowErrorMessageIfAnyAndSafeExit( const std::string& error = "" );
void ReleaseGameSources( );

bool FrameFunc( )
{
	// Get timer delta
	dt = hge->Timer_GetDelta( );
	scene->setTimer( );

	// Press ESC to exit
	if ( Input::handleEsc( ) )
	{
		return true;
	}

	// Press Enter to continue
	if( Input::handleEnter( ) )
	{
		if( attempts > 0 && objects->getTank( )->getHealth( ) < 0.0f )
		{
			toExit = false;
			return true;
		}
	}

	if( objects->getTank( )->getHealth( ) < 0.0f || scene->getTimer( ) >= SURVIVAL_TIME )
	{
		return false;
	}

	objects->frameObjects( );

	return false;	
}

bool RenderFunc( )
{
	hge->Gfx_BeginScene( );
	
	scene->renderScene( );

	// Player loses
	if( objects->getTank( )->getHealth( ) < 0.0f )
	{
		if( attempts == 0 )
		{
			scene->renderFont( 255, 255, 0, 0, 3.0f, GAME_WIDTH / 2.0f, GAME_HEIGHT / 2.0f, HGETEXT_CENTER, "-=GAME OVER=-" ); 
			scene->renderFont( 255, 255, 0, 0, 1.0f, GAME_WIDTH / 2.0f, GAME_HEIGHT / 2.0f + 100.0f, HGETEXT_CENTER, "Press Esc to exit" ); 
		}
		else
		{
			scene->renderFont( 255, 255, 0, 0, 3.0f, GAME_WIDTH / 2.0f, GAME_HEIGHT / 2.0f, HGETEXT_CENTER, "-=LOSE=-" );
			scene->renderFont( 255, 255, 0, 0, 1.0f, GAME_WIDTH / 2.0f, GAME_HEIGHT / 2.0f + 100.0f, HGETEXT_CENTER, "Press Enter to try again" ); 
		}
		hge->Gfx_EndScene( );
		return false;
	}
	
	// Player wins
	if( scene->getTimer( ) >= SURVIVAL_TIME )
	{
		scene->renderFont( 255, 0, 255, 0, 3.0f, GAME_WIDTH / 2.0f, GAME_HEIGHT / 2.0f, HGETEXT_CENTER, "-=WIN=-" ); 
		scene->renderFont( 255, 0, 255, 0, 1.0f, GAME_WIDTH / 2.0f, GAME_HEIGHT / 2.0f + 100.0f, HGETEXT_CENTER, "Press Esc to exit" ); 
		hge->Gfx_EndScene( );
		return false;
	}
	
	objects->renderObjects( );

	scene->renderGameStatistics( );
	
	hge->Gfx_EndScene( );
	return false;
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{	
	// Check for memory leak if debug build
	#if defined( DEBUG ) | defined( _DEBUG )
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );	
	#endif
	
	hge = hgeCreate( HGE_VERSION );
		
	hge->System_SetState( HGE_FRAMEFUNC, FrameFunc );
	hge->System_SetState( HGE_RENDERFUNC, RenderFunc );
	hge->System_SetState( HGE_WINDOWED, true );	
	hge->System_SetState( HGE_SCREENWIDTH, GAME_WIDTH );
	hge->System_SetState( HGE_SCREENHEIGHT, GAME_HEIGHT );
	hge->System_SetState( HGE_SCREENBPP, 32 );
	hge->System_SetState( HGE_TITLE, "TankVSMonsters" );
	
	if( hge->System_Initiate( ) )
	{
		while( attempts > 0 )
		{
			try
			{
				scene = Scene::getInstance( );
				objects = Objects::getInstance( );
			}
			catch( const game_errors& gerr )
			{
				switch( gerr )
				{
				case game_errors::LOAD_SCENE_SOURCES:
					ShowErrorMessageIfAnyAndSafeExit( "Can't load scene sources." );
					return 0;
				case game_errors::LOAD_TANK_SOURCES:
					ShowErrorMessageIfAnyAndSafeExit( "Can't load tank sources." );
					return 0;
				case game_errors::LOAD_MONSTER_SOURCES:
					ShowErrorMessageIfAnyAndSafeExit( "Can't load monster sources." );
					return 0;
				case game_errors::LOAD_WEAPON_SOURCES:
					ShowErrorMessageIfAnyAndSafeExit( "Can't load weapon sources." );
					return 0;
				case game_errors::LOAD_PACKET_SOURCES:
					ShowErrorMessageIfAnyAndSafeExit( "Can't load packet sources." );
					return 0;
				case game_errors::UNKNOWN_ERROR: 
					ShowErrorMessageIfAnyAndSafeExit( "Unknown error." );
					return 0;
				}
			}
			catch(...)
			{
				ShowErrorMessageIfAnyAndSafeExit( "Something goes wrong." );
				return 0;
			}	

			hge->System_Start();

			if( toExit )
			{
					break;
			}
			
			toExit = true;
			ReleaseGameSources();
		}
	}
	else
	{
		MessageBox( NULL, hge->System_GetErrorMessage( ), "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL );
	}

	ShowErrorMessageIfAnyAndSafeExit( ); 
	return 0;
}

void ReleaseGameSources( )
{
	delete objects;
	delete scene;
}

void ShowErrorMessageIfAnyAndSafeExit( const std::string& error )
{
	if( !error.empty( ) )
	{
		MessageBox( NULL, error.c_str( ), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL );
	}
	ReleaseGameSources( );
	hge->System_Shutdown( );
	hge->Release( );
}
