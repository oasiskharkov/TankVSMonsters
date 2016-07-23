#ifndef _SCENE_H_
#define _SCENE_H_

#include "Service.h"

class Scene
{
private:
	// Background tile texture
	HTEXTURE h_backgroundTex;

	// Unique pointer to the background tile sprite
	std::unique_ptr<hgeSprite> up_background;

	// Render background
	void renderBackground( );

	// Free all sources
	void release();

	// Prepare all sources
	bool prepareSources( );

	// Private constructor
	Scene( );

	// Scene instance
	static Scene* instance;
public:
	// Destructor
	~Scene( );

	// Render all scene
	void renderScene( );

	// Get scene instance
	static Scene* getInstance( );
};

#endif