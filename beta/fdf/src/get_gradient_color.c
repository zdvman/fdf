#include "../includes/libfdf.h"

// Функция для линейной интерполяции между двумя значениями
float lerp(float start, float end, float t)
{
	return (start + t * (end - start));
}

// Функция для расчета цвета пикселя с градиентом
unsigned int	get_gradient_color(unsigned int startColor, unsigned int endColor, float t)
{
	// Извлекаем компоненты RGB из начального и конечного цветов
	int startRed = (startColor >> 16) & 0xFF;
	int startGreen = (startColor >> 8) & 0xFF;
	int startBlue = startColor & 0xFF;
	int endRed = (endColor >> 16) & 0xFF;
	int endGreen = (endColor >> 8) & 0xFF;
	int endBlue = endColor & 0xFF;
	// Интерполируем компоненты RGB
	int red = lerp(startRed, endRed, t);
	int green = lerp(startGreen, endGreen, t);
	int blue = lerp(startBlue, endBlue, t);
	// Возвращаем результирующий цвет
	return (red << 16) | (green << 8) | blue;
}
