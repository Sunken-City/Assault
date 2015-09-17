#include "Engine/Renderer/TheRenderer.hpp"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl/gl.h>
#include <math.h>
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/MathUtils.hpp"
#include "Engine/Renderer/AABB2.hpp"
#include "Engine/Renderer/RGBA.hpp"
#include "Engine/Renderer/Texture.hpp"
#pragma comment( lib, "opengl32" ) // Link in the OpenGL32.lib static library

TheRenderer* TheRenderer::instance = nullptr;

TheRenderer::TheRenderer()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
}

void TheRenderer::ClearScreen(float red, float green, float blue)
{
	glClearColor(red, green, blue, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void TheRenderer::ClearScreen(const RGBA& color)
{
	glClearColor(color.red, color.green, color.blue, color.alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}

void TheRenderer::SetOrtho(const Vector2& bottomLeft, const Vector2& topRight)
{
	glLoadIdentity();
	glOrtho(bottomLeft.x, topRight.x, bottomLeft.y, topRight.y, 0.f, 1.f);
}

void TheRenderer::DrawPoint(float x, float y)
{
	glBegin(GL_POINTS);
	{
		glVertex2f(x, y);
	}
	glEnd();
}

void TheRenderer::DrawPoint(const Vector2& point)
{
	DrawPoint(point.x, point.y);
}

void TheRenderer::DrawLine(const Vector2& start, const Vector2& end, float lineThickness)
{
	glLineWidth(lineThickness);
	glBegin(GL_LINES);
	{
		glVertex2f(start.x, start.y);
		glVertex2f(end.x, end.y);
	}
	glEnd();
}

void TheRenderer::DrawLines(Vector2* const* verts, int numVerts, float lineThickness)
{
	glLineWidth(lineThickness);
	glBegin(GL_LINES);
	{
		for (int i = 0; i < numVerts; i++)
		{
			glVertex2f(verts[i]->x, verts[i]->y);
		}
	}
	glEnd();
}

void TheRenderer::SetColor(float red, float green, float blue, float alpha)
{
	glColor4f(red, green, blue, alpha);
}

void TheRenderer::SetColor(const RGBA& color)
{
	glColor4f(color.red, color.green, color.blue, color.alpha);
}

void TheRenderer::SetPointSize(float size)
{
	glPointSize(size);
}

void TheRenderer::PushMatrix()
{
	glPushMatrix();
}

void TheRenderer::PopMatrix()
{
	glPopMatrix();
}

void TheRenderer::Translate(float x, float y, float z)
{
	glTranslatef(x, y, z);
}

void TheRenderer::Translate(const Vector2& xy)
{
	glTranslatef(xy.x, xy.y, 0.0f);
}

void TheRenderer::Rotate(float rotationDegrees)
{
	glRotatef(rotationDegrees, 0.f, 0.f, 1.f);
}

void TheRenderer::Rotate(float rotationDegrees, float x, float y, float z)
{
	glRotatef(rotationDegrees, x, y, z);
}

void TheRenderer::Scale(float x, float y, float z)
{
	glScalef(x, y, z);
}

void TheRenderer::DrawPolygonOutline(const Vector2& center, float radius, int numSides, float radianOffset)
{
	const float radiansTotal = 2.0f * MathUtils::pi;
	const float radiansPerSide = radiansTotal / numSides;

	glBegin(GL_LINE_LOOP);
	{
		for (float radians = 0.0f; radians < radiansTotal; radians += radiansPerSide)
		{
			float adjustedRadians = radians + radianOffset;
			float x = center.x + (radius * cos(adjustedRadians));
			float y = center.y + (radius * sin(adjustedRadians));
			glVertex2f(x, y);
		}
	}
	glEnd();

}

void TheRenderer::DrawPolygon(const Vector2& center, float radius, int numSides, float radianOffset)
{
	const float radiansTotal = 2.0f * MathUtils::pi;
	const float radiansPerSide = radiansTotal / numSides;

	glBegin(GL_POLYGON);
	{
		for (float radians = 0.0f; radians < radiansTotal; radians += radiansPerSide)
		{
			float adjustedRadians = radians + radianOffset;
			float x = center.x + (radius * cos(adjustedRadians));
			float y = center.y + (radius * sin(adjustedRadians));
			glVertex2f(x, y);
		}
	}
	glEnd();
}

void TheRenderer::DrawLineLoop(Vector2* const* verts, int numVerts, float lineThickness)
{
	glLineWidth(lineThickness);
	glBegin(GL_LINE_LOOP);
	{
		for (int i = 0; i < numVerts; i++)
		{
			glVertex2f(verts[i]->x, verts[i]->y);
		}
	}
	glEnd();
}

void TheRenderer::DrawAABB(const AABB2& bounds, const RGBA& color)
{
	SetColor(color);
	glBegin(GL_QUADS);
	{
		glVertex2f(bounds.mins.x, bounds.mins.y);
		glVertex2f(bounds.maxs.x, bounds.mins.y);
		glVertex2f(bounds.maxs.x, bounds.maxs.y);
		glVertex2f(bounds.mins.x, bounds.maxs.y);
	}
	glEnd();
}

void TheRenderer::DrawTexturedAABB(const AABB2& bounds, const Vector2& texCoordMins, const Vector2& texCoordMaxs, const Texture& texture, const RGBA& color)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.m_openglTextureID);

	SetColor(color);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(texCoordMins.x, texCoordMins.y);
		glVertex2f(bounds.mins.x, bounds.mins.y);
		glTexCoord2f(texCoordMaxs.x, texCoordMins.y);
		glVertex2f(bounds.maxs.x, bounds.mins.y);
		glTexCoord2f(texCoordMaxs.x, texCoordMaxs.y);
		glVertex2f(bounds.maxs.x, bounds.maxs.y);
		glTexCoord2f(texCoordMins.x, texCoordMaxs.y);
		glVertex2f(bounds.mins.x, bounds.maxs.y);
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

