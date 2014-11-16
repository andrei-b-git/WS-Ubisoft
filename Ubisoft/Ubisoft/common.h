#pragma once

#include <GLEW/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdio.h>
#include <assert.h>

// Globale
#define PI				3.141592741f

#define WWIDTH			1366
#define WHEIGHT			720
#define inner_lim		0.6f
#define outer_lim		1.5f
#define GL_LOG_FILE		"gl.log"
#define anim_speed		25.0f
#define	dt_physics		0.01f
#define collision_delay	0.2f
#define wave_delay		32.0f

enum SPRITE_TYPES
{
							BACKGROUND	= 10,
						
	PLAYER		= 1,		THRUST		= 11,		RED_BAR		= 18,		NUMBER_7	= 27,
	PROJECTILE	= 2,		GUN_BLAST	= 12,		GREEN_BAR	= 19,		NUMBER_8	= 28,
	ROCKET		= 3,														NUMBER_9	= 29,

	ENEMY1		= 4,		EXPLOSION1	= 13,		NUMBER_0	= 20,		RKT_ICON	= 30,
	ENEMY2		= 5,		EXPLOSION2	= 14,		NUMBER_1	= 21,		SCORE		= 31,
	ENEMY3		= 6,		EXPLOSION3	= 15,		NUMBER_2	= 22,		READY		= 32,
							EXPLOSION4	= 16,		NUMBER_3	= 23,		OVER		= 33,
	BONUS		= 7,		EXPLOSION5	= 17,		NUMBER_4	= 24,
	ROCK1		= 8,								NUMBER_5	= 25,
	ROCK2		= 9,								NUMBER_6	= 26
};

extern GLFWwindow* window;
extern float winRatio;
extern glm::mat4 projection_matrix;
extern glm::mat4 view_matrix;
extern int score;
extern int nr_rockets;
extern int nr_e1_killed;
extern int nr_e2_killed;
extern bool GAME_OVER;

// BACKGROUND
#define b_speed			0.05f

// PLAYER
#define p_coords_x		0.0f
#define p_coords_y		-winRatio/3
#define p_speed			1.0f
#define p_hp			100.0f
#define p_dmg			50.0f

#define p_left_begin	1.0f
#define p_left_end		16.0f
#define p_right_begin	17.0f
#define p_right_end		32.0f
#define p_up_begin		33.0f
#define p_up_end		48.0f
#define p_idle_begin	49.0f
#define p_idle_end		63.0f

// THRUST
#define jp_speed		1.5f

#define jp_idle_begin	0.0f
#define jp_idle_end		23.0f

#define jr_idle_begin	0.0f
#define jr_idle_end		23.0f

#define je1_texRatio	(float)64/1024
#define je1_idle_begin	0.0f
#define je1_idle_end	15.0f

// PROJECTILE
#define ppr_speed		1.3f
#define fire_rate		0.3f
#define ppr_dmg			10.0f

#define e1pr_speed		0.5f
#define e1pr_delay		5.0f
#define e1pr_dmg		10.0f

#define pr_texRatio		(float)32/512

#define pr_idle_begin	0.0f
#define pr_idle_end		15.0f

// GUN_BLAST
#define gp_idle_begin	0.0f
#define gp_idle_end		7.0f

#define gr_idle_begin	0.0f
#define gr_idle_end		11.0f

#define ge1_idle_begin	0.0f
#define ge1_idle_end	7.0f

// ROCKET
#define r_speed			1.5f
#define r_delay			0.5f
#define r_dmg			100.0f

// BONUS
#define b_idle_begin	0.0f
#define b_idle_end		15.0f

// ENEMY1
#define e1_nr_wave		7

#define e1_speed		0.07f
#define e1_hp			30.0f
#define e1_red_rate		0.3f
#define e1_dmg			30.0f
#define e1_hit			5
#define e1_kill			20

#define e1_idle_begin	0.0f
#define e1_idle_end		15.0f

// ENEMY2
#define e2_nr_wave		10

#define e2_speed		0.08f
#define e2_hp			30.0f
#define e2_red_rate		0.2f
#define e2_dmg			30.0f
#define e2_hit			15
#define e2_kill			60

#define e2_idle_begin	0.0f
#define e2_idle_end		15.0f

// EXPLOSION1
#define ex1_idle_begin	0.0f
#define ex1_idle_end	39.0f

// EXPLOSION2
#define ex2_idle_begin	0.0f
#define ex2_idle_end	31.0f

// EXPLOSION3
#define ex3_idle_begin	0.0f
#define ex3_idle_end	47.0f

// EXPLOSION4
#define ex4_idle_begin	0.0f
#define ex4_idle_end	63.0f

// EXPLOSION5
#define ex5_idle_begin	0.0f
#define ex5_idle_end	63.0f