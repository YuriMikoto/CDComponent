#pragma once

struct CD_Vector
{
	CD_Vector()
	{

	}

	CD_Vector(float xPos, float yPos)
	{
		x = xPos;
		y = yPos;
	}

	void operator=(CD_Vector right)
	{
		x = right.x;
		y = right.y;
	}

	float x;
	float y;
};