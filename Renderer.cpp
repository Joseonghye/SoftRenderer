
#include "stdafx.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"

#include "Vector.h"
#include "IntPoint.h"

bool IsInRange(int x, int y);
void PutPixel(int x, int y);

bool IsInRange(int x, int y)
{
	return (abs(x) < (g_nClientWidth / 2)) && (abs(y) < (g_nClientHeight / 2));
}

void PutPixel(const IntPoint& InPt)
{
	PutPixel(InPt.X, InPt.Y);
}

void PutPixel(int x, int y)
{
	if (!IsInRange(x, y)) return;

	ULONG* dest = (ULONG*)g_pBits;
	DWORD offset = g_nClientWidth * g_nClientHeight / 2 + g_nClientWidth / 2 + x + g_nClientWidth * -y;
	*(dest + offset) = g_CurrentColor;
}

void DrawQuad(Vector3 center,int nradius, Matrix3 TRS)
{
	for (int i = -nradius+center.X ; i <= nradius + center.X; i++)
	{
		for (int j = -nradius+center.Y; j <= nradius+center.Y; j++)
		{
			PutPixel(Vector3((float)i, (float)j) * TRS);
		}
	}
}

void DrawCircle(Vector3 center, int nradius, Matrix3 TRS)
{
	for (int i = -nradius + center.X; i <= nradius + center.X; i++)
	{
		for (int j = -nradius + center.Y; j <= nradius + center.Y; j++)
		{
			Vector3 vec((float)i, (float)j);
			if(Vector3::DistSquared(center, vec)<= nradius*nradius)
			PutPixel(Vector3((float)i, (float)j) * TRS);
		}
	}
}

void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();

	// Draw



	// Draw a filled circle with radius 100
	Vector3 center(0.0f, 0.0f);
	float radius = 100.0f;
	int nradius = (int)radius;

	static float degree = 0;
	degree += 0.1f;
	degree = fmodf(degree, 360.0f);

	Matrix3 rotMat;
	rotMat.SetRotation(degree);
	rotMat.Transpose();

	float maxScale = 2;
    float scale = (sinf((Deg2Rad(degree*2))+1) *0.5)* maxScale;
	Matrix3 scaleMat;
	scaleMat.SetScale(scale, scale,0);

	float maxPos = 150;
	float pos = sinf(Deg2Rad(degree)) * maxPos;
	Matrix3 translationMat;
	translationMat.SetTranslation(pos, pos);

	Matrix3 SR = scaleMat * rotMat;
	Matrix3 TRS = translationMat * rotMat * scaleMat;

	
	static float g = 0;
	g++;
	g = fmodf(g, 225);
	SetColor(255, g, 0);
	DrawQuad(center,nradius, TRS);

	Matrix3 mat; 
	mat.SetTranslation(0, 0);

	static float de = 360.0f;
	de -= 0.2f;
	de = fmodf(de, 360);
	Matrix3 rotM; rotM.SetRotation(de);

	static float b = 255;
	b --;
	b = fmodf(b, 255);
	SetColor(0, g, b);
	center = Vector3(120, 120);
	DrawCircle(center, 10, TRS*mat*rotM);

	center = Vector3(140, 140);
	
	static float d = 0;
	d += 0.5f;
	d = fmodf(d, 360.0f);
	Matrix3 rot; rot.SetRotation(d);
	DrawQuad(center, 2, TRS * mat*rot);

	/*
	for (int i = -nradius; i <= nradius; i++)
	{
		for (int j = -nradius; j <= nradius; j++)
		{
			PutPixel(Vector3((float)i, (float)j) * TRS);
		}
	}
	*/
	// Buffer Swap 
	BufferSwap();
}
