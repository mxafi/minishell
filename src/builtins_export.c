/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:47:45 by lclerc            #+#    #+#             */
/*   Updated: 2023/08/25 09:54:47 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_export_error_identifier(char *key)
{
	ft_putstr_fd("shellfishy: export: `", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_minishell->exit_status = 1;
}

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
			ft_export_error_identifier(key);
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
static t_return_value	ft_export_handle_equal_sign(char *arg)
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
		else
			ft_export_error_identifier(key);
		return (SUCCESS);
	}
	return (FAILURE);
}

static void	print_export(void)
{
	int	i;
	int	j;

	i = 0;
	while (g_minishell->envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		j = 0;
		while (g_minishell->envp[i][j] && g_minishell->envp[i][j] != '=')
			ft_putchar_fd(g_minishell->envp[i][j++], 1);
		j++;
		ft_putstr_fd("=\"", 1);
		while (g_minishell->envp[i][j])
			ft_putchar_fd(g_minishell->envp[i][j++], 1);
		ft_putstr_fd("\"\n", 1);
		i++;
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

	g_minishell->exit_status = 0;
	if (node->argv_count == 1)
	{
		print_export();
		return ;
	}
	i = 0;
	while (++i < node->argv_count)
	{
		arg = node->exec_argv[i];
		if (ft_export_handle_equal_sign(arg) == SUCCESS)
			;
		else
			ft_export_validate_and_execute(arg, "");
	}
}
