using namespace std;
#include <iostream>
#include <SDL.h>
#include "CDComponent.h"

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

void initializeScene1()
{
	appstate = 1;
	r1 = CD_Rect(CD_Vector(0.0f, 0.0f));
	r2 = CD_Rect(CD_Vector(6.0f, 0.0f));
}

void initializeScene2()
{
	appstate = 2;
	c1 = CD_Circle(CD_Vector(0.0f, 0.0f));
	c2 = CD_Circle(CD_Vector(6.0f, 0.0f));
}

void initializeScene3()
{
	appstate = 3;
	r3 = CD_Rect(CD_Vector(0.0f, 0.0f));
	c3 = CD_Circle(CD_Vector(6.0f, 0.0f));
}

void initializeScene4()
{
	appstate = 4;
	//Creates a polygon.
	std::vector<CD_Vector> p1Verts = {
	CD_Vector(-2.5f, -2.5f),
	CD_Vector(2.5f, -2.5f),
	CD_Vector(2.5f, 2.5f),
	CD_Vector(-2.5f, 2.5f)
	};
	p1 = CD_Polygon(CD_Vector(2.5f, 2.5f), p1Verts);

	p2 = CD_Polygon(CD_Vector(8.5f, 2.5f), std::vector<CD_Vector> {
		CD_Vector(-2.5f, -2.5f),
		CD_Vector(2.5f, -2.5f),
		CD_Vector(2.5f, 2.5f),
		CD_Vector(-2.5f, 2.5f)
	});
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window = SDL_CreateWindow("Demo App", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	//Becomes true when any quit input is received; allows the application to quit while true.
	bool quit = false;

	//Handles keyboard events.
	SDL_Event e;

	CD_CollisionManager cm;
	//cm.AddShape(r1);
	//cm.AddShape(r2);

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
			}
		}

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

			if (cm.CheckCollision(p1, p2))
			{
				cout << "Collision detected." << endl;
			}
		}
	}

	SDL_Quit();
	return 0;
}