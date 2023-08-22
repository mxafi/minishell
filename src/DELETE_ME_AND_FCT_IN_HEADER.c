#include "../inc/minishell.h"

void	print_list(t_lexer *list)
{
	t_token	*current_token;
	char	token_type[30];
	char	list_state[30];
	char	list_error[30];

	current_token = list->head;
	if (list->state == UNDEFINED)
		strncpy(list_state, "UNDEFINED", sizeof(list_state) - 1);
	if (list->state == SGL_QUOTE_OPENED)
		strncpy(list_state, "SGL_QUOTE_OPENED", sizeof(list_state) - 1);
	else if (list->state == SGL_QUOTE_CAN_BE_CLOSED)
		strncpy(list_state, "SGL_QUOTE_CAN_BE_CLOSED", sizeof(list_state) - 1);
	else if (list->state == DBL_QUOTE_OPENED)
		strncpy(list_state, "DBL_QUOTE_OPENED", sizeof(list_state) - 1);
	else if (list->state == DBL_QUOTE_CAN_BE_CLOSED)
		strncpy(list_state, "DBL_QUOTE_CAN_BE_CLOSED", sizeof(list_state) - 1);
	list_state[sizeof(list_state) - 1] = '\0';
	
	if (list->error_code == FAILURE)
		strncpy(list_error, "FAILURE", sizeof(list_error) - 1);
	if (list->error_code == SUCCESS)
		strncpy(list_error, "SUCCESS", sizeof(list_error) - 1);
	if (list->error_code == CALLOC_FAIL)
		strncpy(list_error, "CALLOC_FAIL", sizeof(list_error) - 1);

	if (list->error_code == FORK_FAIL)
		strncpy(list_error, "FORK_FAIL", sizeof(list_error) - 1);
	if (list->error_code == WAIT_PID_FAIL)
		strncpy(list_error, "WAIT_PID_FAIL", sizeof(list_error) - 1);
	if (list->error_code == FILE_OPEN_ERROR)
		strncpy(list_error, "FILE_OPEN_ERROR", sizeof(list_error) - 1);

	if (list->error_code == EXIT_SYNTAX_ERROR)
		strncpy(list_error, "EXIT_SYNTAX_ERROR", sizeof(list_error) - 1);
	list_error[sizeof(list_error) - 1] = '\0';

	printf("List state\t\t:%p:\nlist error\t\t:%p:\n", list_state, list_error);
	while (current_token != NULL)
	{
		if (current_token->type == UNDEFINED_TOKEN)
			strncpy(token_type, "UNDEFINED_TOKEN", sizeof(token_type) - 1);
		else if (current_token->type == MY_SPACE)
			strncpy(token_type, "MY_SPACE", sizeof(token_type) - 1);
		else if (current_token->type == STRING)
			strncpy(token_type, "STRING", sizeof(token_type) - 1);
		else if (current_token->type == HEREDOC)
			strncpy(token_type, "HEREDOC", sizeof(token_type) - 1);
		else if (current_token->type == APPEND_TO)
			strncpy(token_type, "APPEND_TO", sizeof(token_type) - 1);
		else if (current_token->type == CMD)
			strncpy(token_type, "CMD", sizeof(token_type) - 1);
		else if (current_token->type == ARG)
			strncpy(token_type, "ARG", sizeof(token_type) - 1);
		else if (current_token->type == SGL_QUOTE_STR)
			strncpy(token_type, "SGL_QUOTE_STR", sizeof(token_type) - 1);
		else if (current_token->type == DBL_QUOTE_STR)
			strncpy(token_type, "DBL_QUOTE_STR", sizeof(token_type) - 1);
		else if (current_token->type == QUOTE_NEED_NULL_STR)
			strncpy(token_type, "QUOTE_NEED_NULL_STR", sizeof(token_type) - 1);
		else if (current_token->type == SINGLE_QUOTE)
			strncpy(token_type, "SINGLE_QUOTE", sizeof(token_type) - 1);
		else if (current_token->type == DOUBLE_QUOTE)
			strncpy(token_type, "DOUBLE_QUOTE", sizeof(token_type) - 1);
		else if (current_token->type == OUTFILE)
			strncpy(token_type, "OUTFILE", sizeof(token_type) - 1);
		else if (current_token->type == INFILE)
			strncpy(token_type, "INFILE", sizeof(token_type) - 1);
		else if (current_token->type == PIPE)
			strncpy(token_type, "PIPE", sizeof(token_type) - 1);
		token_type[sizeof(token_type) - 1] = '\0';
		printf("Token[#%d] [%s]:\t:%p:\n", current_token->token_count, token_type,
				current_token->content);
		current_token = current_token->next;
	}
}
