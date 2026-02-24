#include "../lib/raylib/src/raylib.h"
#include "../TriEngine/include/TriEngine.h"
#include "../TriEngine/include/TriGroup.h"
#include <string>
#include <iostream>
#define SPEED 300.0
#define	SPRITE_SIZE 32
#define SPRITE_Y SPRITE_SIZE * 10
#define SPRITE_X SPRITE_SIZE * 10
#define SPRITES_PATH "assets/sprites/"
#define SOUNDS_PATH "assets/sounds/"
#define MUSICS_PATH "assets/musics/"
#define PLAYER_SPEED 200



// int main()
// {
// 	InitWindow(720, 480, "test");
// 	// Rectangle rectangleA{-30, -30, 20, 20};
// 	// Rectangle rectangleB{-30, 30, 20, 20};
// 	// Rectangle rectangleC{30, 30, 20, 20};
// 	// Rectangle rectangleD{30, -30, 20, 20};
// 	// Tri::camera().setPosition({0,0});
// 	while (!WindowShouldClose())
// 	{
// 		// std::cout << "coucou" << std::endl;
// 		DrawRectangle(50,50,50,50,RED);
// 		// drawRectangleCamera(rectangleA, 1.0f, GRAY);
// 		// drawRectangleCamera(rectangleB, 1.0f, GRAY);
// 		// drawRectangleCamera(rectangleC, 1.0f, GRAY);
// 		// drawRectangleCamera(rectangleD, 1.0f, GRAY);
// 	}
// 	CloseWindow();
// 	return (0);
// }

int main()
{
	Tri::Engine engine(800, 450, "basic window");
	Tri::Group	background({-100,-100,200,200});
	background.cameraSpeed = 0.5f;
	Tri::Group	mainPlan({-100,-100,200,200});
	Rectangle 	rectangleA{-40, -40, 20, 20};
	background.addRectangle(&rectangleA, GRAY);
	mainPlan.addRectangle(&rectangleA, BLUE);
	Rectangle 	rectangleB{-40, 20, 20, 20};
	background.addRectangle(&rectangleB, GRAY);
	mainPlan.addRectangle(&rectangleB, BLUE);
	Rectangle 	rectangleC{20, 20, 20, 20};
	background.addRectangle(&rectangleC, GRAY);
	mainPlan.addRectangle(&rectangleC, BLUE);
	Rectangle 	rectangleD{20, -40, 20, 20};
	background.addRectangle(&rectangleD, GRAY);
	mainPlan.addRectangle(&rectangleD, BLUE);
	Vector2		camPosition{0,0};
	Tri::AnimatedSprite	sprite(static_cast<std::string>(SPRITES_PATH) + static_cast<std::string>("spritesheet.png"));
	unsigned int	frameSetIndex = sprite.addFrameSet({0,0,SPRITE_SIZE,SPRITE_SIZE}, 11, {0,0}, 12.0f, {
		{{0,0,SPRITE_SIZE,SPRITE_SIZE}},
		{{0,0,SPRITE_SIZE,SPRITE_SIZE}},
		{{0,0,SPRITE_SIZE,SPRITE_SIZE}},
		{{0,0,SPRITE_SIZE,SPRITE_SIZE}},
		{{0,0,SPRITE_SIZE,SPRITE_SIZE}},
		{{0,0,SPRITE_SIZE,SPRITE_SIZE}},
		{{0,0,SPRITE_SIZE,SPRITE_SIZE}},
		{{0,0,SPRITE_SIZE,SPRITE_SIZE}},
		{{0,0,SPRITE_SIZE,SPRITE_SIZE}},
		{{0,0,SPRITE_SIZE,SPRITE_SIZE}},
		{{0,0,SPRITE_SIZE,SPRITE_SIZE}}
	});
	sprite.getFrameSet(frameSetIndex).setOriginToCenter();
	// sprite.getFrameSet().setCameraSpeed(0.9f);
	Tri::Object		obj(sprite, {0,0});
	Tri::camera().setPosition(camPosition);
	engine.loop([&]{
		// std::cout << "coucou" << std::endl;
		camPosition.y = obj.position.y;
		if (IsKeyDown(KEY_UP))
		{
			obj.position.y -= PLAYER_SPEED * GetFrameTime();
			if (mainPlan.checkGroupCollisionAll(obj))
				obj.position.y = camPosition.y;
		}
		else if (IsKeyDown(KEY_DOWN))
		{
			obj.position.y += PLAYER_SPEED * GetFrameTime();
			if (mainPlan.checkGroupCollisionAll(obj))
				obj.position.y = camPosition.y;
		}
		camPosition.x = obj.position.x;
		if (IsKeyDown(KEY_RIGHT))
		{
			obj.position.x += PLAYER_SPEED * GetFrameTime();
			if (mainPlan.checkGroupCollisionAll(obj))
				obj.position.x = camPosition.x;
		}
		else if (IsKeyDown(KEY_LEFT))
		{
			obj.position.x -= PLAYER_SPEED * GetFrameTime();
			if (mainPlan.checkGroupCollisionAll(obj))
				obj.position.x = camPosition.x;
		}
		Tri::camera().setPosition(camPosition);
		BeginDrawing();
		ClearBackground(WHITE);
		background.draw();
		mainPlan.draw();
		obj.draw();
		EndDrawing();
	});
	return (0);
}

// int main()
// {
// 	unsigned int	n = 0;
// 	float			x = 400;
// 	float			y = 225;
// 	std::string nString;
// 	int			gamepad = 0;
// 	Sound	sfx;
// 	Music	bo;
// 	Vector2	tmpPosition;
// 	// Rectangle	tmpRectangle;
// 	Rectangle hitTestBox = {400, 400, 100, 100};
// 	std::string	tmpStr;
// 	Tri::Engine engine(800, 450, "raylib [core] example - basic window");
// 	Vector2 spritePosition = (Vector2){static_cast<float>(GetScreenWidth() / 2.0), static_cast<float>(GetScreenHeight() / 2.0)};
// 	Tri::camera().setPosition(spritePosition);
// 	tmpStr = (std::string)((std::string)SPRITES_PATH + (std::string)"spritesheet.png");
// 	// spritesheet = LoadTexture(tmpStr.c_str());
// 	Tri::AnimatedSprite	sprites(tmpStr.c_str(), 5.0);
// 	Tri::Object obj(sprites, spritePosition);
// 	Tri::Object obj2(sprites, (Vector2){100.0, 100.0});
// 	unsigned int	spriteIndex = sprites.addFrameSet((Rectangle){0, 0, SPRITE_SIZE, SPRITE_SIZE}, 11, {0, 0}, 24, {
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}},
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}},
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}},
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}},
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}},
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}},
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}},
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}},
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}},
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}},
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}}
// 	});
// 	sprites.getFrameSet(spriteIndex).setOriginToCenter();
// 	spriteIndex = sprites.addFrameSet((Rectangle){0, SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE}, 11, {0, 0}, 12, {
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}, {5, 5, 25, 10}},
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}, {5, 5, 25, 10}},
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}, {5, 5, 25, 10}},
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}, {5, 5, 25, 10}},
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}, {5, 5, 25, 10}},
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}, {5, 5, 25, 10}},
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}, {5, 5, 25, 10}},
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}, {5, 5, 25, 10}},
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}, {5, 5, 25, 10}},
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}, {5, 5, 25, 10}},
// 		{{SPRITE_SIZE / 4.0, SPRITE_SIZE / 4.0, SPRITE_SIZE / 2.0, SPRITE_SIZE / 2.0}, {5, 5, 25, 10}}
// 	});
// 	sprites.getFrameSet(spriteIndex).setOriginToCenter();
// 	tmpStr = (std::string)((std::string)SOUNDS_PATH + (std::string)"Notif2.wav");
// 	sfx = LoadSound(tmpStr.c_str());
// 	tmpStr = (std::string)((std::string)MUSICS_PATH + (std::string)"LvlUp 2026 Soundtrack.wav");
// 	bo = LoadMusicStream(tmpStr.c_str());
// 	PlayMusicStream(bo);
// 	// if (!spritesheet)
// 	// {
// 	// 	std::cerr << "spritesheet not loaded" << std::endl;
// 	// 	CloseWindow();
// 	// 	return (1);
// 	// }
// 	// SetWindowState(FLAG_WINDOW_RESIZABLE);
//     engine.loop([&]{
// 		UpdateMusicStream(bo);
// 		if (IsKeyPressed(KEY_F))
// 		{
// 			PlaySound(sfx);
// 			ToggleFullscreen();
// 		}
// 		if ((IsKeyPressed(KEY_D) || IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))/* && selectSpriteX < SPRITE_X*/)
// 			/*selectSpriteX += SPRITE_SIZE*/ obj.getSprite().getFrameSet(spriteIndex)++;
// 		if ((IsKeyPressed(KEY_S) || IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN)))
// 			sprites++;
// 		if ((IsKeyPressed(KEY_A) || IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_LEFT))/* && selectSpriteX > 0*/)
// 			/*selectSpriteX -= SPRITE_SIZE*/ obj.getSprite().getFrameSet(spriteIndex)--;
// 		if ((IsKeyPressed(KEY_W) || IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_UP)))
// 			sprites--;
// 		if ((IsKeyDown(KEY_DOWN) || GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y) > 0.1) && (int)y < GetScreenHeight() - 40)
// 			obj.position.y += GetFrameTime() * SPEED;
// 		if ((IsKeyDown(KEY_RIGHT) || GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X) > 0.1) && (int)x < GetScreenWidth() - 40)
// 			obj.position.x += GetFrameTime() * SPEED;
// 		if ((IsKeyDown(KEY_UP) || GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y) < -0.1) && (int)y > 40)
// 			obj.position.y -= GetFrameTime() * SPEED;
// 		if ((IsKeyDown(KEY_LEFT) || GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X) < -0.1) && (int)x > 40)
// 			obj.position.x -= GetFrameTime() * SPEED;
// 		nString = std::to_string(n);
//         BeginDrawing();
// 			if (IsGamepadAvailable(gamepad))
// 			{
// 				tmpPosition = Tri::convertCamera({static_cast<float>(GetScreenWidth() - 300), static_cast<float>(GetScreenHeight() - 40)}, 1.0f);
// 				DrawText("Gamepad available", tmpPosition.x, tmpPosition.y, 30, LIGHTGRAY);
// 			}
//             ClearBackground(RAYWHITE);
// 			tmpPosition = Tri::convertCamera({x, y}, 1.0f);
// 			DrawCircle(tmpPosition.x, tmpPosition.y, 40, {255,0,0,127});
// 			// Rectangle	source = {(float)selectSpriteX, (float)selectSpriteY, SPRITE_SIZE, SPRITE_SIZE};
// 			// Rectangle	dest = {400, 225, SPRITE_SIZE * 3, SPRITE_SIZE * 3};
// 			tmpPosition = Tri::convertCamera({20.0f, 20.0f}, 1.0f);
// 			DrawTexture(obj.getSprite().getSpriteSheet(), tmpPosition.x, tmpPosition.y, WHITE);
// 			if (obj.checkCollisionRec(hitTestBox))
// 				DrawRectangleRec(hitTestBox, RED);
// 			else
// 				DrawRectangleRec(hitTestBox, BLUE);
// 			obj.draw();
// 			obj2.draw();
// 			if (obj.checkCollisionObj(obj2))
// 				DrawText("OBJECT COLISION", (GetScreenWidth() / 2) - 70, (GetScreenHeight() / 2) - 10, 30, RED);
// 			// hitboxView = obj.getSprite().getFrameSet().getFrameHitboxes()[0];
// 			// hitboxView.x += spritePosition.x - obj.getSprite().getFrameSet().getOrigin().x;
// 			// hitboxView.y += spritePosition.y - obj.getSprite().getFrameSet().getOrigin().y;
// 			// DrawRectangleRec(hitboxView, {255, 100, 100, 127});
// 			// DrawTexturePro(spritesheet, source, dest, (Vector2){SPRITE_SIZE * 3 / 2, SPRITE_SIZE * 3 / 2}, 0, WHITE);
//             //DrawText(nString.c_str(), 400, 225, 50, LIGHTGRAY);
//         EndDrawing();
// 		++n;
//     });
// 	StopMusicStream(bo);
// 	// CloseAudioDevice();
//     // CloseWindow();

//     return 0;
// }

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
