#include "../inc/hck.h"

static size_t	ft_secure_strlen(char *s)
{
	size_t	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static size_t	ft_get_num_len(long n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*itoa(int	n)
{
	long	num;
	char	*res;
	size_t	len;

	num = n;
	if (n < 0)
		num *= -1;
	len = ft_get_num_len(n);
	res = (char *)calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (len--)
	{
		res[len] = (num % 10) + 48;
		num /= 10;
	}
	if (n < 0)
		res[0] = 45;
	return (res);
}

char	*ft_joinstr(char *s1, char *s2)
{
	size_t	size;
	char	*res;
	size_t	i;
	size_t	res_id;

	size = ft_secure_strlen(s1) + ft_secure_strlen(s2);
	res = (char *)calloc(size + 1, sizeof(char));
	if (!res)
		return (free(s1), NULL);
	res_id = 0;
	while (s1 && s1[res_id])
	{
		res[res_id] = s1[res_id];
		res_id++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		res[res_id + i] = s2[i];
		i++;
	}
	if (!res[0])
		return (free(res), free(s1), NULL);
	return (free(s1), res);
}

int	hck_is_coord_message(char *s)
{
	while (*s  && (((*s >= 9 && *s <= 13) || *s ==32) || (*s >= '0' && *s <= '9')))
			s++;
	return (*s == '\0');
}
