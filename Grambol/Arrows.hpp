//////////////////////////////////////////////////////////////////////////////
//
// Grambol (https://github.com/Hapaxia/Grambol)
// --
//
// Basics
//
// Copyright(c) 2023-2025 M.J.Silk
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

#ifndef GRAMBOL_ARROWS_HPP
#define GRAMBOL_ARROWS_HPP

#include "PlainSymbol.hpp"

#include <cmath>

#include <iostream>

namespace grambol
{

namespace Selection
{

	enum class Arrow
	{
		Dart,
		Standard,
		StandardDoubleEnded,
	};

} // namespace Selection

template <Selection::Arrow>
class Arrow { Arrow() = delete; };

class ArrowBase : public PlainSymbol
{
public:
	ArrowBase(sf::PrimitiveType primitiveType) : PlainSymbol(primitiveType) { }

	void setControlPoints(sf::Vector2f start, sf::Vector2f end) { setStartControlPoint(start); setEndControlPoint(end); }
	void setStartControlPoint(sf::Vector2f point) { m_startControlPoint = point; }
	void setEndControlPoint(sf::Vector2f point) { m_endControlPoint = point; }
	sf::Vector2f getStartControlPoint() const { return m_startControlPoint; }
	sf::Vector2f getEndControlPoint() const { return m_endControlPoint; }
	void setWidth(float width) { setSize({ getSize().x, width }); }
	float getWidth() const { return getSize().y; }
	void setLength(float length) { setSize({ length, getSize().y }); }
	float getLength() const { return getSize().x; }

	void updateFromControlPoints()
	{
		setScale({ 1.f, 1.f });
		setPosition(getStartControlPoint());
		const sf::Vector2f direction{ getEndControlPoint() - getStartControlPoint() };

		constexpr float zeroEpsilon{ 0.00001f };
		if (abs(direction.x) < zeroEpsilon && abs(direction.y) < zeroEpsilon)
		{
			setRotation(sf::degrees(0.f));
			setOrigin({ 0.f, 0.f });
			setSize({ 0.f, 0.f });
			priv_update();
			return;
		}

		const float directionLength{ std::sqrt(direction.x * direction.x + direction.y * direction.y) };
		const sf::Vector2f directionUnit{ direction / directionLength };
		const float directionAngleInRadians{ std::atan2(directionUnit.y, directionUnit.x) };
		const float directionAngle{ directionAngleInRadians * constants::degreesFromRadiansMultiplier };
		setOrigin({ 0.f, getSize().y / 2.f });
		setRotation(sf::degrees(directionAngle));
		setSize({ directionLength, getSize().y });
		priv_update();
	}
	void updateControlPoints()
	{
		sf::Transform transform{ getTransform() };
		const sf::Vector2f size{ getSize() };
		const float centerY{ size.y / 2.f };
		setStartControlPoint(transform.transformPoint({ 0.f, centerY }));
		setEndControlPoint(transform.transformPoint({ size.x, centerY }));
	}

private:
	sf::Vector2f m_startControlPoint;
	sf::Vector2f m_endControlPoint;
};

template <>
class Arrow<Selection::Arrow::Dart> : public ArrowBase
{
public:
	Arrow() : ArrowBase(sf::PrimitiveType::TriangleStrip), m_innerDistanceMultiplier(0.25f) { }

	void setInnerDistanceMultiplier(float innerDistanceMultiplier) { m_innerDistanceMultiplier = innerDistanceMultiplier; priv_update(); }
	float getInnerDistanceMultiplier() const { return m_innerDistanceMultiplier; }

private:
	float m_innerDistanceMultiplier;

	virtual std::size_t priv_getNumberOfVertices() const final override { return 4u; }
	virtual sf::Vector2f priv_getVertexPosition(std::size_t vertexIndex) const final override;
};

template <>
class Arrow<Selection::Arrow::Standard> : public ArrowBase
{
public:
	Arrow()
		: ArrowBase(sf::PrimitiveType::TriangleStrip)
		, m_startThickness(10.f)
		, m_endThickness(10.f)
		, m_headSize(10.f)
		, m_headOvershootSize(0.f)
	{ }

	void setStartThickness(float startThickness) { m_startThickness = startThickness; priv_update(); }
	float getStartThickness() const { return m_startThickness; }
	void setEndThickness(float endThickness) { m_endThickness = endThickness; priv_update(); }
	float getEndThickness() const { return m_endThickness; }
	void setThicknesses(float startThickness, float endThickness) { setStartThickness(startThickness); setEndThickness(endThickness); priv_update(); }
	void setThickness(float thickness) { setThicknesses(thickness, thickness); priv_update(); }
	void setHeadSize(float headSize) { m_headSize = headSize; priv_update(); }
	float getHeadSize() const { return m_headSize; }
	void setHeadOvershootSize(float headOvershootSize) { m_headOvershootSize = headOvershootSize; priv_update(); }
	float getHeadOvershootSize() const { return m_headOvershootSize; }

private:
	float m_startThickness;
	float m_endThickness;
	float m_headSize;
	float m_headOvershootSize;

	virtual std::size_t priv_getNumberOfVertices() const final override { return 10u; }
	virtual sf::Vector2f priv_getVertexPosition(std::size_t vertexIndex) const final override;
};

template <>
class Arrow<Selection::Arrow::StandardDoubleEnded> : public ArrowBase
{
public:
	Arrow()
		: ArrowBase(sf::PrimitiveType::TriangleStrip)
		, m_startThickness(10.f)
		, m_endThickness(10.f)
		, m_startHeadSize(10.f)
		, m_endHeadSize(10.f)
		, m_startHeadWidthMultiplier(1.f)
		, m_endHeadWidthMultiplier(1.f)
		, m_startHeadOvershootSize(0.f)
		, m_endHeadOvershootSize(0.f)
	{ }

	void setStartThickness(float startThickness) { m_startThickness = startThickness; priv_update(); }
	float getStartThickness() const { return m_startThickness; }
	void setEndThickness(float endThickness) { m_endThickness = endThickness; priv_update(); }
	float getEndThickness() const { return m_endThickness; }
	void setThicknesses(float startThickness, float endThickness) { setStartThickness(startThickness); setEndThickness(endThickness); priv_update(); }
	void setThickness(float thickness) { setThicknesses(thickness, thickness); priv_update(); }
	void setStartHeadSize(float startHeadSize) { m_startHeadSize = startHeadSize; priv_update(); }
	float getStartHeadSize() const { return m_startHeadSize; }
	void setEndHeadSize(float endHeadSize) { m_endHeadSize = endHeadSize; priv_update(); }
	float getEndHeadSize() const { return m_endHeadSize; }
	void setHeadSizes(float startHeadSize, float endHeadSize) { setStartHeadSize(startHeadSize); setEndHeadSize(endHeadSize); priv_update(); }
	void setHeadSizes(float headSize) { setHeadSizes(headSize, headSize); priv_update(); }
	void setStartHeadWidthMultiplier(float startHeadWidthMultiplier) { m_startHeadWidthMultiplier = startHeadWidthMultiplier; priv_update(); }
	float getStartHeadWidthMultiplier() const { return m_startHeadWidthMultiplier; }
	void setEndHeadWidthMultiplier(float endHeadWidthMultiplier) { m_endHeadWidthMultiplier = endHeadWidthMultiplier; priv_update(); }
	float getEndHeadWidthMultiplier() const { return m_endHeadWidthMultiplier; }
	void setHeadWidthMultipliers(float startHeadWidthMultiplier, float endHeadWidthMultiplier) { setStartHeadWidthMultiplier(startHeadWidthMultiplier); setEndHeadWidthMultiplier(endHeadWidthMultiplier); priv_update(); }
	void setHeadWidthMultipliers(float headWidthMultiplier) { setHeadSizes(headWidthMultiplier, headWidthMultiplier); priv_update(); }
	void setStartHeadOvershootSize(float startHeadOvershootSize) { m_startHeadOvershootSize = startHeadOvershootSize; priv_update(); }
	float getStartHeadOvershootSize() const { return m_startHeadOvershootSize; }
	void setEndHeadOvershootSize(float endHeadOvershootSize) { m_endHeadOvershootSize = endHeadOvershootSize; priv_update(); }
	float getEndHeadOvershootSize() const { return m_endHeadOvershootSize; }
	void setHeadOvershootSizes(float startHeadOvershootSize, float endHeadOvershootSize) { setStartHeadOvershootSize(startHeadOvershootSize); setEndHeadOvershootSize(endHeadOvershootSize); priv_update(); }
	void setHeadOvershootSizes(float headOvershootSize) { setHeadOvershootSizes(headOvershootSize, headOvershootSize); priv_update(); }

private:
	float m_startThickness;
	float m_endThickness;
	float m_startHeadSize;
	float m_endHeadSize;
	float m_startHeadWidthMultiplier;
	float m_endHeadWidthMultiplier;
	float m_startHeadOvershootSize;
	float m_endHeadOvershootSize;

	virtual std::size_t priv_getNumberOfVertices() const final override { return 16u; }
	virtual sf::Vector2f priv_getVertexPosition(std::size_t vertexIndex) const final override;
};







sf::Vector2f Arrow<Selection::Arrow::Dart>::priv_getVertexPosition(const std::size_t vertexIndex) const
{
	//const sf::Vector2f size{ getSize() };
	const sf::Vector2f center{ 0.5f, 0.5f };
	switch (vertexIndex)
	{
	case 1u:
		return{ 1.f, center.y };
	case 2u:
		return{ m_innerDistanceMultiplier, center.y };
	case 3u:
		return{ 0.f, 1.f };
	case 0u:
	default:
		return{ 0.f, 0.f };
	}
}

sf::Vector2f Arrow<Selection::Arrow::Standard>::priv_getVertexPosition(const std::size_t vertexIndex) const
{
	const sf::Vector2f size{ getSize() };
	const float centerY{ 0.5f };
	const float startThickness{ m_startThickness / size.y };
	const float endThickness{ m_endThickness / size.y };
	const float headSize{ m_headSize / size.x };
	const float headOvershootSize{ m_headOvershootSize / size.x };

	const float startHalfThickness{ startThickness / 2.f };
	const float endHalfThickness{ endThickness / 2.f };
	const float startBarTop{ centerY - startHalfThickness };
	const float startBarBottom{ centerY + startHalfThickness };
	const float endBarTop{ centerY - endHalfThickness };
	const float endBarBottom{ centerY + endHalfThickness };
	const float headInside{ 1.f - headSize };
	const float headOvershoot{ headInside - headOvershootSize };
	const sf::Vector2f endPoint{ 1.f, centerY };
	switch (vertexIndex)
	{
	case 0u:
		return{ headOvershoot, 0.f };
	case 1u:
		return{ headInside, endBarTop };
	case 2u:
		return endPoint;
	case 3u:
		return{ headInside, endBarBottom };
	case 4u:
		return{ headOvershoot, 1.f };
	case 5u:
		return endPoint;
	case 6u:
		return{ headInside, endBarBottom };
	case 7u:
		return{ headInside, endBarTop };
	case 8u:
		return{ 0.f, startBarBottom };
	case 9u:
		return{ 0.f, startBarTop };
	default:
		return endPoint;
	}
}

sf::Vector2f Arrow<Selection::Arrow::StandardDoubleEnded>::priv_getVertexPosition(const std::size_t vertexIndex) const
{
	const sf::Vector2f size{ getSize() };
	const float centerY{ 0.5f };

	const float startThickness{ m_startThickness / size.y };
	const float endThickness{ m_endThickness / size.y };
	const float startHeadSize{ m_startHeadSize / size.x };
	const float endHeadSize{ m_endHeadSize / size.x };
	const float startHeadOvershootSize{ m_startHeadOvershootSize / size.x };
	const float endHeadOvershootSize{ m_endHeadOvershootSize / size.x };
	/*
	, m_startThickness(10.f)
	, m_endThickness(10.f)
	, m_startHeadSize(10.f)
	, m_endHeadSize(10.f)
	, m_startHeadWidthMultiplier(1.f)
	, m_endHeadWidthMultiplier(1.f)
	, m_startHeadOvershootSize(0.f)
	, m_endHeadOvershootSize(0.f)
	*/


	const float startHalfThickness{ startThickness / 2.f };
	const float endHalfThickness{ endThickness / 2.f };
	const float startBarTop{ centerY - startHalfThickness };
	const float startBarBottom{ centerY + startHalfThickness };
	const float endBarTop{ centerY - endHalfThickness };
	const float endBarBottom{ centerY + endHalfThickness };
	const float startHeadInside{ startHeadSize };
	const float endHeadInside{ 1.f - endHeadSize };
	const float startHeadOvershoot{ startHeadInside + startHeadOvershootSize };
	const float endHeadOvershoot{ endHeadInside - endHeadOvershootSize };
	const float startHeadHalfWidth{ centerY * m_startHeadWidthMultiplier };
	const float startHeadTop{ centerY - startHeadHalfWidth };
	const float startHeadBottom{ centerY + startHeadHalfWidth };
	const float endHeadHalfWidth{ centerY * m_endHeadWidthMultiplier };
	const float endHeadTop{ centerY - endHeadHalfWidth };
	const float endHeadBottom{ centerY + endHeadHalfWidth };
	const sf::Vector2f startPoint{ 0.f, centerY };
	const sf::Vector2f endPoint{ 1.f, centerY };
	switch (vertexIndex)
	{
	case 0u:
		return{ endHeadOvershoot, endHeadTop };
	case 1u:
		return{ endHeadInside, endBarTop };
	case 2u:
		return endPoint;
	case 3u:
		return{ endHeadInside, endBarBottom };
	case 4u:
		return{ endHeadOvershoot, endHeadBottom };
	case 5u:
		return endPoint;
	case 6u:
		return{ endHeadInside, endBarBottom };
	case 7u:
		return{ endHeadInside, endBarTop };
	case 8u:
		return{ startHeadInside, startBarBottom };
	case 9u:
		return{ startHeadInside, startBarTop };
	case 10u:
		return startPoint;
	case 11u:
		return{ startHeadOvershoot, startHeadTop };
	case 12u:
		return{ startHeadInside, startBarTop };
	case 13u:
		return startPoint;
	case 14u:
		return{ startHeadInside, startBarBottom };
	case 15u:
		return{ startHeadOvershoot, startHeadBottom };
	default:
		return startPoint;
	}
}

} // namespace grambol
#endif // GRAMBOL_ARROWS_HPP
