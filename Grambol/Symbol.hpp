//////////////////////////////////////////////////////////////////////////////
//
// Grambol (https://github.com/Hapaxia/Grambol)
// --
//
// Symbol
//
// Copyright(c) 2020-2023 M.J.Silk
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions :
//
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software.If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
// M.J.Silk
// MJSilk2@gmail.com
//
//////////////////////////////////////////////////////////////////////////////

#ifndef GRAMBOL_SYMBOL_HPP
#define GRAMBOL_SYMBOL_HPP

#include <exception>
#include <string>
#include <vector>
#include <cmath>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

namespace grambol
{
namespace constants
{

	constexpr float pi{ 3.141592653589f };
	constexpr float radiansFromDegreesMultiplier{ pi / 180.f };
	constexpr float degreesFromRadiansMultiplier{ 180.f / pi };

} // namespace constants

template <class T> T abs(const T& value) { return (value < 0) ? -value : value; }

class Symbol : public sf::Drawable, public sf::Transformable
{
public:
	Symbol(sf::PrimitiveType primitiveType = sf::PrimitiveType::Triangles) : m_primitiveType{ primitiveType } { }
	virtual ~Symbol() { }

	void setSize(sf::Vector2f size);
	sf::Vector2f getSize() const;

protected:
	virtual std::size_t priv_getNumberOfVertices() const = 0;
	virtual sf::Vertex priv_getVertex(std::size_t vertexIndex) const = 0;
	void priv_update();

private:
	const sf::PrimitiveType m_primitiveType;
	std::vector<sf::Vertex> m_vertices;
	sf::Vector2f m_size;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

inline void Symbol::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = nullptr;
	target.draw(m_vertices.data(), m_vertices.size(), m_primitiveType, states);
}

inline void Symbol::priv_update()
{
	m_vertices.resize(priv_getNumberOfVertices());
	for (auto begin{ m_vertices.begin() }, end{ m_vertices.end() }, it{ begin }; it != end; ++it)
	{
		const std::size_t vertexIndex{ static_cast<std::size_t>(it - begin) };
		*it = priv_getVertex(vertexIndex);
		it->position.x = it->position.x * m_size.x;
		it->position.y = it->position.y * m_size.y;
	}
}

inline void Symbol::setSize(const sf::Vector2f size)
{
	m_size = size;
	priv_update();
}

inline sf::Vector2f Symbol::getSize() const
{
	return m_size;
}

} // namespace grambol

#ifndef GRAMBOL_NO_NAMESPACE_SHORTCUT
namespace gr = grambol; // create shortcut namespace
#endif // GRAMBOL_NO_NAMESPACE_SHORTCUT

#endif // GRAMBOL_SYMBOL_HPP
