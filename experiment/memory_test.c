#include <stdio.h>
#include <stdlib.h>

// memory test
int	main(int argc, char **argv)
{
	char *str;
	int i;

	i = 0;
	str = calloc(1, argc);
	free(str);
	return (0);
}
