// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__82D5D1A4_E385_4BCA_A7C0_ED3A374961A6__INCLUDED_)
#define AFX_STDAFX_H__82D5D1A4_E385_4BCA_A7C0_ED3A374961A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <stdio.h>

// TODO: reference additional headers your program requires here

#include <GTypes.hpp>

#ifdef __cplusplus
extern "C"{
#endif
	
#include <GScript\lua52\lua.h>
#include <GScript\lua52\lauxlib.h>
#include <GScript\lua52\lualib.h>
#pragma comment (lib, "lua52.lib")
	
#ifdef __cplusplus
}
#endif

#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>

#pragma comment(lib, "winmm.lib ") 

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__82D5D1A4_E385_4BCA_A7C0_ED3A374961A6__INCLUDED_)
