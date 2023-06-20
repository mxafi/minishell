# include "../inc/lexer.h"

void	print_list(t_lexer *list)
{
	t_token *current_token = list->token_list;
	while (current_token != NULL)
	{
		ft_printf("Token %d: %s\n", current_token->token_count, current_token->token);
		current_token = current_token->next;
	}
}


