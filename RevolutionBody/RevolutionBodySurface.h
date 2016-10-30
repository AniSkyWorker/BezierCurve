#pragma once
#include "ISceneObject.h"
#include <functional>
#include <vector>
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>

using Function3D = std::function<glm::vec3(float, float)>;

// ¬ершина с трЄхмерной позицией и нормалью.
struct SVertexP3N
{
	glm::vec3 position;
	glm::vec3 normal;

	SVertexP3N() = default;
	SVertexP3N(const glm::vec3 &position)
		: position(position)
	{
	}
};

class CRevolutionBodySurface final : public ISceneObject
{
public:
	CRevolutionBodySurface(const Function3D &fn) : m_fn(fn) {};

	/// »нициализирует индексированную сетку треугольников
	/// @param rangeX - диапазон, где x - нижн€€ граница, y - верхн€€ граница
	/// @param rangeZ - диапазон, где x - нижн€€ граница, y - верхн€€ граница
	void Tesselate(const glm::vec2 &rangeX, const glm::vec2 &rangeZ, float step);

	// IBody interface.
	void Update(float) final {}
	void Draw() const final;

private:
	Function3D m_fn;
	std::vector<SVertexP3N> m_vertices;
	std::vector<uint32_t> m_indicies;
};