long	phil_atoi(char *str) {
	long	out;
	int		i;

	out = 0;
	i = 0;
	while (str[i] != '\0') {
		out *= 10;
		out += str[i] - '0';
		i++;
	}
	return (out);
}