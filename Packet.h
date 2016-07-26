#ifndef _PACKET_H_
#define _PACKET_H_

#include "Service.h"

class Packet
{
private:
	// Packet's type
	packet_type m_ePacketType;

	// Current packet's position
	hgeVector m_vPos;

	// Packet's direction
	hgeVector m_vDir;

	// Packet's damage
	float m_fDamage;

	// Packet's speed
	float m_fSpeed;
		
	// Packet's texture
	HTEXTURE m_hPacketTex;
	
	// Packets's animation
	hgeAnimation* m_pPacketAnimated;

	// Prepeare packet's resources
	bool prepareResources();

	// Release all allocated memory
	void release();

	// Private copy constructor
	Packet( const Packet& );

	// Private copy assignment operator
	Packet& operator = ( const Packet& );
public:
	// Constructor
	Packet( );

	// Destructor
	~Packet( );
			
	// Get packet's type
	packet_type getType( ) const;

	// Get packet's position
	hgeVector getPosition( ) const;

	// Get packet's direction
	hgeVector getDirection( ) const;

	// Get packet's damage
	float getDamage( ) const;

	// Get packet's speed
	float getSpeed( ) const;

	// Set packet's position
	void setPosition( hgeVector position );
	
	// Set packet's direction
	void setDirection( hgeVector direction );

	// Set packet's damage
	void setDamage( float damage );

	// Set packet's speed
	void setSpeed( float speed );
};

inline packet_type Packet::getType( ) const
{
	return m_ePacketType;
}

inline hgeVector Packet::getPosition( ) const
{
	return m_vPos;
}

inline hgeVector Packet::getDirection( ) const
{
	return m_vDir;
}

inline float Packet::getDamage( ) const
{
	return m_fDamage;
}

inline float Packet::getSpeed( ) const
{
	return m_fSpeed;
}

inline void Packet::setPosition( hgeVector position )
{
	m_vPos = position;
}
	
inline void Packet::setDirection( hgeVector direction )
{
	m_vDir = direction;
}

inline void Packet::setDamage( float damage )
{
	m_fDamage = damage;
}


inline void Packet::setSpeed( float speed )
{
	m_fSpeed = speed;
}

#endif

