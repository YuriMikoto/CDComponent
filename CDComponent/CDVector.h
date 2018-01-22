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

	CD_Vector operator+(CD_Vector right)
	{
		return CD_Vector(x + right.x, y + right.y);
	}

	CD_Vector operator-(CD_Vector right)
	{
		return CD_Vector(x - right.x, y - right.y);
	}

	float operator*(CD_Vector right)
	{
		return ((x * right.x) + (y * right.y));
	}

	CD_Vector operator*(float right)
	{
		return CD_Vector(x * right, y * right);
	}

	float x;
	float y;
};