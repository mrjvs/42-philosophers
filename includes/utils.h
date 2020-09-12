#ifndef STR_UTILS_H
# define STR_UTILS_H

# include <stddef.h>

# define LLINT_CHARLEN 19
# define INT_CHARLEN 10
# define INT_MAXLEN 2147483647

size_t	phil_strlen(char *str);
char	*phil_make_log(long long time, int id, char *text);
long	phil_atoi(char *str);

#endif
