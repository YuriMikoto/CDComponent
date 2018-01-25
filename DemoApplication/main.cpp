using namespace std;
#include <iostream>
#include <SDL.h>
#include "CD_Component.h"

int appstate = 0;
enum AppState {
	MAIN_MENU,
	RECTS_AABB,
	CIRCLES_RADII,
	RECT_CIRCLE_SAT,
	POLYGONS_SAT
};

//Creates shapes to test with.
//Rectangles r1 and r2 are used in AABB testing; r3 is used with c3 in Rect-Circle collision.
CD_Rect r1, r2, r3;
//Circles c1 and c2 are used in circle testing; c3 is used with r3 in Rect-Circle collision.
CD_Circle c1, c2, c3;
//Polygons p1 and p2 are used in polygon testing. Naturally.
CD_Polygon p1, p2;

CD_CollisionManager cm;

/// <summary>
/// Starts up scene 1, Rect-Rect collision. 
/// </summary>
void initializeScene1()
{
	appstate = 1;
	r1 = CD_Rect(CD_Vector(0.0f, 0.0f));
	r2 = CD_Rect(CD_Vector(6.0f, 0.0f));
}

/// <summary>
/// Starts up scene 2, Circle-Circle collision.
/// </summary>
void initializeScene2()
{
	appstate = 2;
	c1 = CD_Circle(CD_Vector(5.0f, 5.0f));
	c2 = CD_Circle(CD_Vector(11.0f, 5.0f));
}

/// <summary>
/// Starts up scene 3, Rect-Circle collision.
/// </summary>
void initializeScene3()
{
	appstate = 3;
	r3 = CD_Rect(CD_Vector(0.0f, 0.0f));
	c3 = CD_Circle(CD_Vector(11.0f, 5.0f));
}
/// <summary>
/// Starts up scene 4, Polygon-Polygon collision.
/// </summary>
void initializeScene4()
{
	appstate = 4;
	//Creates a polygon. This makes a triangle that's as close to equilateral as I cared to make it. Not that it matters much.
	std::vector<CD_Vector> p1Verts = {
	CD_Vector(0.0f, 0.0f),
	CD_Vector(2.5f, 4.33f),
	CD_Vector(-2.5f, 4.33f)
	};
	p1 = CD_Polygon(CD_Vector(2.5f, 2.5f), p1Verts);

	//Here's another way of writing it that does the same thing, but a rectangle this time.
	p2 = CD_Polygon(CD_Vector(8.5f, 2.5f), std::vector<CD_Vector> {
		CD_Vector(-2.5f, -2.5f),
		CD_Vector(2.5f, -2.5f),
		CD_Vector(2.5f, 2.5f),
		CD_Vector(-2.5f, 2.5f)
	});
}

/// <summary>
/// Prints the positions and details of game objects in the console. Refreshes each time this data changes to make it more easily readable.
/// </summary>
void showConsole()
{
	//Display console.
	if (appstate == MAIN_MENU)
	{
		system("CLS");
		cout << "Please select the Demo App window and press one of the following number keys to open a feature." << endl
			<< "1: Rectangles using AABB" << endl
			<< "2: Circles using radii" << endl
			<< "3: Rectangle and circle using SAT" << endl
			<< "4: Complex polygons using SAT" << endl << endl
			<< "You may return to this menu at any time during a feature test by pressing the ESC key." << endl
			<< "Alternatively, you may press ESC now to close this program entirely." << endl;
	}
	else if (appstate == RECTS_AABB)
	{
		system("CLS");
		cout << "R1 Position: (" << r1.GetPosition().x << ", " << r1.GetPosition().y << ");" << endl
			<< "R1 Dimensions: " << r1.GetWidth() << " units width, " << r1.GetHeight() << " units height." << endl << endl
			<< "R2 Position: (" << r2.GetPosition().x << ", " << r2.GetPosition().y << ");" << endl
			<< "R2 Dimensions: " << r2.GetWidth() << " units width, " << r2.GetHeight() << " units height." << endl << endl;
		if (cm.CheckCollision(r1, r2))
		{
			cout << "Collision detected." << endl;
		}
	}
	else if (appstate == AppState::CIRCLES_RADII)
	{
		system("CLS");
		cout << "C1 Position: (" << c1.GetPosition().x << ", " << c1.GetPosition().y << ");" << endl
			<< "C1 Radius: " << c1.GetRadius() << " units." << endl << endl
			<< "C2 Position: (" << c2.GetPosition().x << ", " << c2.GetPosition().y << ");" << endl
			<< "C2 Radius: " << c2.GetRadius() << " units." << endl << endl;
		if (cm.CheckCollision(c1, c2))
		{
			cout << "Collision detected." << endl;
		}
	}
	else if (appstate == AppState::RECT_CIRCLE_SAT)
	{
		system("CLS");
		cout << "R3 Position: (" << r3.GetPosition().x << ", " << r3.GetPosition().y << ");" << endl
			<< "R3 Dimensions: " << r3.GetWidth() << " units width, " << r3.GetHeight() << " units height." << endl << endl
			<< "C3 Position: (" << c3.GetPosition().x << ", " << c3.GetPosition().y << ");" << endl
			<< "C3 Radius: " << c3.GetRadius() << " units." << endl << endl;
		if (cm.CheckCollision(r3, c3))
		{
			cout << "Collision detected." << endl;
		}
	}
	else if (appstate == AppState::POLYGONS_SAT)
	{
		system("CLS");

		cout << "P1 Position: (" << p1.GetPosition().x << ", " << p1.GetPosition().y << ");" << endl
			<< "P1 Vertices: {" << endl;
		for (unsigned int i = 0; i < p1.GetVertices().size(); i++)
		{
			cout << "(" << p1.GetVertices()[i].x + p1.GetPosition().x << ", " << p1.GetVertices()[i].y + p1.GetPosition().y << ");" << endl;
		}

		cout << endl << "P2 Position: (" << p2.GetPosition().x << ", " << p2.GetPosition().y << ");" << endl
			<< "P2 Vertices: {" << endl;
		for (unsigned int i = 0; i < p2.GetVertices().size(); i++)
		{
			cout << "(" << p2.GetVertices()[i].x + p2.GetPosition().x << ", " << p2.GetVertices()[i].y + p2.GetPosition().y << ");" << endl;
		}

		if (cm.CheckCollision(p1, p2))
		{
			cout << "Collision detected." << endl;
		}
	}
}

//Found this here: https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
//draw one quadrant arc, and mirror the other 4 quadrants
void sdl_ellipse(SDL_Renderer* r, int x0, int y0, int radiusX, int radiusY)
{
	float pi = 3.14159265358979323846264338327950288419716939937510;
	float pih = pi / 2.0; //half of pi

						  //drew  28 lines with   4x4  circle with precision of 150 0ms
						  //drew 132 lines with  25x14 circle with precision of 150 0ms
						  //drew 152 lines with 100x50 circle with precision of 150 3ms
	const int prec = 27; // precision value; value of 1 will draw a diamond, 27 makes pretty smooth circles.
	float theta = 0;     // angle that will be increased each loop

						 //starting point
	int x = (float)radiusX * cos(theta);//start point
	int y = (float)radiusY * sin(theta);//start point
	int x1 = x;
	int y1 = y;

	//repeat until theta >= 90;
	float step = pih / (float)prec; // amount to add to theta each time (degrees)
	for (theta = step; theta <= pih; theta += step)//step through only a 90 arc (1 quadrant)
	{
		//get new point location
		x1 = (float)radiusX * cosf(theta) + 0.5; //new point (+.5 is a quick rounding method)
		y1 = (float)radiusY * sinf(theta) + 0.5; //new point (+.5 is a quick rounding method)

												 //draw line from previous point to new point, ONLY if point incremented
		if ((x != x1) || (y != y1))//only draw if coordinate changed
		{
			SDL_RenderDrawLine(r, x0 + x, y0 - y, x0 + x1, y0 - y1);//quadrant TR
			SDL_RenderDrawLine(r, x0 - x, y0 - y, x0 - x1, y0 - y1);//quadrant TL
			SDL_RenderDrawLine(r, x0 - x, y0 + y, x0 - x1, y0 + y1);//quadrant BL
			SDL_RenderDrawLine(r, x0 + x, y0 + y, x0 + x1, y0 + y1);//quadrant BR
		}
		//save previous points
		x = x1;//save new previous point
		y = y1;//save new previous point
	}
	//arc did not finish because of rounding, so finish the arc
	if (x != 0)
	{
		x = 0;
		SDL_RenderDrawLine(r, x0 + x, y0 - y, x0 + x1, y0 - y1);//quadrant TR
		SDL_RenderDrawLine(r, x0 - x, y0 - y, x0 - x1, y0 - y1);//quadrant TL
		SDL_RenderDrawLine(r, x0 - x, y0 + y, x0 - x1, y0 + y1);//quadrant BL
		SDL_RenderDrawLine(r, x0 + x, y0 + y, x0 + x1, y0 + y1);//quadrant BR
	}
}

/// <summary>
/// Draw the current scene's shapes on screen.
/// </summary>
/// <param name="renderer">Renderer to draw on.</param>
void render(SDL_Renderer *renderer)
{
	//Clear the screen.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//Draw shapes in white.
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	//Draw the shapes from the current scene.
	if (appstate == 1)
	{
		SDL_Point points1[5] = {
			{ (r1.GetPosition().x) * 10, (r1.GetPosition().y) * 10 },
			{ (r1.GetPosition().x + r1.GetWidth()) * 10, (r1.GetPosition().y) * 10 },
			{ (r1.GetPosition().x + r1.GetWidth()) * 10, (r1.GetPosition().y + r1.GetHeight()) * 10 },
			{ (r1.GetPosition().x) * 10, (r1.GetPosition().y + r1.GetHeight()) * 10 },
			{ (r1.GetPosition().x) * 10, (r1.GetPosition().y) * 10 },
		};
		SDL_RenderDrawLines(renderer, points1, 5);

		SDL_Point points2[5] = {
			{ (r2.GetPosition().x) * 10, (r2.GetPosition().y) * 10 },
			{ (r2.GetPosition().x + r2.GetWidth()) * 10, (r2.GetPosition().y) * 10 },
			{ (r2.GetPosition().x + r2.GetWidth()) * 10, (r2.GetPosition().y + r2.GetHeight()) * 10 },
			{ (r2.GetPosition().x) * 10, (r2.GetPosition().y + r2.GetHeight()) * 10 },
			{ (r2.GetPosition().x) * 10, (r2.GetPosition().y) * 10 },
		};
		SDL_RenderDrawLines(renderer, points2, 5);
	}
	else if (appstate == 2)
	{
		sdl_ellipse(renderer, c1.GetPosition().x * 10, c1.GetPosition().y * 10, c1.GetRadius() * 10, c1.GetRadius() * 10);
		sdl_ellipse(renderer, c2.GetPosition().x * 10, c2.GetPosition().y * 10, c2.GetRadius() * 10, c2.GetRadius() * 10);
	}
	else if (appstate == 3)
	{
		SDL_Point points[5] = {
			{ (r3.GetPosition().x) * 10, (r3.GetPosition().y) * 10 },
			{ (r3.GetPosition().x + r3.GetWidth()) * 10, (r3.GetPosition().y) * 10 },
			{ (r3.GetPosition().x + r3.GetWidth()) * 10, (r3.GetPosition().y + r3.GetHeight()) * 10 },
			{ (r3.GetPosition().x) * 10, (r3.GetPosition().y + r3.GetHeight()) * 10 },
			{ (r3.GetPosition().x) * 10, (r3.GetPosition().y) * 10 },
		};
		SDL_RenderDrawLines(renderer, points, 5);

		sdl_ellipse(renderer, c3.GetPosition().x * 10, c3.GetPosition().y * 10, c3.GetRadius() * 10, c3.GetRadius() * 10);
	}
	else if (appstate == 4)
	{
		SDL_Point points1[4] = {
			{ (p1.GetPosition().x + p1.GetVertices()[0].x) * 10, (p1.GetPosition().y + p1.GetVertices()[0].y) * 10 },
			{ (p1.GetPosition().x + p1.GetVertices()[1].x) * 10, (p1.GetPosition().y + p1.GetVertices()[1].y) * 10 },
			{ (p1.GetPosition().x + p1.GetVertices()[2].x) * 10, (p1.GetPosition().y + p1.GetVertices()[2].y) * 10 },
			{ (p1.GetPosition().x + p1.GetVertices()[0].x) * 10, (p1.GetPosition().y + p1.GetVertices()[0].y) * 10 }
		};
		SDL_RenderDrawLines(renderer, points1, 4);
		SDL_Point points2[5] = {
			{ (p2.GetPosition().x + p2.GetVertices()[0].x) * 10, (p2.GetPosition().y + p2.GetVertices()[0].y) * 10 },
			{ (p2.GetPosition().x + p2.GetVertices()[1].x) * 10, (p2.GetPosition().y + p2.GetVertices()[1].y) * 10 },
			{ (p2.GetPosition().x + p2.GetVertices()[2].x) * 10, (p2.GetPosition().y + p2.GetVertices()[2].y) * 10 },
			{ (p2.GetPosition().x + p2.GetVertices()[3].x) * 10, (p2.GetPosition().y + p2.GetVertices()[3].y) * 10 },
			{ (p2.GetPosition().x + p2.GetVertices()[0].x) * 10, (p2.GetPosition().y + p2.GetVertices()[0].y) * 10 }
		};
		SDL_RenderDrawLines(renderer, points2, 5);
	}

	SDL_RenderPresent(renderer);
}

/// <summary>
/// Medium between the main() function and all others. Handles user input and also calls to rendering the game screen and console.
/// </summary>
/// <param name="renderer">Renderer to draw on.</param>
void update(SDL_Renderer* renderer)
{
	//Becomes true when any quit input is received; allows the application to quit while true.
	bool quit = false;

	//Handles keyboard events.
	SDL_Event e;

	showConsole();

	while (!quit)
	{
		//Handle input.
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					if (appstate == AppState::MAIN_MENU)
					{
						quit = true;
					}
					else
					{
						appstate = 0;
					}
				}

				if (appstate == AppState::MAIN_MENU)
				{//Menu state - press 1-4 to select a state to switch to.
					switch (e.key.keysym.sym)
					{
					case SDLK_1:
						initializeScene1();
						break;
					case SDLK_2:
						initializeScene2();
						break;
					case SDLK_3:
						initializeScene3();
						break;
					case SDLK_4:
						initializeScene4();
						break;
					}
				}
				else if (appstate == AppState::RECTS_AABB)
				{//Rects state - press the arrow keys to move one of the two rectangles.
					switch (e.key.keysym.sym)
					{
					case SDLK_UP:
						r1.SetPosition(CD_Vector(r1.GetPosition().x, r1.GetPosition().y - 1));
						break;
					case SDLK_DOWN:
						r1.SetPosition(CD_Vector(r1.GetPosition().x, r1.GetPosition().y + 1));
						break;
					case SDLK_LEFT:
						r1.SetPosition(CD_Vector(r1.GetPosition().x - 1, r1.GetPosition().y));
						break;
					case SDLK_RIGHT:
						r1.SetPosition(CD_Vector(r1.GetPosition().x + 1, r1.GetPosition().y));
						break;
					}
				}
				else if (appstate == AppState::CIRCLES_RADII)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_UP:
						c1.SetPosition(CD_Vector(c1.GetPosition().x, c1.GetPosition().y - 1));
						break;
					case SDLK_DOWN:
						c1.SetPosition(CD_Vector(c1.GetPosition().x, c1.GetPosition().y + 1));
						break;
					case SDLK_LEFT:
						c1.SetPosition(CD_Vector(c1.GetPosition().x - 1, c1.GetPosition().y));
						break;
					case SDLK_RIGHT:
						c1.SetPosition(CD_Vector(c1.GetPosition().x + 1, c1.GetPosition().y));
						break;
					}
				}
				else if (appstate == AppState::RECT_CIRCLE_SAT)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_UP:
						r3.SetPosition(CD_Vector(r3.GetPosition().x, r3.GetPosition().y - 1));
						break;
					case SDLK_DOWN:
						r3.SetPosition(CD_Vector(r3.GetPosition().x, r3.GetPosition().y + 1));
						break;
					case SDLK_LEFT:
						r3.SetPosition(CD_Vector(r3.GetPosition().x - 1, r3.GetPosition().y));
						break;
					case SDLK_RIGHT:
						r3.SetPosition(CD_Vector(r3.GetPosition().x + 1, r3.GetPosition().y));
						break;
					}
				}
				else if (appstate == AppState::POLYGONS_SAT)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_UP:
						p1.SetPosition(CD_Vector(p1.GetPosition().x, p1.GetPosition().y - 1));
						break;
					case SDLK_DOWN:
						p1.SetPosition(CD_Vector(p1.GetPosition().x, p1.GetPosition().y + 1));
						break;
					case SDLK_LEFT:
						p1.SetPosition(CD_Vector(p1.GetPosition().x - 1, p1.GetPosition().y));
						break;
					case SDLK_RIGHT:
						p1.SetPosition(CD_Vector(p1.GetPosition().x + 1, p1.GetPosition().y));
						break;
					}
				}
				showConsole();
				render(renderer);
			}
		}
	}
}

/// <summary>
/// Entry point. Also handles player input.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window = SDL_CreateWindow("Demo App", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	update(renderer);

	SDL_Quit();
	return 0;
}