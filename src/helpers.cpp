#include "helpers.h"
#include "raylib.h"

void Helpers::DrawCenteredText(const char* text, int posX, int posY, int fontSize, Color color)
{
	auto textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 4);
	DrawText(text, posX - textSize.x / 2, posY - textSize.y / 2, fontSize, color);
}


