#pragma once


#ifndef _WIN32_WINNT            
#define _WIN32_WINNT 0x0500     
#define NDEBUG
#endif
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NON_CONFORMING_SWPRINTFS 
#define _CRT_NONSTDC_NO_DEPRECATE

#include < Windows.h >
#include < Iostream >
#include < Assert.h >
#include < Fstream >
#include < Vector >
#include < Stdio.h >
#include < D3DX9.h >
//#include < DDraw.h >
#include < String >
#include < D3D9.h >
#include < Time.h >
#include < List >
#include < Map >
#include < math.h>
#include <process.h>
#include <tlhelp32.h>

#include <Psapi.h>
#pragma comment( lib, "psapi.lib" )

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )
//#pragma comment( lib, "ddraw.lib" )
#pragma comment( lib, "dxguid.lib" )

#include "foundation/PxVec3.h" 
#include "foundation/PxTransform.h" 
#include "PxScene.h" 
#include "PxSceneQueryReport.h" 
#include "PxShape.h"

#include "MinHook/buffer.h"
#include "MinHook/minhook.h"

#include < algorithm >
#include "Xor.h"
#include "detours.h"
#include "ABytes.h"
#include "imgui/defs.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imconfig.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_memory_editor.h"

#include "detours.h"
#pragma comment( lib, "detours.lib" )
using namespace std;






class Color
{
public:
	Color()
	{
		*((int*)this) = 0;
	}
	Color(int color32)
	{
		*((int*)this) = color32;
	}
	Color(int _r, int _g, int _b)
	{
		SetColor(_r, _g, _b, 255);
	}
	Color(int _r, int _g, int _b, int _a)
	{
		SetColor(_r, _g, _b, _a);
	}

	void SetColor(int _r, int _g, int _b, int _a = 255)
	{
		_color[0] = (unsigned char)_r;
		_color[1] = (unsigned char)_g;
		_color[2] = (unsigned char)_b;
		_color[3] = (unsigned char)_a;
	}

	void GetColor(int& _r, int& _g, int& _b, int& _a) const
	{
		_r = _color[0];
		_g = _color[1];
		_b = _color[2];
		_a = _color[3];
	}

	void SetRawColor(int color32)
	{
		*((int*)this) = color32;
	}

	int GetRawColor() const
	{
		return *((int*)this);
	}

	int GetD3DColor() const
	{
		return ((int)((((_color[3]) & 0xff) << 24) | (((_color[0]) & 0xff) << 16) | (((_color[1]) & 0xff) << 8) | ((_color[2]) & 0xff)));
	}

	inline int r() const { return _color[0]; }
	inline int g() const { return _color[1]; }
	inline int b() const { return _color[2]; }
	inline int a() const { return _color[3]; }

	unsigned char& operator[](int index)
	{
		return _color[index];
	}

	const unsigned char& operator[](int index) const
	{
		return _color[index];
	}

	bool operator == (const Color& rhs) const
	{
		return (*((int*)this) == *((int*)& rhs));
	}

	bool operator != (const Color& rhs) const
	{
		return !(operator==(rhs));
	}

	Color& operator=(const Color& rhs)
	{
		SetRawColor(rhs.GetRawColor());
		return *this;
	}

	float* Base()
	{
		float clr[3];

		clr[0] = _color[0] / 255.0f;
		clr[1] = _color[1] / 255.0f;
		clr[2] = _color[2] / 255.0f;

		return &clr[0];
	}

	float* BaseAlpha()
	{
		float clr[4];

		clr[0] = _color[0] / 255.0f;
		clr[1] = _color[1] / 255.0f;
		clr[2] = _color[2] / 255.0f;
		clr[3] = _color[3] / 255.0f;

		return &clr[0];
	}

	float Hue() const
	{
		if (_color[0] == _color[1] && _color[1] == _color[2])
		{
			return 0.0f;
		}

		float r = _color[0] / 255.0f;
		float g = _color[1] / 255.0f;
		float b = _color[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		float delta = max - min;
		float hue = 0.0f;

		if (r == max)
		{
			hue = (g - b) / delta;
		}
		else if (g == max)
		{
			hue = 2 + (b - r) / delta;
		}
		else if (b == max)
		{
			hue = 4 + (r - g) / delta;
		}
		hue *= 60;

		if (hue < 0.0f)
		{
			hue += 360.0f;
		}
		return hue;
	}

	ImU32 GetU32()
	{
		return ((_color[3] & 0xff) << 24) + ((_color[2] & 0xff) << 16) + ((_color[1] & 0xff) << 8)
			+ (_color[0] & 0xff);
		//return (ImU32)(((_color[3] & 0xff) << 24) + ((_color[0] & 0xff) << 16) + ((_color[1] & 0xff) << 8) + (_color[2] & 0xff));
	}

	float Saturation() const
	{
		float r = _color[0] / 255.0f;
		float g = _color[1] / 255.0f;
		float b = _color[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		float l, s = 0;

		if (max != min)
		{
			l = (max + min) / 2;
			if (l <= 0.5f)
				s = (max - min) / (max + min);
			else
				s = (max - min) / (2 - max - min);
		}
		return s;
	}

	float Brightness() const
	{
		float r = _color[0] / 255.0f;
		float g = _color[1] / 255.0f;
		float b = _color[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		return (max + min) / 2;
	}

	Color FromHSB(float hue, float saturation, float brightness)
	{
		float h = hue == 1.0f ? 0 : hue * 6.0f;
		float f = h - (int)h;
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));

		if (h < 1)
		{
			return Color(
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255),
				(unsigned char)(p * 255)
			);
		}
		else if (h < 2)
		{
			return Color(
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255)
			);
		}
		else if (h < 3)
		{
			return Color(
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255)
			);
		}
		else if (h < 4)
		{
			return Color(
				(unsigned char)(p * 255),
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255)
			);
		}
		else if (h < 5)
		{
			return Color(
				(unsigned char)(t * 255),
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255)
			);
		}
		else
		{
			return Color(
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255),
				(unsigned char)(q * 255)
			);
		}
	}
private:
	unsigned char _color[4];
};
#define VALID( x ) ( x != NULL && HIWORD( x ) )

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

#define Transparent				D3DCOLOR_ARGB(0, 0, 0, 0)
#define Red						D3DCOLOR_ARGB(255,255,0,0)
#define TRed					D3DCOLOR_ARGB(255,255,0,0)
#define DarkRed					D3DCOLOR_ARGB(255, 200, 0, 0)
#define Green					D3DCOLOR_ARGB(255, 0, 255, 97)
#define TGreen					D3DCOLOR_ARGB(255, 0, 255, 97)
#define Orange					D3DCOLOR_ARGB(255, 255, 150, 150)
#define Blue					D3DCOLOR_ARGB(255, 0, 90, 90)
#define Orange                  D3DCOLOR_ARGB(255, 252, 75, 0)
#define Yellow					D3DCOLOR_ARGB(255, 255, 255, 0)
#define TYellow					D3DCOLOR_ARGB(255, 255, 255, 0)
#define Black					D3DCOLOR_ARGB(255, 0, 0, 0)
#define TBlack					D3DCOLOR_ARGB(150, 0, 0, 0)
#define TTBlack					D3DCOLOR_ARGB(200, 0, 0, 0)
#define LBlack					D3DCOLOR_ARGB(255, 10, 10, 10)
#define Grey					D3DCOLOR_ARGB(255, 150, 150, 150)
#define LightGrey				D3DCOLOR_ARGB(255, 45, 45, 45)
#define DarkGrey				D3DCOLOR_ARGB(255, 15, 15, 15)
#define TDarkGrey				D3DCOLOR_ARGB(125, 15, 15, 15)
#define Gold					D3DCOLOR_ARGB(255, 255, 215, 0)
#define Pink					D3DCOLOR_ARGB(255, 252, 0, 201)
#define Purple					D3DCOLOR_ARGB(255, 92, 33, 255)
#define White					D3DCOLOR_ARGB(255, 255, 255, 255)
#define COL_WHITEA(a)           D3DCOLOR_ARGB(a,255,255,255)
#define Cyan					D3DCOLOR_ARGB(255, 0, 210, 252)
#define zombieWhite				D3DCOLOR_ARGB(255, 0, 128, 255)
#define Rainbow					D3DCOLOR_ARGB(rand() % 255,rand() % 255,rand() % 255,rand() % 255)
#define RadarGrey				D3DCOLOR_ARGB(150, 25, 25, 25)
#define HeliosWhite				D3DCOLOR_ARGB(255, 200, 200, 200)

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>      // for printf
#include <string.h>     // for strnlen
#include <stdlib.h>     // for _countof, _itoa fns, _MAX_COUNT macros


#include "CTools.h"
#include "Menu.h"
#include "Classes.h"
#include "Engine.h"
#include "D3D.h"
#include "ESP.h"

