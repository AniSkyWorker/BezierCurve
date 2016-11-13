#include "stdafx.h"
#include "PointsLine.h"
#include <algorithm>

namespace
{
const float MIN_LENGTH = 1.f;
const float UV_DELTA = 0.05f;
const float SHIFT_COEF = 0.25f;

void CalculateTriangleStripIndicies(std::vector<uint32_t> &indicies,
                                    unsigned columnCount, unsigned rowCount)
{
    indicies.clear();
    indicies.reserve((columnCount - 1) * rowCount * 2);
    // вычисляем индексы вершин.
    for (unsigned ci = 0; ci < columnCount - 1; ++ci)
    {
        if (ci % 2 == 0)
        {
            for (unsigned ri = 0; ri < rowCount; ++ri)
            {
                unsigned index = ci * rowCount + ri;
                indicies.push_back(index + rowCount);
                indicies.push_back(index);
            }
        }
        else
        {
            for (unsigned ri = rowCount - 1; ri < rowCount; --ri)
            {
                unsigned index = ci * rowCount + ri;
                indicies.push_back(index);
                indicies.push_back(index + rowCount);
            }
        }
    }
}

/// Привязывает вершины к состоянию OpenGL,
/// затем вызывает 'callback'.
template <class T>
void DoWithBindedArrays(const std::vector<SVertexP3N> &vertices, T && callback)
{
    // Включаем режим vertex array и normal array.
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    // Выполняем привязку vertex array и normal array
    const size_t stride = sizeof(SVertexP3N);
    glNormalPointer(GL_FLOAT, stride, glm::value_ptr(vertices[0].normal));
    glVertexPointer(3, GL_FLOAT, stride, glm::value_ptr(vertices[0].position));

    // Выполняем внешнюю функцию.
    callback();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

glm::vec3 GetSurfacePoint(float u, float v)
{
    // Приводим параметры из диапазона [0..1] к диапазону [-3..3]
    u = 6.f * (u - 0.5f);
    v = 6.f * (v - 0.5f);
    return { u * v, u, v * v };
}
}

CPointsLine::CPointsLine(float length, size_t amountVertex)
{
    Tesselate(length, amountVertex);
}

void CPointsLine::Draw() const
{
	DoWithBindedArrays(m_vertices, [this] {
		glDrawArrays(GL_POINTS, 0, GLsizei(m_vertices.size()));
	});
}

void CPointsLine::Tesselate(float length, size_t amountVertex)
{
	assert(length >= MIN_LENGTH);
    m_vertices.reserve(amountVertex);
    for (unsigned i = 0; i < amountVertex; ++i)
	{
		SVertexP3N vertex;
        vertex.position = { (-SHIFT_COEF * amountVertex + i) * length / amountVertex, -3.f, 0.f };
		m_vertices.push_back(vertex);
		m_indicies.push_back(i);
    }
}

