// experiment strlcpy

#include <stdio.h>
#include <string.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (strlen(src));
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (strlen(src));
}

int	main(void)
{
	char	dst[10];
	char	src[] = "Hello, World!";
	size_t	dstsize;

	dstsize = 10;
	printf("ft_strlcpy: %zu\n", ft_strlcpy(dst, src, dstsize));
	printf("dst: %s\n", dst);
	return (0);
}
