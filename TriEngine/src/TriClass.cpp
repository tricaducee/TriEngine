#include "../include/TriClass.h"
#include <cmath>

Tri::Circle	Tri::convertCircleToWorld(Tri::Circle circle, Vector2 position, float scale, float rotation)
{
	Tri::Circle worldCircle;

    // 1. Le décalage EST directement la position locale du cercle
    // Un cercle en (0,0) aura dx=0 et dy=0, donc il restera pile sur la "position" du poisson
    float dx = circle.x;
    float dy = circle.y;
    // 2. On applique l'échelle
    dx *= scale;
    dy *= scale;
    // 3. On applique la rotation
    float rad = rotation * DEG2RAD;
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);
    float rotX = dx * cosA - dy * sinA;
    float rotY = dx * sinA + dy * cosA;
    // 4. On ajoute la position du joueur dans le monde
    worldCircle.x = position.x + rotX;
    worldCircle.y = position.y + rotY;
    worldCircle.radius = circle.radius * scale;
    return worldCircle;
}