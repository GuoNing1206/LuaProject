// LuaBindOpenGL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LuaLibOpenGL.h"

LuaLibOpenGL gLuaLibOpenGL;

void OnInitialize()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void CALLBACK OnWindowSize(GLsizei w,GLsizei h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(w<=h)
		glOrtho(-1.5,1.5,-1.5*(GLfloat)h/(GLfloat)w,
		1.5*(GLfloat)h/(GLfloat)w,-10.0,10.0);
	else
		glOrtho(-1.5*(GLfloat)w/(GLfloat)h,
		1.5*(GLfloat)w/(GLfloat)h,-1.5,1.5,-10.0,10.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CALLBACK OnRend(void)
{
	gLuaLibOpenGL.Rend();
	glFlush();
}

int main(int argc, char* argv[])
{
	lua_State*	L = luaL_newstate();
	luaL_openlibs(L);
	gLuaLibOpenGL.Initialize(L);

	auxInitDisplayMode(AUX_SINGLE | AUX_RGBA);
	auxInitPosition(1366 - 550, 50, 500, 500);
	auxInitWindow("Lua bind OpenGL");
	OnInitialize();
	auxReshapeFunc(OnWindowSize);
  auxMainLoop(OnRend);

	lua_close(L);
	return 0;
}

