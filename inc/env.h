/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:50:39 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/30 13:47:31 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

const char	*env_get_value_by_key(const char *key);
int		init_envp(void);
void	env_print_list(void);

#endif