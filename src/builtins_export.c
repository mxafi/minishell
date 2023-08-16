/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:47:45 by lclerc            #+#    #+#             */
/*   Updated: 2023/08/16 15:54:56 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_export_validate_and_execute(char *key, char *value)
{
	char *sanitize_check = key;
	
	while (*sanitize_check != '\0')
	{
		if (!(ft_isalpha(*sanitize_check) || *sanitize_check == '_'))
		{
			printf("Invalid variable name: %s\n", key);
			g_minishell->exit_status = 1;
			return ();
		}
		sanitize_check++;
	}
	env_set_value_by_key(key, value);
}

static void	ft_export_handle_empty_value(char *key)
{
	char *sanitize_check = key;
	
	while (*sanitize_check != '\0')
	{
		if (!(ft_isalpha(*sanitize_check) || *sanitize_check == '_'))
		{
			printf("Invalid variable name: %s\n", key);
			g_minishell->exit_status = 1;
			return ();
		}
		sanitize_check++;
	}
	env_set_value_by_key(key, "");
}

static void	ft_export_preserve_variables(char *key, char *value)
{
	char *declaration = (char *)malloc(strlen(key) + strlen(value) + 15);
	sprintf(declaration, "declare -x %s=\"%s\"", key, value);
	env_set_value_by_key(declaration, ""); // Export as an empty value
	free(declaration);
}

void	ft_export(t_ast_node *node)
{
	int		i;
	char	*arg;
	char	*equal_sign;
	char	*key;
	char	*value;

	i = 0;
	if (node->argv_count == 1)
	{
		env_print_list();
		return ();
	}
	while (++i < node->argv_count)
	{
		arg = node->exec_argv[i];
		equal_sign = ft_strchr(arg, '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			key = arg;
			value = equal_sign + 1;
			if (*key && *value)
				ft_export_validate_and_execute(key, value);
		}
		else
			ft_export_handle_empty_value(arg);
		
		if (*key && *value)
			ft_export_preserve_variables(key, value);
	}
	g_minishell->exit_status = 0;
}