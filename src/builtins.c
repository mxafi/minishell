/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:58:09 by lclerc            #+#    #+#             */
/*   Updated: 2023/08/16 13:53:23by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Execute the pwd built-in command.
 * 
 * This function prints the current working directory to stdout and updates the
 * exit status in g_minishell.
 */
void	ft_pwd(void)
{
	char	*working_directory_path;

	working_directory_path = getcwd(NULL, 0);
	if (working_directory_path == NULL)
	{
		perror("getcwd");
		g_minishell->exit_status = 1; // Set exit status
		return ;
	}
	ft_putstr_fd(working_directory_path, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(working_directory_path);
	// Set the proper exit status
	g_minishell->exit_status = 0;
}

/**
 * @brief Execute the echo built-in command.
 * 
 * This function prints the arguments to stdout with an optional newline and
 * updates the exit status in g_minishell.
 * 
 * @param node The AST node representing the echo command.
 */
void	ft_echo(t_ast_node *node)
{
	t_bool	print_newline;
	int		argument_count;
	int		flag_length;

	argument_count = 1;
	print_newline = TRUE;
	flag_length = ft_strlen(node->exec_argv[1]);
	if (node->argv_count > 1 && !ft_strncmp(node->exec_argv[1], "-n", 2) &&
		flag_length == 2)
	{
		print_newline = FALSE;
		argument_count++;
	}
	while (argument_count < node->argv_count)
	{
		ft_putstr_fd(node->exec_argv[argument_count], STDOUT_FILENO);
		if (argument_count < node->argv_count - 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
		argument_count++;
	}
	if (print_newline == TRUE)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_minishell->exit_status = 0;
}

/**
 * @brief Execute the cd built-in command.
 * 
 * This function changes the current working directory and updates the exit 
 * status in g_minishell.
 * 
 * @param node The AST node representing the cd command.
 */
void	ft_cd(t_ast_node *node)
{
	char	*path;

	path = node->exec_argv[1];
	if (chdir(path) != 0)
	{
		perror("☠️  shellfishy ☠️  > cd");
		g_minishell->exit_status = 1;
		return ;
	}
	g_minishell->exit_status = 0;
}

void	ft_exit(t_ast_node *node)
{
	int	i;

	ft_putstr_fd("exit\n", 1);
	g_minishell->exit_status = 0;
	if (node->argv_count > 2)
	{
		ft_putstr_fd("shellfishy: exit: too many arguments\n", 2);
		g_minishell->exit_status = 1;
	}
	else if (node->argv_count == 2)
	{
		i = 0;
		while (ft_isdigit((int)node->exec_argv[i]))
			i++;
		if (node->exec_argv[i] == '\0')
			exit(ft_atoi(node->exec_argv[1]) % 255);
		ft_putstr_fd("shellfishy: exit: ", 2);
		ft_putstr_fd(node->exec_argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	else
		exit(0);
}

/**
 * @brief Execute the unset built-in command.
 *
 * This function unsets the specified environment variable.
 * 
 * @param node The token representing the unset command.
 */
void	ft_unset(t_ast_node *node)
{
	int	argument_count;

	argument_count = 1;
	while (argument_count < node->argv_count)
	{
		env_unset_key(node->exec_argv[argument_count]);
		argument_count++;
	}
	g_minishell->exit_status = 0;
}

static void	ft_export_validate_and_execute(char *key, char *value)
{
	char *sanitize_check = key;

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
		return ;
	}
	while (++i < node->argv_count)
	{
		arg = node->exec_argv[i];
		equal_sign = ft_strchr(arg, '=');
		if (equal_sign) // Split the argument at '=' to get key and value
		{
			*equal_sign = '\0';
			key = arg;
			value = equal_sign + 1;
			if (*key) // Check if key is not empty
				ft_export_validate_and_execute(key, value);
		}
		else // Export the key with an empty value and check if key is valid
			ft_export_validate_and_execute(arg, "");
		
		//if (*key && *value) // Preserve the exported variables across new shell sessions
		//{
			//char *declaration = (char *)malloc(strlen(key) + strlen(value) + 15);
			//sprintf(declaration, "declare -x %s=\"%s\"", key, value);
			//env_set_value_by_key(declaration, ""); // Export as an empty value
			//free(declaration);
		//}
	}
	g_minishell->exit_status = 0;
}


