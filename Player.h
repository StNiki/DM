#ifndef PLAYER_H
#define PLAYERL_H

#pragma once

class Player
{
public:
	std::string						armor;
	glm::vec3						myPosition;
	glm::vec3						newPosition;
	glm::vec3						eyePosition;
	glm::vec3						targetPosition;
	glm::vec3						front;
	glm::vec3						r;
	float							v;
	float							rotangle;
	int								treasures;
	bool							isAlive;
	int								xz[56][58];


	// Constructor
	Player(std::string	name,glm::vec3 myPosition, glm::vec3 eyePosition, glm::vec3 targetPosition);

	// Destructor
	~Player(void);

	// public function declarations
	void								Die();
	bool								Win();
	bool								Trap();
	bool								checkCollision(float x, float y);
	void								moveRight();
	void								moveLeft();
	void								moveForward();
	void								moveBack();

};

#endif