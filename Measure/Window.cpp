#include "stdafx.h"
#include "Window.h"
#include "Colors.h"


CWindow::CWindow()
	: m_measure(WINDOW_WIDTH, WINDOW_HEIGTH)
{
    SetBackgroundColor(color::WHITE);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
    m_windowSize = size;
    SetupView();
	m_measure.Draw();
}

void CWindow::OnKeyDown(const SDL_KeyboardEvent &event)
{
}

void CWindow::SetupView()
{
    const glm::mat4 matrix = glm::ortho<float>(0, float(WINDOW_WIDTH), float(WINDOW_HEIGTH), 0);
    glViewport(0, 0, m_windowSize.x, m_windowSize.y);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(matrix));
    glMatrixMode(GL_MODELVIEW);
}
