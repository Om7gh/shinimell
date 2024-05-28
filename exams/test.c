#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

int ft_strlen(char *s)
{
        int i;

        i = 0;
        while (s[i])
                i++;
        return (i);
}

char    *ft_search(char *s, int c)
{
        while (*s)
        {
                if (*s == (char)c)
                        return ((char *)s);
                s++;
        }
        return (NULL);
}

void	ft_strcopy(char *dst, const char *src)
{
	while (*src)	
		*dst++ = *src++;
	*dst = '\0';
}

char    *ft_strdup(char *s)
{
        char *new;
        int     i;

        i = 0;
        new = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
        if (!new)
                return (NULL);
        ft_strcopy(s, new);
        return (new);
}

char *ft_strjoin(char *s1, char *s2)
{
        char *new;
        int     i;
        int     j;

        if (!s1 || !s2)
                return (NULL);
        new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
        if (!new)
                return (NULL);
        ft_strcopy(new, s1);        
        ft_strcopy(new + ft_strlen(s1), s2);
        free(s1);
        return (new);
}


char    *get_next_line(int fd)
{
        if (fd == -1 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
                return (NULL);

        int     bytes = 1;
        int     line_len;
        char    *line;
        char    *new_line;
        static char buff[BUFFER_SIZE + 1];

        line = ft_strdup(buff);
        while (!(new_line = ft_search(buff, '\n')) && (bytes == read(fd, buff, BUFFER_SIZE)))
        {
                buff[bytes] = '\0';
                line = ft_strjoin(line, buff);
        }
        if (ft_strlen(line) == 0)
                return (free(line), NULL);
        if(new_line != NULL)
        {
                line_len = new_line - line + 1;
                ft_strcopy(buff, new_line + 1);
        }
        else
        {
                line_len = ft_strlen(line);
                buff[0] = '\0';
        }
        line[line_len] = '\0';
        return (line);
}


int main()
{
        int fd = open("/dev/random", O_RDONLY, 0644);
        char    *s = get_next_line(fd);
        while (s)
        {
                printf("%s", s);
                s = get_next_line(fd);
        }
}