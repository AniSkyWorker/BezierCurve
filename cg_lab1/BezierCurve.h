#pragma once

class CBezierCurve : private boost::noncopyable
{
public:
	CBezierCurve(glm::fvec2 startPoint, glm::fvec2 endPoint, glm::fvec2 fControlPoint, glm::fvec2 sControlPoint)
		: m_startPoint(startPoint)
		, m_fControlPoin(fControlPoint)
		, m_sControlPoint(sControlPoint)
		, m_endPoint(endPoint)
	{}
	void Draw();
private:
	glm::fvec2 GetPointOnCurve(glm::fvec2 p1, glm::fvec2 p2, glm::fvec2 p3, glm::fvec2 p4, float t) const;

	glm::fvec2 m_startPoint;
	glm::fvec2 m_fControlPoin;
	glm::fvec2 m_sControlPoint;
	glm::fvec2 m_endPoint;
};