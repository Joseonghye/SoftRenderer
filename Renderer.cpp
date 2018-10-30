
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

void PutPixel(int x, int y)
{
	if (!IsInRange(x, y)) return;

	ULONG* dest = (ULONG*)g_pBits;
	DWORD offset = g_nClientWidth * g_nClientHeight / 2 + g_nClientWidth / 2 + x + g_nClientWidth * -y;
	*(dest + offset) = g_CurrentColor;
}
void PutPixel(const IntPoint& point)
{
	PutPixel(point.X, point.Y);
}

void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();

	// Draw
	SetColor(255, 0, 0);
	
	//Draw a circle with radius 100
	Vector2 center(0.0f, 0.0f);
	float radius = 100.0f;
	int nradius = (int)radius;

	Vector2 startVec(radius, 0.0f);

	static float degree = 0; 
	degree += 0.1f;
	degree = fmodf(degree, 360.0f);

	Matrix2 rotMat;
	rotMat.SetRotation(degree);

	for (int i = -nradius; i <= nradius; i++) {
		for (int j = -nradius; j <= nradius; j++)
		{
			IntPoint p(i, j);
			PutPixel(p.ToVector2() * rotMat);
		}
	}


	//// Draw circle Line
	//for (int i = 0; i < 360; i++) 
	//{
	//	Matrix2 rotMat;
	//	rotMat.SetRotation((float)i);
	//	PutPixel(startVec * rotMat);
	//}

	/*Matrix2 scaleMat;
	scaleMat.SetScale(2.0f, 0.5f);

	Matrix2 rotMat;
	rotMat.SetRotation(30.0f);

	Matrix2 SRMat = scaleMat * rotMat;
	Matrix2 RSMat = rotMat * scaleMat;

	for (int i = -nradius; i <= nradius; i++) {
		for (int j = 0; j <= nradius; j++) 
		{
			IntPoint p(i, j);
			Vector2 v = p.ToVector2();
		
			if (Vector2::Dist(center, v) <= radius*radius) 
			{
			//	PutPixel(p);
				
				// Scale
			//	IntPoint scaledPt(v * scaleMat);
			//	PutPixel(scaledPt);

				// Rotation
			//	IntPoint rotPt(scaledPt.ToVector2() * rotMat);
			//	PutPixel(rotPt);


				// 행렬 곱은 순서를 역순으로 가야함
			//	IntPoint result(v * SRMat);
				IntPoint result(v * RSMat);
				PutPixel(result);
			}
		}
	}

	*/

	// Buffer Swap 
	BufferSwap();
}
