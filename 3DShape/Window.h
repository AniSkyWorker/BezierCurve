#pragma once
#include "DispatchEvent.h"
#include <vector>

namespace
{
	const int WINDOW_WIDTH = 1024;
	const int WINDOW_HEIGTH = 768;
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

    glm::ivec2 m_windowSize;
	std::unique_ptr<glm::vec2*> m_draggingPoint = nullptr;
	glm::vec2 m_dragOffset;
};
