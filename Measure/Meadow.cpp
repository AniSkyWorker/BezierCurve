#include "stdafx.h"
#include "Meadow.h"
#include "Colors.h"

using namespace glm;
using namespace color;

namespace
{

void FillEllipse(float xCenter, float yCenter, float rx, float ry, int pointCount = 360)
{
	const float step = float(2 * M_PI) / pointCount;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(xCenter, yCenter);
	for (float angle = 0; angle <= float(2 * M_PI); angle += step)
	{
		float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
		const float dx = rx * cosf(a);
		const float dy = ry * sinf(a);
		glVertex2f(dx + xCenter, dy + yCenter);
	}
	glEnd();
}

void FillCircle(float xCenter, float yCenter, float radius, int pointCount = 360)
{
	const float step = float(2 * M_PI) / pointCount;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(xCenter, yCenter);
	for (float angle = 0; angle <= float(2 * M_PI); angle += step)
	{
		float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
		const float dx = radius * cosf(a);
		const float dy = radius * sinf(a);
		glVertex2f(dx + xCenter, dy + yCenter);
	}
	glEnd();
}

void DrawCannabis(float xCenter, float yCenter, float r, float petalCount = 7.f, const vec4 & color = MIDLLE_GREEN)
{
	petalCount += 1;
	const float step = float(2 * M_PI) / float(petalCount * 2000);
	
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(color.r, color.g, color.b);

	for (float angle = 0; angle <= float(2 * M_PI) + 0.5f * step; angle += step)
	{
		float fixedAngle = (fabsf(angle - float(2 * M_PI)) < 1e-4f) ? 0 : angle - 80.f;
		float radius = 0.5f * r * cosf(angle * petalCount);
		float x = radius * cosf(fixedAngle);
		float y = radius * sinf(fixedAngle);
		glVertex2f(x + xCenter, y + yCenter);
	}

	glEnd();
}

void DrawFlower(float xCenter, float yCenter, float petalCount, float r = 1.f, const vec4 & cColor = RED, const vec4 & pColor = GREEN, const vec4 & lColor = YELLOW)
{
	glm::vec3 offset = { xCenter, yCenter, 0.f };
	glm::mat4 transform = glm::translate(glm::mat4(), offset);

	glPushMatrix();
	glLoadMatrixf(glm::value_ptr(transform));

	const float step = float(2 * M_PI) / float(petalCount * 20);

	glBegin(GL_LINE_STRIP);

	glColor3f(lColor.r, lColor.g, lColor.b);
	glVertex2f(0.f, 0.f);
	glVertex2f(0.f, 30.f);
	glEnd();

	DrawCannabis(0.f, 30.f, 20.f, 2.f, lColor);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(cColor.r, cColor.g, cColor.b);
	glVertex2f(0, 0);
	glColor3f(pColor.r, pColor.g, pColor.b);
	for (float angle = 0; angle <= float(2 * M_PI) + 0.5f * step; angle += step)
	{
		float fixedAngle = (fabsf(angle - float(2 * M_PI)) < 1e-4f) ? 0 : angle;

		float radius = 0.5f * r * (30.f - 10.f)
			* cosf(angle * petalCount - 1) + 10.f;
		float x = radius * cosf(fixedAngle);
		float y = radius * sinf(fixedAngle);

		glVertex2f(x, y);
	}

	glEnd();

	glColor3f(pColor.r, pColor.g, pColor.b);
	FillCircle(0.f, 0.f, r);

	glColor3f(cColor.r, cColor.g, cColor.b);
	FillCircle(0.f, 0.f, r / 2.f);

	glPopMatrix();
}

void DrawCloud(float xCenter, float yCenter, const glm::vec4 & color = WHITE)
{
	vec3 offset = { xCenter, yCenter, 0.f };
	mat4 transform = translate(mat4(), offset);

	glPushMatrix();
	glLoadMatrixf(glm::value_ptr(transform));

	float rx = 20.f;
	float ry = 10.f;
	float dimension = 3.f;

	glColor3f(color.r, color.g, color.b);
	FillEllipse(0.f, 0.f, rx,ry);
	FillEllipse(0.f, 1.5f * ry, rx + 5, ry + 5);
	FillEllipse(1.5f * rx, 0.f, rx + 2, ry + 2);
	FillEllipse(1.5f * rx, 1.5f * ry , rx, ry);

	glPopMatrix();
}

void DrawButterfly(float xCenter, float yCenter, float size = 16.f, const vec4 & color = QUIET_RED, const vec4 & bColor = BLACK, const vec4 & wColor = BLUE)
{
	vec3 offset = { xCenter, yCenter, 0.f };
	mat4 transform = translate(mat4(), offset);

	glPushMatrix();
	glLoadMatrixf(glm::value_ptr(transform));

	DrawCannabis(0.f, 0.f, size, 6.f, color);
	glColor3f(bColor.r, bColor.g, bColor.b);
	FillEllipse(0.f, 3.f, 1.f, size / 4.f);
	glColor3f(wColor.r, wColor.g, wColor.b);
	FillCircle(- size / 4.f, 0.f, size / 16.f);
	FillCircle(size / 4.f, size / 16.f, size / 16.f);
	FillCircle(size / 4.f - 1, size / 4.f + size / 16.f, size / 16.f);
	FillCircle(- size / 4.f, size / 4.f, size / 16.f);

	glPopMatrix();
}

void DrawRabbit(float xCenter, float yCenter, float bSize = 15.f, const vec4 & bColor = WHITE, const vec4 & eColor = RED)
{
	vec3 offset = { xCenter, yCenter, 0.f };
	mat4 transform = translate(mat4(), offset);

	glPushMatrix();
	glLoadMatrixf(glm::value_ptr(transform));

	glColor3f(bColor.r, bColor.g, bColor.b);
	FillEllipse(0.f, 0.f, bSize, bSize / 1.2f);
	FillCircle(bSize, bSize / 7.5f, bSize / 2.f);
	FillEllipse(bSize / 1.25f, -bSize / 1.875f, bSize / 10.f, bSize);
	FillEllipse(bSize, -bSize / 1.875f, bSize / 10.f, bSize / 1.2f);
	glColor3f(eColor.r, eColor.g, eColor.b);
	FillCircle(bSize * 1.2f, bSize / 7.5f, bSize / 8.5f);
	glColor3f(BLACK.r, BLACK.g, BLACK.b);
	FillEllipse(3.f * bSize / 2.f, bSize / 7.5f, bSize / 14.f, bSize / 12.f);

	glPopMatrix();
}

}

Meadow::Meadow(float wWidth, float wHeight) : m_wWidth(wWidth), m_wHeight(wHeight)
{
}

void Meadow::Draw()
{
	glColor3f(BLUE.r, BLUE.g, BLUE.b);
	glRectf(0.f, 0.f, m_wWidth, m_wHeight / 2.f);

	glColor3f(QUIET_GREEN.r, QUIET_GREEN.g, QUIET_GREEN.b);
	glRectf(0.f, m_wHeight / 2.f, m_wWidth, m_wHeight);

	glColor3f(1.f, 1.f, 0.f);
	FillCircle(100, 100, 50);

	DrawRabbit(m_wWidth * 0.577f, m_wHeight * 0.73f);
	DrawRabbit(m_wWidth * 0.37f, m_wHeight * 0.48f, 8.f);

	DrawCannabis(m_wWidth * 0.04f, m_wHeight * 0.5f, 50.f, 7.f, ORANGE);
	DrawCannabis(m_wWidth * 0.56f, m_wHeight * 0.7f, 50.f, 7.f, ORANGE);
	DrawCannabis(m_wWidth * 0.4f, m_wHeight, 50.f);
	DrawCannabis(m_wWidth * 0.93f, m_wHeight * 0.57f, 80.f);
	DrawCannabis(m_wWidth * 0.85f, m_wHeight * 0.47f, 20.f);
	DrawCannabis(m_wWidth * 0.46f, m_wHeight * 0.48f, 20.f);
	DrawCannabis(m_wWidth * 0.45f, m_wHeight * 0.47f, 25.f);
	DrawCannabis(m_wWidth * 0.3f, m_wHeight * 0.6f, 35.f);

	DrawFlower(m_wWidth * 0.48f, m_wHeight * 0.8f, 3.f);
	DrawFlower(m_wWidth * 0.17f, m_wHeight * 0.45f, 8.f);
	DrawFlower(m_wWidth * 0.68f, m_wHeight * 0.65f, 5.f);
	DrawFlower(m_wWidth * 0.8f, m_wHeight * 0.5f, 5.f, 1.f, YELLOW, QUIET_BLUE, GREEN);
	DrawFlower(m_wWidth * 0.2f, m_wHeight * 0.6f, 5.f, 1.f, YELLOW, QUIET_BLUE, GREEN);
	
	DrawCloud(m_wWidth * 0.25f, m_wHeight * 0.28f);
	DrawCloud(m_wWidth * 0.08f, m_wHeight * 0.125f);
	DrawCloud(m_wWidth * 0.533f, m_wHeight * 0.03);
	DrawCloud(m_wWidth * 0.833f, m_wHeight * 0.125f);

	DrawButterfly(m_wWidth * 0.5f, m_wHeight * 0.8f);
	DrawButterfly(m_wWidth * 0.18f, m_wHeight * 0.42f, 13.f, BLUE, GREEN, WHITE);
	DrawButterfly(m_wWidth * 0.14f, m_wHeight * 0.53f, 13.f, BLUE, GREEN, WHITE);
	DrawButterfly(m_wWidth * 0.75f, m_wHeight * 0.5f, 20.f, ORANGE, BLACK, RED);

	DrawCannabis(0.f, m_wHeight, 300.f, 200.f, QUIET_YELLOW);
	DrawCannabis(m_wWidth, m_wHeight, 300.f, 200.f, QUIET_YELLOW);
}

