#include "stdafx.h"
#include "CoordinateSystem.h"

namespace
{
const int AXIS_WIDTH = 2;
const float DIVISION_STEP = 25.f;
const float DIVISION_WIDTH = 8.f;
const float DIVISION_HEIGHT = 4.f;
}

CCoordinateSystem::CCoordinateSystem(int wWidth, int wHeight) : m_wWidth(wWidth), m_wHeight(wHeight)
{
}

void CCoordinateSystem::Draw()
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glRecti(m_wWidth / 2, 0, m_wWidth / 2 + AXIS_WIDTH, m_wHeight);

	glRecti(0, m_wHeight / 2, m_wWidth, m_wHeight / 2 + AXIS_WIDTH);

	glm::vec2 position = { m_wWidth / 2.f, 0.f };
	while(position.y < m_wHeight)
	{
		glRectf(position.x - DIVISION_WIDTH / 2, position.y, position.x + DIVISION_WIDTH, position.y + DIVISION_HEIGHT);
		position.y += DIVISION_STEP;
	}

	position.x = 0;
	position.y = m_wHeight / 2.f;
	while (position.x < m_wWidth)
	{
		glRectf(position.x, position.y - DIVISION_WIDTH / 2, position.x + DIVISION_HEIGHT, position.y + DIVISION_WIDTH);
		position.x += DIVISION_STEP;
	}
}

