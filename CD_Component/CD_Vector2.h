#pragma once

struct CD_Vector
{
	CD_Vector();
	CD_Vector(float xPos, float yPos);
	void operator=(CD_Vector right);
	CD_Vector operator+(CD_Vector right);
	CD_Vector operator-(CD_Vector right);
	float operator*(CD_Vector right);
	CD_Vector operator*(float right);
	float x;
	float y;
};