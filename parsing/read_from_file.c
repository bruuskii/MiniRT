#include "../miniRT.h"

char    **ft_lines(char *filename)
{
    int     fd;
    char    *line;
    char    **lst;
    int     i;

    lst = malloc(20 * sizeof(char *));
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error when openning file\n");
        free(lst);
        return (NULL);
    }
    i = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        if (ft_strcmp(line, ""))
            lst[i] = line;
        else
            free(line);
        i++;
    }
    lst[i] = NULL;
    close(fd);
    return (lst);
}
