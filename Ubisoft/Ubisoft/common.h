#pragma once

#include <GLEW/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdio.h>
#include <assert.h>

// Globale
#define WWIDTH			1366
#define WHEIGHT			720
#define GL_LOG_FILE		"gl.log"
#define anim_speed		25.0f

enum SPRITE_TYPES
{
	PLAYER		= 1,		BACKGROUND	= 0,
	PROJECTILE	= 2,		JET_PLAYER	= 1,
	ROCKET		= 3,		JET_ROCKET	= 2,
	ENEMY1		= 4,		EXPLOSION1	= 3,
	ENEMY2		= 5,		EXPLOSION2	= 4,
	ENEMY3		= 6,
	ENEMY4		= 7,
	ROCK1		= 8,
	ROCK2		= 9,
	ROCK3		= 10
};

extern GLFWwindow* window;
extern float winRatio;
extern glm::mat4 projection_matrix;
extern glm::mat4 view_matrix;

// PLAYER:
#define p_speed			1.0f

#define p_left_begin	1.0f
#define p_left_end		16.0f
#define p_right_begin	17.0f
#define p_right_end		32.0f
#define p_up_begin		33.0f
#define p_up_end		48.0f
#define p_idle_begin	49.0f
#define p_idle_end		63.0f

// JET_PLAYER:
#define jp_idle_begin	0.0f
#define jp_idle_end		23.0f

// PROJECTILE:
#define pr_speed		1.3f
#define pr_texRatio		(float)32/512
#define pr_delay		0.5f

#define pr_idle_begin	0.0f
#define pr_idle_end		15.0f
