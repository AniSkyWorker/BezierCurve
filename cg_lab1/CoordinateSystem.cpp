#include "stdafx.h"
#include "CoordinateSystem.h"

namespace
{
	const int AXIS_WIDTH = 2;
}

CCoordinateSystem::CCoordinateSystem(int wWidth, int wHeight) : m_wWidth(wWidth), m_wHeght(wHeight)
{
}

void CCoordinateSystem::Draw()
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glRecti(m_wWidth / 2, 0, m_wWidth / 2 + AXIS_WIDTH, m_wHeght);

	glRecti(0, m_wHeght / 2, m_wWidth, m_wHeght / 2 + AXIS_WIDTH);

	glm::vec2 position = { m_wWidth / 2, 0 };
	for (int i = 0; i < 24; i++)
	{
		glRectf(position.x, position.y, position.x + 8, position.y + 4);
		position.y += 25.f;
	}

	position.x = 0;
	position.y = m_wHeght / 2;
	for (int i = 0; i < 25; i++)
	{
		glRectf(position.x, position.y, position.x + 4, position.y + 8);
		position.x += 25.f;
	}
}

