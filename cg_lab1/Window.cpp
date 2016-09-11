#include "stdafx.h"
#include "Window.h"
#include "BezierCurve.h"

namespace
{
const glm::vec4 BLACK = { 255, 0, 0, 1 };
const  glm::vec4 WHITE = { 255, 255, 255, 1 };
}

CWindow::CWindow()
	: m_system(WINDOW_WIDTH, WINDOW_HEIGTH)
	, m_curve(glm::fvec2(WINDOW_WIDTH / 2,  WINDOW_HEIGTH / 2)
		, glm::fvec2(WINDOW_WIDTH, WINDOW_HEIGTH / 4)
		, glm::fvec2(WINDOW_WIDTH / 2, WINDOW_HEIGTH / 1.25)
		, glm::fvec2(WINDOW_WIDTH / 1.55, WINDOW_HEIGTH / 4))
{
    SetBackgroundColor(WHITE);
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
	m_curve.Draw();
    m_system.Draw();
}

void CWindow::OnKeyDown(const SDL_KeyboardEvent &event)
{
    //switch (event.keysym.sym)
    //{
    ////case SDLK_LEFT:
    ////    m_system.SlowdownTime();
    ////    break;
    ////case SDLK_RIGHT:
    ////    m_system.SpeedupTime();
    ////    break;
    ////case SDLK_EQUALS:
    ////    m_system.ZoomIn();
    ////    SetupView();
    ////    break;
    ////case SDLK_MINUS:
    ////    m_system.ZoomOut();
    ////    SetupView();
    ////    break;
    //}
}

void CWindow::SetupView()
{
    const glm::mat4 matrix = glm::ortho<float>(0, float(WINDOW_WIDTH), float(WINDOW_HEIGTH), 0);
    glViewport(0, 0, m_windowSize.x, m_windowSize.y);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(matrix));
    glMatrixMode(GL_MODELVIEW);
}
