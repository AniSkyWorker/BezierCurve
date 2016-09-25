#pragma once
#include "DispatchEvent.h"
#include <vector>
#include "Meadow.h"

namespace
{
	const float WINDOW_WIDTH = 600;
	const float WINDOW_HEIGTH = 320;
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

	Meadow m_measure;
    glm::ivec2 m_windowSize;
};
