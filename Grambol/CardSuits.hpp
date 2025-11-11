//////////////////////////////////////////////////////////////////////////////
//
// Grambol (https://github.com/Hapaxia/Grambol)
// --
//
// Card Suits
//
// Copyright(c) 2020-2025 M.J.Silk
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

#ifndef GRAMBOL_CARDSUITS_HPP
#define GRAMBOL_CARDSUITS_HPP

#include "PlainSymbol.hpp"

#include <cmath>

namespace grambol
{

namespace Selection
{

	enum class CardSuit
	{
		Heart,
		Spade,
		Diamond,
		Club,
	};

} // namespace Selection

template <Selection::CardSuit>
class CardSuit { CardSuit() = delete; };

template <>
class CardSuit<Selection::CardSuit::Diamond> : public PlainSymbol
{
public:
	CardSuit() : PlainSymbol(sf::PrimitiveType::TriangleFan) { }

private:
	virtual std::size_t priv_getNumberOfVertices() const final override { return 6u; }
	virtual sf::Vector2f priv_getVertexPosition(std::size_t vertexIndex) const final override;
};

template <>
class CardSuit<Selection::CardSuit::Heart> : public PlainSymbol
{
public:
	CardSuit() : PlainSymbol(sf::PrimitiveType::TriangleFan), m_numberOfEdges(72u) { }

	void setNumberOfEdges(std::size_t numberOfEdges) { m_numberOfEdges = (numberOfEdges < 4u) ? 3u : numberOfEdges; priv_update(); }
	std::size_t getNumberOfEdges() const { return m_numberOfEdges; }

private:
	std::size_t m_numberOfEdges;

	virtual std::size_t priv_getNumberOfVertices() const final override { return m_numberOfEdges + 2u; }
	virtual sf::Vector2f priv_getVertexPosition(std::size_t vertexIndex) const final override;
};

template <>
class CardSuit<Selection::CardSuit::Spade> : public PlainSymbol
{
public:
	CardSuit() : PlainSymbol(sf::PrimitiveType::TriangleFan), m_numberOfEdges(72u) { }

	void setNumberOfEdges(std::size_t numberOfEdges) { m_numberOfEdges = (numberOfEdges < 4u) ? 3u : numberOfEdges; priv_update(); }
	std::size_t getNumberOfEdges() const { return m_numberOfEdges; }

private:
	std::size_t m_numberOfEdges;

	virtual std::size_t priv_getNumberOfVertices() const final override { return m_numberOfEdges + 2u; }
	virtual sf::Vector2f priv_getVertexPosition(std::size_t vertexIndex) const final override;
};

template <>
class CardSuit<Selection::CardSuit::Club> : public PlainSymbol
{
public:
	CardSuit() : PlainSymbol(sf::PrimitiveType::TriangleFan), m_numberOfEdges(72u) { }

	void setNumberOfEdges(std::size_t numberOfEdges) { m_numberOfEdges = (numberOfEdges < 4u) ? 3u : numberOfEdges; priv_update(); }
	std::size_t getNumberOfEdges() const { return m_numberOfEdges; }

private:
	std::size_t m_numberOfEdges;

	virtual std::size_t priv_getNumberOfVertices() const final override { return m_numberOfEdges + 2u; }
	virtual sf::Vector2f priv_getVertexPosition(std::size_t vertexIndex) const final override;
};









inline sf::Vector2f CardSuit<Selection::CardSuit::Diamond>::priv_getVertexPosition(const std::size_t vertexIndex) const
{
	//const sf::Vector2f size{ getSize() };
	const sf::Vector2f center{ 0.5f, 0.5f };
	switch (vertexIndex)
	{
	case 1u:
	case 5u:
		return{ 1.f, center.y };
	case 2u:
		return{ center.x, 1.f };
	case 3u:
		return{ 0.f, center.y };
	case 4u:
		return{ center.x, 0.f };
	case 0u:
	default:
		return center;
	}
}

inline sf::Vector2f CardSuit<Selection::CardSuit::Heart>::priv_getVertexPosition(const std::size_t vertexIndex) const
{
	//const sf::Vector2f size{ getSize() };
	const sf::Vector2f center{ 0.5f, 0.5f };

	sf::Vector2f position;

	const float t{ static_cast<float>(vertexIndex) / priv_getNumberOfVertices() * 2.f * constants::pi };

	const float sine{ std::sin(t) };
	position.x = center.x * ((sine * sine * sine) + 1.f);
	position.y = -(13.f * std::cos(t) - 5.f * std::cos(2.f * t) - 2.f * std::cos(3.f * t) - std::cos(4.f * t));
	position.y += 11.9233f;
	//position.y *= size.y;
	position.y /= 28.9233f;

	return position;
}

inline sf::Vector2f CardSuit<Selection::CardSuit::Spade>::priv_getVertexPosition(const std::size_t vertexIndex) const
{
	//const sf::Vector2f size{ getSize() };
	const sf::Vector2f center{ 0.5f, 0.5f };
	const sf::Vector2f triangleFanCenter{ center.x, center.y + 0.15f };

	sf::Vector2f position;

	const std::size_t numberOfVertices{ priv_getNumberOfVertices() };
	const std::size_t halfVertexIndex{ (numberOfVertices + 1u) / 2u };
	const std::size_t baseIndexWidth{ 12u };
	const std::size_t baseIndexHalfWidth{ baseIndexWidth / 2u };

	if (vertexIndex == 0u)
		position = triangleFanCenter;
	else if (vertexIndex >= baseIndexHalfWidth && vertexIndex <= numberOfVertices - baseIndexHalfWidth)
	{
		const float t{ static_cast<float>(vertexIndex) / numberOfVertices * 2.f * constants::pi };

		const float sine{ std::sin(t) };
		position.x = center.x * ((sine * sine * sine) + 1.f);
		position.y = 13.f * std::cos(t) - 5.f * std::cos(2.f * t) - 2.f * std::cos(3.f * t) - std::cos(4.f * t);
		position.y += 17.f;
		position.y *= 0.8f;
		position.y /= 28.9233f;
	}
	else if ((vertexIndex == 1u) || (vertexIndex == numberOfVertices - 1u))
		position = { center.x, 1.f };
	else
	{
		const float baseHalfWidth{ 0.2f };
		if (vertexIndex < halfVertexIndex)
			position = { center.x + baseHalfWidth, 1.f };
		else
			position = { center.x - baseHalfWidth, 1.f };
	}

	return position;
}

inline sf::Vector2f CardSuit<Selection::CardSuit::Club>::priv_getVertexPosition(const std::size_t vertexIndex) const
{
	//const sf::Vector2f size{ getSize() };
	const sf::Vector2f center{ 0.5f, 0.5f };
	const sf::Vector2f triangleFanCenter{ center.x, center.y + 0.15f };

	sf::Vector2f position;

	const std::size_t numberOfVertices{ priv_getNumberOfVertices() };
	const std::size_t halfVertexIndex{ (numberOfVertices + 1u) / 2u };
	const std::size_t baseIndexWidth{ 12u };
	const std::size_t baseIndexHalfWidth{ baseIndexWidth / 2u };
	const std::size_t numberOfNonBaseVertices{ numberOfVertices - baseIndexWidth };
	const std::size_t numberOfVerticesPerLeaf{ numberOfNonBaseVertices / 3u };
	const std::size_t numberOfSpareVertices{ numberOfNonBaseVertices % 3u };
	const std::size_t numberOfLeaf{ (vertexIndex - baseIndexHalfWidth) / numberOfVerticesPerLeaf };

	if (vertexIndex == 0u)
		position = triangleFanCenter;
	else if ((vertexIndex == 1u) || (vertexIndex == numberOfVertices - 1u))
		position = { center.x, 1.f };
	else if (vertexIndex < baseIndexHalfWidth || vertexIndex > numberOfVertices - baseIndexHalfWidth)
	{
		const float baseHalfWidth{ 0.2f };
		if (vertexIndex < halfVertexIndex)
			position = { center.x + baseHalfWidth, 1.f };
		else
			position = { center.x - baseHalfWidth, 1.f };
	}
	else
	{
		const std::size_t leafStartIndex{ baseIndexHalfWidth + numberOfLeaf * numberOfVerticesPerLeaf };
		const std::size_t vertexIndexWithinLeaf{ vertexIndex - leafStartIndex };
		const float indexLeafRatio{ static_cast<float>(vertexIndexWithinLeaf) / (numberOfVerticesPerLeaf - 1u) };
		const float angle{ -indexLeafRatio * 2.f / 3.f }; // two thirds of a circle per leaf
		const float centredAngle{ angle + (1.f / 12.f) };
		float t;

		sf::Vector2f leafCenterOffsetFromCentre;
		bool isExtraVertex{ false };

		switch (numberOfLeaf)
		{
		case 0u:
			leafCenterOffsetFromCentre = { 0.2f, 0.125f };
			t = centredAngle + (1.f / 3.f);
			break;
		case 1u:
			leafCenterOffsetFromCentre = { 0.f, -0.225f };
			t = centredAngle;
			break;
		case 2u:
			leafCenterOffsetFromCentre = { -0.2f, 0.125f };
			t = centredAngle + (2.f / 3.f);
			break;
		case 3u:
		default:
			leafCenterOffsetFromCentre = { -0.2f, 0.125f };
			t = 1.f / 12.f;
		}

		t *= 2.f * constants::pi;

		position.x = center.x + leafCenterOffsetFromCentre.x + std::cos(t) * 0.225f;
		position.y = center.y + leafCenterOffsetFromCentre.y + std::sin(t) * 0.225f;
	}

	return position;
}

/*

centred (c) angle (a) is:
a + 1/12

*/

} // namespace grambol
#endif // GRAMBOL_CARDSUITS_HPP
