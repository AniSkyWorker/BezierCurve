#include "stdafx.h"
#include "Window.h"

namespace
{
const glm::vec4 BLACK = { 0, 0, 0, 1 };
const  glm::vec4 WHITE = { 255, 255, 255, 1 };

template<typename T>
T GetMidPoint(T & vec, const T & vec2)
{
	for (size_t i = 0; i < vec.length(); i++)
	{
		vec[i] = (vec[i] + vec2[i]) / 2.f;
	}

	return vec;
}

void DrawStar()
{
	std::vector<glm::vec3> vertices = 
	{
		{ 250, 225, -500 },
		{ 350, 275, -200 },
		{ 750, 225, -225 },
		{ 500, 900, 0 }
	};

	auto lastPoint = vertices[0];

	glBegin(GL_POINTS);
	for (int i = 0; i <= 1000000; i++) 
	{
		lastPoint = GetMidPoint(lastPoint, vertices[rand() % 4]);
		float intensity = (700 + lastPoint.z) / 500.0;
		glColor3f(intensity, intensity, 0.25f);
		glVertex3f(lastPoint.x, lastPoint.y, lastPoint.z);
	}
	glEnd();
	glFlush();
}
}

CWindow::CWindow()
{
    SetBackgroundColor(BLACK);
    glEnable(GL_DEPTH_TEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
    m_windowSize = size;
    SetupView();
	DrawStar();
}

void CWindow::SetupView()
{
    const glm::mat4 matrix = glm::ortho<float>(0, float(WINDOW_WIDTH), float(WINDOW_HEIGTH), 0);
    glViewport(0, 0, m_windowSize.x, m_windowSize.y);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glLoadMatrixf(glm::value_ptr(matrix));
}

void CWindow::OnDragBegin(const glm::vec2 &pos)
{

}

void CWindow::OnDragMotion(const glm::vec2 &pos)
{
	if (m_draggingPoint != nullptr)
	{
		**m_draggingPoint = pos - m_dragOffset;
	}
}

void CWindow::OnDragEnd(const glm::vec2 &pos)
{
	if (m_draggingPoint != nullptr)
	{
		**m_draggingPoint = pos - m_dragOffset;
		m_draggingPoint = nullptr;
	}
}
