//////////////////////////////////////////////////////////////////////////////
//
// Grambol (https://github.com/Hapaxia/Grambol)
// --
//
// Icons
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

#ifndef GRAMBOL_ICONS_HPP
#define GRAMBOL_ICONS_HPP

#include "PlainSymbol.hpp"

#include <cmath>

namespace grambol
{

namespace Selection
{

	enum class Icon
	{
		Cog,
		Download,
		Upload,
		Home,
		Pin,
		Clock,
		Bluetooth,
	};

} // namespace Selection

inline float mod(const float numerator, const unsigned int denominator)
{
	return numerator - std::floor(numerator / denominator) * denominator;
}

template <Selection::Icon>
class Icon { Icon() = delete; };

/*
COG symbol
	"tooth" = one "bump" around the outside of the cog
	"tip" = "highest" part of the outside of the cog (the end of the tooth)
	"root" = "lowest" part of the outside of the cog (the "inbetween" parts of the teeth)
	"pitch" = (circular) distance between the same part of each tooth (e.g. distance between the start of a tooth tip and the start of the next tooth tip)

	tip radius is the radius to the "furthest" edges of the symbol. this is represented by "size" and can be elliptical if size is not square in shape.
	root radius multiplier (0.f - 1.f): the ratio of the tip radius for the root height
	hole radius multiplier (0.f - 1.f): the ratio of the tip radius for the hole. this should be lower than the root radius multiplier

	tooth tip width multiplier (0.f - 1.f): the ratio of the pitch that describes how wide each tooth tip is
	tooth root width multiplier (0.f - 1.f): the ratio of the remainder of the pitch (between tooth tip widths) that describes how wide the root is. the rest is filled with the ramps between tip and root.
*/
template <>
class Icon<Selection::Icon::Cog> : public PlainSymbol
{
public:
	Icon()
		: PlainSymbol(sf::PrimitiveType::TriangleStrip)
		, m_numberOfTeeth{ 8u }
		, m_rootRadiusMultiplier{ 0.8f }
		, m_holeRadiusMultiplier{ 0.5f }
		, m_toothTipWidthMultiplier{ 0.3f }
		, m_toothRootWidthMultiplier{ 0.5357f }
	{ }
	void setNumberOfTeeth(std::size_t numberOfTeeth) { m_numberOfTeeth = numberOfTeeth; priv_update(); }
	std::size_t getNumberOfTeeth() const { return m_numberOfTeeth; }
	void setRootRadiusMultiplier(float rootRadiusMultiplier) { m_rootRadiusMultiplier = rootRadiusMultiplier; priv_update(); }
	float getRootRadiusMultiplier() const { return m_rootRadiusMultiplier; }
	void setHoleRadiusMultiplier(float holeRadiusMultiplier) { m_holeRadiusMultiplier = holeRadiusMultiplier; priv_update(); }
	float getHoleRadiusMultiplier() const { return m_rootRadiusMultiplier; }
	void setToothTipWidthMultiplier(float toothTipWidthMultiplier) { m_toothTipWidthMultiplier = toothTipWidthMultiplier; priv_update(); }
	float getToothTipWidthMultiplier() const { return m_toothTipWidthMultiplier; }
	void setToothRootWidthMultiplier(float toothRootWidthMultiplier) { m_toothRootWidthMultiplier = toothRootWidthMultiplier; priv_update(); }
	float getToothRootWidthMultiplier() const { return m_toothRootWidthMultiplier; }
	void autoSetToothRootWidthMultiplier()
	{
		constexpr float zeroEpsilon{ 0.0000001f };
		const float invertedToothTipWidthMultiplier{ ((1.f - m_toothTipWidthMultiplier) <= zeroEpsilon) ? zeroEpsilon : (1.f - m_toothTipWidthMultiplier) };
		const float rootRadiusMultiplier{ (m_rootRadiusMultiplier <= zeroEpsilon) ? zeroEpsilon : m_rootRadiusMultiplier };
		m_toothRootWidthMultiplier = m_toothTipWidthMultiplier / (invertedToothTipWidthMultiplier * rootRadiusMultiplier);
		priv_update();
	}
	void autoSetToothTipWidthMultiplier()
	{
		const float rw{ m_rootRadiusMultiplier * m_toothRootWidthMultiplier };
		m_toothTipWidthMultiplier = rw / (rw + 1.f);
		priv_update();
	}



	/*

	w = t / ((1-t) * r)
	
	w * (1-t) * r = t
	t = w * (1-t) * r
	t / (1-t) = w * r

	= t = (w*r) / ((w*r) + 1)
	

	...
	t / (1-t) = rw
	t / (-t + 1) = rw

	t = rw(-t + 1)
	t = rw(-t) + rw
	t = -rwt + rw
	t + rwt = rw
	t(rw + 1) = rw
	t = rw / (rw + 1)
	...


	=====
	w = t / ((1-t) * r)
	t = (1-t)rw
	t = rw - trw
	t + trw = rw
	t(1 + rw) = rw
	t = rw / (1 + rw)

	*/



private:
	std::size_t m_numberOfTeeth;
	float m_rootRadiusMultiplier;
	float m_holeRadiusMultiplier;
	float m_toothTipWidthMultiplier;
	float m_toothRootWidthMultiplier;

	std::size_t priv_getNumberOfVertices() const final override { return m_numberOfTeeth * 8u + 2u; }
	sf::Vector2f priv_getVertexPosition(std::size_t vertexIndex) const final override;
};

template <>
class Icon<Selection::Icon::Download> : public PlainSymbol
{
public:
	Icon()
		: PlainSymbol(sf::PrimitiveType::Triangles)
		, m_flipArrowDirection{ false }
		, m_arrowHeightMultiplier{ 0.8f }
		, m_arrowMidMultiplier{ 0.5f }
		, m_barHeightMultiplier{ 0.1f }
		, m_arrowWidthMultiplier{ 1.f }
		, m_arrowThicknessMultiplier{ 0.45f }
	{ }
	void setFlipArrowDirection(bool flipArrowDirection) { m_flipArrowDirection = true; priv_update(); }
	bool getFlipArrowDirection() const { return m_flipArrowDirection; }
	void setArrowHeightMultiplier(float arrowHeightMultiplier) { m_arrowHeightMultiplier = arrowHeightMultiplier; priv_update(); }
	float getArrowHeightMultiplier() const { return m_arrowHeightMultiplier; }
	void setArrowMidMultiplier(float arrowMidMultiplier) { m_arrowMidMultiplier = arrowMidMultiplier; priv_update(); }
	float getArrowMidMultiplier() const { return m_arrowMidMultiplier; }
	void setBarHeightMultiplier(float barHeightMultiplier) { m_barHeightMultiplier = barHeightMultiplier; priv_update(); }
	float getBarHeightMultiplier() const { return m_barHeightMultiplier; }
	void setArrowWidthMultiplier(float arrowWidthMultiplier) { m_arrowWidthMultiplier = arrowWidthMultiplier; priv_update(); }
	float getArrowWidthMultiplier() const { return m_arrowWidthMultiplier; }
	void setArrowThicknessMultiplier(float arrowThicknessMultiplier) { m_arrowThicknessMultiplier = arrowThicknessMultiplier; priv_update(); }
	float getArrowThicknessMultiplier() const { return m_arrowThicknessMultiplier; }

private:
	bool m_flipArrowDirection;
	float m_arrowHeightMultiplier;
	float m_arrowMidMultiplier;
	float m_barHeightMultiplier;
	float m_arrowWidthMultiplier;
	float m_arrowThicknessMultiplier;
	virtual std::size_t priv_getNumberOfVertices() const final override { return 15u; }
	virtual sf::Vector2f priv_getVertexPosition(std::size_t vertexIndex) const final override;
};

/*
Home symbol
	roof height multiplier (0.f - 1.f): the ratio of the overall height for the roof section (the rest is wall)
	wall width multiplier (0.f - 1.f): the ratio of the overall width for the wall section
	door width multiplier (0.f - 1.f): the ratio of the wall width for the door section
	door height multiplier (0.f - 1.f): the ratio of the wall height (see "roof height multiplier" above for more info)
*/
template <>
class Icon<Selection::Icon::Home> : public PlainSymbol
{
public:
	Icon() : PlainSymbol(sf::PrimitiveType::TriangleStrip), m_roofHeightMultiplier{ 0.5f }, m_wallWidthMultiplier{ 0.7f }, m_doorWidthMultiplier{ 0.32f }, m_doorHeightMultiplier{ 0.7f } { }
	void setRoofHeightMultiplier(float roofHeightMultiplier) { m_roofHeightMultiplier = roofHeightMultiplier; priv_update(); }
	float getRoofHeightMultiplier() const { return m_roofHeightMultiplier; }
	void setWallWidthMultiplier(float wallWidthMultiplier) { m_wallWidthMultiplier = wallWidthMultiplier; priv_update(); }
	float getWallWidthMultiplier() const { return m_wallWidthMultiplier; }
	void setDoorWidthMultiplier(float doorWidthMultiplier) { m_doorWidthMultiplier = doorWidthMultiplier; priv_update(); }
	float getDoorWidthMultiplier() const { return m_doorWidthMultiplier; }
	void setDoorHeightMultiplier(float doorHeightMultiplier) { m_doorHeightMultiplier = doorHeightMultiplier; priv_update(); }
	float getDoorHeightMultiplier() const { return m_doorHeightMultiplier; }

private:
	float m_roofHeightMultiplier;
	float m_wallWidthMultiplier;
	float m_doorWidthMultiplier;
	float m_doorHeightMultiplier;
	virtual std::size_t priv_getNumberOfVertices() const final override { return 16u; }
	virtual sf::Vector2f priv_getVertexPosition(std::size_t vertexIndex) const final override;
};

template <>
class Icon<Selection::Icon::Pin> : public PlainSymbol
{
public:
	Icon() : PlainSymbol(sf::PrimitiveType::TriangleStrip), m_numberOfEdges{ 32u }, m_stretchAmount{ 2.f }, m_innerRadiusMultiplier{ 0.4f } { }
	void setStretchAmount(float stretchAmount) { m_stretchAmount = stretchAmount; priv_update(); }
	float getStretchAmount() const { return m_stretchAmount; }
	void setInnerRadiusMultiplier(float innerRadiusMultiplier) { m_innerRadiusMultiplier = innerRadiusMultiplier; }
	float getInnerRadiusMultiplier() const { return m_innerRadiusMultiplier; }
	void autoSetScaleX() { setScale({ getScale().y * 2.f / (m_stretchAmount + 2.f), getScale().y }); }

private:
	std::size_t m_numberOfEdges;
	float m_stretchAmount;
	float m_innerRadiusMultiplier;

	virtual std::size_t priv_getNumberOfVertices() const final override { return (m_numberOfEdges + 1u) * 2u; }
	virtual sf::Vector2f priv_getVertexPosition(std::size_t vertexIndex) const final override;
};

template <>
class Icon<Selection::Icon::Clock> : public PlainSymbol
{
public:
	Icon()
		: PlainSymbol(sf::PrimitiveType::Triangles)
		, m_numberOfOuterEdges{ 64u }
		, m_innerRadiusMultiplier{ 0.8f }
		, m_hourHandLengthMultiplier{ 0.6f }
		, m_minuteHandLengthMultiplier{ 0.85f }
		, m_secondHandLengthMultiplier{ 0.9f }
		, m_hourHandWidthMultiplier{ 0.15f }
		, m_minuteHandWidthMultiplier{ 0.15f }
		, m_secondHandWidthMultiplier{ 0.075f }
		, m_hourHandTipWidthMultiplier{ 1.f }
		, m_minuteHandTipWidthMultiplier{ 1.f }
		, m_secondHandTipWidthMultiplier{ 0.5f }
		, m_hour{ 10.175f }
		, m_minute{ 10.5f }
		, m_second{ 30.f }
		, m_showHour{ true }
		, m_showMinute{ true }
		, m_showSecond{ false }
	{ }
	void setNumberOfOuterEdges(std::size_t numberOfOuterEdges) { m_numberOfOuterEdges = numberOfOuterEdges; priv_update(); }
	std::size_t getNumberOfOuterEdges() const { return m_numberOfOuterEdges; }
	void setInnerRadiusMultiplier(float innerRadiusMultiplier) { m_innerRadiusMultiplier = innerRadiusMultiplier; priv_update(); }
	float getInnerRadiusMultiplier() const { return m_innerRadiusMultiplier; }

	void setHourHandLengthMultiplier(float hourHandLengthMultiplier) { m_hourHandLengthMultiplier = hourHandLengthMultiplier; priv_update(); }
	float getHourHandLengthMultiplier() const { return m_hourHandLengthMultiplier; }
	void setMinuteHandLengthMultiplier(float minuteHandLengthMultiplier) { m_minuteHandLengthMultiplier = minuteHandLengthMultiplier; priv_update(); }
	float getMinuteHandLengthMultiplier() const { return m_minuteHandLengthMultiplier; }
	void setSecondHandLengthMultiplier(float secondHandLengthMultiplier) { m_secondHandLengthMultiplier = secondHandLengthMultiplier; priv_update(); }
	float getSecondHandLengthMultiplier() const { return m_secondHandLengthMultiplier; }

	void setHourHandWidthMultiplier(float hourHandWidthMultiplier) { m_hourHandWidthMultiplier = hourHandWidthMultiplier; priv_update(); }
	float getHourHandWidthMultiplier() const { return m_hourHandWidthMultiplier; }
	void setMinuteHandWidthMultiplier(float minuteHandWidthMultiplier) { m_minuteHandWidthMultiplier = minuteHandWidthMultiplier; priv_update(); }
	float getMinuteHandWidthMultiplier() const { return m_minuteHandWidthMultiplier; }
	void setSecondHandWidthMultiplier(float secondHandWidthMultiplier) { m_secondHandWidthMultiplier = secondHandWidthMultiplier; priv_update(); }
	float getSecondHandWidthMultiplier() const { return m_secondHandWidthMultiplier; }

	void setHour(float hour) { m_hour = hour; priv_update(); }
	float getHour() const { return m_hour; }
	void setMinute(float minute) { m_minute = minute; priv_update(); }
	float getMinute() const { return m_minute; }
	void setSecond(float second) { m_second = second; priv_update(); }
	float getSecond() const { return m_second; }

	void setShowHour(bool showHour) { m_showHour = showHour; priv_update(); }
	bool getShowHour() const { return m_showHour; }
	void setShowMinute(bool showMinute) { m_showMinute = showMinute; priv_update(); }
	bool getShowMinute() const { return m_showMinute; }
	void setShowSecond(bool showSecond) { m_showSecond = showSecond; priv_update(); }
	bool getShowSecond() const { return m_showSecond; }

	void setTime(unsigned int hour, unsigned int minute = 0u, float second = 0.f)
	{
		m_second = priv_mod(second, 60u);
		m_minute = (minute % 60u) + m_second / 60.f;
		m_hour = (hour % 12u) + m_minute / 60.f;
		priv_update();
	}
	void setTime(unsigned int hour, unsigned int minute, unsigned int second) { setTime(hour, minute, static_cast<float>(second)); }
	void setTimeFromSeconds(float totalSeconds)
	{
		totalSeconds = priv_mod(totalSeconds, 86400u);
		const float s{ priv_mod(totalSeconds, 60u) };
		const unsigned int m{ static_cast<unsigned int>(priv_mod(totalSeconds, 3600u)) / 60u };
		const unsigned int h{ static_cast<unsigned int>(priv_mod(totalSeconds, 86400u)) / 3600u };
		setTime(h, m, s);
	}
	void setTimeFromSeconds(unsigned long int totalSeconds) { setTimeFromSeconds(static_cast<float>(totalSeconds)); }
	float getTimeInSeconds() const { return (std::floor(m_hour) * 3600.f) + (std::floor(m_minute) * 60.f) + m_second; }

private:
	std::size_t m_numberOfOuterEdges;
	float m_innerRadiusMultiplier;
	float m_hourHandLengthMultiplier;
	float m_minuteHandLengthMultiplier;
	float m_secondHandLengthMultiplier;
	float m_hourHandWidthMultiplier;
	float m_minuteHandWidthMultiplier;
	float m_secondHandWidthMultiplier;
	float m_hourHandTipWidthMultiplier;
	float m_minuteHandTipWidthMultiplier;
	float m_secondHandTipWidthMultiplier;
	float m_hour;
	float m_minute;
	float m_second;
	bool m_showHour;
	bool m_showMinute;
	bool m_showSecond;

	virtual std::size_t priv_getNumberOfVertices() const final override { return m_numberOfOuterEdges * 6u + (m_showHour ? 6u : 0u) + (m_showMinute ? 6u : 0u) + (m_showSecond ? 6u : 0u); }
	virtual sf::Vector2f priv_getVertexPosition(std::size_t vertexIndex) const final override;
	float priv_mod(float numerator, unsigned int denominator) { return numerator - std::floor(numerator / denominator) * denominator; }
};

template <>
class Icon<Selection::Icon::Bluetooth> : public PlainSymbol
{
public:
	Icon() : PlainSymbol(sf::PrimitiveType::TriangleStrip), m_thicknessMultiplier{ 0.08f } { }
	void setWidthMultiplier(float thicknessMultiplier) { m_thicknessMultiplier = thicknessMultiplier; priv_update(); }
	float getWidthMultiplier() const { return m_thicknessMultiplier; }

private:
	float m_thicknessMultiplier;

	virtual std::size_t priv_getNumberOfVertices() const final override { return 26u; }
	virtual sf::Vector2f priv_getVertexPosition(std::size_t vertexIndex) const final override;
};











inline sf::Vector2f Icon<Selection::Icon::Cog>::priv_getVertexPosition(const std::size_t vertexIndex) const
{
	/*
	._.     ._.
	   \._./   \._./
	._._._._._._._._
	*/
	//const sf::Vector2f size{ getSize() };
	const sf::Vector2f center{ 0.5f, 0.5f };

	const bool isOuter{ (vertexIndex % 2u) == 0u };
	const bool isTooth{ (vertexIndex % 8u) < 4u };

	const std::size_t toothIndex{ vertexIndex / 8u };
	const std::size_t vertexType{ vertexIndex / 2u % 4u }; // (for outers) assuming on top of cog, 0 is tip right, 1 is tip left, 2 is root right, 3 is root left (going anti-clockwise)

	//const float rootRadiusMultiplier{ 0.85f };
	//const float innerRadiusMultiplier{ 0.5f };

	//const float toothTipWidthMultiplier{ 0.3f }; // ratio of pitch (distance between each tooth in the same position - here is 2*step)
	//const float toothRootWidthRatio{ 0.5f }; // ratio of the remainder of the pitch (after tooth tip, this is how much of what is left is root - the rest is the ramp between them)

	const float toothWidthRemainingMultiplier{ 1.f - m_toothTipWidthMultiplier };
	const float toothRootWidthMultiplier{ toothWidthRemainingMultiplier * m_toothRootWidthMultiplier }; // ratio of the remainder of the pitch (after tooth tip, this is how much of what is left is root - the rest is the ramp between them)
	const float toothRampWidthMultiplier{ (toothWidthRemainingMultiplier - toothRootWidthMultiplier) / 2.f };

	float pitchMultiplier{ 0.f };
	switch (vertexType)
	{
	case 1u:
		pitchMultiplier = m_toothTipWidthMultiplier;
		break;
	case 2u:
		pitchMultiplier = m_toothTipWidthMultiplier + toothRampWidthMultiplier;
		break;
	case 3u:
		pitchMultiplier = m_toothTipWidthMultiplier + toothRampWidthMultiplier + toothRootWidthMultiplier;
		break;
	case 0u:
	default:
		break;
	}

	const float pitchAngle{ 360.f / m_numberOfTeeth };
	const float angle{ (toothIndex - (m_toothTipWidthMultiplier / 2.f)) * pitchAngle + ((isOuter ? pitchMultiplier : (vertexType / 4.f)) * pitchAngle) + 90.f };
	const float angleInRadians{ angle * constants::radiansFromDegreesMultiplier };

	if (!isOuter)
	{
		float x{ center.x + (std::cos(angleInRadians) * center.x * m_holeRadiusMultiplier) };
		float y{ center.y - (std::sin(angleInRadians) * center.y * m_holeRadiusMultiplier) };
		return{ x, y };
	}
	else
	{
		float x{ center.x + (std::cos(angleInRadians) * center.x * (isTooth ? 1.f : m_rootRadiusMultiplier)) };
		float y{ center.y - (std::sin(angleInRadians) * center.y * (isTooth ? 1.f : m_rootRadiusMultiplier)) };
		return{ x, y };
	}
}

inline sf::Vector2f Icon<Selection::Icon::Download>::priv_getVertexPosition(const std::size_t vertexIndex) const
{
	//const sf::Vector2f size{ getSize() };
	constexpr float centerX{ 0.5f };

	const float top{ m_flipArrowDirection ? m_arrowHeightMultiplier : 0.f };
	const float bottom{ m_flipArrowDirection ? 0.f : m_arrowHeightMultiplier };
	const float mid{ m_arrowHeightMultiplier * m_arrowMidMultiplier };
	const float barTop{ 1.f - m_barHeightMultiplier };
	const float arrowHeadLeft{ centerX * (1.f - m_arrowWidthMultiplier) };
	const float arrowHeadRight{ 1.f - arrowHeadLeft };
	const float arrowBaseLeft{ centerX * (1.f - (m_arrowThicknessMultiplier * m_arrowWidthMultiplier)) };
	const float arrowBaseRight{ 1.f - arrowBaseLeft };
	switch (vertexIndex)
	{
	case 1u:
		return{ arrowHeadLeft, mid };
	case 2u:
		return{ arrowHeadRight, mid };
	case 3u:
		return{ arrowBaseLeft, top };
	case 4u:
	case 7u:
		return{ arrowBaseLeft, mid };
	case 5u:
	case 8u:
		return{ arrowBaseRight, top };
	case 6u:
		return{ arrowBaseRight, mid };
	case 9u:
	case 12u:
		return{ 0.f, barTop };
	case 10u:
		return{ 0.f, 1.f };
	case 11u:
	case 13u:
		return{ 1.f, 1.f };
	case 14u:
		return{ 1.f, barTop };
	case 0u:
	default:
		return{ centerX, bottom };
	}
}

inline sf::Vector2f Icon<Selection::Icon::Home>::priv_getVertexPosition(const std::size_t vertexIndex) const
{
	//const sf::Vector2f size{ getSize() };
	const sf::Vector2f center{ 0.5f, 0.5f };
	const float roofHeight{ m_roofHeightMultiplier };
	const float doorTop{ 1.f - m_doorHeightMultiplier * (1.f - m_roofHeightMultiplier) };

	const float wallLeft{ center.x * (1.f - m_wallWidthMultiplier) };// size.x * 0.15f };
	const float wallRight{ 1.f - wallLeft };
	const float doorLeft{ center.x * (1.f - (m_doorWidthMultiplier * m_wallWidthMultiplier)) };// size.x * 0.3875f };
	const float doorRight{ 1.f - doorLeft };
	switch (vertexIndex)
	{
	case 1u:
		return{ center.x, 0.f };
	case 2u:
		return{ 1.f, roofHeight };
	case 3u:
	case 7u:
	case 10u:
		return{ doorLeft, roofHeight };
	case 4u:
		return{ wallLeft, roofHeight };
	case 5u:
		return{ wallLeft, 1.f };
	case 6u:
		return{ doorLeft, 1.f };
	case 8u:
		return{ doorLeft, doorTop };
	case 9u:
		return{ doorRight, doorTop };
	case 11u:
	case 14u:
		return{ wallRight, roofHeight };
	case 12u:
		return{ doorRight, doorTop };
	case 13u:
		return{ doorRight, 1.f };
	case 15u:
		return{ wallRight, 1.f };
	case 0u:
	default:
		return{ 0.f, roofHeight };
	}
}

inline sf::Vector2f Icon<Selection::Icon::Pin>::priv_getVertexPosition(const std::size_t vertexIndex) const
{
	//const sf::Vector2f size{ getSize() };
	const sf::Vector2f center{ 0.5f, 0.5f };

	const float stretchAmount{ m_stretchAmount };

	const bool isOuter{ (vertexIndex % 2) == 0u };

	const float outerRadius{ 0.5f / (1.f + 0.5f * stretchAmount) };
	const float innerRadius{ outerRadius * m_innerRadiusMultiplier };
	constexpr float outerRadiusX{ 0.5f };
	const float innerRadiusX{ outerRadiusX * m_innerRadiusMultiplier };

	const float midConversionAngle{ static_cast<float>(vertexIndex) / m_numberOfEdges };
	const float angle{ midConversionAngle * 180.f };
	const float angleInRadians{ midConversionAngle * constants::pi };
	const float radius{ isOuter ? outerRadius : innerRadius };
	const float radiusX{ isOuter ? outerRadiusX : innerRadiusX };

	const float mirroredAngle{ (angle > 180.f) ? (360.f - angle) : angle };
	const bool isStretch{ isOuter && (mirroredAngle > 90.f) };
	const float stretchScale{ (mirroredAngle - 90.f) / 90.f };
	const float stretch{ stretchScale * stretchAmount };

	const float x{ std::sin(angleInRadians) * radiusX };
	const float y{ -std::cos(angleInRadians) * radius * (isStretch ? 1.f + stretch : 1.f) };

	return{ center.x + x, outerRadius + y };
}

inline sf::Vector2f Icon<Selection::Icon::Clock>::priv_getVertexPosition(const std::size_t vertexIndex) const
{
	const sf::Vector2f center{ 0.5f, 0.5f };

	const bool isCircle{ vertexIndex < (m_numberOfOuterEdges * 6u) };
	if (isCircle)
	{
		const std::size_t vertexNumber{ vertexIndex % 6u };
		const std::size_t step{ vertexIndex / 6u };
		const float stepAngle{ 360.f / m_numberOfOuterEdges };
		std::size_t stepAddition{ 0u };
		switch (vertexNumber)
		{
		case 2u:
		case 4u:
		case 5u:
			++stepAddition;
		}
		const bool isOuter{ (vertexIndex % 2u) == 0u };
		const float radius{ isOuter ? 0.5f : m_innerRadiusMultiplier * 0.5f };
		const float angle{ stepAngle * (step + stepAddition) };
		const float angleInRadians{ angle * constants::radiansFromDegreesMultiplier };
		const float x{ center.x + std::cos(angleInRadians) * radius };
		const float y{ center.y - std::sin(angleInRadians) * radius };
		return{ x, y };
	}

	std::size_t finalVertexIndex{ vertexIndex - (m_numberOfOuterEdges * 6u) };
	std::size_t handNumber{ finalVertexIndex / 6u };
	std::size_t vertexNumber{ finalVertexIndex % 6u };

	std::size_t handType{ 0u }; // 0 = hour, 1 = minute, 2 = second
	switch (handNumber)
	{
	case 0u:
		if (m_showHour)
			handType = 0u;
		else if (m_showMinute)
			handType = 1u;
		else
			handType = 2u;
		break;
	case 1u:
		if (m_showHour)
		{
			if (m_showMinute)
				handType = 1u;
			else
				handType = 2u;
		}
		else
			handType = 2u;
		break;
	case 2u:
		handType = 2u;
		break;
	}

	float handLength{ m_innerRadiusMultiplier * 0.5f };
	float handWidth{ m_innerRadiusMultiplier * 0.5f };
	float handTipWidth;
	float ratio;

	switch (handType)
	{
	case 0u:
		handLength *= m_hourHandLengthMultiplier;
		handWidth *= m_hourHandWidthMultiplier;
		handTipWidth = handWidth * m_hourHandTipWidthMultiplier;
		ratio = m_hour / 12.f;
		break;
	case 1u:
		handLength *= m_minuteHandLengthMultiplier;
		handWidth *= m_minuteHandWidthMultiplier;
		handTipWidth = handWidth * m_minuteHandTipWidthMultiplier;
		ratio = m_minute / 60.f;
		break;
	case 2u:
		handLength *= m_secondHandLengthMultiplier;
		handWidth *= m_secondHandWidthMultiplier;
		handTipWidth = handWidth * m_secondHandTipWidthMultiplier;
		ratio = m_second / 60.f;
		break;
	}

	const float halfWidth{ handWidth * 0.5f };
	const float halfTipWidth{ handTipWidth * 0.5f };

	const float angle{ ratio * -360.f + 90.f };
	const float angleInRadians{ angle * constants::radiansFromDegreesMultiplier };

	float length{ handLength };
	float sideOffset{ halfTipWidth };

	switch (vertexNumber)
	{
	case 0u:
		sideOffset = -sideOffset;
		break;
	case 1u:
	case 3u:
		sideOffset = -halfWidth;
		length = -halfWidth * 0.7f;
		break;
	case 2u:
	case 4u:
		break;
	case 5u:
		sideOffset = halfWidth;
		length = -halfWidth * 0.7f;
		break;
	}

	const float cos{ std::cos(angleInRadians) };
	const float sin{ std::sin(angleInRadians) };

	const float x{ center.x + cos * length - sin * sideOffset };
	const float y{ center.y - sin * length - cos * sideOffset };
	return{ x, y };

}

inline sf::Vector2f Icon<Selection::Icon::Bluetooth>::priv_getVertexPosition(const std::size_t vertexIndex) const
{
	const sf::Vector2f center{ 0.5f, 0.5f };

	constexpr float sine{ 0.707f };
	//const float sqrt2{ std::sqrt(2.f) };
	constexpr float sq2{ 1.414f };

	const float thickness{ m_thicknessMultiplier };
	const float halfThickness{ m_thicknessMultiplier / 2.f };


	const float a{ (halfThickness + halfThickness * sq2) };
	const float b{ 0.5f - ((0.5f - a) * 0.5f) };

	const float left{ 0.5f - halfThickness - 2.f * (thickness * sq2) };
	const float right{ 0.5f + halfThickness + 2.f * (thickness * sq2) };

	const float vertLeft{ 0.5f - halfThickness };
	const float vertRight{ 0.5f + halfThickness };
	const float centerLeft{ 0.5f - sq2 * halfThickness };
	const float centerRight{ 0.5f + sq2 * halfThickness };
	const float horizExtremesTop{ b };
	const float horizExtremesBottom{ 1.f - b };
	const float horizExtremeRightInner{ right - sq2 * thickness };
	const float horizExtremeLeftInner{ left + sine * thickness };
	const float horizExtremeLeftInnerTop{ horizExtremesTop - sine * thickness };
	const float horizExtremeLeftInnerBottom{ horizExtremesBottom + sine * thickness };
	const float innerTop{ thickness + sq2 * thickness };
	const float innerBottom{ 1.f - innerTop };
	const float centerTop{ 0.4f }; // ish
	const float centerBottom{ 0.6f }; // ish

	/*
	
	w = width
	s = sqrt2 x width

	FW = full width
	FH = full height

	FW = w + s + s + s + s
	FH = 2(w + s + s + s + w)

	FW = w + 4s
	FH = 4w + 6s

	FW = w + 4 * 1.414 * w
	= w + 5.656 * w
	= 6.656 * w

	FH = 4w + 6 * 1.414 * w
	= 4w + 8.484 * w
	= 12.484 * w
	
	RATIO: width is 0.533162448 of height
	
	*/

	switch (vertexIndex)
	{
	case 1u:
		return{ vertRight, centerBottom };
	case 2u:
		return{ right, horizExtremesBottom };
	case 3u:
		return{ horizExtremeRightInner, horizExtremesBottom };
	case 4u:
		return{ vertLeft, 1.f };
	case 5u:
		return{ vertRight, innerBottom };
	case 6u:
		return{ vertLeft, centerBottom };
	case 7u:
		return{ vertRight, centerBottom };
	case 8u:
		return{ centerRight, center.y };
	case 9u:
		return{ vertLeft, centerBottom };
	case 10u:
		return{ centerLeft, center.y };
	case 11u:
		return{ horizExtremeLeftInner, horizExtremeLeftInnerBottom };
	case 12u:
		return{ left, horizExtremesBottom };
	case 13u:
		return{ centerLeft, center.y };
	case 14u:
		return{ centerRight, center.y };

	case 15u:
		return{ vertRight, centerTop };
	case 16u:
		return{ right, horizExtremesTop };
	case 17u:
		return{ horizExtremeRightInner, horizExtremesTop };
	case 18u:
		return{ vertLeft, 0.f };
	case 19u:
		return{ vertRight, innerTop };
	case 20u:
		return{ vertLeft, centerTop };
	case 21u:
		return{ vertRight, centerTop };
	case 22u:
		return{ centerLeft, center.y };
	case 23u:
		return{ vertLeft, centerTop };
	case 24u:
		return{ left, horizExtremesTop };
	case 25u:
		return{ horizExtremeLeftInner, horizExtremeLeftInnerTop };

	case 0u:
	default:
		return{ centerRight, center.y };
	}
}

} // namespace grambol
#endif // GRAMBOL_ICONS_HPP
