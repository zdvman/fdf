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

// Пример использования в цикле рисования линии
// Предположим, что dx и dy уже вычислены как разница между x1 и x0 и y1 и y0 соответственно
// И предположим, что sx и sy определены как знак шага по каждой из осей
// Также предполагаем, что длина линии можно вычислить как sqrt(dx*dx + dy*dy)
int dx = x1 - x0, dy = y1 - y0;
int sx = (x0 < x1) ? 1 : -1, sy = (y0 < y1) ? 1 : -1;
float length = sqrt(dx*dx + dy*dy);
float progress, t;
int x = x0, y = y0, e2, err = dx - dy;

while (1) {
    progress = sqrt((x - x0)*(x - x0) + (y - y0)*(y - y0)) / length;
    t = progress;
    data->color = get_gradient_color(startColor, endColor, t);
    put_pixel_to_img(data->img->img_pixel_ptr, x, y, data->color, data);
    if (x == x1 && y == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x += sx; }
    if (e2 <= dx) { err += dx; y += sy; }
}
