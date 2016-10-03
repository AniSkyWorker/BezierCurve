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

	void OnDragBegin(const glm::vec2 &pos) override;
	void OnDragMotion(const glm::vec2 &pos) override;
	void OnDragEnd(const glm::vec2 &pos) override;

private:
    void SetupView();

    CCoordinateSystem m_system;
	CBezierCurve m_curve;
    glm::ivec2 m_windowSize;
	std::unique_ptr<glm::vec2*> m_draggingPoint = nullptr;
	glm::vec2 m_dragOffset;
};
