#pragma once

#include <time.h>
#include <stdarg.h>


bool RestartLog();
bool GameLog(const char* message, ...);
bool ErrorLog(const char* message, ...);
void LogOpenGLParams();

char * LoadFileInMemory(const char *filename);
void FlipTexture(unsigned char* image_data,int x,int y , int n);
