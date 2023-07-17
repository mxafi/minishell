# include "../inc/minishell.h"

void	print_list(t_lexer *list)
{
	t_token *current_token = list->head;
	while (current_token != NULL)
	{
		printf("Token[#%d] [%d]: %s\n", current_token->token_count, current_token->type, current_token->content);
		current_token = current_token->next;
	}
}


