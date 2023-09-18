#include "minishell.h"

static int	token_len(char *token);
static int	is_metachar(char c);
static int	is_quoted(char c);

void	tokenization(t_data *data)
{
	int		i;
	int		len;
	char	*temp;

	i = -1;
	while (data->prompt[++i] != '\0')
	{
		while (ft_strchr(BLANK, data->prompt[i]) != NULL)
			i++;
		len = token_len(&data->prompt[i]);
		temp = malloc((len + 1) * sizeof(char));
		ft_strlcpy(temp, &data->prompt[i], len + 1);
		ft_lstadd_back(&data->token, ft_lstnew(ft_strdup(temp)));
		free(temp);
		i += len - 1;
	}
}

static int	token_len(char *token)
{
	int	i;
	int	quoted;
	int	metachar;

	metachar = is_metachar(token[0]);
	quoted = is_quoted(token[0]);
	i = 0;
	while (token[++i] != '\0')
	{
		if (metachar == 1)
		{
			if (token[i] == token[i - 1])
				return (2);
			return (1);
		}
		else if (quoted == 0)
		{
			if (token[i] == ' ' || is_metachar(token[i]) == 1)
				return (i);
			quoted = is_quoted(token[i]);
		}
		else
			quoted = is_quoted(token[i]);
	}
	return (i);
}

static int	is_quoted(char c)
{
	if (c == S_QUOTE)
		return (1);
	else if (c == D_QUOTES)
		return (2);
	return (0);
}

static int	is_metachar(char c)
{
	if (ft_strchr(METACHAR, c) == NULL)
		return (0);
	return (1);
}