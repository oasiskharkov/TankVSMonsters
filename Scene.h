#ifndef _SCENE_H_
#define _SCENE_H_

#include "Service.h"

class Scene
{
private:
	// Timer
	float m_fTimer; 

	// Unique pointer to the font 
	std::unique_ptr<hgeFont> m_upFont;

	// Background tile texture
	HTEXTURE h_backgroundTex;

	// Unique pointer to the background tile sprite
	std::unique_ptr<hgeSprite> m_upBackground;

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

	// Render game statistics
	void renderGameStatistics();

	// Get scene instance
	static Scene* getInstance( );

	// Get timer
	float getTimer( ) const;

	// Set timer
	void setTimer( );

	// Render strings
	void renderFont( int a, int r, int g, int b, float scale, float x, float y, int align, const std::string& str );
};

inline float Scene::getTimer( ) const
{
	return m_fTimer;
}

inline void Scene::setTimer( )
{
	m_fTimer += dt;
}

#endif