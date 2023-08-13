//////////////////////////////////////////////////////////////////////////////
//
// Grambol (https://github.com/Hapaxia/Grambol)
// --
//
// PlainSymbol
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

#ifndef GRAMBOL_PLAINSYMBOL_HPP
#define GRAMBOL_PLAINSYMBOL_HPP

#include "Symbol.hpp"

namespace grambol
{

class PlainSymbol : public Symbol
{
public:
	PlainSymbol(sf::PrimitiveType primitiveType = sf::PrimitiveType::Triangles) : Symbol(primitiveType), m_color{ sf::Color::Black } { }
	virtual ~PlainSymbol() { }

	void setColor(sf::Color color);
	sf::Color getColor() const;

protected:
	virtual std::size_t priv_getNumberOfVertices() const = 0;
	
	virtual sf::Vector2f priv_getVertexPosition(std::size_t vertexIndex) const = 0;











private:
	sf::Color m_color;

	virtual sf::Vertex priv_getVertex(std::size_t vertexIndex) const final override;
};

inline void PlainSymbol::setColor(const sf::Color color)
{
	m_color = color;
	priv_update();
}

inline sf::Color PlainSymbol::getColor() const
{
	return m_color;
}

inline sf::Vertex PlainSymbol::priv_getVertex(std::size_t vertexIndex) const
{
	sf::Vertex vertex;
	vertex.position = priv_getVertexPosition(vertexIndex);
	vertex.color = m_color;
	return vertex;
}

} // namespace grambol
#endif // GRAMBOL_PLAINSYMBOL_HPP
