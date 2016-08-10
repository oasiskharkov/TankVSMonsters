#ifndef _INPUT_H_
#define _INPUT_H_

#include "Service.h"

class Input
{
private:
	// Old 'W' key state
	static bool oldWKeyState;

	// Old 'Q' key state
	static bool oldQKeyState;

	// Old 'X' key state
	static bool oldXKeyState;

		// Handle 'left arrow' key
	static void handleLeftArrow( );

	// Handle 'right arrow' key
	static void handleRightArrow( );

	// Handle 'up arrow' key
	static void handleUpArrow( );

	// Handle 'down arrow' key
	static void handleDownArrow( );
	
	// Handle 'Q' key
	static void handleQ( );

	// Handle 'W' key
	static void handleW( );

	// Handle 'X' key
	static void handleX( );
public:
	// Handle all tank control keys
	static void handleTankControlKeys( );

	// Handle 'Esc' key
	static bool handleEsc( );

	// Handle 'Enter' key
	static bool handleEnter( );
};

#endif