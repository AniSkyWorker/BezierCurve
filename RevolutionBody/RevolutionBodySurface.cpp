#include "stdafx.h"
#include "RevolutionBodySurface.h"

namespace
{
const float DOT_SIZE = 5.f;

glm::vec3 GetPosition(const Function3D &fn, float x, float z)
{
	return fn(x, z);
}

// вычисляет нормали численным методом,
// с помощью векторного произведения.
void CalculateNormals(std::vector<SVertexP3N> &vertices)
{
	for (size_t i = 0; i < vertices.size() - 2; i++)
	{
		vertices[i].normal = glm::normalize(glm::cross(vertices[i + 1].position, vertices[i + 2].position));
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

	// Выключаем режим vertex array и normal array.
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

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
}

void CRevolutionBodySurface::Tesselate(const glm::vec2 &rangeX, const glm::vec2 &rangeZ, float step)
{
	const unsigned columnCount = unsigned((rangeX.y - rangeX.x) / step);
	const unsigned rowCount = unsigned((rangeZ.y - rangeZ.x) / step);
	m_vertices.clear();
	m_vertices.reserve(columnCount * rowCount);

	// вычисляем позиции вершин.
	for (unsigned ci = 0; ci < columnCount; ++ci)
	{
		const float u = rangeX.x + step * float(ci);
		for (unsigned ri = 0; ri < rowCount; ++ri)
		{
			const float v = rangeZ.x + step * float(ri);
			m_vertices.push_back(SVertexP3N(m_fn(u, v)));
		}
	}
	CalculateTriangleStripIndicies(m_indicies, columnCount, rowCount);
	CalculateNormals( m_vertices);
}

void CRevolutionBodySurface::Draw() const
{
	glColor3f(1.f, 1.f, 0.f);
	glFrontFace(GL_CW);
	DoWithBindedArrays(m_vertices, [&] {
		glDrawElements(GL_TRIANGLE_STRIP, GLsizei(m_indicies.size()),
			GL_UNSIGNED_INT, m_indicies.data());
	});
	glFrontFace(GL_CCW);

	DoWithBindedArrays(m_vertices, [&] {
		glDrawElements(GL_TRIANGLE_STRIP, GLsizei(m_indicies.size()),
			GL_UNSIGNED_INT, m_indicies.data());
	});
}