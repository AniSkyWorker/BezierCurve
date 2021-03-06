#pragma once
#include "DispatchEvent.h"
#include <vector>
#include "Meadow.h"

namespace
{
	const float WINDOW_WIDTH = 640.f;
	const float WINDOW_HEIGTH = 320.f;
}

class CWindow : public CAbstractInputControlWindow
{
public:
    CWindow();

protected:
    // CAbstractWindow interface
    void OnUpdateWindow(float deltaSeconds) override;
    void OnDrawWindow(const glm::ivec2 &size) override;

private:
    void SetupView();

	Meadow m_meadow;
    glm::ivec2 m_windowSize;
};
