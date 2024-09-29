#include "miniRT.h"

void  mlx_helpers(void)
{
    t_win *win;

    win = ft_window(800, 800);
    if (!win)
        return;
    ft_display(win);
    mlx_key_hook(win->win, ft_escape_key, win);
    mlx_hook(win->win, 17, 0, ft_close, win);
    mlx_loop(win->ptr);
}

int parse_scene_file(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if(fd < 0)
    {
        perror(ERROR_MESSAGE "Failed to open scene file");
        return 1;
    }
    close(fd);
    return 0;
    
}




int main(int argc, char **argv)
{
    if(argc != 2)
        return 0;
    while (argc == 2)
    {
        if(parse_scene_file(argv[1] ) != 0)
        {
            fprintf(stderr, ERROR_MESSAGE "Failed to parse scene file.\n");
            return 1;
        }
        mlx_helpers();
    }
}
