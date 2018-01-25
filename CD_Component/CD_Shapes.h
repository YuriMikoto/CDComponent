#include "CD_Vector2.h"
#include <vector>

class CD_Shape
{
public:
	//virtual void SetPosition(CD_Vector newPos) = 0;
};

class CD_Rect : public CD_Shape
{
public:
	CD_Rect();
	CD_Rect(CD_Vector pos, float w = 5, float h = 5);
	void SetPosition(CD_Vector newPos);
	CD_Vector GetPosition();
	void SetDimensions(float newW, float newH);
	float GetWidth();
	float GetHeight();
private:
	CD_Vector position;
	float width;
	float height;
};

class CD_Circle : public CD_Shape
{
public:
	CD_Circle();
	CD_Circle(CD_Vector pos, float rad = 5);
	void SetPosition(CD_Vector newPos);
	CD_Vector GetPosition();
	void SetRadius(float newR);
	float GetRadius();
private:
	CD_Vector position;
	float radius;
};

class CD_Polygon : public CD_Shape
{
public:
	CD_Polygon();
	CD_Polygon(CD_Vector pos, std::vector<CD_Vector> verts);
	void SetPosition(CD_Vector newPos);
	CD_Vector GetPosition();
	std::vector<CD_Vector> GetVertices();
private:
	CD_Vector position;
	std::vector<CD_Vector> vertices;
};