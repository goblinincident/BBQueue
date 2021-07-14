int	string_to_int(char *str)
{
	int	number;

	number = 0;
	while (*str >= '0' && *str <= '9')
	{
		number *= 10;
		number += *str - '0';
		str++;
	}
	return (number);
}
