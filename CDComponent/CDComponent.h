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
	/// <param name="a">First circle shape.</param>
	/// <param name="b">Second circle shape.</param>
	/// <returns>True if a collision occurs, false otherwise.</returns>
	bool CheckCollision(CD_Circle a, CD_Circle b)
	{
		float distance = sqrt(((a.GetPosition().x - b.GetPosition().x) * (a.GetPosition().x - b.GetPosition().x))
			+ ((a.GetPosition().y - b.GetPosition().y) * (a.GetPosition().y - b.GetPosition().y)));
		if (distance <= (a.GetRadius() + b.GetRadius()))
		{//If they're touching or intersecting, respond. Otherwise, do nothing. 
			return true;
		}
		return false;
	}

	/// <summary>
	/// Check for collision between two rectangles.
	/// Simple collision detection using Axis-Aligned Bounding Boxes.
	/// </summary>
	/// <param name="a">First rectangle shape.</param>
	/// <param name="b">Second rectangle shape. </param>
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
	/// <param name="a">Rectangle shape.</param>
	/// <param name="b">Circle shape.</param>
	/// <returns>True if a collision occurs, false otherwise.</returns>
	bool CheckCollision(CD_Rect a, CD_Circle b)
	{
		std::vector<CD_Vector> aVerts;
		std::vector<CD_Vector> axes;

		//Convert rect to polygon, sort of.
		aVerts.push_back(CD_Vector(0, 0));
		aVerts.push_back(CD_Vector(a.GetWidth(), 0));
		aVerts.push_back(CD_Vector(a.GetWidth(), a.GetHeight()));
		aVerts.push_back(CD_Vector(0, a.GetHeight()));

		CD_Polygon aPoly(a.GetPosition(), aVerts);
		//axes = GetAxes(aPoly, axes);

		/*cout << "P1 Position: (" << aPoly.GetPosition().x << ", " << aPoly.GetPosition().y << ");" << endl
			<< "P1 Vertices: {" << endl;
		for (int i = 0; i < aPoly.GetVertices().size(); i++)
		{
			cout << "(" << aPoly.GetVertices()[i].x + aPoly.GetPosition().x << ", " << aPoly.GetVertices()[i].y + aPoly.GetPosition().y << ");" << endl;
		}*/

		//Because a rect's opposite sides are parallel, only need to check two axes of four edges.
		axes.push_back(CD_Vector(1, 0));
		axes.push_back(CD_Vector(0, 1));

		//Go through every axis and check every angle.
		for (int i = 0; i < axes.size(); i++)
		{
			float min1 = std::numeric_limits<float>::infinity();
			float min2 = std::numeric_limits<float>::infinity();
			float max1 = -std::numeric_limits<float>::infinity();
			float max2 = -std::numeric_limits<float>::infinity();

			//Project A's vertices onto the axis and find the object's range.
			for (int j = 0; j < aVerts.size(); j++)
			{
				float projection = axes[i].x * (a.GetPosition().x + aVerts[j].x) + axes[i].y * (a.GetPosition().y + aVerts[j].y);

				if (projection < min1)
				{
					min1 = projection;
				}
				if (projection > max1)
				{
					max1 = projection;
				}
			}

			//Project B's minimum and maximum points onto the axis and find the object's range.
			float circlePosition = axes[i].x * b.GetPosition().x + axes[i].y * b.GetPosition().y;

			float projection = circlePosition - b.GetRadius();
			if (projection < min2)
			{
				min2 = projection;
			}
			if (projection > max2)
			{
				max2 = projection;
			}

			projection = circlePosition + b.GetRadius();
			if (projection < min2)
			{
				min2 = projection;
			}
			if (projection > max2)
			{
				max2 = projection;
			}
			//Check the projections to see if there's a gap between them.
			if (max1 < min2 || max2 < min1)
			{
				//Gap visible from this angle. Definitely not colliding. Return false and cancel the rest of the check.
				return false;
			}
			//Here, we're done with this axis and it's time to check the next one. 
		}
		//If it hasn't found a gap by now, it's time to check the distance between the centre and the nearest vertex.
		//Get the distance between the centre of the circle and each point on the rectangle. Find which one is closest.
		//If the closest vertex is less than (radius) units away, there's a collision.
		//IMPROVEMENT: Project points onto an axis formed between the circle's centre and this closest point and check for a separation there.
		float distance = std::numeric_limits<float>::infinity();
		int nearest = -1;

		for (int l = 0; l < aVerts.size(); l++)
		{
			//I worry that this section is prone to errors. Will test this tomorrow.
			//This seems to be backwards. It's not marking the right vertex as the closest one at all.
			float tempdist = sqrt(((b.GetPosition().x - (a.GetPosition().x + aVerts[l].x)) * (b.GetPosition().x - (a.GetPosition().x + aVerts[l].x)))
				+ ((b.GetPosition().y - (a.GetPosition().y + aVerts[l].y)) * (b.GetPosition().y - (a.GetPosition().y + aVerts[l].y))));

			if (tempdist < distance)
			{//If this vertex is closer than the last one, mark this one as the closest.
				distance = tempdist;
				nearest = l; //Probably not necessary, but keeping a note of this in case.
			}
		}
		cout << nearest << endl;



		if (distance <= b.GetRadius())
		{//Check the distance. If they're close enough, we've checked every axis by now, so there's definitely a collision.
			return true;
		}
		//Otherwise, they're far enough away that there's a gap here too. No collision detected.
		return false;
	}

	/// <summary>
	/// Check for collision between two different shapes.
	/// Advanced collision detection using the Separating Axis Theorem.
	/// Parallel function to CheckCollision(CD_Rect a, CD_Circle b); same effect with different argument permutation.
	/// </summary>
	/// <param name="a">Circle shape.</param>
	/// <param name="b">Rectangle shape.</param>
	/// <returns>True if a collision occurs, false otherwise.</returns>
	bool CheckCollision(CD_Circle a, CD_Rect b)
	{
		return false;
	}

	/// <summary>
	/// Check for collision between two polygons.
	/// Advanced collision detection using the Separating Axis Theorem.
	/// Does not expect concave polygons; expect inaccuracies if using them.
	/// 
	/// I need to clean this up, holy hell.
	/// </summary>
	/// <param name="a">First polygon shape.</param>
	/// <param name="b">Second polygon shape.</param>
	/// <returns>True if a collision occurs, false otherwise.</returns>
	bool CheckCollision(CD_Polygon a, CD_Polygon b)
	{
		//List of axes to set. 
		std::vector<CD_Vector> axes;

		axes = GetAxes(a, axes);
		axes = GetAxes(b, axes);

		//Go through every axis and check every angle.
		for (int i = 0; i < axes.size(); i++)
		{
			float min1 = std::numeric_limits<float>::infinity();
			float min2 = std::numeric_limits<float>::infinity();
			float max1 = -std::numeric_limits<float>::infinity();
			float max2 = -std::numeric_limits<float>::infinity();

			//Project A's vertices onto the axis and find the object's range.
			for (int j = 0; j < a.GetVertices().size(); j++)
			{
				float projection = axes[i].x * (a.GetPosition().x + a.GetVertices()[j].x) + axes[i].y * (a.GetPosition().y + a.GetVertices()[j].y);

				if (projection < min1)
				{
					min1 = projection;
				}
				if (projection > max1)
				{
					max1 = projection;
				}
			}

			//Project B's vertices onto the axis and find the object's range.
			for (int k = 0; k < b.GetVertices().size(); k++)
			{
				float projection = axes[i].x * (b.GetPosition().x + b.GetVertices()[k].x) + axes[i].y * (b.GetPosition().y + b.GetVertices()[k].y);

				if (projection < min2)
				{
					min2 = projection;
				}
				if (projection > max2)
				{
					max2 = projection;
				}
			}

			//Check the projections to see if there's a gap between them.
			if (max1 < min2 || max2 < min1)
			{
				//Gap visible from this angle. Definitely not colliding. Return false and cancel the rest of the check.
				return false;
			}
			//Here, we're done with this axis and it's time to check the next one. 
		}
		//If it hasn't found a gap by now, there is none. 
		return true;
	}

	/// <summary>
	/// Check for collision between two different shapes.
	/// Advanced collision detection using the Separating Axis Theorem.
	/// Parallel function to CheckCollision(CD_Circle a, CD_Polygon b); same effect with different argument permutation.
	/// </summary>
	/// <param name="a">Polygon shape.</param>
	/// <param name="b">Circle shape.</param>
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
	/// <param name="a">Circle shape.</param>
	/// <param name="b">Polygon shape.</param>
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
	/// <param name="a">Polygon shape.</param>
	/// <param name="b">Rectangle shape.</param>
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
	/// <param name="a">Rectangle shape.</param>
	/// <param name="b">Polygon shape.</param>
	/// <returns>True if a collision occurs, false otherwise.</returns>
	bool CheckCollision(CD_Rect a, CD_Polygon b)
	{
		return false;
	}

	//Per-Pixel Collision - Will I even get the chance to do this?
	//bool PerPixelCollision();

	//Collision Response?

private:

	std::vector<CD_Vector> GetAxes(CD_Polygon p, std::vector<CD_Vector> vec)
	{
		//Mark each axis to work with, calculating them from normals of given edges.
		for (int i = 0; i < p.GetVertices().size(); i++)
		{
			CD_Vector point1 = p.GetVertices()[i];
			CD_Vector point2;
			if (i + 1 == p.GetVertices().size())
			{
				point2 = p.GetVertices()[0];
			}
			else
			{
				point2 = p.GetVertices()[i + 1];
			}
			CD_Vector edge = point2 - point1;
			CD_Vector normal = CD_Vector(edge.y, -edge.x);
			vec.push_back(normal);
		}

		return vec;
	}

	bool CheckAxes()
	{

	}
};