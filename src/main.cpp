#include "../lib/raylib/src/raylib.h"
#include "../lib/raylib/src/raymath.h"
#include "../TriEngine/include/TriEngine.h"
#include "../TriEngine/include/TriGroup.h"
#include <string>
#include <iostream>
#include <unordered_map>
#include <cmath> // Pour std::floor
#include <unistd.h>

#define CHUNK_SIZE 1000.0f
#define CHUNK_DENSITY 30
#define ALGUE_PERCENT 60
#define SPEED 300.0f
#define	SPRITE_SIZE 32
#define SPRITE_Y SPRITE_SIZE * 10
#define SPRITE_X SPRITE_SIZE * 10
#define FISH_SPRITE_WIDTH 540
#define FISH_SPRITE_HEIGHT 960
#define SEAWEED_SPRITE_SIZE 128
#define SPRITES_PATH "assets/sprites/"
#define SOUNDS_PATH "assets/sounds/"
#define MUSICS_PATH "assets/musics/"
#define FONTS_PATH "assets/fonts/"
// #define PLAYER_SPEED 200
#define MOUSE_DEAD_MIN 10.0f
#define MAX_DIST_SPEED 350.0f
#define GAMEPAD_DEAD_MIN 0.15f
#define	MAX_LIFE	100.0f
#define	LEVEL_XP_REQUIER 1000.0f
#define	LIFE_GAIN	1.0f
#define	LIFE_LOOZE	2.5f
#define XP_GAIN		20.0f
#define XP_LOOZE	5.0f
#define PLAYER_MIN_SIZE 0.1f
#define WATER_COLOR {0, 53, 90, 60}

enum {
	TYPE_EMPTY,
	TYPE_PLAYER,
	TYPE_ALGUE,
	TYPE_BOTTLE,
	TYPE_FISH
};

enum {
	ANIMATION_SWIM,
	ANIMATION_STOP
};

struct PlayerMovement {
	Vector2	inputVec;
	float	inputMag;
	float	distance;
	Vector2	lastInputVec;
	Vector2 inputPosition;
};

struct PlayerVar
{
	float	life;
	float	xp;
	int		level;
};


void	applyMouvement(Tri::Object &obj, PlayerMovement playerMov) {
	float	dt = GetFrameTime();
	float	currentFriction = std::pow(obj.friction ,dt * TRI_FPS);
	float	currentSpeed;
	if (playerMov.inputMag > 0.0f)
	{
		obj.velocity.x += playerMov.inputVec.x * playerMov.inputMag * obj.accelerationSpeed * dt;
		obj.velocity.y += playerMov.inputVec.y * playerMov.inputMag * obj.accelerationSpeed * dt;
	}
	obj.velocity.x *= currentFriction;
	obj.velocity.y *= currentFriction;
	if (Vector2Length(obj.velocity) < 1.0f && playerMov.inputMag == 0.0f)
		obj.velocity = {0.0f,0.0f};
	currentSpeed = Vector2Length(obj.velocity);
	if (currentSpeed > obj.maxSpeed)
		obj.velocity = Vector2Scale(Vector2Normalize(obj.velocity), obj.maxSpeed);
	if (currentSpeed > 5.0f) {
		obj.rotation = std::atan2(obj.velocity.y, obj.velocity.x) * RAD2DEG + 90.0f;
	}
	// Mouvement X
    obj.position.x += obj.velocity.x * dt;
    // if (collisionGroup.checkGroupCollisionAll(obj)) {
    //     obj.position.x -= obj.velocity.x * dt; // Annule X si on tape un mur
    //     obj.velocity.x = 0.0f; // On tue l'inertie sur cet axe
    // }
    // // Mouvement Y
    obj.position.y += obj.velocity.y * dt;
    // if (collisionGroup.checkGroupCollisionAll(obj)) {
    //     obj.position.y -= obj.velocity.y * dt; // Annule Y si on tape un mur
    //     obj.velocity.y = 0.0f; // On tue l'inertie sur cet axe
    // }
}

struct ChunkManager {
    std::unordered_map<std::string, Tri::Group> chunks;

    // On stocke les deux références !
    Tri::AnimatedSprite* spriteAlgue;
    Tri::AnimatedSprite* spriteBottle;

    // Le constructeur prend maintenant les deux sprites
    ChunkManager(Tri::AnimatedSprite* algue, Tri::AnimatedSprite* bottle) 
        : spriteAlgue(algue), spriteBottle(bottle) {}

    std::string getChunkKey(int x, int y) {
        return std::to_string(x) + "_" + std::to_string(y);
    }

    void update(Vector2 playerPos) {
        int currentChunkX = static_cast<int>(std::floor(playerPos.x / CHUNK_SIZE));
        int currentChunkY = static_cast<int>(std::floor(playerPos.y / CHUNK_SIZE));

        for (int x = currentChunkX - 1; x <= currentChunkX + 1; x++) {
            for (int y = currentChunkY - 1; y <= currentChunkY + 1; y++) {
                
                std::string key = getChunkKey(x, y);

                if (chunks.find(key) == chunks.end()) {
                    Rectangle chunkRect = { x * CHUNK_SIZE, y * CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE };
                    Tri::Group newChunk(chunkRect);

                    // Génération de 8 objets par chunk (tu peux augmenter si c'est trop vide)
                    for (int i = 0; i < CHUNK_DENSITY; i++) {
                        // Position aléatoire
                        float randomX = chunkRect.x + (GetRandomValue(0, 100) / 100.0f) * CHUNK_SIZE;
                        float randomY = chunkRect.y + (GetRandomValue(0, 100) / 100.0f) * CHUNK_SIZE;

                        // 🌟 NOUVEAU : Rotation et Délai d'animation aléatoires
                        float randomRot = (float)GetRandomValue(0, 360);
                        int randomDelay = GetRandomValue(0, 20); // Un chiffre au hasard (le modulo gère le reste !)

                        // 70% Algues, 30% Bouteilles
                        if (GetRandomValue(0, 100) < 70) {
                            // On remplace le '0' par randomDelay, et le '90.0f' par randomRot
                            newChunk.addObject(spriteAlgue, randomDelay, 1.0f, randomRot, {randomX, randomY}, 0.0f, TYPE_ALGUE);
                        } else {
                            newChunk.addObject(spriteBottle, randomDelay, 1.0f, randomRot, {randomX, randomY}, 0.0f, TYPE_BOTTLE);
                        }
                    }
                    chunks[key] = newChunk;
                }
            }
        }

        for (auto it = chunks.begin(); it != chunks.end(); ) {
            int underscorePos = it->first.find('_');
            int cx = std::stoi(it->first.substr(0, underscorePos));
            int cy = std::stoi(it->first.substr(underscorePos + 1));

            if (std::abs(cx - currentChunkX) > 2 || std::abs(cy - currentChunkY) > 2) {
                it = chunks.erase(it);
            } else {
                ++it;
            }
        }
    }

    int eatResources(Tri::Object& player) {
        for (auto& pair : chunks) {
            int type = pair.second.supCollidedObj(player);
            if (type != 0) return type;
        }
        return 0;
    }

    void draw() {
		spriteAlgue->setCameraSpeed(1.0f);
		spriteBottle->setCameraSpeed(1.0f);
        for (auto& pair : chunks) {
            pair.second.draw();
        }
    }
};

struct BackgroundChunkManager {
    std::unordered_map<std::string, Tri::Group> chunks;
    Tri::AnimatedSprite* spriteRef;
    
    float parallaxSpeed;
    float bgScale;

    BackgroundChunkManager(Tri::AnimatedSprite* sprite, float speed, float scale) 
        : spriteRef(sprite), parallaxSpeed(speed), bgScale(scale) {}

    std::string getChunkKey(int x, int y) {
        return std::to_string(x) + "_" + std::to_string(y);
    }

    void update(Vector2 playerPos) {
        Vector2 virtualPos = { playerPos.x * parallaxSpeed, playerPos.y * parallaxSpeed };
        int currentChunkX = static_cast<int>(std::floor(virtualPos.x / CHUNK_SIZE));
        int currentChunkY = static_cast<int>(std::floor(virtualPos.y / CHUNK_SIZE));

        for (int x = currentChunkX - 1; x <= currentChunkX + 1; x++) {
            for (int y = currentChunkY - 1; y <= currentChunkY + 1; y++) {
                std::string key = getChunkKey(x, y);

                if (chunks.find(key) == chunks.end()) {
                    Rectangle chunkRect = { x * CHUNK_SIZE, y * CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE };
                    Tri::Group newChunk(chunkRect);
                    
                    // Génération purement décorative
                    for (int i = 0; i < CHUNK_DENSITY; i++) { // Ou CHUNK_DENSITY si tu l'utilises ici aussi
                        float randomX = chunkRect.x + (GetRandomValue(0, 100) / 100.0f) * CHUNK_SIZE;
                        float randomY = chunkRect.y + (GetRandomValue(0, 100) / 100.0f) * CHUNK_SIZE;
                        
                        // 🌟 NOUVEAU : Rotation et Délai
                        float randomRot = (float)GetRandomValue(0, 360);
                        int randomDelay = GetRandomValue(0, 20);

                        // On passe randomDelay au lieu de 0
                        newChunk.addObject(spriteRef, randomDelay, bgScale, randomRot, {randomX, randomY}, 0.0f, TYPE_EMPTY);
                    }
                    
                    // 🌟 CORRECTION 1 : On set la vitesse APRES avoir ajouté les objets !
                    newChunk.setCameraSpeed(parallaxSpeed);
                    chunks[key] = newChunk;
                }
            }
        }

        for (auto it = chunks.begin(); it != chunks.end(); ) {
            int underscorePos = it->first.find('_');
            int cx = std::stoi(it->first.substr(0, underscorePos));
            int cy = std::stoi(it->first.substr(underscorePos + 1));
            if (std::abs(cx - currentChunkX) > 2 || std::abs(cy - currentChunkY) > 2) {
                it = chunks.erase(it);
            } else {
                ++it;
            }
        }
    }

    void draw() {
        // 🌟 CORRECTION 2 : On force la vitesse du sprite partagé juste avant de dessiner !
        spriteRef->setCameraSpeed(parallaxSpeed);
        for (auto& pair : chunks) {
            pair.second.draw(); 
        }
    }
};

int main()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	static std::string	tmpStr;
	static Tri::Engine engine(960, 540, "Everything is a resource");
	// static Tri::Group	background({-100,-100,200,200});
	// background.cameraSpeed = 0.5f;
	// static Tri::Group	mainPlan({-150,-150,300,300});
	static Vector2		camPosition{0,0};
	static Tri::AnimatedSprite	spriteAlgue(static_cast<std::string>(SPRITES_PATH) + static_cast<std::string>("seaweed.png"));
	static unsigned int	algueAnimation = spriteAlgue.addFrameSet({0,0,SEAWEED_SPRITE_SIZE,SEAWEED_SPRITE_SIZE}, 4, {0,0}, 0.0f, {
		{{0,0,SEAWEED_SPRITE_SIZE / 3.0}},
		{{0,0,SEAWEED_SPRITE_SIZE / 3.0}},
		{{0,0,SEAWEED_SPRITE_SIZE / 3.0}},
		{{0,0,SEAWEED_SPRITE_SIZE / 3.0}}
	});
	spriteAlgue.getFrameSet(algueAnimation).setOriginToCenter();
	static Tri::AnimatedSprite	spriteBottle(static_cast<std::string>(SPRITES_PATH) + static_cast<std::string>("seaweedRed.png"));
	static unsigned int	bottleAnimation = spriteBottle.addFrameSet({0,0,SEAWEED_SPRITE_SIZE,SEAWEED_SPRITE_SIZE}, 4, {0,0}, 0.0f, {
		{{0,0,SEAWEED_SPRITE_SIZE / 3.0}},
		{{0,0,SEAWEED_SPRITE_SIZE / 3.0}},
		{{0,0,SEAWEED_SPRITE_SIZE / 3.0}},
		{{0,0,SEAWEED_SPRITE_SIZE / 3.0}}
	});
	spriteBottle.getFrameSet(bottleAnimation).setOriginToCenter();
	static Tri::AnimatedSprite	sprite(static_cast<std::string>(SPRITES_PATH) + static_cast<std::string>("fish.png"));
	static unsigned int	swimAnimation = sprite.addFrameSet({0,0,FISH_SPRITE_WIDTH,FISH_SPRITE_HEIGHT}, 8, {0,0}, 12.0f, {
		{{0,-280.0,FISH_SPRITE_WIDTH / 4.0}, {0,-130.0,FISH_SPRITE_WIDTH / 4.0}, {0,-5.0,FISH_SPRITE_WIDTH / 5.0}},
		{{0,-280.0,FISH_SPRITE_WIDTH / 4.0}, {0,-130.0,FISH_SPRITE_WIDTH / 4.0}, {0,-5.0,FISH_SPRITE_WIDTH / 5.0}},
		{{0,-280.0,FISH_SPRITE_WIDTH / 4.0}, {0,-130.0,FISH_SPRITE_WIDTH / 4.0}, {0,-5.0,FISH_SPRITE_WIDTH / 5.0}},
		{{0,-280.0,FISH_SPRITE_WIDTH / 4.0}, {0,-130.0,FISH_SPRITE_WIDTH / 4.0}, {0,-5.0,FISH_SPRITE_WIDTH / 5.0}},
		{{0,-280.0,FISH_SPRITE_WIDTH / 4.0}, {0,-130.0,FISH_SPRITE_WIDTH / 4.0}, {0,-5.0,FISH_SPRITE_WIDTH / 5.0}},
		{{0,-280.0,FISH_SPRITE_WIDTH / 4.0}, {0,-130.0,FISH_SPRITE_WIDTH / 4.0}, {0,-5.0,FISH_SPRITE_WIDTH / 5.0}},
		{{0,-280.0,FISH_SPRITE_WIDTH / 4.0}, {0,-130.0,FISH_SPRITE_WIDTH / 4.0}, {0,-5.0,FISH_SPRITE_WIDTH / 5.0}},
		{{0,-280.0,FISH_SPRITE_WIDTH / 4.0}, {0,-130.0,FISH_SPRITE_WIDTH / 4.0}, {0,-5.0,FISH_SPRITE_WIDTH / 5.0}}
	});
	sprite.getFrameSet(swimAnimation).setOriginToCenter();
	static unsigned int	stopAnimation = sprite.addFrameSet({0,0,FISH_SPRITE_WIDTH,FISH_SPRITE_HEIGHT}, 8, {0,0}, 6.0f, {
		{{0,-280.0,FISH_SPRITE_WIDTH / 4.0}, {0,-130.0,FISH_SPRITE_WIDTH / 4.0}, {0,-5.0,FISH_SPRITE_WIDTH / 5.0}},
		{{0,-280.0,FISH_SPRITE_WIDTH / 4.0}, {0,-130.0,FISH_SPRITE_WIDTH / 4.0}, {0,-5.0,FISH_SPRITE_WIDTH / 5.0}},
		{{0,-280.0,FISH_SPRITE_WIDTH / 4.0}, {0,-130.0,FISH_SPRITE_WIDTH / 4.0}, {0,-5.0,FISH_SPRITE_WIDTH / 5.0}},
		{{0,-280.0,FISH_SPRITE_WIDTH / 4.0}, {0,-130.0,FISH_SPRITE_WIDTH / 4.0}, {0,-5.0,FISH_SPRITE_WIDTH / 5.0}},
		{{0,-280.0,FISH_SPRITE_WIDTH / 4.0}, {0,-130.0,FISH_SPRITE_WIDTH / 4.0}, {0,-5.0,FISH_SPRITE_WIDTH / 5.0}},
		{{0,-280.0,FISH_SPRITE_WIDTH / 4.0}, {0,-130.0,FISH_SPRITE_WIDTH / 4.0}, {0,-5.0,FISH_SPRITE_WIDTH / 5.0}},
		{{0,-280.0,FISH_SPRITE_WIDTH / 4.0}, {0,-130.0,FISH_SPRITE_WIDTH / 4.0}, {0,-5.0,FISH_SPRITE_WIDTH / 5.0}},
		{{0,-280.0,FISH_SPRITE_WIDTH / 4.0}, {0,-130.0,FISH_SPRITE_WIDTH / 4.0}, {0,-5.0,FISH_SPRITE_WIDTH / 5.0}}
	});
	sprite.getFrameSet(stopAnimation).setOriginToCenter();
	// sprite.getFrameSet().setCameraSpeed(0.9f);
	static Tri::Object		obj(&sprite, 0, PLAYER_MIN_SIZE, 0.0, {0,0}, 300.0, TYPE_PLAYER);
	// mainPlan.addObject(&sprite, 0, 2.0, 90.0, {80,80}, 300.0, TYPE_ALGUE);
	Tri::camera().setPosition(camPosition);
	static PlayerMovement	playerMov={};
	static PlayerVar		playerVar={MAX_LIFE, 0.0f, 1};
	static ChunkManager world(&spriteAlgue, &spriteBottle);
	static BackgroundChunkManager	bg1(&spriteAlgue, 0.7, 0.8);
	static BackgroundChunkManager	bg2(&spriteAlgue, 0.5, 0.6);
	static BackgroundChunkManager	bg3(&spriteAlgue, 0.3, 0.4);
	static BackgroundChunkManager	bg4(&spriteAlgue, 0.1, 0.2);
	//----------FONT-----------//
	Font fontRegular = LoadFontEx("assets/fonts/Jura-Regular.ttf", 64, 0, 250);
	GenTextureMipmaps(&fontRegular.texture);
	SetTextureFilter(fontRegular.texture, TEXTURE_FILTER_TRILINEAR);
	Font fontBold = LoadFontEx("assets/fonts/Jura-SemiBold.ttf", 64, 0, 250);
	GenTextureMipmaps(&fontBold.texture);
	SetTextureFilter(fontBold.texture, TEXTURE_FILTER_TRILINEAR);
	//---------FONT-END--------//
	tmpStr = (std::string)((std::string)MUSICS_PATH + (std::string)"music.ogg");
	static Music bo = LoadMusicStream(tmpStr.c_str());
	tmpStr = (std::string)((std::string)SOUNDS_PATH + (std::string)"EatAlgue.wav");
	static Sound algueSfx = LoadSound(tmpStr.c_str());
	tmpStr = (std::string)((std::string)SOUNDS_PATH + (std::string)"EatBottle.wav");
	static Sound bottleSfx = LoadSound(tmpStr.c_str());
	PlayMusicStream(bo);
	engine.loop([&]{
        UpdateMusicStream(bo);
        
        // 🌟 L'HORLOGE MANUELLE DES DÉCHETS (6 FPS)
        static float envTimer = 0.0f;
        envTimer += GetFrameTime();
        if (envTimer >= 1.0f / 8.0f) {
            envTimer -= (1.0f / 8.0f);
            // Ton opérateur ++ magique va passer à la frame suivante !
            spriteAlgue.getFrameSet(algueAnimation)++;
            spriteBottle.getFrameSet(bottleAnimation)++;
        }
		if (IsKeyPressed(KEY_F)) {
            ToggleFullscreen();
        }
		playerMov.inputMag = 0.0;
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			playerMov.inputPosition = GetMousePosition();
			// playerMov.inputPosition = Vector2Subtract(playerMov.inputPosition, {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f});
			playerMov.inputPosition = Vector2Subtract(playerMov.inputPosition, Tri::convertCamera(obj.position, 1.0f));
			playerMov.distance = Vector2Length(playerMov.inputPosition);
			if (playerMov.distance >= MOUSE_DEAD_MIN) {
				playerMov.inputVec = Vector2Normalize(playerMov.inputPosition);
				playerMov.inputMag = playerMov.distance / MAX_DIST_SPEED;
				if (playerMov.inputMag > 1.0)
					playerMov.inputMag = 1.0;
			}
		} else if (IsGamepadAvailable(0)) {
			playerMov.inputPosition = {GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X), GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_Y)};
			playerMov.distance = Vector2Length(playerMov.inputPosition);
			if (playerMov.distance > GAMEPAD_DEAD_MIN) {
				playerMov.inputVec = Vector2Normalize(playerMov.inputPosition);
				playerMov.inputMag = playerMov.distance;
				if (playerMov.inputMag > 1.0)
					playerMov.inputMag = 1.0;
			}
		}
		if (playerMov.inputMag > 0.0f && obj.getSprite().getFrameSetIndex() != swimAnimation)
			obj.getSprite().selectFrameSet(swimAnimation);
		else if (playerMov.inputMag == 0.0f && obj.getSprite().getFrameSetIndex() != stopAnimation)
			obj.getSprite().selectFrameSet(stopAnimation);
		applyMouvement(obj, playerMov);
		world.update(obj.position);
		bg1.update(obj.position);
        bg2.update(obj.position);
		bg3.update(obj.position);
        bg4.update(obj.position);
		int typeMange = world.eatResources(obj);
    	if (typeMange != 0) {
    	    if (typeMange == TYPE_ALGUE) {
				PlaySound(algueSfx);
    	        obj.scale += 0.005f; // Le poisson grossit !
				if (obj.scale > 5.0f)
					obj.scale = 5.0f;
				playerVar.xp -= XP_LOOZE;
				if (playerVar.xp < 0.0f)
					playerVar.xp = 0.0f;
				if (playerVar.life < MAX_LIFE) {
					playerVar.life += LIFE_GAIN;
					if (playerVar.life > MAX_LIFE)
						playerVar.life = MAX_LIFE;
				}
    	    } else if (typeMange == TYPE_BOTTLE) {
				PlaySound(bottleSfx);
				obj.scale -= 0.005f;
				if (obj.scale < PLAYER_MIN_SIZE)
					obj.scale = PLAYER_MIN_SIZE;
				playerVar.life -= LIFE_LOOZE;
				playerVar.xp += XP_GAIN;
				if (playerVar.xp >= LEVEL_XP_REQUIER) {
					++playerVar.level;
					playerVar.xp = playerVar.xp - LEVEL_XP_REQUIER;
				}
				if (playerVar.life <= 0.0f) {
					playerVar.level -= 1;
					playerVar.xp = 0.0f;
					playerVar.life = MAX_LIFE / 2.0f;
				}
			}
    	}
		Tri::camera().setPosition(obj.position);
		BeginDrawing();
		ClearBackground(WATER_COLOR);
		// background.draw();
		bg1.draw();
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WATER_COLOR);
		bg2.draw();
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WATER_COLOR);
		bg3.draw();
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WATER_COLOR);
		bg4.draw();
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WATER_COLOR);
		world.draw();
		obj.draw();
		// ==========================================================
        // DESSIN DE L'INTERFACE UTILISATEUR (UI)
        // ==========================================================
        
        float uiX = 20.0f; // Marge à gauche
        float uiY = 20.0f; // Marge en haut
        float barWidth = 250.0f; // Longueur des barres
        
        // 1. Afficher le Niveau
        std::string levelText = "NIVEAU " + std::to_string(playerVar.level);
        DrawTextEx(fontBold, levelText.c_str(), {uiX, uiY}, 36.0f, 2.0f, WHITE);
        
        // 2. Afficher la Barre de Vie (Rouge)
        uiY += 45.0f; // On descend un peu sous le texte
        float healthBarHeight = 25.0f;
        float healthRatio = playerVar.life / MAX_LIFE;
        if (healthRatio < 0.0f) healthRatio = 0.0f; // Sécurité anti-bug graphique
        
        // Fond de la barre (Gris foncé)
        DrawRectangle(uiX, uiY, barWidth, healthBarHeight, DARKGRAY); 
        // Intérieur de la barre (Rouge, proportionnel à la vie)
        DrawRectangle(uiX, uiY, barWidth * healthRatio, healthBarHeight, MAROON); 
        // Contour de la barre (Noir)
        // DrawRectangleLines(uiX, uiY, barWidth, healthBarHeight, BLACK); 

        // Petit texte par dessus la barre de vie
        std::string hpText = std::to_string((int)playerVar.life) + " / " + std::to_string((int)MAX_LIFE);
        DrawTextEx(fontRegular, hpText.c_str(), {uiX + 10.0f, uiY + 3.0f}, 20.0f, 1.0f, WHITE);

        // 3. Afficher la Barre d'XP (Cyan/Bleu)
        uiY += healthBarHeight + 10.0f; // On descend sous la barre de vie
        float xpBarHeight = 15.0f; // Un peu plus fine que la barre de vie
        float xpRatio = playerVar.xp / LEVEL_XP_REQUIER;
        if (xpRatio > 1.0f) xpRatio = 1.0f;
        
        DrawRectangle(uiX, uiY, barWidth, xpBarHeight, DARKGRAY); 
        DrawRectangle(uiX, uiY, barWidth * xpRatio, xpBarHeight, SKYBLUE); 
        // DrawRectangleLines(uiX, uiY, barWidth, xpBarHeight, BLACK); 
        
        // ==========================================================
		EndDrawing();
	});
	UnloadFont(fontBold);
	UnloadFont(fontRegular);
	return (0);
}
