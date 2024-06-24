#include "../inc/hck.h"

void	hck_error(int code)
{
	if (code == 1)
		dprintf(2, "There is an error\n");
	exit(code);
}
