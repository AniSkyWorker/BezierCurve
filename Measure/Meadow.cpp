#include "stdafx.h"
#include "Meadow.h"

namespace
{

const glm::vec3 LIGHT_YELLOW = { 1.f, 1.f, 0.5f};
const glm::vec3 RED = {1, 0, 0};
const glm::vec3 ORANGE = {1.f, 0.5f, 0.f};
const glm::vec3 YELLOW = {1.f, 1.f, 0.f};
const glm::vec4 QUIET_GREEN = {0.f, 0.5f, 0.2f, 1.f};

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

void DrawCannabis(float xCenter, float yCenter, float r)
{
	const float step = float(2 * M_PI) / float(8 * 20);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.f, 1.f, 0.f);

	for (float angle = 0; angle <= float(2 * M_PI) + 0.5f * step; angle += step)
	{
		float fixedAngle = (fabsf(angle - float(2 * M_PI)) < 1e-4f) ? 0 : angle - 80.f;
		float radius = 0.5f * (r)* cosf(angle * 8);
		float x = radius * cosf(fixedAngle);
		float y = radius * sinf(fixedAngle);
		glVertex2f(x + xCenter, y + yCenter);
	}
	
	glEnd();
}

void DrawFlower(float xCenter, float yCenter, float petalCount)
{
	glm::vec3 offset = { xCenter, yCenter, 0.f };
	glm::mat4 transform = glm::translate(glm::mat4(), offset);

	glPushMatrix();
	glLoadMatrixf(glm::value_ptr(transform));

	const float step = float(2 * M_PI) / float(petalCount * 20);
	glBegin(GL_LINE_STRIP);

	glColor3f(YELLOW.r, YELLOW.g, YELLOW.b);
	glVertex2f(0, 0);
	glVertex2f(0, 30);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(RED.r, RED.g, RED.b);
	glVertex2f(0, 0);
	glColor3f(0.f, 1.f, 0.f);
	for (float angle = 0; angle <= float(2 * M_PI) + 0.5f * step; angle += step)
	{
		float fixedAngle = (fabsf(angle - float(2 * M_PI)) < 1e-4f) ? 0 : angle;

		float radius = 0.5f * (30 - 10)
			* cosf(angle * petalCount) + 10;
		float x = radius * cosf(fixedAngle);
		float y = radius * sinf(fixedAngle);

		glVertex2f(x, y);
	}

	glEnd();

	glPopMatrix();
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

	DrawCannabis(20.f, 200.f, 50.f);
	DrawCannabis(350.f, 220.f, 50.f);
	DrawCannabis(200.f, 320.f, 50.f);
	DrawCannabis(450.f, 200.f, 100.f);

	DrawFlower(300.f, 250.f, 3.f);
	DrawFlower(100.f, 150.f, 8.f);
	DrawFlower(400.f, 200.f, 5.f);
}

