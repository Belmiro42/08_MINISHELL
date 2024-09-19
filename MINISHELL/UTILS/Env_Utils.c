/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Env_Utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 07:54:09 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/08 13:42:39 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

char	*get_val_env(char *key, t_env *environment)
{
	t_env	*cpy;

	cpy = environment;
	while (cpy)
	{
		if (ft_strncmp(cpy->key, key, ft_strlen(key) + 1) == 0)
			return (ft_strdup(cpy->value));
		cpy = cpy->next;
	}
	return (NULL);
}

void	new_val_env(char *key, char *new_val, t_env **environment)
{
	t_env	*cpy;
	t_env	*new;

	cpy = *environment;
	while (cpy)
	{
		if (ft_strncmp(cpy->key, key, ft_strlen(key)) == 0)
		{
			free(cpy->value);
			cpy->value = ft_strdup(new_val);
			return ;
		}
		cpy = cpy->next;
	}
	cpy = *environment;
	while (cpy->next)
		cpy = cpy->next;
	new = malloc(sizeof(t_env));
	new->key = ft_strdup(key);
	new->value = ft_strdup(new_val);
	new->next = NULL;
	cpy->next = new;
}

// TODO: TODO: UNTESTED
void	del_var_env(char *key, t_env **environment)
{
	t_env	*cpy;
	t_env	*tmp;

	cpy = *environment;
	tmp = NULL;
	if (ft_strncmp(cpy->key, key, ft_strlen(key) + 1) == 0)
	{
		*environment = (*environment)->next;
		free(cpy->key);
		free(cpy->value);
		free(cpy);
	}
	while (cpy->next != NULL)
	{
		tmp = cpy;
		cpy = cpy->next;
		if (ft_strncmp(cpy->key, key, ft_strlen(key) + 1) == 0)
		{
			tmp->next = cpy->next;
			free(cpy->key);
			free(cpy->value);
			free(cpy);
			return ;
		}
	}
}

char	**env_to_char(t_env *env)
{
	char	**envp;
	char	**envp_cpy;
	int		count;
	t_env	*cpy;
	int		buffer;

	count = 0;
	env = env->next;
	cpy = env;
	while (cpy && ++count)
		cpy = cpy->next;
	envp = malloc(sizeof(char *) * (count + 1));
	envp_cpy = envp;
	while (env)
	{
		buffer = ft_strlen(env->key) + ft_strlen(env->value) + 2;
		*envp_cpy = malloc(sizeof(char) * (buffer));
		ft_strlcpy(*envp_cpy, env->key, buffer);
		ft_strlcat(*envp_cpy, "=", buffer);
		ft_strlcat(*envp_cpy, env->value, buffer);
		env = env->next;
		envp_cpy++;
	}
	return ((void)(*envp_cpy = NULL), envp);
}
