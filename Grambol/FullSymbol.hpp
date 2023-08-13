//////////////////////////////////////////////////////////////////////////////
//
// Grambol (https://github.com/Hapaxia/Grambol)
// --
//
// FullSymbol
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

#ifndef GRAMBOL_FULLSYMBOL_HPP
#define GRAMBOL_FULLSYMBOL_HPP

#include <initializer_list>

#include "Symbol.hpp"

namespace grambol
{

class FullSymbol : public Symbol
{
public:
	FullSymbol(sf::PrimitiveType primitiveType = sf::PrimitiveType::Triangles, std::size_t numberOfColors = 1u) : Symbol(primitiveType), m_colors(numberOfColors) { }
	FullSymbol(sf::PrimitiveType primitiveType, std::initializer_list<sf::Color> colors) : Symbol(primitiveType), m_colors{ colors } { }
	virtual ~FullSymbol() { }

	std::size_t getNumberOfColors() const;
	void setColor(std::size_t colorIndex, sf::Color color);
	sf::Color getColor(std::size_t colorIndex) const;
	void setColors(const std::vector<sf::Color>& colors);

protected:
	void setNumberOfColors(std::size_t numberOfColors);
	virtual std::size_t priv_getNumberOfVertices() const = 0;
	virtual sf::Vertex priv_getVertex(std::size_t vertexIndex) const = 0;











private:
	std::vector<sf::Color> m_colors;

	bool isValidColorIndex(std::size_t colorIndex) const;
};

inline bool FullSymbol::isValidColorIndex(std::size_t colorIndex) const
{
	return colorIndex < m_colors.size();
}

inline void FullSymbol::setNumberOfColors(std::size_t numberOfColors)
{
	m_colors.resize(numberOfColors);
}

inline std::size_t FullSymbol::getNumberOfColors() const
{
	return m_colors.size();
}

inline void FullSymbol::setColor(std::size_t colorIndex, sf::Color color)
{
	if (!isValidColorIndex(colorIndex))
		return;
	m_colors[colorIndex] = color;
	priv_update();
}

inline void FullSymbol::setColors(const std::vector<sf::Color>& colors)
{
	std::size_t index{ 0u };
	for (auto& color : colors)
		setColor(index++, color);
}

inline sf::Color FullSymbol::getColor(std::size_t colorIndex) const
{
	if (!isValidColorIndex(colorIndex))
		return sf::Color::Transparent;
	return m_colors[colorIndex];
}

} // namespace grambol
#endif // GRAMBOL_FULLSYMBOL_HPP
