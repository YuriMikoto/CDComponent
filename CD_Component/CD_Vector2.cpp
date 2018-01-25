#include "CD_Vector2.h"

/// <summary>
/// Default constructor.
/// </summary>
CD_Vector::CD_Vector()
{

}

/// <summary>
/// Constructor function.
/// </summary>
/// <param name="xPos">X-axis position of vector.</param>
/// <param name="yPos">Y-axis position of vector.</param>
CD_Vector::CD_Vector(float xPos, float yPos)
{
	x = xPos;
	y = yPos;
}

/// <summary>
/// Assignment operator.
/// Set the value of a vector equal to a given one.
/// </summary>
/// <param name="right">Value to assign to this vector.</param>
void CD_Vector::operator=(CD_Vector right)
{
	x = right.x;
	y = right.y;
}

/// <summary>
/// Addition operator.
/// Adds one vector's components to another's.
/// </summary>
/// <param name="right">Vector to add to the given one.</param>
/// <returns>Result of the addition operation.</returns>
CD_Vector CD_Vector::operator+(CD_Vector right)
{
	return CD_Vector(x + right.x, y + right.y);
}

/// <summary>
/// Subtraction operator.
/// Subtracts one vector's components from another's.
/// </summary>
/// <param name="right">Vector to subtract from the given one.</param>
/// <returns>Result of the subtraction operation.</returns>
CD_Vector CD_Vector::operator-(CD_Vector right)
{
	return CD_Vector(x - right.x, y - right.y);
}

/// <summary>
/// Multiplication operator with another vector.
/// Get "dot product" between the two.
/// </summary>
/// <param name="right">Vector to multiply with the given one.</param>
/// <returns>Result of the dot product calculation.</returns>
float CD_Vector::operator*(CD_Vector right)
{
	return ((x * right.x) + (y * right.y));
}

/// <summary>
/// Multiplication operator with a scalar.
/// Multiplies the vector's components by this scalar value.
/// </summary>
/// <param name="right">Scalar to multiply the given vector by.</param>
/// <returns>Result of the multiplication operation.</returns>
CD_Vector CD_Vector::operator*(float right)
{
	return CD_Vector(x * right, y * right);
}