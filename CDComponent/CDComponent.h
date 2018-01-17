#pragma once
#include "CDShapes.h"
#include "CDVector.h"
#include <math.h>
#include <vector>

class CD_CollisionManager
{
public:
	/*//Vector of all shapes. 
	//Each CD_CollisionManager object has its own group of shapes and will check between all of them for any collision.
	//They will not, however, check for collisions between objects in its own vector and objects in another's.
	//This can be used to one's advantage; if there are specific objects you don't want to allow collision between, you could associate them with different managers.
	std::vector<CD_Shape> shapes;

	/// <summary>
	/// Collision manager update should be called in the game loop's update function, or wherever appropriate.
	/// It will iterate through the list of shapes associated with the current collision manager, and check for any collision between them.
	/// This is used to check on every object in the list. If you want to check specific objects, use CheckCollision(...).
	/// </summary>
	void Update()
	{

	}

	/// <summary>
	/// Add a shape to the vector.
	/// </summary>
	/// <param name="shape">The shape to be added. This can be any subclass of CD_Shape; CD_Circle, CD_Rect or CD_Polygon.</param>
	void AddShape(CD_Shape shape)
	{
		shapes.push_back(shape);
	}

	std::vector<CD_Shape> GetShapes()
	{
		return shapes;
	}

	/// <summary>
	/// Remove a shape from the vector. No idea how to do that, but it seems logical.
	/// </summary>
	void RemoveShape()
	{
	
	}*/

	/// <summary>
	/// Check for collision between two circles.
	/// Simple collision detection using the distance between the radii.
	/// </summary>
	/// <param name="a">Circle shape.</param>
	/// <param name="b">Circle shape.</param>
	/// <returns>True if a collision occurs, false otherwise.</returns>
	bool CheckCollision(CD_Circle a, CD_Circle b)
	{
		float distance = sqrt(((a.GetPosition().x - b.GetPosition().x) * (a.GetPosition().x - b.GetPosition().x))
			+ ((a.GetPosition().y - b.GetPosition().y) * (a.GetPosition().y - b.GetPosition().y)));
		if (distance <= (a.GetRadius() + b.GetRadius()) / 2)
		{//If they're touching or intersecting, respond. Otherwise, do nothing. 
			return true;
		}
		return false;
	}

	/// <summary>
	/// Check for collision between two rectangles.
	/// Simple collision detection using Axis-Aligned Bounding Boxes.
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns>True if a collision occurs, false otherwise.</returns>
	bool CheckCollision(CD_Rect a, CD_Rect b)
	{
		if (a.GetPosition().x + a.GetWidth() >= b.GetPosition().x &&
			a.GetPosition().x <= b.GetPosition().x + b.GetWidth() &&
			a.GetPosition().y + a.GetHeight() >= b.GetPosition().y &&
			a.GetPosition().y <= b.GetPosition().y + b.GetHeight())
		{//If they're touching or intersecting, respond. Otherwise, do nothing.
			return true;
		}
		return false;
	}

	/// <summary>
	/// Check for collision between two different shapes.
	/// Advanced collision detection using the Separating Axis Theorem.
	/// Parallel function to CheckCollision(CD_Circle a, CD_Rect b); same effect with different argument permutation.
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns>True if a collision occurs, false otherwise.</returns>
	bool CheckCollision(CD_Rect a, CD_Circle b)
	{
		return false;
	}

	/// <summary>
	/// Check for collision between two different shapes.
	/// Advanced collision detection using the Separating Axis Theorem.
	/// Parallel function to CheckCollision(CD_Rect a, CD_Circle b); same effect with different argument permutation.
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns>True if a collision occurs, false otherwise.</returns>
	bool CheckCollision(CD_Circle a, CD_Rect b)
	{
		return false;
	}

	/// <summary>
	/// Check for collision between two polygons.
	/// Advanced collision detection using the Separating Axis Theorem.
	/// Does not expect concave polygons; expect inaccuracies if using them.
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns>True if a collision occurs, false otherwise.</returns>
	bool CheckCollision(CD_Polygon a, CD_Polygon b)
	{
		return false;
	}

	/// <summary>
	/// Check for collision between two different shapes.
	/// Advanced collision detection using the Separating Axis Theorem.
	/// Parallel function to CheckCollision(CD_Circle a, CD_Polygon b); same effect with different argument permutation.
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns>True if a collision occurs, false otherwise.</returns>
	bool CheckCollision(CD_Polygon a, CD_Circle b)
	{
		return false;
	}

	/// <summary>
	/// Check for collision between two different shapes.
	/// Advanced collision detection using the Separating Axis Theorem.
	/// Parallel function to CheckCollision(CD_Polygon a, CD_Circle b); same effect with different argument permutation.
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns>True if a collision occurs, false otherwise.</returns>
	bool CheckCollision(CD_Circle a, CD_Polygon b)
	{
		return false;
	}

	/// <summary>
	/// Check for collision between two different shapes.
	/// Advanced collision detection using the Separating Axis Theorem.
	/// Parallel function to CheckCollision(CD_Rect a, CD_Polygon b); same effect with different argument permutation.
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns>True if a collision occurs, false otherwise.</returns>
	bool CheckCollision(CD_Polygon a, CD_Rect b)
	{
		return false;
	}

	/// <summary>
	/// Check for collision between two different shapes.
	/// Advanced collision detection using the Separating Axis Theorem.
	/// Parallel function to CheckCollision(CD_Polygon a, CD_Rect b); same effect with different argument permutation.
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns>True if a collision occurs, false otherwise.</returns>
	bool CheckCollision(CD_Rect a, CD_Polygon b)
	{
		return false;
	}

	//Per-Pixel Collision - Will I even get the chance to do this?
	//bool PerPixelCollision();

	//Collision Response?
};