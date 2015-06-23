/*-----------------------------------------------------------------------------

	作者：郭宁 2015/03/02
	备注：
	审核：

-----------------------------------------------------------------------------*/
#if !defined(AFX_LUALIBOPENGL_H__D84BB67D_FC84_452F_A220_D5FC8549C2AD__INCLUDED_)
#define AFX_LUALIBOPENGL_H__D84BB67D_FC84_452F_A220_D5FC8549C2AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*===========================================================================

	功能:  脚本普通表注册器   2014/10/17

===========================================================================*/
class ScriptTableRegister
{
private:
	ConstCharPtr m_TableName;
	lua_State* m_LuaState;

public:
	ScriptTableRegister(lua_State* A_LuaState, ConstCharPtr A_TableName);

	void BeginRegistTable();

	void RegistFunc(ConstCharPtr A_FuncName, lua_CFunction A_Func);
	void RegistNumber(ConstCharPtr A_Name, lua_Number A_Num);
	void RegistString(ConstCharPtr A_Name, ConstCharPtr A_Value);

	void EndRegistTable();

};//end ScriptTableRegister

/*===========================================================================
	
	功能:     2015/03/02
	
===========================================================================*/
class LuaLibOpenGL
{
private:
	lua_State *m_L;
	void RegistTableGL();
	bool FuncCall(ConstCharPtr A_FuncName);

public:
	LuaLibOpenGL();
	virtual ~LuaLibOpenGL();

	void Initialize(lua_State* A_L);
	void Rend();

	// Tool functions
	static int Lua_auxWireSphere(lua_State* A_L);

	// Initialize functions
	static int Lua_glClear(lua_State* A_L);

	// Matrix functions
	static int Lua_glMatrixMode(lua_State* A_L);
	static int Lua_glPushMatrix(lua_State* A_L);
	static int Lua_glPopMatrix(lua_State* A_L);
	static int Lua_glLoadIdentity(lua_State* A_L);
	static int Lua_glTranslatef(lua_State* A_L);
	static int Lua_glRotatef(lua_State* A_L);

	// BeginMode
	static int Lua_glBegin(lua_State* A_L);
	static int Lua_glEnd(lua_State* A_L);
	static int Lua_glVertex3f(lua_State* A_L);
	static int Lua_glTexCoord2f(lua_State* A_L);
	static int Lua_glNormal3f(lua_State* A_L);
	static int Lua_glPointSize(lua_State* A_L);
	static int Lua_glLineWidth(lua_State* A_L);

	// Color
	static int Lua_glColor3f(lua_State* A_L);
	static int Lua_glColor4f(lua_State* A_L);

	// Enable/Disable
	static int Lua_glEnable(lua_State* A_L);
	static int Lua_glDisable(lua_State* A_L);

};//end LuaLibOpenGL

#endif // !defined(AFX_LUALIBOPENGL_H__D84BB67D_FC84_452F_A220_D5FC8549C2AD__INCLUDED_)
