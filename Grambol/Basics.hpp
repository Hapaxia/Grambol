//////////////////////////////////////////////////////////////////////////////
//
// Grambol (https://github.com/Hapaxia/Grambol)
// --
//
// Basics
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

#ifndef GRAMBOL_BASICS_HPP
#define GRAMBOL_BASICS_HPP

#include "PlainSymbol.hpp"

#include <cmath>

namespace grambol
{

namespace Selection
{

	enum class Basic
	{
		Rectangle,
		Frame,
		Ellipse,
		Star,
		RoundedRectangle,
		RoundedFrame,
		RegularPolygon,
		Parallelogram,
	};

} // namespace Selection

template <Selection::Basic>
class Basic { Basic() = delete; };

template <>
class Basic<Selection::Basic::Rectangle> : public PlainSymbol
{
public:
	Basic() : PlainSymbol(sf::PrimitiveType::TriangleStrip) { }

private:
	virtual std::size_t priv_getNumberOfVertices() const final override { return 4u; }
	virtual sf::Vector2f priv_getVertexPosition(std::size_t vertexIndex) const final override;
};

template <>
class Basic<Selection::Basic::Ellipse> : public PlainSymbol
{
public:
	Basic() : PlainSymbol(sf::PrimitiveType::TriangleFan), m_numberOfEdges(36u) { }

	void setNumberOfEdges(std::size_t numberOfEdges) { m_numberOfEdges = (numberOfEdges < 4u) ? 3u : numberOfEdges; priv_update(); }
	std::size_t getNumberOfEdges() const { return m_numberOfEdges; }

private:
	std::size_t m_numberOfEdges;

	virtual std::size_t priv_getNumberOfVertices() const override { return m_numberOfEdges + 2u; }
	virtual sf::Vector2f priv_getVertexPosition(std::size_t vertexIndex) const final override;
};

template <>
class Basic<Selection::Basic::Star> : public PlainSymbol
{
public:
	Basic() : PlainSymbol(sf::PrimitiveType::TriangleFan), m_numberOfSpikes(5u), m_innerDistanceMultiplier(0.38196601125010515179541316563436f) { }

	void setNumberOfSpikes(std::size_t numberOfSpikes) { m_numberOfSpikes = (numberOfSpikes < 4u) ? 3u : numberOfSpikes; priv_update(); }
	std::size_t getNumberOfEdges() const { return m_numberOfSpikes * 2u; }
	void setInnerDistanceMultiplier(float innerDistanceMultiplier) { m_innerDistanceMultiplier = innerDistanceMultiplier; priv_update(); }
	float getInnerDistanceMultiplier() const { return m_innerDistanceMultiplier; }
	void setInnerDistanceMultiplierAutomatically(unsigned int spikeStep = 2u)
	{
		setInnerDistanceMultiplier(std::cos(constants::pi * spikeStep / m_numberOfSpikes) / std::cos(constants::pi * (static_cast<int>(spikeStep) - 1) / m_numberOfSpikes));
	}

private:
	std::size_t m_numberOfSpikes;
	float m_innerDistanceMultiplier;

	virtual std::size_t priv_getNumberOfVertices() const final override { return (m_numberOfSpikes * 2u) + 2u; }
	virtual sf::Vector2f priv_getVertexPosition(std::size_t vertexIndex) const final override;
};

template <>
class Basic<Selection::Basic::Frame> : public PlainSymbol
{
public:
	Basic() : PlainSymbol(sf::PrimitiveType::TriangleStrip), m_thickness(10.f) { }

	void setThickness(float thickness) { m_thickness = thickness; priv_update(); }
	float getThickness() const { return m_thickness; }

private:
	float m_thickness;

	virtual std::size_t priv_getNumberOfVertices() const final override { return 10u; }
	virtual sf::Vector2f priv_getVertexPosition(std::size_t vertexIndex) const final override;
};

template <>
class Basic<Selection::Basic::RoundedRectangle> : public PlainSymbol
{
public:
	Basic() : PlainSymbol(sf::PrimitiveType::TriangleStrip), m_numberOfCornerEdges(16u), m_cornerRadius{ 10.f, 10.f } { }

	void setNumberOfCornerEdges(std::size_t numberOfCornerEdges) { m_numberOfCornerEdges = (numberOfCornerEdges < 1u) ? 1u : numberOfCornerEdges; priv_update(); }
	std::size_t getNumberOfCornerEdges() const { return m_numberOfCornerEdges; }
	void setCornerRadius(sf::Vector2f cornerRadius) { m_cornerRadius = cornerRadius; priv_update(); }
	void setCornerRadius(float cornerRadius) { setCornerRadius({ cornerRadius, cornerRadius }); }
	sf::Vector2f getCornerRadius() const { return m_cornerRadius; }

private:
	std::size_t m_numberOfCornerEdges;
	sf::Vector2f m_cornerRadius;

	virtual std::size_t priv_getNumberOfVertices() const final override { return (m_numberOfCornerEdges + 1u) * 4u; }
	virtual sf::Vector2f priv_getVertexPosition(std::size_t vertexIndex) const final override;
};

template <>
class Basic<Selection::Basic::RoundedFrame> : public PlainSymbol
{
public:
	Basic() : PlainSymbol(sf::PrimitiveType::TriangleStrip), m_numberOfCornerEdges(16u), m_thickness(10.f), m_outerCornerRadius{ 10.f, 10.f }, m_innerCornerRadius{ 5.f, 5.f } { }

	void setNumberOfCornerEdges(std::size_t numberOfCornerEdges) { m_numberOfCornerEdges = (numberOfCornerEdges < 1u) ? 1u : numberOfCornerEdges; priv_update(); }
	std::size_t getNumberOfCornerEdges() const { return m_numberOfCornerEdges; }
	void setThickness(float thickness) { m_thickness = thickness; priv_update(); }
	float getThickness() const { return m_thickness; }
	void setOuterCornerRadius(sf::Vector2f outerCornerRadius) { m_outerCornerRadius = outerCornerRadius; priv_update(); }
	void setOuterCornerRadius(float outerCornerRadius) { setOuterCornerRadius({ outerCornerRadius, outerCornerRadius }); }
	sf::Vector2f getOuterCornerRadius() const { return m_outerCornerRadius; }
	void setInnerCornerRadius(sf::Vector2f innerCornerRadius) { m_innerCornerRadius = innerCornerRadius; priv_update(); }
	void setInnerCornerRadius(float innerCornerRadius) { setInnerCornerRadius({ innerCornerRadius, innerCornerRadius }); }
	sf::Vector2f getInnerCornerRadius() const { return m_innerCornerRadius; }

private:
	std::size_t m_numberOfCornerEdges;
	float m_thickness;
	sf::Vector2f m_outerCornerRadius;
	sf::Vector2f m_innerCornerRadius;

	virtual std::size_t priv_getNumberOfVertices() const final override { return (m_numberOfCornerEdges + 1u) * 8u + 2u; }
	virtual sf::Vector2f priv_getVertexPosition(std::size_t vertexIndex) const final override;
};

template <>
class Basic<Selection::Basic::RegularPolygon> : public Basic<Selection::Basic::Ellipse>
{
public:
	Basic() : Basic<Selection::Basic::Ellipse>() { Basic<Selection::Basic::Ellipse>::setNumberOfEdges(36u); }

	sf::Vector2f getLocalCenter() { return getSize() / 2.f; }
	sf::Vector2f getLocalAltCenter() { return{ getSize().x * ((1.f - (std::cos(constants::pi / getNumberOfEdges()))) / 4.f + 0.5f), getLocalCenter().y }; }
	sf::Vector2f getLocalAltFlatSide() { return{ getSize().x * (0.5f - (std::cos(constants::pi / getNumberOfEdges()) / 2.f)), getLocalCenter().y }; }
	float getAltScaleMultiplier() { return 2.f / ((std::cos(constants::pi / getNumberOfEdges())) + 1.f); }

private:
	virtual std::size_t priv_getNumberOfVertices() const final override { return getNumberOfEdges() + 2u; }
};

template <>
class Basic<Selection::Basic::Parallelogram> : public PlainSymbol
{
public:
	Basic() : PlainSymbol(sf::PrimitiveType::TriangleStrip), m_skew{ 0.1f } { }

	void setSkew(float skew) { m_skew = skew; priv_update(); }
	float getSkew() const { return m_skew; }

private:
	float m_skew;

	virtual std::size_t priv_getNumberOfVertices() const final override { return 4u; }
	virtual sf::Vector2f priv_getVertexPosition(std::size_t vertexIndex) const final override;
};

























sf::Vector2f Basic<Selection::Basic::Rectangle>::priv_getVertexPosition(const std::size_t vertexIndex) const
{
	switch (vertexIndex)
	{
	case 1u:
		return{ 1.f, 0.f };
	case 2u:
		return{ 0.f, 1.f };
	case 3u:
		return{ 1.f, 1.f };
	case 0u:
	default:
		return{ 0.f, 0.f };
	}
}

sf::Vector2f Basic<Selection::Basic::Ellipse>::priv_getVertexPosition(const std::size_t vertexIndex) const
{
	const sf::Vector2f center{ 0.5f, 0.5f };

	if (vertexIndex == 0u)
		return center;
	const std::size_t numberOfVerticesAroundPerimeter{ priv_getNumberOfVertices() - 2 };
	if (vertexIndex <= numberOfVerticesAroundPerimeter)
	{
		const float radians{ 2.f * constants::pi * (vertexIndex - 1) / numberOfVerticesAroundPerimeter };
		return{ center.x + center.x * std::cos(radians), center.y + center.y * std::sin(radians) };
	}

	return{ 1.f, center.y };
}

sf::Vector2f Basic<Selection::Basic::Star>::priv_getVertexPosition(const std::size_t vertexIndex) const
{
	const sf::Vector2f center{ 0.5f, 0.5f };

	if (vertexIndex == 0u)
		return center;
	const std::size_t numberOfVerticesAroundPerimeter{ priv_getNumberOfVertices() - 2 };
	if (vertexIndex > numberOfVerticesAroundPerimeter)
		return{ center.x, 0.f };

	const float radius{ (vertexIndex % 2 == 1) ? 1.f : m_innerDistanceMultiplier };
	const float radians{ 2.f * constants::pi * ((vertexIndex - 1.f) / numberOfVerticesAroundPerimeter + 0.25f) };
	return{ center.x + center.x * radius * std::cos(radians), center.y - center.y * radius * std::sin(radians) };
}

sf::Vector2f Basic<Selection::Basic::Frame>::priv_getVertexPosition(const std::size_t vertexIndex) const
{
	const sf::Vector2f size{ getSize() };
	const sf::Vector2f thickness{ m_thickness / size.x, m_thickness / size.y };

	const bool isOuterVertex{ vertexIndex % 2 == 0 };
	const unsigned int corner{ (vertexIndex / 2) % 4 };

	switch (corner)
	{
	case 1u:
		if (isOuterVertex)
			return{ 1.f, 0.f };
		else
			return{ 1.f - thickness.x, thickness.y };
		break;
	case 2u:
		if (isOuterVertex)
			return{ 1.f, 1.f };
		else
			return{ 1.f - thickness.x, 1.f - thickness.y };
	case 3u:
		if (isOuterVertex)
			return{ 0.f, 1.f };
		else
			return{ thickness.x, 1.f - thickness.y };
		break;
	case 0u:
	default:
		if (isOuterVertex)
			return{ 0.f, 0.f };
		else
			return thickness;
	}
}

sf::Vector2f Basic<Selection::Basic::RoundedRectangle>::priv_getVertexPosition(const std::size_t vertexIndex) const
{
	const sf::Vector2f size{ getSize() };
	const sf::Vector2f cornerRadius{ m_cornerRadius.x / size.x, m_cornerRadius.y / size.y };
	const std::size_t halfNumberOfVertices{ priv_getNumberOfVertices() / 2u };
	const bool isRight{ vertexIndex < halfNumberOfVertices };
	const bool isTop{ (vertexIndex % 2u) == 0u };
	const std::size_t vertexNumber{ (vertexIndex % halfNumberOfVertices) / 2u };
	const float ratio{ static_cast<float>(vertexNumber) / m_numberOfCornerEdges };
	sf::Vector2f cornerCenter{ 1.f - cornerRadius.x, cornerRadius.y };
	float angle{ ratio * 90.f };
	if (!isRight)
	{
		angle += 90.f;
		cornerCenter.x = cornerRadius.x;
	}
	if (!isTop)
	{
		angle = -angle;
		cornerCenter.y = 1.f - cornerRadius.y;
	}
	const float angleInRadians{ angle * constants::radiansFromDegreesMultiplier };
	const float x{ cornerCenter.x + std::cos(angleInRadians) * cornerRadius.x };
	const float y{ cornerCenter.y - std::sin(angleInRadians) * cornerRadius.y };
	return{ x, y };
}

sf::Vector2f Basic<Selection::Basic::RoundedFrame>::priv_getVertexPosition(const std::size_t vertexIndex) const
{
	const sf::Vector2f size{ getSize() };
	sf::Vector2f thickness{ m_thickness / size.x, m_thickness / size.y };
	const sf::Vector2f outerCornerRadius{ m_outerCornerRadius.x / size.x, m_outerCornerRadius.y / size.y };
	const sf::Vector2f innerCornerRadius{ m_innerCornerRadius.x / size.x, m_innerCornerRadius.y / size.y };

	const bool isOuter{ (vertexIndex % 2u) == 0u };
	const std::size_t numberOfVerticesPerCorner{ (2u * (m_numberOfCornerEdges + 1u)) };
	const std::size_t corner{ (vertexIndex / numberOfVerticesPerCorner) % 4u };
	const std::size_t vertexNumber{ (vertexIndex % numberOfVerticesPerCorner) };

	const std::size_t numberOfStepsPerCorner{ numberOfVerticesPerCorner / 2u };
	const std::size_t step{ vertexNumber / 2u };

	const float ratio{ static_cast<float>(step) / (numberOfStepsPerCorner - 1u) };
	const float angle{ 90.f * (ratio + corner) }; // ratio * 90.f + 90.f * corner
	const float angleInRadians{ angle * constants::radiansFromDegreesMultiplier };

	sf::Vector2f radius{ isOuter ? outerCornerRadius : innerCornerRadius };
	sf::Vector2f offset{ outerCornerRadius };
	if (!isOuter)
		offset = thickness + innerCornerRadius;

	sf::Vector2f circleCenter;
	switch (corner)
	{
	case 0u:
		circleCenter = { 1.f - offset.x, offset.y };
		break;
	case 1u:
		circleCenter = offset;
		break;
	case 2u:
		circleCenter = { offset.x, 1.f - offset.y };
		break;
	case 3u:
		circleCenter = { 1.f - offset.x, 1.f - offset.y };
		break;
	}

	const float x{ circleCenter.x + std::cos(angleInRadians) * radius.x };
	const float y{ circleCenter.y - std::sin(angleInRadians) * radius.y };
	return{ x, y };
}

sf::Vector2f Basic<Selection::Basic::Parallelogram>::priv_getVertexPosition(const std::size_t vertexIndex) const
{
	const bool positiveSkew{ m_skew >= 0.f };
	if (m_skew < 0.f)
	{
		switch (vertexIndex)
		{
		case 1u:
			return{ 1.f + m_skew, 0.f };
		case 2u:
			return{ -m_skew, 1.f };
		case 3u:
			return{ 1.f, 1.f };
		case 0u:
		default:
			return{ 0.f, 0.f };
		}
	}
	else
	{
		switch (vertexIndex)
		{
		case 1u:
			return{ 1.f, 0.f };
		case 2u:
			return{ 0.f, 1.f };
		case 3u:
			return{ 1.f - m_skew, 1.f };
		case 0u:
		default:
			return{ m_skew, 0.f };
		}
	}
}

} // namespace grambol
#endif // GRAMBOL_BASICS_HPP
