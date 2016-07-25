#include "Service.h"
#include "Objects.h"
#include "Scene.h"

HGE* hge = 0;
Objects* objects = 0;
Scene* scene = 0;
unsigned short lives = 20;
float dt;

void ShowErrorMessageIfAnyAndSafeExit( const std::string& error = "" );
void ReleaseGameSources( );

bool FrameFunc( )
{
	// Get timer delta
	dt = hge->Timer_GetDelta();

	// Press ESC to exit
	if (hge->Input_GetKeyState(HGEK_ESCAPE))
	{
		return true;
	}

	return false;	
}

bool RenderFunc( )
{
	hge->Gfx_BeginScene( );
	
	scene->renderScene( );
	
	hge->Gfx_EndScene();

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
		try
		{
			scene = Scene::getInstance();
		}
		catch(game_errors& gerr)
		{
			switch(gerr)
			{
			case game_errors::LOAD_SCENE_SOURCES:
				ShowErrorMessageIfAnyAndSafeExit("Can't load scene sources.");
				return 0;
			case game_errors::LOAD_TANK_SOURCES:
				ShowErrorMessageIfAnyAndSafeExit("Can't load tank sources.");
				return 0;
			}
		}
		catch(...)
		{
			ShowErrorMessageIfAnyAndSafeExit("Something goes wrong.");
			return 0;
		}	
		hge->System_Start();
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
