#include "stdafx.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"

#include "Vector.h"
#include "Vertex.h"
#include "IntPoint.h"

#include "GameObject.h"
#include "Triangle.h"
#include "Texture.h"

bool IsInRange(int x, int y);
void PutPixel(int x, int y);
void DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
void DrawTriangle(const Vector3&p1, const Vector3& p2, const Vector3&p3);

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

void DrawLine(const Vector3& start, const Vector3& end, const Matrix3 &mat)
{

	//L = (1-t)P + tQ ,  0 <= t <= 1
	float length = Vector3::Dist(end, start);
	float inc = 1.0f / length;
	int nLength = (int)(length+1);
	for (int i = 0; i <= nLength; i++)
	{
		float t = inc*i;
		if (t >= length) t = 1.0f;
		Vector3 pt = start * (1.0f - t) + end *t;
		PutPixel(IntPoint(pt));
	}
}

void DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
	Vector2 minPos = Vector2(INFINITY, INFINITY);
	Vector2 maxPos = Vector2(-INFINITY, -INFINITY);

	Vector3 p1 = v1.position;
	Vector3 p2 = v2.position;
	Vector3 p3 = v3.position;

	if (p1.X < minPos.X) minPos.X = p1.X;
	if (p1.Y < minPos.Y) minPos.Y = p1.Y;
	if (p1.X > maxPos.X) maxPos.X = p1.X;
	if (p1.Y > maxPos.Y) maxPos.Y = p1.Y;

	if (p2.X < minPos.X) minPos.X = p2.X;
	if (p2.Y < minPos.Y) minPos.Y = p2.Y;
	if (p2.X > maxPos.X) maxPos.X = p2.X;
	if (p2.Y > maxPos.Y) maxPos.Y = p2.Y;

	if (p3.X < minPos.X) minPos.X = p3.X;
	if (p3.Y < minPos.Y) minPos.Y = p3.Y;
	if (p3.X > maxPos.X) maxPos.X = p3.X;
	if (p3.Y > maxPos.Y) maxPos.Y = p3.Y;

	Vector3 u = p2 - p1;
	Vector3 v = p3 - p1;
	float dotUU = Vector3::Dot(u, u);
	float dotUV = Vector3::Dot(u, v);
	float dotVV = Vector3::Dot(v, v);
	float invDenom = 1.0f / (dotUU * dotVV - dotUV * dotUV);

	IntPoint minPt(minPos);
	IntPoint maxPt(maxPos);

	for (int x = minPt.X; x < maxPt.X; x++)
	{
		for (int y = minPt.Y; y < maxPt.Y; y++)
		{
			IntPoint pt(x, y);
			Vector3 w = pt.ToVector3() - p1;
			float dotUW = Vector3::Dot(u, w);
			float dotVW = Vector3::Dot(v, w);
			float s = (dotVV * dotUW - dotUV * dotVW) * invDenom;
			float t = (dotUU * dotVW - dotUV * dotUW) * invDenom;
			if (s >= 0 && t >= 0 && ((s + t) <= 1))
			{
				BYTE RV1 = GetRValue(v1.color);
				BYTE RV2 = GetRValue(v2.color);
				BYTE RV3 = GetRValue(v3.color);

				BYTE GV1 = GetGValue(v1.color);
				BYTE GV2 = GetGValue(v2.color);
				BYTE GV3 = GetGValue(v3.color);

				BYTE BV1 = GetBValue(v1.color);
				BYTE BV2 = GetBValue(v2.color);
				BYTE BV3 = GetBValue(v3.color);

				BYTE FinalR = (BYTE)(RV1 * (1 - s - t) + RV2 * s + RV3 * t);
				BYTE FinalG = (BYTE)(GV1 * (1 - s - t) + GV2 * s + GV3 * t);
				BYTE FinalB = (BYTE)(BV1 * (1 - s - t) + BV2 * s + BV3 * t);

				SetColor(FinalR, FinalG, FinalB);
				PutPixel(pt);
			}
		}
	}
}

void DrawTriangle(const Vector3&p1, const Vector3& p2, const Vector3&p3)
{
	Vector2 minPos = Vector2(INFINITY, INFINITY);
	Vector2 maxPos = Vector2(-INFINITY, -INFINITY);


	if (p1.X < minPos.X) minPos.X = p1.X;
	if (p1.Y < minPos.Y) minPos.Y = p1.Y;
	if (p1.X > maxPos.X) maxPos.X = p1.X;
	if (p1.Y > maxPos.Y) maxPos.Y = p1.Y;

	if (p2.X < minPos.X) minPos.X = p2.X;
	if (p2.Y < minPos.Y) minPos.Y = p2.Y;
	if (p2.X > maxPos.X) maxPos.X = p2.X;
	if (p2.Y > maxPos.Y) maxPos.Y = p2.Y;

	if (p3.X < minPos.X) minPos.X = p3.X;
	if (p3.Y < minPos.Y) minPos.Y = p3.Y;
	if (p3.X > maxPos.X) maxPos.X = p3.X;
	if (p3.Y > maxPos.Y) maxPos.Y = p3.Y;

	Vector3 u = p2 - p1;
	Vector3 v = p3 - p1;
	float dotUU = Vector3::Dot(u, u);
	float dotUV = Vector3::Dot(u, v);
	float dotVV = Vector3::Dot(v, v);
	float invDenom = 1.0f / (dotUU * dotVV - dotUV * dotUV);

	IntPoint minPt(minPos);
	IntPoint maxPt(maxPos);

	for (int x = minPt.X; x < maxPt.X; x++)
	{
		for (int y = minPt.Y; y < maxPt.Y; y++)
		{
			IntPoint pt(x, y);
			Vector3 w = pt.ToVector3() - p1;
			float dotUW = Vector3::Dot(u, w);
			float dotVW = Vector3::Dot(v, w);
			float s = (dotVV * dotUW - dotUV * dotVW) * invDenom;
			float t = (dotUU * dotVW - dotUV * dotUW) * invDenom;
			if (s >= 0 && t >= 0 && ((s + t) <= 1))
			{
				PutPixel(pt);
			}
		}
	}
}


void DrawGameObject(Texture* texture, const GameObject2D& gameObj)
{
	for (int i = 0; i < gameObj.Mesh.Length; i++)
	{
		Vertex  vt[3];
		vt[0]= gameObj.Mesh.Triangles[i].vt[0];
		vt[0].position = vt[0].position* gameObj.Transform.TRS;
		vt[1]= gameObj.Mesh.Triangles[i].vt[1];
		vt[1].position = vt[1].position* gameObj.Transform.TRS;
		vt[2] = gameObj.Mesh.Triangles[i].vt[2];
		vt[2].position = vt[2].position* gameObj.Transform.TRS;

		Vector2 minPos = Vector2(INFINITY, INFINITY);
		Vector2 maxPos = Vector2(-INFINITY, -INFINITY);
		for (int j = 0; j < 3; j++)
		{
			float x = vt[j].position.X;
			float y = vt[j].position.Y;
			if (x < minPos.X) minPos.X = x;
			if (y< minPos.Y) minPos.Y = y;
			if (x > maxPos.X) maxPos.X = x;
			if (y> maxPos.Y) maxPos.Y = y;
		}

		Vector3 u = vt[1].position - vt[0].position;
		Vector3 v = vt[2].position - vt[0].position;
		float dotUU = Vector3::Dot(u, u);
		float dotUV = Vector3::Dot(u, v);
		float dotVV = Vector3::Dot(v, v);
		float invDenom = 1.0f / (dotUU * dotVV - dotUV * dotUV);

		IntPoint minPt(minPos);
		IntPoint maxPt(maxPos);

		for (int x = minPt.X; x < maxPt.X; x++)
		{
			for (int y = minPt.Y; y < maxPt.Y; y++)
			{
				IntPoint pt(x, y);
				Vector3 w = pt.ToVector3() - vt[0].position;
				float dotUW = Vector3::Dot(u, w);
				float dotVW = Vector3::Dot(v, w);
				float s = (dotVV * dotUW - dotUV * dotVW) * invDenom;
				float t = (dotUU * dotVW - dotUV * dotUW) * invDenom;
				if (s >= 0 && t >= 0 && ((s + t) <= 1))
				{
					ULONG fColor = RGB32(255, 0, 0);
					if (texture->IsLoaded()) {
						Vector2 baryUV = vt[0].uv * (1 - s - t) + vt[1].uv * s + vt[2].uv * t;
						fColor = texture->GetTexturePixel(baryUV);
					}
					else 
					{
						BYTE RV1 = GetRValue(vt[0].color);
						BYTE RV2 = GetRValue(vt[1].color);
						BYTE RV3 = GetRValue(vt[2].color);

						BYTE GV1 = GetGValue(vt[0].color);
						BYTE GV2 = GetGValue(vt[1].color);
						BYTE GV3 = GetGValue(vt[2].color);

						BYTE BV1 = GetBValue(vt[0].color);
						BYTE BV2 = GetBValue(vt[1].color);
						BYTE BV3 = GetBValue(vt[2].color);

						BYTE FinalR = (BYTE)(RV1 * (1 - s - t) + RV2 * s + RV3 * t);
						BYTE FinalG = (BYTE)(GV1 * (1 - s - t) + GV2 * s + GV3 * t);
						BYTE FinalB = (BYTE)(BV1 * (1 - s - t) + BV2 * s + BV3 * t);

						fColor = RGB32(FinalR, FinalG, FinalB);
					}
					SetColor(fColor);
					PutPixel(pt);
				}
			}
		}
	}
}

void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();
	
	static Vector2 center(0,200);
	static float angle = 0;
	static Vector2 scale(1,1);
	
	if (GetAsyncKeyState(VK_RIGHT)) center.X++;
	if (GetAsyncKeyState(VK_LEFT)) center.X--;

	if (GetAsyncKeyState(VK_LCONTROL)) angle--;

	if (GetAsyncKeyState(VK_PRIOR)) { scale.X += 0.01f; scale.Y += 0.01f; }
	if (GetAsyncKeyState(VK_NEXT)) { scale.X -= 0.01f; scale.Y -= 0.01f; }

	Transform2D trans(center, angle, scale);

	// head
	Vector3 p1 = Vector3::Make2DPoint(-60, -60);
	Vector3 p2 = Vector3::Make2DPoint(-60, 60);
	Vector3 p3 = Vector3::Make2DPoint(60, 60);
	Vector3 p4 = Vector3::Make2DPoint(60, -60);

	Vertex v1(p1,RGB32(255,0,0),Vector2(0.125f,0.25f));
	Vertex v2(p2,RGB32(0,0,0), Vector2(0.125f, 0.125f));
	Vertex v3(p3,RGB32(0,0,255), Vector2(0.25f, 0.125f));
	Vertex v4(p4,RGB32(0,0,0), Vector2(0.25f, 0.25f));

	// body
	Vector3 p5 = Vector3::Make2DPoint(-60, -250);
	Vector3 p6 = Vector3::Make2DPoint(-60, -60);
	Vector3 p7 = Vector3::Make2DPoint(60, -60);
	Vector3 p8 = Vector3::Make2DPoint(60, -250);

	Vertex v5(p5, RGB32(255, 0, 0), Vector2(0.3125f, 0.5f));
	Vertex v6(p6, RGB32(0, 0, 0), Vector2(0.3125f, 0.3125f));
	Vertex v7(p7, RGB32(0, 0, 255), Vector2(0.4375f, 0.3125f));
	Vertex v8(p8, RGB32(0, 0, 0), Vector2(0.4375f, 0.5f));

	// left aram
	Vector3 p9 = Vector3::Make2DPoint(60, -250);
	Vector3 p10 = Vector3::Make2DPoint(60, -60);
	Vector3 p11 = Vector3::Make2DPoint(120, -60);
	Vector3 p12 = Vector3::Make2DPoint(120, -250);

	Vertex v9(p9, RGB32(255, 0, 0), Vector2(0.5625f, 1.0f));
	Vertex v10(p10, RGB32(0, 0, 0), Vector2(0.5625f, 0.8125f));
	Vertex v11(p11, RGB32(0, 0, 255), Vector2(0.625f, 0.8125f));
	Vertex v12(p12, RGB32(0, 0, 0), Vector2(0.625f, 1.0f));

	// right aram
	Vector3 p13 = Vector3::Make2DPoint(-120, -250);
	Vector3 p14 = Vector3::Make2DPoint(-120, -60);
	Vector3 p15 = Vector3::Make2DPoint(-60, -60);
	Vector3 p16 = Vector3::Make2DPoint(-60, -250);

	Vertex v13(p13, RGB32(255, 0, 0), Vector2(0.6875f, 0.5f));
	Vertex v14(p14, RGB32(0, 0, 0), Vector2(0.6875f, 0.3125f));
	Vertex v15(p15, RGB32(0, 0, 255), Vector2(0.75f, 0.3125f));
	Vertex v16(p16, RGB32(0, 0, 0), Vector2(0.75f, 0.5f));

	// left leg
	Vector3 p17 = Vector3::Make2DPoint(0, -450);
	Vector3 p18 = Vector3::Make2DPoint(0, -250);
	Vector3 p19 = Vector3::Make2DPoint(60, -250);
	Vector3 p20 = Vector3::Make2DPoint(60, -450);

	Vertex v17(p17, RGB32(255, 0, 0), Vector2(0.3125f, 1.0f));
	Vertex v18(p18, RGB32(0, 0, 0), Vector2(0.3125f, 0.8125f));
	Vertex v19(p19, RGB32(0, 0, 255), Vector2(0.375f, 0.8125f));
	Vertex v20(p20, RGB32(0, 0, 0), Vector2(0.375f, 1.0f));

	// right leg
	Vector3 p21 = Vector3::Make2DPoint(-60, -450);
	Vector3 p22 = Vector3::Make2DPoint(-60, -250);
	Vector3 p23 = Vector3::Make2DPoint(0, -250);
	Vector3 p24 = Vector3::Make2DPoint(0, -450);

	Vertex v21(p21, RGB32(255, 0, 0), Vector2(0.0625f, 0.5f));
	Vertex v22(p22, RGB32(0, 0, 0), Vector2(0.0625f, 0.3125f));
	Vertex v23(p23, RGB32(0, 0, 255), Vector2(0.125f, 0.3125f));
	Vertex v24(p24, RGB32(0, 0, 0), Vector2(0.125f, 0.5f));

	static Triangle tris[]
	{
		// HEAD
		Triangle(v1,v2,v3), Triangle(v1,v3,v4),

		// BODY
		Triangle(v5,v6,v7), Triangle(v5,v7,v8),

		// L ARAM
		Triangle(v9,v10,v11), Triangle(v9,v11,v12),

		// R ARAM
		Triangle(v13,v14,v15), Triangle(v13,v15,v16),

		// L LEG
		Triangle(v17,v18,v19), Triangle(v17,v19,v20),

		// R LEG
		Triangle(v21,v22,v23), Triangle(v21,v23,v24),
	};


	GameObject2D obj(trans,Mesh(tris,_countof(tris)));
	DrawGameObject(g_Texture, obj);

	// Buffer Swap 
	BufferSwap();
}