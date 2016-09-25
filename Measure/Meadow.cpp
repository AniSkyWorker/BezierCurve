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

		float radius = 0.5f * r * (30 - 10)
			* cosf(angle * petalCount - 1) + 10;
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
	float rx = 20.f;
	float ry = 10.f;
	float dimension = 3.f;

	glColor3f(color.r, color.g, color.b);
	FillEllipse(xCenter,yCenter, rx,ry);
	FillEllipse(xCenter, yCenter +1.5f * ry, rx + 5, ry + 5);
	FillEllipse(xCenter + 1.5f * rx, yCenter, rx + 2, ry + 2);
	FillEllipse(xCenter + 1.5f * rx, yCenter + 1.5f * ry , rx, ry);
}

}

Meadow::Meadow(int wWidth, int wHeight) : m_wWidth(wWidth), m_wHeight(wHeight)
{
}

void Meadow::Draw()
{
	glColor3f(0.f, 0.f, 1.f);
	glRecti(0, 0, m_wWidth, m_wHeight / 2);

	glColor3f(QUIET_GREEN.r, QUIET_GREEN.g, QUIET_GREEN.b);
	glRecti(0, m_wHeight / 2, m_wWidth, m_wHeight);

	glColor3f(1.f, 1.f, 0.f);
	FillCircle(100, 100, 50);

	DrawCannabis(20.f, 180.f, 50.f, 7.f, ORANGE);
	DrawCannabis(350.f, 220.f, 50.f, 7.f, ORANGE);
	DrawCannabis(200.f, 320.f, 50.f);
	DrawCannabis(560.f, 180.f, 80.f);
	DrawCannabis(500.f, 150.f, 20.f);
	DrawCannabis(300.f, 152.f, 20.f);
	DrawCannabis(290.f, 150.f, 25.f);
	DrawCannabis(m_wWidth * 0.4f, m_wHeight * 0.7f, 25.f, 6.f, QUIET_RED);
	DrawCannabis(m_wWidth * 0.25f, m_wHeight * 0.5f, 25.f, 6.f, QUIET_RED);
	DrawCannabis(m_wWidth * 0.3f, m_wHeight * 0.6f, 35.f);

	DrawFlower(300.f, 250.f, 3.f);
	DrawFlower(100.f, 150.f, 8.f);
	DrawFlower(400.f, 200.f, 5.f);
	DrawFlower(m_wWidth * 0.8f, m_wHeight * 0.5f, 5.f, 1.f, YELLOW, QUIET_BLUE, GREEN);
	DrawFlower(m_wWidth * 0.2f, m_wHeight * 0.6f, 5.f, 1.f, YELLOW, QUIET_BLUE, GREEN);
	
	DrawCloud(150, 90);
	DrawCloud(50, 40);
	DrawCloud(320, 10);
	DrawCloud(500, 40);

	DrawCannabis(0.f, m_wHeight, 300.f, 200.f, QUIET_YELLOW);
	DrawCannabis(m_wWidth, m_wHeight, 300.f, 200.f, QUIET_YELLOW);
}

