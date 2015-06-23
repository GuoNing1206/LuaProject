/*-----------------------------------------------------------------------------

	作者：郭宁 2015/03/02
	备注：
	审核：

-----------------------------------------------------------------------------*/
#include "stdafx.h"
#include "LuaLibOpenGL.h"

/*===========================================================================
	
	功能:     2014/10/17
	
===========================================================================*/
ScriptTableRegister::ScriptTableRegister(
	lua_State* A_LuaState, ConstCharPtr A_TableName)
	: m_TableName(A_TableName),
		m_LuaState(A_LuaState)
{}

/*---------------------------------------------------------------------------
	2014/10/17 功能: 
---------------------------------------------------------------------------*/
void ScriptTableRegister::BeginRegistTable()
{
	lua_newtable(m_LuaState);
}

/*---------------------------------------------------------------------------
	2014/10/17 功能: 
---------------------------------------------------------------------------*/
void ScriptTableRegister::EndRegistTable()
{
	lua_setglobal(m_LuaState,  m_TableName);
}

/*---------------------------------------------------------------------------
	2014/10/17 功能: 
---------------------------------------------------------------------------*/
void ScriptTableRegister::RegistFunc(ConstCharPtr A_FuncName, lua_CFunction A_Func)
{
	lua_pushstring(m_LuaState, A_FuncName);
	lua_pushcfunction(m_LuaState, A_Func);
	lua_settable(m_LuaState, -3);
}

/*---------------------------------------------------------------------------
	2014/10/17 功能: 
---------------------------------------------------------------------------*/
void ScriptTableRegister::RegistNumber(ConstCharPtr A_Name, lua_Number A_Num)
{
	lua_pushstring(m_LuaState, A_Name);
	lua_pushnumber(m_LuaState, A_Num);
	lua_settable(m_LuaState, -3);
}

void ScriptTableRegister::RegistString(ConstCharPtr A_Name, ConstCharPtr A_Value)
{
	lua_pushstring(m_LuaState, A_Name);
	lua_pushstring(m_LuaState, A_Value);
	lua_settable(m_LuaState, -3);
}

/*===========================================================================
	
	功能:     2015/03/02
	
===========================================================================*/
/*---------------------------------------------------------------------------
	2015/03/02 功能:   
---------------------------------------------------------------------------*/
LuaLibOpenGL::LuaLibOpenGL() : m_L(NULL)
{}

/*---------------------------------------------------------------------------
	2015/03/02 功能:   
---------------------------------------------------------------------------*/
LuaLibOpenGL::~LuaLibOpenGL()
{}

/*---------------------------------------------------------------------------
	2015/03/02 功能:   
---------------------------------------------------------------------------*/
void LuaLibOpenGL::Initialize(lua_State* A_L)
{
	m_L = A_L;
	luaopen_bit32(A_L);

	FILE* pFile = fopen("OpenGL.lua", "rb");
	if(pFile != NULL)
	{
		fseek(pFile, 0, SEEK_END);
		int nLen = ftell(pFile);
		char* pBuff = new char[nLen + 1];
		pBuff[nLen] = 0;
		fseek(pFile, 0, SEEK_SET);
		fread(pBuff, nLen, 1, pFile);
		fclose(pFile);
		
		luaL_dostring(m_L, pBuff);
		delete[] pBuff;
	}

	// 注册 OpenGL 函数到 gl 表中
	RegistTableGL();

	// 调用初始化函数
	FuncCall("Init");
}

/*---------------------------------------------------------------------------
	2015/03/02 功能:   
---------------------------------------------------------------------------*/
void LuaLibOpenGL::Rend()
{
	FuncCall("Rend");
}

/*---------------------------------------------------------------------------
	2015/03/02 功能:   
---------------------------------------------------------------------------*/
bool LuaLibOpenGL::FuncCall(ConstCharPtr A_FuncName)
{
	lua_getglobal(m_L, A_FuncName);
	int error = lua_pcall(m_L, 0, 0, 0);
	if(error)
	{
		fprintf(stderr, "%s\n", lua_tostring(m_L, -1));
		lua_pop(m_L, 1);
		return false;
	}
	return true;
}

/*---------------------------------------------------------------------------
	2015/03/02 功能:   
---------------------------------------------------------------------------*/
void LuaLibOpenGL::RegistTableGL()
{
	#define BIND_GL_FUNC(func)	\
		oTable.RegistFunc(#func, LuaLibOpenGL::Lua_##func);
	#define BIND_GL_CONST(name)	\
		oTable.RegistNumber(#name, lua_Number(name));

	ScriptTableRegister oTable(m_L, "gl");
	oTable.BeginRegistTable();
	{
		BIND_GL_FUNC(auxWireSphere);
		BIND_GL_FUNC(glClear);

		// Matrix functions
		BIND_GL_FUNC(glMatrixMode);
		BIND_GL_FUNC(glLoadIdentity);
		BIND_GL_FUNC(glPushMatrix);
		BIND_GL_FUNC(glPopMatrix);
		BIND_GL_FUNC(glTranslatef);
		BIND_GL_FUNC(glRotatef);

		// MatrixMode
		BIND_GL_CONST(GL_MODELVIEW);
		BIND_GL_CONST(GL_PROJECTION);
		BIND_GL_CONST(GL_TEXTURE);

		// Color
		BIND_GL_FUNC(glColor3f);
		BIND_GL_FUNC(glColor4f);

		// Enable/Disable
		BIND_GL_FUNC(glEnable);
		BIND_GL_FUNC(glDisable);
		BIND_GL_CONST(GL_LIGHTING);
		BIND_GL_CONST(GL_FOG);
		BIND_GL_CONST(GL_ALPHA_TEST);
		BIND_GL_CONST(GL_TEXTURE_2D);

		// Shape
		BIND_GL_FUNC(glVertex3f);
		BIND_GL_FUNC(glTexCoord2f);
		BIND_GL_FUNC(glNormal3f);
		BIND_GL_FUNC(glPointSize);
		BIND_GL_FUNC(glLineWidth);
		
		// BeginMode
		BIND_GL_FUNC(glBegin);
		BIND_GL_CONST(GL_POINTS);
		BIND_GL_CONST(GL_LINES);
		BIND_GL_CONST(GL_LINE_LOOP);
		BIND_GL_CONST(GL_LINE_STRIP);
		BIND_GL_CONST(GL_TRIANGLES);
		BIND_GL_CONST(GL_TRIANGLE_STRIP);
		BIND_GL_CONST(GL_TRIANGLE_FAN);
		BIND_GL_CONST(GL_QUADS);
		BIND_GL_CONST(GL_QUAD_STRIP);
		BIND_GL_CONST(GL_POLYGON);
		BIND_GL_FUNC(glEnd);

		// Blend
		BIND_GL_CONST(GL_ZERO);
		BIND_GL_CONST(GL_ONE);
		BIND_GL_CONST(GL_SRC_COLOR);
		BIND_GL_CONST(GL_ONE_MINUS_SRC_COLOR);
		BIND_GL_CONST(GL_SRC_ALPHA);
		BIND_GL_CONST(GL_ONE_MINUS_SRC_ALPHA);
		BIND_GL_CONST(GL_DST_ALPHA);
		BIND_GL_CONST(GL_ONE_MINUS_DST_ALPHA);
		BIND_GL_CONST(GL_DST_COLOR);
		BIND_GL_CONST(GL_ONE_MINUS_DST_COLOR);
		BIND_GL_CONST(GL_SRC_ALPHA_SATURATE);

		// Boolean
		BIND_GL_CONST(GL_TRUE);
		BIND_GL_CONST(GL_FALSE);

		// AlphaFunction
		BIND_GL_CONST(GL_NEVER);
		BIND_GL_CONST(GL_LESS);
		BIND_GL_CONST(GL_EQUAL);
		BIND_GL_CONST(GL_LEQUAL);
		BIND_GL_CONST(GL_GREATER);
		BIND_GL_CONST(GL_NOTEQUAL);
		BIND_GL_CONST(GL_GEQUAL);
		BIND_GL_CONST(GL_ALWAYS);

		// AttribMask
		BIND_GL_CONST(GL_CURRENT_BIT);
		BIND_GL_CONST(GL_POINT_BIT);
		BIND_GL_CONST(GL_LINE_BIT);
		BIND_GL_CONST(GL_POLYGON_BIT);
		BIND_GL_CONST(GL_POLYGON_STIPPLE_BIT);
		BIND_GL_CONST(GL_PIXEL_MODE_BIT);
		BIND_GL_CONST(GL_LIGHTING_BIT);
		BIND_GL_CONST(GL_FOG_BIT);
		BIND_GL_CONST(GL_DEPTH_BUFFER_BIT);
		BIND_GL_CONST(GL_ACCUM_BUFFER_BIT);
		BIND_GL_CONST(GL_STENCIL_BUFFER_BIT);
		BIND_GL_CONST(GL_VIEWPORT_BIT);
		BIND_GL_CONST(GL_TRANSFORM_BIT);
		BIND_GL_CONST(GL_ENABLE_BIT);
		BIND_GL_CONST(GL_COLOR_BUFFER_BIT);
		BIND_GL_CONST(GL_HINT_BIT);
		BIND_GL_CONST(GL_EVAL_BIT);
		BIND_GL_CONST(GL_LIST_BIT);
		BIND_GL_CONST(GL_TEXTURE_BIT);
		BIND_GL_CONST(GL_SCISSOR_BIT);
		BIND_GL_CONST(GL_ALL_ATTRIB_BITS);
	}
	oTable.EndRegistTable();
}

/*---------------------------------------------------------------------------
	2015/03/02 功能:   
---------------------------------------------------------------------------*/
int LuaLibOpenGL::Lua_glClear(lua_State* A_L)
{
	::glClear(GLenum(lua_tonumber(A_L, 1)));
	return 0;
}

/*---------------------------------------------------------------------------
	2015/03/02 功能:   
---------------------------------------------------------------------------*/
int LuaLibOpenGL::Lua_auxWireSphere(lua_State* A_L)
{
	lua_Number fRadius = lua_tonumber(A_L, 1);
	::auxWireSphere(fRadius);
	return 0;
}

/*---------------------------------------------------------------------------
	2015/03/02 功能:   
---------------------------------------------------------------------------*/
int LuaLibOpenGL::Lua_glMatrixMode(lua_State* A_L)
{
	::glMatrixMode(GLenum(lua_tonumber(A_L, 1)));
	return 0;
}

/*---------------------------------------------------------------------------
	2015/03/02 功能:   
---------------------------------------------------------------------------*/
int LuaLibOpenGL::Lua_glPushMatrix(lua_State* A_L)
{
	::glPushMatrix();
	return 0;
}

/*---------------------------------------------------------------------------
	2015/03/02 功能:   
---------------------------------------------------------------------------*/
int LuaLibOpenGL::Lua_glPopMatrix(lua_State* A_L)
{
	::glPopMatrix();
	return 0;
}

/*---------------------------------------------------------------------------
	2015/03/02 功能:   
---------------------------------------------------------------------------*/
int LuaLibOpenGL::Lua_glLoadIdentity(lua_State* A_L)
{
	::glLoadIdentity();
	return 0;
}

/*---------------------------------------------------------------------------
	2015/03/02 功能:   
---------------------------------------------------------------------------*/
int LuaLibOpenGL::Lua_glTranslatef(lua_State* A_L)
{
	::glTranslatef(lua_tonumber(A_L, 1),
		lua_tonumber(A_L, 2),lua_tonumber(A_L, 3));
	return 0;
}

/*---------------------------------------------------------------------------
	2015/03/02 功能:   
---------------------------------------------------------------------------*/
int LuaLibOpenGL::Lua_glRotatef(lua_State* A_L)
{
	::glRotatef(lua_tonumber(A_L, 1), lua_tonumber(A_L, 2), 
		lua_tonumber(A_L, 3), lua_tonumber(A_L, 4));
	return 0;
}

/*---------------------------------------------------------------------------
	2015/03/02 功能:   
---------------------------------------------------------------------------*/
int LuaLibOpenGL::Lua_glVertex3f(lua_State* A_L)
{
	::glVertex3f(lua_tonumber(A_L, 1),
		lua_tonumber(A_L, 2),lua_tonumber(A_L, 3));
	return 0;
}

/*---------------------------------------------------------------------------
	2015/03/02 功能:   
---------------------------------------------------------------------------*/
int LuaLibOpenGL::Lua_glTexCoord2f(lua_State* A_L)
{
	::glTexCoord2f(lua_tonumber(A_L, 1), lua_tonumber(A_L, 2));
	return 0;
}

/*---------------------------------------------------------------------------
	2015/03/02 功能:   
---------------------------------------------------------------------------*/
int LuaLibOpenGL::Lua_glNormal3f(lua_State* A_L)
{
	::glNormal3f(lua_tonumber(A_L, 1), 
		lua_tonumber(A_L, 2), lua_tonumber(A_L, 3));
	return 0;
}

/*---------------------------------------------------------------------------
	2015/03/05 功能:   
---------------------------------------------------------------------------*/
int LuaLibOpenGL::Lua_glPointSize(lua_State* A_L)
{
	::glPointSize(lua_tonumber(A_L, 1));
	return 0;
}

/*---------------------------------------------------------------------------
	2015/03/05 功能:   
---------------------------------------------------------------------------*/
int LuaLibOpenGL::Lua_glLineWidth(lua_State* A_L)
{
	::glLineWidth(lua_tonumber(A_L, 1));
	return 0;
}

/*---------------------------------------------------------------------------
	2015/03/02 功能:   
---------------------------------------------------------------------------*/
int LuaLibOpenGL::Lua_glBegin(lua_State* A_L)
{
	::glBegin(GLenum(lua_tonumber(A_L, 1)));
	return 0;
}

/*---------------------------------------------------------------------------
	2015/03/02 功能:   
---------------------------------------------------------------------------*/
int LuaLibOpenGL::Lua_glEnd(lua_State* A_L)
{
	::glEnd();
	return 0;
}

/*---------------------------------------------------------------------------
	2015/03/02 功能:   
---------------------------------------------------------------------------*/
int LuaLibOpenGL::Lua_glColor3f(lua_State* A_L)
{
	::glColor3f(lua_tonumber(A_L, 1),
		lua_tonumber(A_L, 2),lua_tonumber(A_L, 3));
	return 0;
}

/*---------------------------------------------------------------------------
	2015/03/05 功能:   
---------------------------------------------------------------------------*/
int LuaLibOpenGL::Lua_glColor4f(lua_State* A_L)
{
	::glColor4f(lua_tonumber(A_L, 1), lua_tonumber(A_L, 2),
		lua_tonumber(A_L, 3), lua_tonumber(A_L, 4));
	return 0;
}

/*---------------------------------------------------------------------------
	2015/03/05 功能:   
---------------------------------------------------------------------------*/
int LuaLibOpenGL::Lua_glEnable(lua_State* A_L)
{
	::glEnable(GLenum(lua_tonumber(A_L, 1)));
	return 0;
}

/*---------------------------------------------------------------------------
	2015/03/05 功能:   
---------------------------------------------------------------------------*/
int LuaLibOpenGL::Lua_glDisable(lua_State* A_L)
{
	::glDisable(GLenum(lua_tonumber(A_L, 1)));
	return 0;
}