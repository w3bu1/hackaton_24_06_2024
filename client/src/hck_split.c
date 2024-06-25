#include "../inc/hck.h"


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*res;

	if (!s)
		return (NULL);
	s_len = strlen(s);
	if (start > s_len)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	res = (char *)calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	strncpy(res, &s[start], len + 1);
	return (res);
}

size_t	ft_words_count(char const *str, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static size_t	ft_get_next_id(char const *str, char c, size_t start)
{
	size_t	len;

	len = 0;
	while (str[start] && str[start] == c)
		start++;
	len = 0;
	while (str[start + len] && str[start + len] != c)
		len++;
	return (start + len);
}

static char	*ft_get_word(char const *str, char c, size_t start)
{
	size_t	len;
	char	*word;

	while (str[start] && str[start] == c)
		start++;
	len = 0;
	while (str[start + len] && str[start + len] != c)
		len++;
    
	word = ft_substr(str, start, len);
	if (!word)
		return (NULL);
	return (word);
}

static void	*ft_free_all(char **splitted, size_t last_id)
{
	size_t	i;

	i = 0;
	while (i < last_id)
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
	splitted = NULL;
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	size;
	size_t	i;
	size_t	w_id;
	char	**splitted;

	if (!s)
		return (NULL);
	size = ft_words_count(s, c);
	splitted = (char **)calloc(size + 1, sizeof(char *));
	if (!splitted)
		return (NULL);
	splitted[size] = NULL;
	i = 0;
	w_id = 0;
	while (i < size)
	{
		splitted[i] = ft_get_word(s, c, w_id);
		if (!splitted[i])
			return (ft_free_all(splitted, i));
		w_id = ft_get_next_id(s, c, w_id);
		i++;
	}
	return (splitted);
}
