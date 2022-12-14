#include "./include/cub3d.h"

void draw_3d_view(t_game *game)
{
	int color = 0xABCDEF; // will be the texture pixels someday

	for(int y = 0; y < HEIGHT - 40; ++y)//how much in height
	for(int x = 0; x < 10; ++x)//how much in width the column goes
	{
		int pixel = ((y + 0) * game->columns.line_size) + (x * 4);// change the 0 to offset the height

			game->columns.pixels[pixel + 0] = (color) & 0xFF; //blue
			game->columns.pixels[pixel + 1] = (color >> 8) & 0xFF;//green
			game->columns.pixels[pixel + 2] = (color >> 16) & 0xFF;//red
			game->columns.pixels[pixel + 3] = 0; //alpha
	}
	mlx_put_image_to_window(game->mlx, game->win, game->columns.ptr, 0, 0);
	return ;
}

void draw_3d_real(t_game *game, int height, int ray)
{
	int color = 0xABCDEF; // will be the texture pixels someday
	double	top_offset = ceil((HEIGHT - height) / 2); // column height
	double	bot_offset = ceil((HEIGHT - height) / 2);
	printf("%d\n", (int)bot_offset);
	for(int y = 0; y + (int)top_offset < HEIGHT - (int)bot_offset; ++y)//offset is how much in bottom offset
	{
		int pixel = ((y + (int)top_offset) * game->columns.line_size) + (ray * 4);// change the 'offset' to top offset the height

			game->columns.pixels[pixel + 0] = (color) & 0xFF; //blue
			game->columns.pixels[pixel + 1] = (color >> 8) & 0xFF;//green
			game->columns.pixels[pixel + 2] = (color >> 16) & 0xFF;//red
			game->columns.pixels[pixel + 3] = 0; //alpha
	}
	return ;
}
