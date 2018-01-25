using namespace std;
#include "CD_Component.h"
#include <assert.h>
#include <iostream>

//Creates shapes to test with.
//Rectangles r1 and r2 are used in AABB testing; r3 is used with c3 in Rect-Circle collision.
CD_Rect r1, r2, r3;
//Circles c1 and c2 are used in circle testing; c3 is used with r3 in Rect-Circle collision.
CD_Circle c1, c2, c3;
//Polygons p1 and p2 are used in polygon testing. Naturally.
CD_Polygon p1, p2;

CD_CollisionManager cm;

int main()
{
	cout << "Initiating Unit Tests." << endl << endl;
	{
		cout << "Testing basic Rect-Rect collision... ";
		//Test Rect-Rect collision.
		r1 = CD_Rect(CD_Vector(1.0f, 0.0f));
		r2 = CD_Rect(CD_Vector(6.0f, 0.0f));

		//Checking horizontal.
		assert(cm.CheckCollision(r1, r2));
		r1.SetPosition(CD_Vector(0.9f, 0.0f));
		assert(!cm.CheckCollision(r1, r2));
		r1.SetPosition(CD_Vector(11.1f, 0.0f));
		assert(!cm.CheckCollision(r1, r2));

		//Checking vertical.
		r1.SetPosition(CD_Vector(6.0f, -5.0f));
		assert(cm.CheckCollision(r1, r2));
		r1.SetPosition(CD_Vector(6.0f, -5.1f));
		assert(!cm.CheckCollision(r1, r2));
		r1.SetPosition(CD_Vector(6.0f, 5.1f));
		assert(!cm.CheckCollision(r1, r2));

		//Checking diagonals.
		r1.SetPosition(CD_Vector(11.0f, 5.0f));
		assert(cm.CheckCollision(r1, r2));
		r1.SetPosition(CD_Vector(11.1f, 5.0f));
		assert(!cm.CheckCollision(r1, r2));
		r1.SetPosition(CD_Vector(11.0f, 5.1f));
		assert(!cm.CheckCollision(r1, r2));

		cout << "OK" << endl;
	}

	{
		cout << "Testing basic Circle-Circle collision... ";
		//Test Circle-Circle collision.
		c1 = CD_Circle(CD_Vector(5.0f, 5.0f));
		c2 = CD_Circle(CD_Vector(11.0f, 5.0f));

		//Checking axis-aligned.
		assert(cm.CheckCollision(c1, c2));
		
		//Checking "corner".
		c1.SetPosition(CD_Vector(12.0f, 4.0f));
		assert(cm.CheckCollision(c1, c2));
		c1.SetPosition(CD_Vector(3.0f, 12.0f));
		assert(!cm.CheckCollision(c1, c2));
		c1.SetPosition(CD_Vector(4.0f, 13.0f));
		assert(!cm.CheckCollision(c1, c2));

		cout << "OK" << endl;
	}

	{
		cout << "Testing SAT-based Rect-Circle collision... ";
		//SAT: Rect-Circle collision.
		r3 = CD_Rect(CD_Vector(0.0f, 0.0f));
		c3 = CD_Circle(CD_Vector(11.0f, 5.0f));

		//Checking horizontal.
		assert(!cm.CheckCollision(r3, c3));
		r3.SetPosition(CD_Vector(1.0f, 2.0f));
		assert(cm.CheckCollision(r3, c3));
		r3.SetPosition(CD_Vector(16.0f, 2.0f));
		assert(cm.CheckCollision(r3, c3));

		//Checking vertical.
		r3.SetPosition(CD_Vector(8.0f, 10.0f));
		assert(cm.CheckCollision(r3, c3));
		r3.SetPosition(CD_Vector(8.0f, -5.0f));
		assert(cm.CheckCollision(r3, c3));

		//Checking diagonal.
		r3.SetPosition(CD_Vector(8.0f, 3.0f));
		assert(cm.CheckCollision(r3, c3));
		r3.SetPosition(CD_Vector(2.0f, 9.0f));
		assert(!cm.CheckCollision(r3, c3));

		cout << "OK" << endl;
	}

	{
		cout << "Testing SAT with simple polygons... ";
		//SAT: Polygons.
		p1 = CD_Polygon(CD_Vector(2.5f, 2.5f), std::vector<CD_Vector> {
			CD_Vector(0.0f, 0.0f),
				CD_Vector(2.5f, 4.33f),
				CD_Vector(-2.5f, 4.33f)
		});
		p2 = CD_Polygon(CD_Vector(8.5f, 2.5f), std::vector<CD_Vector> {
			CD_Vector(-2.5f, -2.5f),
				CD_Vector(2.5f, -2.5f),
				CD_Vector(2.5f, 2.5f),
				CD_Vector(-2.5f, 2.5f)
		});

		assert(!cm.CheckCollision(p1, p2));

		//Check internal.
		p1.SetPosition(CD_Vector(8.5f, 0.5f));
		assert(cm.CheckCollision(p1, p2));

		//Check horizontal and vertical.
		p1.SetPosition(CD_Vector(12.5f, 0.5f));
		assert(cm.CheckCollision(p1, p2));
		p1.SetPosition(CD_Vector(8.5f, 4.5f));
		assert(cm.CheckCollision(p1, p2));

		//Check diagonal.
		p1.SetPosition(CD_Vector(4.5f, 2.5f));
		assert(!cm.CheckCollision(p1, p2));
		p1.SetPosition(CD_Vector(5.5f, 2.5f));
		assert(cm.CheckCollision(p1, p2));
		p1.SetPosition(CD_Vector(4.5f, 1.5f));
		assert(cm.CheckCollision(p1, p2));

		cout << "OK" << endl;
	}

	cout << endl << "All tests complete. Library is fully functional." << endl;
	system("PAUSE");
}