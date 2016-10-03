#include "stdafx.h"
#include "BezierCurve.h"

using namespace glm;

namespace
{
const float MAX_STEPS = 25.0f;

float GetRadiusByAngle(float angle)
{
	// вычисляем радиус искривленной окружности для данного угла.
	return 2.5f * cosf(angle * 1) + 5;
}
}

void CBezierCurve::Draw()
{
	glColor3f(0.f, 0.f, 0.f); //BLACK color
	glLineWidth(5.f);

	glBegin(GL_LINE_STRIP);
	
	for (float t = 0.f, delta = 1.0f / MAX_STEPS; t <= (1 + delta); t += delta)
	{
		auto point = GetPointOnCurve(m_startPoint, m_endPoint, m_fControlPoin, m_sControlPoint, t);
		glVertex2f(point.x, point.y);
	}

	glEnd();

	glColor3ub(255, 0, 0); // RED color
	glLineWidth(3.f);

	glBegin(GL_LINE_STRIP);

	glVertex2f(m_startPoint.x, m_startPoint.y);
	glVertex2f(m_fControlPoin.x, m_fControlPoin.y);
	glVertex2f(m_sControlPoint.x, m_sControlPoint.y);
	glVertex2f(m_endPoint.x, m_endPoint.y);

	glEnd();
}

void CBezierCurve::SetPosition(glm::vec2 & point, const glm::vec2 & position)
{
	point = position;
}

std::unique_ptr<glm::vec2*> CBezierCurve::HitTest(const glm::vec2 & point)
{
	glm::vec2 position = point - m_startPoint;
	float angle = std::atan2(point.y, point.x);
	float radius = GetRadiusByAngle(angle);
	if (glm::length(position) < radius)
	{
		return std::move(std::make_unique<glm::vec2*>(&m_startPoint));
	}

	position = point - m_fControlPoin;
	angle = std::atan2(point.y, point.x);
	radius = GetRadiusByAngle(angle);
	if (glm::length(position) < radius)
	{
		return std::move(std::make_unique<glm::vec2*>(&m_fControlPoin));
	}

	position = point - m_sControlPoint;
	angle = std::atan2(point.y, point.x);
	radius = GetRadiusByAngle(angle);
	if (glm::length(position) < radius)
	{
		return std::move(std::make_unique<glm::vec2*>(&m_sControlPoint));
	}

	position = point - m_endPoint;
	angle = std::atan2(point.y, point.x);
	radius = GetRadiusByAngle(angle);
	if (glm::length(position) < radius)
	{
		return std::move(std::make_unique<glm::vec2*>(&m_endPoint));
	}

	return nullptr;
}

fvec2 CBezierCurve::GetPointOnCurve(fvec2 p1, fvec2 p2, fvec2 p3, fvec2 p4, float t) const
{
	// B(t) = P1 * ( 1 - t )^3 + P4 * 3 * t * ( 1 - t )^2 + P3 * 3 * t^2 * ( 1 - t ) + P2 * t^3

	auto coef = 1 - t;

	auto a = pow(coef, 3);
	auto b = 3 * t * pow(coef, 2);
	auto c = 3 * coef * pow(t, 2);
	auto d = pow(t, 3);

	return { a *p1.x + b * p4.x + c * p3.x + d * p2.x
		, a * p1.y + b * p4.y + c * p3.y + d * p2.y };
}

