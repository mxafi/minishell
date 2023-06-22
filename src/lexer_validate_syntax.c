/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_syntax.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:11:59 by lclerc            #+#    #+#             */
/*   Updated: 2023/06/22 14:12:02 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"


//
//static void	check_first_character(char *input)
//{
//	if (*input != '|')
//		return;
//	ft_printf("shellfish> syntax error near unexpected token `|' ");
//	exit(258);
//}
//
//static void	check_redirectors(char *input)
//{
//	int	i;
//	int	j;
//
//	i = 0;
//	j = 0;
//	while (input[i] != '\0')
//	{
//		if (input[i] == '<')
//		{
//			if (input[i + 1] == '<' && input[i + 1] != '\0')
//			{
//				trim_white_spaces(input[i]);
//				if (!ft_isalnum(input[i]))
//
//
//
//			}
//		}
//		i++;
//	}
//}


//int	validate_syntax(char *input)
//{
//	check_first_character(input);
//	check_redirectors(input);
//	check_quotes(input);
//	check_last_chharacer(input);
//
//	return (SUCCESS);
//}
//

int	validate_syntax(t_lexer *token_list)
{
	t_token	*token;

	token = token_list->token_list;
	token_list->state = STRING;
	while (token->next != NULL)
	{
		if (token->token_count == 0 && token->type == PIPE)
		{
			ft_printf("shellfish> syntax error near unexpected token `|' ");
			token_list->state = 258;
		}
		if (token->type == OUTFILE || token->type == INFILE || token->type == HEREDOC || token->type == APPEND_TO)
		{
			token_list->state = token->type;
			if (token->next != NULL)
			{
				token = token->next;
				if (token->type == SPACE)
					delete_space_token(&token_list, token->token_count);
				if (token->type == STRING)
					token_list->state = STRING;
				else
				{
					ft_printf("shellfish> syntax error near unexpected token %c", token->type);
					exit (258);
				}
			}
			else
			{
				ft_printf("shellfish> syntax error near unexpected token `newline'");
				exit (258);

		}

	}

	return (SUCCESS);
}
