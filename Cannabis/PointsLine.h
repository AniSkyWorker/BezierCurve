#pragma once

#include <functional>
#include <vector>
#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

// Вершина с трёхмерной позицией и нормалью.
struct SVertexP3N
{
    glm::vec3 position;
    glm::vec3 normal;
};

// Класс поверхности "Зонтик Уитни"
// https://en.wikipedia.org/wiki/Whitney_umbrella
class CPointsLine
{
public:
	CPointsLine(float length, size_t amountVertex);

    void Draw()const;

private:
    void Tesselate(float length, size_t amountVertex);

    std::vector<SVertexP3N> m_vertices;
    std::vector<uint32_t> m_indicies;
};
