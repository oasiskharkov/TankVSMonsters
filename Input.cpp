#include "Input.h"
#include "Objects.h"
#include "Tank.h"
#include "Weapon.h"

bool Input::oldWKeyState( true );

bool Input::oldQKeyState( true );

bool Input::oldXKeyState( true );

void Input::handleLeftArrow( )
{
	if( hge->Input_GetKeyState( HGEK_LEFT ) ) 
	{
		objects->getTank( )->turn( false );
	}
}

void Input::handleRightArrow( )
{
	if( hge->Input_GetKeyState( HGEK_RIGHT ) )
	{
		objects->getTank( )->turn( );
	}
}

void Input::handleUpArrow( )
{
	hge->Input_GetKeyState( HGEK_UP ) ? objects->getTank( )->setMoving( ) 
		: objects->getTank( )->setMoving( false );  
}

void Input::handleDownArrow( )
{
	hge->Input_GetKeyState( HGEK_DOWN ) ? objects->getTank( )->setBackMoving( ) 
		: objects->getTank( )->setBackMoving( false );
}

void Input::handleQ( )
{
	if( !oldQKeyState && hge->Input_GetKeyState( HGEK_Q ) )
	{
		 objects->getTank( )->changeWeapon( false );
	}
	oldQKeyState = hge->Input_GetKeyState( HGEK_Q );
}

void Input::handleW( )
{
	if( !oldWKeyState && hge->Input_GetKeyState( HGEK_W ) )
	{
		objects->getTank( )->changeWeapon( );
	}
	oldWKeyState = hge->Input_GetKeyState( HGEK_W );
}

void Input::handleX( )
{
	if( !oldXKeyState && hge->Input_GetKeyState( HGEK_X ) )
	{
		objects->getTank( )->getCurrentWeapon( )->shot( );
	}
	oldXKeyState = hge->Input_GetKeyState( HGEK_X );
}

void Input::handleTankControlKeys( )
{
	handleLeftArrow( );
	handleRightArrow( );
	handleUpArrow( );
	handleDownArrow( );
	handleQ( );
	handleW( );
	handleX( );
}

bool Input::handleEsc( )
{
	return hge->Input_GetKeyState( HGEK_ESCAPE );
}

bool Input::handleEnter( )
{
	return hge->Input_GetKeyState( HGEK_ENTER );
}

	

	
