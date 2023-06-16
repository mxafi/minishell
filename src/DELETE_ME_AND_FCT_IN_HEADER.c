# include "../inc/lexer.h"


void	print_list(t_lexer *list)
{
	for (int i = 0; i < list->token_amount; i++)
		ft_printf("Token %d: %s\n", i + 1);
}

