/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:47:45 by lclerc            #+#    #+#             */
/*   Updated: 2023/08/16 17:07:34 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Validates and exports the given variable.
 *
 * This function validates the variable name and then exports it with the 
 * specified value. The variable name must consist of alphabetic characters 
 * and underscores only.
 *
 * @param key The variable name to validate and export.
 * @param value The value to be associated with the variable.
 */
static void	ft_export_validate_and_execute(char *key, char *value)
{
	char	*sanitize_check;

	sanitize_check = key;
	while (*sanitize_check != '\0')
	{
		if (!(ft_isalpha(*sanitize_check) || *sanitize_check == '_'))
		{
			printf("Invalid variable name: %s\n", key);
			g_minishell->exit_status = 1;
			return ;
		}
		sanitize_check++;
	}
	env_set_value_by_key(key, value);
}

/**
 * @brief Handles the export of a variable with an equal sign.
 *
 * This function processes the variable that includes an equal sign and 
 * extracts the key and value. If the key is not empty, it validates and 
 * exports the variable.
 *
 * @param arg The argument containing the variable with an equal sign.
 */
static void	ft_export_handle_equal_sign(char *arg)
{
	char	*equal_sign;
	char	*key;
	char	*value;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		key = arg;
		value = equal_sign + 1;
		if (*key)
			ft_export_validate_and_execute(key, value);
	}
}

/**
 * @brief Exports environment variables based on the provided command node.
 *
 * This function exports environment variables according to the arguments 
 * provided in the command node. It validates variable names and optionally 
 * assigns values. It also mimics the behavior of preserving exported variables
 * x across new shell sessions.
 *
 * @param node The command node containing the arguments to export.
 */
void	ft_export(t_ast_node *node)
{
	int		i;
	char	*arg;

	i = 0;
	if (node->argv_count == 1)
	{
		env_print_list();
		return ;
	}
	while (++i < node->argv_count)
	{
		arg = node->exec_argv[i];
		ft_export_handle_equal_sign(arg);
		ft_export_validate_and_execute(arg, "");
	}
	g_minishell->exit_status = 0;
}
