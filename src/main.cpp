#include "RealVector.hpp"
#include "raylib.h"
#include "config.hpp"
#include "Boid.hpp"
#include <stdlib.h>
#include <time.h>
#include <vector>
using std::vector;
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

// TODO: Figure out how to avoid needing to use the raylib template repo every time, see https://youtu.be/8o-d9WUsdhs?t=323 and -lraylib, potentially also the .vscode folder

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	// SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Boidular");
	SetTargetFPS(TARGET_FPS); // Program does not want to actually go for 120FPS if FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI flags are set, caps at 60 instead

	// TODO: Adjut factors here!
	double turn_factor = 0.8, avoidance_factor = 0.1, matching_factor = 0.05, centering_factor = 0.0005;
	float turn_padding = 120, min_speed = 6, max_speed = 12;
	float danger_zone = 15, sight_zone = 40, size = 10;

	srand(time(NULL));
	vector<Boid> boids;
	for (int i = 0; i < 100; i++){
		float vx =  rand()%2 ? 1 : -1;
		float vy =  rand()%2 ? 1 : -1;

		boids.push_back(Boid(rand()%SCREEN_WIDTH, rand()%SCREEN_HEIGHT, vx, vy, danger_zone, sight_zone, size)); // Creates a vector of a lot of boids with random positions and initial velocity
	}
	Boid boid(100, 100, 1, 1, 15, 40, 10);


	RealVector player(0, 0);
	float player_radius = 40.0f;

	SearchAndSetResourceDir("resources");

	Texture wabbit = LoadTexture("wabbit_alpha.png");

	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);
		player.x = GetMouseX();
		player.y = GetMouseY();
		// DrawCircle(player.x, player.y, player_radius, RED);
		DrawTexture(wabbit, player.x-20, player.y-20, RED);

		for (int i = 0; i < boids.size(); i++){
			alter_boid_path(boids, i, avoidance_factor, matching_factor, centering_factor);

			RealVector diff = boids[i].position.sub(player);
			if (diff.getMag() < boids[i].sight_zone + player_radius) {
				boids[i].velocity = boids[i].velocity.add(diff);
				boids[i].color = WHITE;
			} else {
				boids[i].color = PINK;
			}

			limit_speed(boids[i], min_speed, max_speed);
			bound_boid(boids[i], turn_factor, turn_padding, SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		for (int i = 0; i < boids.size(); i++){
			boids[i].move_boid();
			boids[i].show_boid();
		}

		DrawFPS(0, 0);

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	CloseWindow();
	return 0;
}
