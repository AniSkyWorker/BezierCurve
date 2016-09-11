#include "stdafx.h"
#include "BezierCurve.h"
namespace
{
const float MAX_STEPS = 25.0f;
}

void CBezierCurve::Draw()
{
	glColor3f(0.f, 0.f, 0.f);
	glLineWidth(5.f);

	glBegin(GL_LINE_STRIP);

	for (float t = 0; t <= (1 + (1.0f / MAX_STEPS)); t += (1.0f / MAX_STEPS))
	{
		auto point = PointOnCurve(m_startPoint, m_endPoint, m_fControlPoin, m_sControlPoint, t);
		glVertex2f(point.x, point.y);
	}

	glEnd();

	glColor3f(255.f, 0.f, 0.f);
	glLineWidth(3.f);

	glBegin(GL_LINE_STRIP);

	glVertex2f(m_startPoint.x, m_startPoint.y);
	glVertex2f(m_fControlPoin.x, m_fControlPoin.y);
	glVertex2f(m_sControlPoint.x, m_sControlPoint.y);
	glVertex2f(m_endPoint.x, m_endPoint.y);

	glEnd();
}

glm::fvec2 CBezierCurve::PointOnCurve(glm::fvec2 p1, glm::fvec2 p2, glm::fvec2 p3, glm::fvec2 p4, float t)
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