#include "raylib.h"
#include "config.hpp"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Boidular");
	SetTargetFPS(TARGET_FPS);

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");
	
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font

		// BEGIN GAY
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
		*/ // END GAY FLAG

		// START TRANS FLAG
		DrawText("Hello Translib", SCREEN_WIDTH/2 - 60,MARGIN/2,20,WHITE);
		int idx = 0;
		Color col;
		for (int i = 0; i < (int)((SCREEN_WIDTH - 2*MARGIN)/20); i++){
			for (int j = 0; j < 18; j++){
				idx = i % 8;
				switch(idx){
					case 0:
					case 1:
						col = BLUE;
						break;
					case 2:
					case 3:
						col = PINK;
						break;
					case 4:
					case 5:
						col = WHITE;
						break;
					case 6:
					case 7:
						col = PINK;
						break;
				}
				DrawTexture(wabbit, 20*i + MARGIN, 30*j + MARGIN, col);
			}
		}

		// END TRANS FLAG

		// DrawTexture(wabbit, 400, 200, ORANGE);
		// DrawTexture(wabbit, 360, 200, ORANGE);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	UnloadTexture(wabbit);
	CloseWindow();
	return 0;
}
