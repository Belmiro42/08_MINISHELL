/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:14:29 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/08 12:53:15 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

static void	shlvl(t_env *environment)
{
	char	*current;
	int		shlvl;

	shlvl = 0;
	current = get_val_env("SHLVL", environment);
	if (current)
	{
		shlvl = ft_atoi(current);
		free(current);
	}
	current = ft_itoa(shlvl + 1);
	new_val_env("SHLVL", current, &environment);
	free(current);
}

static void	create_env_nodes(char *key, char *value, t_env **env)
{
	t_env	*current;
	t_env	*cpy;

	current = malloc(sizeof(t_env));
	current->next = NULL;
	current->key = key;
	current->value = value;
	cpy = *env;
	while (cpy->next)
		cpy = cpy->next;
	cpy->next = current;
}

t_env	*create_env_variables(char **ex_variables, int argc, char **argv)
{
	char	*key;
	char	*value;
	int		equal_pos;
	int		length;
	t_env	*environment_variables;

	(void)(argc + (int)((unsigned long)(argv)));
	environment_variables = malloc(sizeof(t_env));
	if (!environment_variables)
		return (NULL);
	environment_variables->key = ft_strdup("?");
	environment_variables->value = ft_strdup("0");
	environment_variables->next = NULL;
	while (*ex_variables)
	{
		length = ft_strlen(*ex_variables);
		equal_pos = ft_strnstr(*ex_variables, "=", length) - *(ex_variables);
		key = ft_substr(*(ex_variables), 0, equal_pos);
		value = ft_substr(*(ex_variables), equal_pos + 1, length - equal_pos);
		create_env_nodes(key, value, &environment_variables);
		ex_variables++;
	}
	shlvl(environment_variables);
	return (environment_variables);
}
