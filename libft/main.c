
#include <stdio.h>
#include "libft.h"

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		printf("Hash of \"%s\" with size %d: %d\n",
			argv[1],
			ft_atoi(argv[2]),
			hm_hash(argv[1], ft_atoi(argv[2]))
			);
	}
	return (0);
}
