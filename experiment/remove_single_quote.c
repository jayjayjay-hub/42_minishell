#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_token
{
	char			*str;
	struct s_token	*next;
}	t_token;

bool	is_double_quote(char c)
{
	return (c && c == '\"');
}

void	remove_single_quote(char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_double_quote(str[i]))
		{
			str[j++] = str[i++];
			while (str[i] && !is_double_quote(str[i]))
				str[j++] = str[i++];
		}
		else if (str[i] == '\'')
			i++;
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
}

int	main(void)
{
	// t_token	*token;

	// token = (t_token *)malloc(sizeof(t_token));
	// token->str = strdup("hoge 'fuga' piyo");
	// token->next = (t_token *)malloc(sizeof(t_token));
	// token->next->str = strdup("hoge'f uga'piyo");
	// token->next->next = NULL;
	// remove_single_quote(token);
	// // print
	// while (token)
	// {
	// 	printf("%s\n", token->str);
	// 	token = token->next;
	// }

	char	str[100] = "hoge 'fuga' piyo\"";

	printf("%s\n", str);
	remove_single_quote(str);
	printf("%s\n", str);
	return (0);
}
