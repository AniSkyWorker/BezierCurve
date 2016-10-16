#include "stdafx.h"
#include "Bodies.h"
#include <stdint.h>

namespace
{

template<typename T>
T GetMidPoint(T & vec, const T & vec2)
{
	for (size_t i = 0; i < vec.length(); i++)
	{
		vec[i] = (vec[i] + vec2[i]) / 2.f;
	}

	return vec;
}

const std::vector<glm::vec3> ñ_carpetVertices =
{
	{ 0.f, 1.f, 0.f },
	{ 0.f, -1.f, -1.f },
	{ -1.f, -1.f, 1.f },
	{ 1.f, -1.f, 1.f }
};

void GeneratePoints(std::vector<glm::vec3> & points)
{
	auto lastPoint = ñ_carpetVertices[0];

	for (int i = 0; i <= 200000; i++)
	{
		lastPoint = GetMidPoint(lastPoint, ñ_carpetVertices[rand() % 4]);
		points.push_back({ lastPoint.x, lastPoint.y, lastPoint.z });
	}
}
}


void CIdentityCube::Update(float deltaTime)
{
    (void)deltaTime;
}

void CIdentityCube::Draw()
{
	if (m_points.size() == 0)
	{
		GeneratePoints(m_points);
	}

	glBegin(GL_POINTS);
	for (auto point : m_points)
	{
		float intensityY = (700 + point.y * 1000) / 500.0;
		float intensityX = (700 + point.x * 1000) / 500.0;
		float intensityZ = (700 + point.z * 1000) / 500.0;
		glColor3f(intensityX, intensityY, intensityZ);
		glVertex3f(point.x, point.y, point.z);
	}
	glEnd();
}
