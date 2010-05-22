#pragma once
#ifndef _SPACIALOBJECT_H
#define _SPACIALOBJECT_H

#include <irrlicht.h>
using namespace irr;
using namespace core;

//! Definiert ein Objekt im Raum
class SpatialObject
{
public:

	/**	Instanziert ein Raumobjekt mit den Vorgabewerten
	 */
	SpatialObject() : position(0, 0, 0), velocity(0, 0, 0), acceleration(0, 0, 0)  {}

	/**	Instanziert ein Raumobjekt mit einer Position.
	 * Geschwindigkeit und Beschleunigung werden auf die Vorgabewerte gesetzt.
	 * @param pos Die zu setzende Position
	 */
	SpatialObject(const vector3df &pos) : position(pos), velocity(0, 0, 0), acceleration(0, 0, 0)  {}

	/**	Instanziert ein Raumobjekt mit Position und Geschwindigkeit.
	 * Die Beschleunigung werden auf die Vorgabewerte gesetzt.
	 * @param pos Die zu setzende Position
	 * @param vel Die zu setzende Geschwindigkeit
	 */
	SpatialObject(const vector3df &pos, const vector3df &vel) : position(pos), velocity(vel), acceleration(0, 0, 0)  {}

	/**	Instanziert ein Raumobjekt mit Position, Geschwindigkeit und Beschleunigung.
	 * @param pos Die zu setzende Position
	 * @param vel Die zu setzende Geschwindigkeit
	 * @param acc Die zu setzende Beschleunigung
	 */
	SpatialObject(const vector3df &pos, const vector3df &vel, const vector3df &acc) : position(pos), velocity(vel), acceleration(acc)  {}
	
	/** Desktuktor */
	virtual ~SpatialObject(void) {}

	/**	Ermittelt die Position des Objekt
	 *	@return Die Position
	 */
	 const vector3df &getPosition() const { return position; }

	/** Ermittelt die Geschwindigkeit des Objekt.
	 *	@return Die Geschwindigkeit
	 */
	 const vector3df &getVelocity() const { return velocity; }

	/** Ermittelt die Beschleunigung des Objekt.
	 *	@return Die Beschleunigung
	 */
	 const vector3df &getAcceleration() const { return acceleration; }
	
	/** Setzt die Position des Objektes
	 * @param position Die zu übernehmende Position
	 */
	void setPosition(const vector3df &position) { this->position = position; }

	/** Setzt die Position des Objektes
	 * @param x X-Koordinate der zu übernehmende Position
	 * @param y Y-Koordinate der zu übernehmende Position
	 * @param z Z-Koordinate der zu übernehmende Position
	 */
	void setPosition(float x, float y, float z) { this->position = vector3df(x, y, z); }

	/** Setzt die Geschwindigkeit des Objektes
	 * @param position Die zu übernehmende Geschwindigkeit
	 */
	void setVelocity(const vector3df &velocity) { this->velocity = velocity; }

	/** Setzt die Position des Objektes
	 * @param x X-Anteil des zu übernehmenden Geschwindigkeitsvektors
	 * @param y Y-Anteil des zu übernehmenden Geschwindigkeitsvektors
	 * @param z Z-Anteil des zu übernehmenden Geschwindigkeitsvektors
	 */
	void setVelocity(float x, float y, float z) { this->velocity = vector3df(x, y, z); }

	/** Setzt die Beschleunigung des Objektes
	 * @param position Die zu übernehmende Beschleunigung
	 */
	void setAcceleration(const vector3df &acceleration) { this->acceleration = acceleration; }

	/** Setzt die Beschleunigung des Objektes
	 * @param x X-Anteil des zu übernehmenden Beschleunigungsvektors
	 * @param y Y-Anteil des zu übernehmenden Beschleunigungsvektors
	 * @param z Z-Anteil des zu übernehmenden Beschleunigungsvektors
	 */
	void setAcceleration(float x, float y, float z) { this->acceleration = vector3df(x, y, z); }

	/** Verändert die Position des Objektes
	 * @param vector Hinzuzufügender Vektor
	 */
	void addPosition(const vector3df &vector) { this->position += vector; }

	/** Verändert die Position des Objektes
	 * @param x Hinzuzufügender X-Anteil
	 * @param y Hinzuzufügender Y-Anteil
	 * @param z Hinzuzufügender Z-Anteil
	 */
	void addPosition(float x, float y, float z) { 
		this->position.X += x;
		this->position.Y += y;
		this->position.Z += z;
	}

	/** Verändert die Geschwindigkeit des Objektes
	 * @param vector Hinzuzufügender Vektor
	 */
	void addVelocity(const vector3df &vector) { this->velocity += vector; }

	/** Verändert die Geschwindigkeit des Objektes
	 * @param x Hinzuzufügender X-Anteil
	 * @param y Hinzuzufügender Y-Anteil
	 * @param z Hinzuzufügender Z-Anteil
	 */
	void addVelocity(float x, float y, float z) { 
		this->velocity.X += x;
		this->velocity.Y += y;
		this->velocity.Z += z;
	}
	
	/** Verändert die Beschleunigung des Objektes
	 * @param vector Hinzuzufügender Vektor
	 */
	void addAcceleration(const vector3df &vector) { this->acceleration += vector; }

	/** Verändert die Beschleunigung des Objektes
	 * @param x Hinzuzufügender X-Anteil
	 * @param y Hinzuzufügender Y-Anteil
	 * @param z Hinzuzufügender Z-Anteil
	 */
	void addAcceleration(float x, float y, float z) { 
		this->acceleration.X += x;
		this->acceleration.Y += y;
		this->acceleration.Z += z;
	}

	/** Aktualisiert Geschwindigkeit und Position.
	 * Aktualisiert die Geschwindigkeit und Position in Abhängigkeit von der vergangenen Zeit und 
	 * Beschleunigung (und konsequenterweise der Geschwindigkeit).
	 * @param deltaTInSeconds Die vergangene Zeit in Sekunden
	 */
	void update(float deltaTInSeconds) { 
		velocity += acceleration * deltaTInSeconds;
		position += velocity * deltaTInSeconds; 
	}

protected:

	/** Aktualisiert die Position.
	 * Aktualisiert die Position in Abhängigkeit von der vergangenen Zeit und der aktuellen Geschwindigkeit.
	 * @param deltaTInSeconds Die vergangene Zeit in Sekunden
	 */
	void updatePosition(float deltaTInSeconds) { position += velocity * deltaTInSeconds; }

	/** Aktualisiert die Geschwindigkeit.
	 * Aktualisiert die Geschwindigkeit in Abhängigkeit von der vergangenen Zeit und der aktuellen Beschleunigung.
	 * @param deltaTInSeconds Die vergangene Zeit in Sekunden
	 */
	void updateVelocity(float deltaTInSeconds) { velocity += acceleration * deltaTInSeconds; }

protected:
	//! Die Position des Objektes
	vector3df position;

	//! Die Geschwindigkeit des Objektes
	vector3df velocity;

	//! Die Beschleunigung des Objektes
	vector3df acceleration;
};

#endif
