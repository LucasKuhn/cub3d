#include "./include/cub3d.h"

void draw_image_column(t_game *game, double dist, int column, int color)
{
	int ground_color = 0x5e3306;
	int sky_color = 0x06c5cf;
	double	column_height;
	double	offset; // column height

	column_height = (1 / dist) * 1500;
	offset = ceil((HEIGHT - column_height) / 2);
	if (offset <= 0)
		offset = 5.0;
	for(int y = 0; y < (int)offset; ++y)// THIS DRAWS THE GROUND
	{
		int pixel = (y * game->columns.line_size) + (column * 4);// change the 'offset' to top offset the dist

			game->columns.pixels[pixel + 0] = (ground_color) & 0xFF; //blue
			game->columns.pixels[pixel + 1] = (ground_color >> 8) & 0xFF;//green
			game->columns.pixels[pixel + 2] = (ground_color >> 16) & 0xFF;//red
			game->columns.pixels[pixel + 3] = 0; //alpha
	}
	for(int y = 0; y + (int)offset < HEIGHT - (int)offset; ++y)// THIS DRAWS THE COLUMNS
	{
		int pixel = ((y + (int)offset) * game->columns.line_size) + (column * 4);// change the 'offset' to top offset the dist

			game->columns.pixels[pixel + 0] = (color) & 0xFF; //blue
			game->columns.pixels[pixel + 1] = (color >> 8) & 0xFF;//green
			game->columns.pixels[pixel + 2] = (color >> 16) & 0xFF;//red
			game->columns.pixels[pixel + 3] = 0; //alpha
	}
	for(int y = HEIGHT - (int)offset; y < HEIGHT; ++y)// THIS DRAWS THE SKY
	{
		int pixel = (y * game->columns.line_size) + (column * 4);// change the 'offset' to top offset the dist

			game->columns.pixels[pixel + 0] = (sky_color) & 0xFF; //blue
			game->columns.pixels[pixel + 1] = (sky_color >> 8) & 0xFF;//green
			game->columns.pixels[pixel + 2] = (sky_color >> 16) & 0xFF;//red
			game->columns.pixels[pixel + 3] = 0; //alpha
	}
	return ;
}
