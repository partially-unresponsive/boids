#include "raylib.h"
#include "config.hpp"
#include "Boid.hpp"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <cmath>
using std::vector;
// #include "resource_dir.h"	// utility header for SearchAndSetResourceDir

// TODO: Figure out how to avoid needing to use the raylib template repo every time, see https://youtu.be/8o-d9WUsdhs?t=323 and -lraylib, potentially also the .vscode folder

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	// SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Boidular");
	SetTargetFPS(TARGET_FPS); // Program does not want to actually go for 120FPS if FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI flags are set, caps at 60 instead

	double turn_factor = 0.2;
	float turn_padding = 100, min_speed = 3, max_speed = 6;

	float danger_zone = 15, sight_zone = 40, size = 10;

	srand(time(NULL));
	vector<Boid> boids;
	for (int i = 0; i < 100; i++){
		float vx =  rand()%2 ? 1 : -1;
		float vy =  rand()%2 ? 1 : -1;

		boids.push_back(Boid(rand()%SCREEN_WIDTH, rand()%SCREEN_HEIGHT, vx, vy, danger_zone, sight_zone, size));
	}
	Boid boid(100, 100, 1, 1, 15, 40, 10);

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		for (int i = 0; i < boids.size(); i++){
			limit_speed(boids[i], min_speed, max_speed);
			bound_boid(boids[i], turn_factor, turn_padding, SCREEN_WIDTH, SCREEN_HEIGHT);
			boids[i].move_boid();
			boids[i].show_boid();
		}
		

		DrawFPS(0, 0);

		// BEGIN GAY FLAG
		/*
		DrawText("Hello Gaylib", SCREEN_WIDTH/2 - 60,MARGIN/2,20,WHITE);
		int idx = 0;
		Color col;
		for (int x = MARGIN; x < SCREEN_WIDTH - MARGIN; x += 20){
			for (int y = MARGIN; y < SCREEN_HEIGHT - MARGIN; y += 30){
				idx++;
				idx %= 8;
				switch(idx){
					case 0:
						col = RED;
						break;
					case 1:
						col = ORANGE;
						break;
					case 2:
						col = YELLOW;
						break;
					case 3:
						col = GREEN;
						break;
					case 4:
						col = BLUE;
						break;
					case 5:
						col = PURPLE;
						break;
					case 6:
						col = VIOLET;
						break;
					case 7:
						col = WHITE;
						break;
				}
				DrawTexture(wabbit, x, y, col);
			}
		}
		*/ 
		// END GAY FLAG

		// BEGIN TRANS FLAG
		// DrawText("Hello Translib", SCREEN_WIDTH/2 - 60,MARGIN/2,20,WHITE);
		// int idx = 0;
		// Color col;
		// for (int i = 0; i < (int)((SCREEN_WIDTH - 2*MARGIN)/20); i++){
		// 	for (int j = 0; j < 18; j++){
		// 		idx = i % 8;
		// 		switch(idx){
		// 			case 0:
		// 			case 1:
		// 				col = BLUE;
		// 				break;
		// 			case 2:
		// 			case 3:
		// 				col = PINK;
		// 				break;
		// 			case 4:
		// 			case 5:
		// 				col = WHITE;
		// 				break;
		// 			case 6:
		// 			case 7:
		// 				col = PINK;
		// 				break;
		// 		}
		// 		DrawTexture(wabbit, 20*i + MARGIN, 30*j + MARGIN, col);
		// 	}
		// }
		// END TRANS FLAG

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	CloseWindow();
	return 0;
}
