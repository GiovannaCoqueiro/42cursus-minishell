#include "libft.h"
#include "minishell.h"

static char	**ft_sep_words(char **strs, int size, char *s, char c);

char	**split_key_and_value(char *str, char c)
{
	char	**strs;
	int		pos;
	int		size;
	int		equal_check;

	if (str == NULL)
		return (NULL);
	pos = -1;
	size = 0;
	equal_check = 0;
	while (str[++pos] != '\0' && equal_check == 0)
	{
		if (str[pos] != c && (str[pos + 1] == c || str[pos + 1] == '\0'))
		{
			size++;
			if (str[pos + 1] == c && str[pos + 2] != '\0')
				size++;
			equal_check = 1;
		}
	}
	strs = malloc((size + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	strs = ft_sep_words(strs, size, str, c);
	return (strs);
}

static char	**ft_sep_words(char **strs, int size, char *s, char c)
{
	int	count;
	int	c_word;
	int	temp;
	int	equal_check;

	count = 0;
	c_word = 0;
	equal_check = 0;
	while (c_word < size)
	{
		temp = count;
		if (s[count] == '=')
		{
			if (c_word != 0)
				count++;
			temp++;
		}
		if (equal_check == 0)
			while (s[temp] != c && s[temp] != '\0')
				temp++;
		else if (equal_check == 1)
			while (s[temp] != '\0')
				temp++;
		if (s[temp] == c)
			equal_check = 1;
		strs[c_word] = malloc((temp - count + 1) * sizeof(char));
		ft_memcpy((void *)strs[c_word], (const void *)&s[count], temp - count);
		strs[c_word][temp - count] = '\0';
		count = temp;
		c_word++;
	}
	strs[c_word] = NULL;
	return (strs);
}

int	check_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]) == 1 || str[i] == '_')
			i++;
		else
			break ;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}
