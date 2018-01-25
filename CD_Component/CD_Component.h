#pragma once
#include "CD_Shapes.h"
#include "CD_Vector2.h"
#include <math.h>
#include <vector>

class CD_CollisionManager
{
public:
	bool CheckCollision(CD_Circle a, CD_Circle b);
	bool CheckCollision(CD_Rect a, CD_Rect b);
	bool CheckCollision(CD_Rect a, CD_Circle b);
	bool CheckCollision(CD_Circle a, CD_Rect b); //Incomplete. Please use the function directly above instead; it's the same but with different argument order.
	bool CheckCollision(CD_Polygon a, CD_Polygon b);
	bool CheckCollision(CD_Polygon a, CD_Circle b); //Incomplete.
	bool CheckCollision(CD_Circle a, CD_Polygon b); //Incomplete.
	bool CheckCollision(CD_Polygon a, CD_Rect b); //Incomplete.
	bool CheckCollision(CD_Rect a, CD_Polygon b); //Incomplete.
private:
	std::vector<CD_Vector> GetAxes(CD_Polygon p, std::vector<CD_Vector> vec);
};