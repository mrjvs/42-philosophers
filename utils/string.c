#include <stdlib.h>
#include <string.h>
#include "utils.h"

size_t		phil_strlen(char *str) {
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static int	num_to_str(long long num, char *str) {
	size_t		i;
	int			char_len;
	long long	num2;

	char_len = 1;
	num2 = num;
	while (num2 >= 10) {
		num2 = num2 / 10;
		char_len++;
	}
	i = 1;
	while (num >= 10) {
		str[char_len - i] = '0' + (num % 10);
		num = num / 10;
		i++;
	}
	str[char_len - i] = '0' + (num % 10);
	return (char_len);
}

static void	phil_memcpy(char *str, char *out) {
	size_t	i;

	i = 0;
	while (str[i] != '\0') {
		out[i] = str[i];
		i++;
	}
}

char		*phil_make_log(long long time, int id, char *text) {
	char	*out;
	int		len;
	size_t	i;

	len = LLINT_CHARLEN + INT_CHARLEN + phil_strlen(text) + 3;
	out = (char *)malloc(len);
	if (out == NULL)
		return (out);
	memset(out, 0, len);
	i = num_to_str(time, out);
	out[i] = ' ';
	i += num_to_str(id, out + i + 1) + 1;
	out[i] = ' ';
	phil_memcpy(text, out + i + 1);
	return (out);
}
