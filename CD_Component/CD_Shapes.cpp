#include "CD_Shapes.h"
#include <vector>

/// <summary>
/// Default constructor.
/// </summary>
CD_Rect::CD_Rect()
{

}

/// <summary>
/// Creates a simple rectangle object.
/// </summary>
/// <param name="pos">Position of the top-left of the rectangle.</param>
/// <param name="w">Width of the horizontal edges.</param>
/// <param name="h">Height of the vertical edges.</param>
CD_Rect::CD_Rect(CD_Vector pos, float w, float h)
	: position(pos), width(w), height(h)
{

}

/// <summary>
/// Change the current position of the rectangle.
/// </summary>
/// <param name="newPos">Destination position.</param>
void CD_Rect::SetPosition(CD_Vector newPos)
{
	position = newPos;
}

/// <summary>
/// 
/// </summary>
/// <returns>Current position of the top-left of the rectangle.</returns>
CD_Vector CD_Rect::GetPosition()
{
	return position;
}

/// <summary>
/// Change the width and height of the rectangle.
/// Use GetWidth() and GetHeight() to maintain the current values of either.
/// </summary>
/// <param name="newW">New width of horizontal edges.</param>
/// <param name="newH">New height of vertical edges.</param>
void CD_Rect::SetDimensions(float newW, float newH)
{
	width = newW;
	height = newH;
}

/// <summary>
/// 
/// </summary>
/// <returns>Current width of the rectangle's horizontal edges.</returns>
float CD_Rect::GetWidth()
{
	return width;
}

/// <summary>
/// 
/// </summary>
/// <returns>Current height of the rectangle's vertical edges.</returns>
float CD_Rect::GetHeight()
{
	return height;
}

////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// Default constructor.
/// </summary>
CD_Circle::CD_Circle()
{

}

/// <summary>
/// Creates a circle object.
/// </summary>
/// <param name="pos">Position of the centre of the circle.</param>
/// <param name="rad">Radius of the circle. Defaults to 5.</param>
CD_Circle::CD_Circle(CD_Vector pos, float rad)
	: position(pos), radius(rad)
{

}

/// <summary>
/// Change the current position of the circle.
/// </summary>
/// <param name="newPos">Destination position.</param>
void CD_Circle::SetPosition(CD_Vector newPos)
{
	position = newPos;
}

/// <summary>
/// 
/// </summary>
/// <returns>Current position of the centre of the circle.</returns>
CD_Vector CD_Circle::GetPosition()
{
	return position;
}

/// <summary>
/// Change the radius of the circle.
/// </summary>
/// <param name="newR">New radius.</param>
void CD_Circle::SetRadius(float newR)
{
	radius = newR;
}

/// <summary>
/// 
/// </summary>
/// <returns>Distance between the centre of the circle and the outer arc.</returns>
float CD_Circle::GetRadius()
{
	return radius;
}

////////////////////////////////////////////////////////////////////////////////
 
/// <summary>
/// Default constructor.
/// </summary>
CD_Polygon::CD_Polygon()
{

}

/// <summary>
/// Creates a polygon object anchored around an origin point.
/// This "anchor point" can be any desired point, whether the top-left or the centre or off wildly in another direction entirely. 
/// Choose an origin point you are comfortable with.
/// Note that the vertices should be given not as absolute values, but offsets in relation to this anchor point. 
/// This library assumes that the vertices will be arranged in a clockwise fashion.
/// Arranging them anti-clockwise or out of order entirely will result in errors, as will constructing a concave shape.
/// </summary>
/// <param name="pos">Position of the "anchor point" of the polygon. This is not a vertex.</param>
/// <param name="verts">Vector of vertex positions.</param>
CD_Polygon::CD_Polygon(CD_Vector pos, std::vector<CD_Vector> verts)
	: position(pos), vertices(verts)
{

}

/// <summary>
/// Change the position of the anchor point, thus moving the entire polygon at once.
/// </summary>
/// <param name="newPos">Destination position of the anchor point.</param>
void CD_Polygon::SetPosition(CD_Vector newPos)
{
	position = newPos;
}

/// <summary>
/// Returns the position of the anchor point. 
/// Note that this will not necessarily give the position of any vertex. 
/// Use the GetVertices() function in conjunction with this to determine vertex positions.
/// </summary>
/// <returns>Current position of the polygon's anchor point.</returns>
CD_Vector CD_Polygon::GetPosition()
{
	return position;
}

/// <summary>
/// 
/// </summary>
/// <returns>Vector of vertex positions in relation to the anchor point.</returns>
std::vector<CD_Vector> CD_Polygon::GetVertices()
{
	return vertices;
}