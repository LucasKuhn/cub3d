# include <mlx.h> // MiniLibX

int	main(int argc, char **argv)
{
	void			*mlx;
	void			*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 200, 200, "cub3D");
	mlx_loop(mlx);
	return (0);
}
