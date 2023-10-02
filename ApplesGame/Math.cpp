#include "Math.h"
#include <cstdlib>

Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight)
{
	Position2D result;
	result.x = rand() / (float)RAND_MAX * screenWidth;
	result.y = rand() / (float)RAND_MAX * screenHeight;
	return result;
}

bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size, Position2D rect2Position, Vector2D rect2Size)
{
	float dx = (float)fabs(rect1Position.x - rect2Position.x);
	float dy = (float)fabs(rect1Position.y - rect2Position.y);
	return (dx <= (rect1Size.x + rect2Size.x) / 2.f &&
		dy <= (rect1Size.y + rect2Size.y) / 2.f);
}

bool IsCirclesCollide(Position2D circle1Position, float circle1Radius, Position2D circle2Position, float circle2Radius)
{
	float squareDistance = (circle1Position.x - circle2Position.x) *
		(circle1Position.x - circle2Position.x) +
		(circle1Position.y - circle2Position.y) * (circle1Position.y - circle2Position.y);
	float squareRadiusSum = (circle1Radius + circle2Radius) * (circle1Radius + circle2Radius);
	return squareDistance <= squareRadiusSum;
}
