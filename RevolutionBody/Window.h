#pragma once
#include "DispatchEvent.h"
#include "Camera.h"
#include "Light.h"
#include "RevolutionBodySurface.h"


class CWindow : public CAbstractInputControlWindow
{
public:
	CWindow();

	// CAbstractWindow interface
protected:
	void OnWindowInit(const glm::ivec2 &size) override;
	void OnUpdateWindow(float deltaSeconds) override;
	void OnDrawWindow(const glm::ivec2 &size) override;

	// IInputEventAcceptor interface
	void OnDragBegin(const glm::vec2 &pos) override;
	void OnDragMotion(const glm::vec2 &pos) override;
	void OnDragEnd(const glm::vec2 &pos) override;
	void OnKeyDown(const SDL_KeyboardEvent &event);
	void OnKeyUp(const SDL_KeyboardEvent &event);

private:
	void SetupView(const glm::ivec2 &size);
	float m_time = 0.f;
	CPhongModelMaterial m_material;
	CRevolutionBodySurface m_surface;
	CCamera m_camera;
	CDirectedLightSource m_sunlight;
};