#pragma once
#include "DispatchEvent.h"
#include <vector>
#include "CoordinateSystem.h"
#include "BezierCurve.h"

namespace
{
	const int WINDOW_WIDTH = 600;
	const int WINDOW_HEIGTH = 600;
}

class CWindow : public CAbstractInputControlWindow
{
public:
    CWindow();

protected:
    // CAbstractWindow interface
    void OnUpdateWindow(float deltaSeconds) override;
    void OnDrawWindow(const glm::ivec2 &size) override;
    // IInputEventAcceptor interface
    void OnKeyDown(const SDL_KeyboardEvent &) override;

private:
    void SetupView();

    CCoordinateSystem m_system;
	CBezierCurve m_curve;
    glm::ivec2 m_windowSize;
};
