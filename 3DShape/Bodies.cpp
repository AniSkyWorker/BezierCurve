#include "stdafx.h"
#include "Bodies.h"
#include <stdint.h>

namespace
{
const unsigned POINTS_COUNT = 150000;
const float SCALE = 2;

template<typename T>
T GetMidPoint(const T & vec, const T & vec2)
{
	T result;
	for (int i = 0; i < vec.length(); i++)
	{
		result[i] = (vec[i] + vec2[i]) / 2.f;
	}

	return result;
}

const std::vector<glm::vec3> �_carpetVertices =
{
	{ 0.f, 1.f, 0.f },
	{ 0.f, -1.f, -1.f },
	{ -1.f, -1.f, 1.f },
	{ 1.f, -1.f, 1.f }
};

void GeneratePoints(std::vector<glm::vec3> & points)
{
	auto lastPoint = �_carpetVertices[0];

	for (int i = 0; i <= POINTS_COUNT; i++)
	{
		lastPoint = GetMidPoint(lastPoint, �_carpetVertices[rand() % 4]);
		points.push_back({ lastPoint.x * SCALE, lastPoint.y * SCALE, lastPoint.z * SCALE });
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
		float intensityY = (700 + point.y * 1000) / 500.f;
		float intensityX = (700 + point.x * 1000) / 500.f;
		float intensityZ = (700 + point.z * 1000) / 500.f;
		glColor3f(intensityX, intensityY, intensityZ);
		glVertex3f(point.x, point.y, point.z);
	}
	glEnd();
}
