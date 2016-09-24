#pragma once

class CCoordinateSystem : private boost::noncopyable
{
public:
	CCoordinateSystem(int wWidth, int wHeight);
	void Draw();

private:
	int m_wWidth;
	int m_wHeight;
};

