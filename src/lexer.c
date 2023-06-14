/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:26:38 by lclerc            #+#    #+#             */
/*   Updated: 2023/06/09 15:26:41 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	main()
{
	t_lexer		token_list;
	t_token		*token;

	token = token_list.token_list;
	
	char		*test_string = "echo -n \"toto va\" 'a' la peche > outfile | <infile wc -l > amount_of_lines";
	token_list.delimiters = " \t<>|\"'";
	


} 
