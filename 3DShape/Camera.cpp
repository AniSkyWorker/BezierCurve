#include "stdafx.h"
#include "Camera.h"
#include <glm/gtx/rotate_vector.hpp>


namespace
{
const float ROTATION_SPEED_RADIANS = 1.f;
const float LINEAR_MOVE_SPEED = 5.f;
const float MIN_DISTANCE = 1.5f;
const float MAX_DISTANCE = 30.f;
const float ROTATION_SPEED_MOUSE_COEF = 300.f;

bool ShouldTrackKeyPressed(const SDL_Keysym &key)
{
    switch (key.sym)
    {
    case SDLK_LEFT:
    case SDLK_RIGHT:
    case SDLK_UP:
    case SDLK_DOWN:
    case SDLK_w:
    case SDLK_a:
    case SDLK_s:
    case SDLK_d:
        return true;
    }
    return false;
}

float GetRotationSpeedRadians(std::set<unsigned> & keysPressed)
{
    if (keysPressed.count(SDLK_RIGHT) || keysPressed.count(SDLK_d))
    {
        return ROTATION_SPEED_RADIANS;
    }
    if (keysPressed.count(SDLK_LEFT) || keysPressed.count(SDLK_a))
    {
        return -ROTATION_SPEED_RADIANS;
    }
    return 0;
}

float GetLinearMoveSpeed(std::set<unsigned> & keysPressed)
{
    if (keysPressed.count(SDLK_UP) || keysPressed.count(SDLK_w))
    {
        return -LINEAR_MOVE_SPEED;
    }
    if (keysPressed.count(SDLK_DOWN) || keysPressed.count(SDLK_s))
    {
        return +LINEAR_MOVE_SPEED;
    }
    return 0;
}
}


CCamera::CCamera(float rotationRadians, float distance)
    : m_rotationRadians(rotationRadians)
    , m_distance(distance)
{
}

void CCamera::Update(float deltaSec)
{
    m_rotationRadians.x += deltaSec * GetRotationSpeedRadians(m_keysPressed);
    m_distance += deltaSec * GetLinearMoveSpeed(m_keysPressed);
    m_distance = glm::clamp(m_distance, MIN_DISTANCE, MAX_DISTANCE);
}

bool CCamera::OnKeyDown(const SDL_KeyboardEvent &event)
{
    if (ShouldTrackKeyPressed(event.keysym))
    {
        m_keysPressed.insert(unsigned(event.keysym.sym));
        return true;
    }
    return false;
}

bool CCamera::OnKeyUp(const SDL_KeyboardEvent &event)
{
    if (ShouldTrackKeyPressed(event.keysym))
    {
        m_keysPressed.erase(unsigned(event.keysym.sym));
        return true;
    }
    return false;
}

void CCamera::OnDragBegin(const glm::vec2 & pos)
{
	m_drag = true;
	m_startPos = pos;
}

void CCamera::OnDragMotion(const glm::vec2 & pos)
{
	if (m_drag)
	{
		glm::vec2 offset = m_startPos - pos;
		m_startPos = pos;
		m_rotationRadians.x += offset.x / ROTATION_SPEED_MOUSE_COEF;
		m_rotationRadians.y += offset.y / ROTATION_SPEED_MOUSE_COEF;
	}
}

void CCamera::OnDragEnd(const glm::vec2 & pos)
{
	m_drag = false;
}

glm::mat4 CCamera::GetViewTransform() const
{
    glm::vec3 direction = {-1.f, 0.f, 0.5f};
    // Нормализуем вектор (приводим к единичной длине),
    // см. http://glm.g-truc.net/0.9.3/api/a00199.html
	direction = glm::rotateZ(glm::normalize(direction), m_rotationRadians.x);
	direction = glm::rotateY(glm::normalize(direction), m_rotationRadians.y);

    const glm::vec3 eye = direction * m_distance;
    const glm::vec3 center = {0, 0, 0};
    const glm::vec3 up = {0, 0, 1};

    // Матрица моделирования-вида вычисляется функцией glm::lookAt.
    // Она даёт матрицу, действующую так, как будто камера смотрит
    // с позиции eye на точку center, а направление "вверх" камеры равно up.
    return glm::lookAt(eye, center, up);
}
