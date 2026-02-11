#include "../lib/raylib/src/raylib.h"
#include "../TriEngine/include/TriEngine.h"
#include <string>
#include <iostream>
#define SPEED 300.0
#define	SPRITE_SIZE 32
#define SPRITE_Y SPRITE_SIZE * 10
#define SPRITE_X SPRITE_SIZE * 10
#define SPRITES_PATH "assets/sprites/"
#define SOUNDS_PATH "assets/sounds/"
#define MUSICS_PATH "assets/musics/"

int main()
{
	unsigned int	n = 0;
	float			x = 400;
	float			y = 225;
	unsigned		selectSpriteX = 0;
	unsigned		selectSpriteY = 0;
	std::string nString;
	int			gamepad = 0;
	Texture2D	spritesheet;
	Sound	sfx;
	Music	bo;
	std::string	tmpStr;
	Tri::Engine engine(800, 450, "raylib [core] example - basic window");
	tmpStr = (std::string)((std::string)SPRITES_PATH + (std::string)"spritesheet.png");
	spritesheet = LoadTexture(tmpStr.c_str());
	tmpStr = (std::string)((std::string)SOUNDS_PATH + (std::string)"Notif2.wav");
	sfx = LoadSound(tmpStr.c_str());
	tmpStr = (std::string)((std::string)MUSICS_PATH + (std::string)"GameJam J42 Music Theme.wav");
	bo = LoadMusicStream(tmpStr.c_str());
	PlayMusicStream(bo);
	// if (!spritesheet)
	// {
	// 	std::cerr << "spritesheet not loaded" << std::endl;
	// 	CloseWindow();
	// 	return (1);
	// }
	SetWindowState(FLAG_WINDOW_RESIZABLE);
    engine.loop([&]{
		UpdateMusicStream(bo);
		if (IsKeyPressed(KEY_F))
		{
			// if (IsWindowFullscreen())

			PlaySound(sfx);
			//if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))

			ToggleFullscreen();
		}
		if ((IsKeyPressed(KEY_D) || IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) && selectSpriteX < SPRITE_X)
			selectSpriteX += SPRITE_SIZE;
		if ((IsKeyPressed(KEY_S) || IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) && selectSpriteY < SPRITE_Y)
			selectSpriteY += SPRITE_SIZE;
		if ((IsKeyPressed(KEY_A) || IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) && selectSpriteX > 0)
			selectSpriteX -= SPRITE_SIZE;
		if ((IsKeyPressed(KEY_W) || IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_UP)) && selectSpriteY > 0)
			selectSpriteY -= SPRITE_SIZE;
		if ((IsKeyDown(KEY_DOWN) || GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y) > 0.1) && (int)y < GetScreenHeight() - 40)
			y += GetFrameTime() * SPEED;
		if ((IsKeyDown(KEY_RIGHT) || GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X) > 0.1) && (int)x < GetScreenWidth() - 40)
			x += GetFrameTime() * SPEED;
		if ((IsKeyDown(KEY_UP) || GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y) < -0.1) && (int)y > 40)
			y -= GetFrameTime() * SPEED;
		if ((IsKeyDown(KEY_LEFT) || GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X) < -0.1) && (int)x > 40)
			x -= GetFrameTime() * SPEED;
		nString = std::to_string(n);
        BeginDrawing();
			if (IsGamepadAvailable(gamepad))
				DrawText("Gamepad available", GetScreenWidth() - 300, GetScreenHeight() - 40, 30, LIGHTGRAY);
            ClearBackground(RAYWHITE);
			DrawCircle(x, y, 40, {255,0,0,127});
			Rectangle	source = {(float)selectSpriteX, (float)selectSpriteY, SPRITE_SIZE, SPRITE_SIZE};
			Rectangle	dest = {400, 225, SPRITE_SIZE * 3, SPRITE_SIZE * 3};
			DrawTexture(spritesheet, 20, 20, WHITE);
			DrawTexturePro(spritesheet, source, dest, (Vector2){SPRITE_SIZE * 3 / 2, SPRITE_SIZE * 3 / 2}, 0, WHITE);
            //DrawText(nString.c_str(), 400, 225, 50, LIGHTGRAY);
        EndDrawing();
		++n;
    });
	StopMusicStream(bo);
	// CloseAudioDevice();
    // CloseWindow();

    return 0;
}

// #include <unistd.h> // pour chdir

// // Ajoutez ceci si vous ne l'avez pas déjà
// #if defined(__APPLE__)
// #include <CoreFoundation/CoreFoundation.h>
// #endif

// void ChangeDirectoryToResources() {
// #if defined(__APPLE__)
//     // Récupère le chemin vers le dossier "Resources" interne au .app
//     CFBundleRef mainBundle = CFBundleGetMainBundle();
//     CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
//     char path[PATH_MAX];
    
//     if (CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX)) {
//         // Change le répertoire de travail vers ce dossier
//         chdir(path);
//     }
    
//     CFRelease(resourcesURL);
// #endif
// }

// int main()
// {
// 	unsigned int	n = 0;
// 	float			x = 400;
// 	float			y = 225;
// 	unsigned		selectSpriteX = 0;
// 	unsigned		selectSpriteY = 0;
// 	std::string nString;
// 	int			gamepad = 0;
// 	Texture2D	spritesheet;
// 	Sound	sfx;
// 	Music	bo;
// 	std::string	tmpStr;
// 	ChangeDirectoryToResources();
//     InitWindow(800, 450, "raylib [core] example - basic window");
// 	InitAudioDevice();
// 	tmpStr = (std::string)((std::string)SPRITES_PATH + (std::string)"spritesheet.png");
// 	spritesheet = LoadTexture(tmpStr.c_str());
// 	tmpStr = (std::string)((std::string)SOUNDS_PATH + (std::string)"Notif2.wav");
// 	sfx = LoadSound(tmpStr.c_str());
// 	tmpStr = (std::string)((std::string)MUSICS_PATH + (std::string)"GameJam J42 Music Theme.wav");
// 	bo = LoadMusicStream(tmpStr.c_str());
// 	PlayMusicStream(bo);
// 	// if (!spritesheet)
// 	// {
// 	// 	std::cerr << "spritesheet not loaded" << std::endl;
// 	// 	CloseWindow();
// 	// 	return (1);
// 	// }
// 	SetWindowState(FLAG_WINDOW_RESIZABLE);
//     while (!WindowShouldClose())
//     {
// 		UpdateMusicStream(bo);
// 		if (IsKeyPressed(KEY_F))
// 		{
// 			// if (IsWindowFullscreen())

// 			PlaySound(sfx);
// 			//if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))

// 			ToggleFullscreen();
// 		}
// 		if ((IsKeyPressed(KEY_D) || IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) && selectSpriteX < SPRITE_X)
// 			selectSpriteX += SPRITE_SIZE;
// 		if ((IsKeyPressed(KEY_S) || IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) && selectSpriteY < SPRITE_Y)
// 			selectSpriteY += SPRITE_SIZE;
// 		if ((IsKeyPressed(KEY_A) || IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) && selectSpriteX > 0)
// 			selectSpriteX -= SPRITE_SIZE;
// 		if ((IsKeyPressed(KEY_W) || IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_UP)) && selectSpriteY > 0)
// 			selectSpriteY -= SPRITE_SIZE;
// 		if ((IsKeyDown(KEY_DOWN) || GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y) > 0.1) && (int)y < GetScreenHeight() - 40)
// 			y += GetFrameTime() * SPEED;
// 		if ((IsKeyDown(KEY_RIGHT) || GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X) > 0.1) && (int)x < GetScreenWidth() - 40)
// 			x += GetFrameTime() * SPEED;
// 		if ((IsKeyDown(KEY_UP) || GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y) < -0.1) && (int)y > 40)
// 			y -= GetFrameTime() * SPEED;
// 		if ((IsKeyDown(KEY_LEFT) || GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X) < -0.1) && (int)x > 40)
// 			x -= GetFrameTime() * SPEED;
// 		nString = std::to_string(n);
//         BeginDrawing();
// 			if (IsGamepadAvailable(gamepad))
// 				DrawText("Gamepad available", GetScreenWidth() - 300, GetScreenHeight() - 40, 30, LIGHTGRAY);
//             ClearBackground(RAYWHITE);
// 			DrawCircle(x, y, 40, {255,0,0,127});
// 			Rectangle	source = {(float)selectSpriteX, (float)selectSpriteY, SPRITE_SIZE, SPRITE_SIZE};
// 			Rectangle	dest = {400, 225, SPRITE_SIZE * 3, SPRITE_SIZE * 3};
// 			DrawTexture(spritesheet, 20, 20, WHITE);
// 			DrawTexturePro(spritesheet, source, dest, (Vector2){SPRITE_SIZE * 3 / 2, SPRITE_SIZE * 3 / 2}, 0, WHITE);
//             //DrawText(nString.c_str(), 400, 225, 50, LIGHTGRAY);
//         EndDrawing();
// 		++n;
//     }
// 	StopMusicStream(bo);
// 	CloseAudioDevice();
//     CloseWindow();

//     return 0;
// }
