/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:31:50 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/11 20:23:38 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

int	g_signal_triggered;

static bool	whitespace_only(char *str)
{
	int	all_ws;

	all_ws = 1;
	while (*str)
	{
		if (!ft_isspace(*str))
			all_ws = 0;
		str++;
	}
	if (all_ws)
		return (true);
	return (false);
}

static void	execute_sets(t_set *set, t_env *environment)
{
	int		val;
	t_pipe	*pipe;

	val = 0;
	g_signal_triggered = 0;
	while (set && g_signal_triggered == 0)
	{
		if (set->exit_val == 0 || (set->exit_val == 1 && \
		ft_atoi(environment->value) != 0) || (set->exit_val == 2 && \
		ft_atoi(environment->value) == 0))
		{
			pipe = set->pipe;
			infunc_signals();
			if (pipe->next == NULL)
				set_exit_val(one_exec(set, environment), environment);
			else
				set_exit_val(multi_exec(set, environment), environment);
			default_signals();
		}
		set = set->next;
	}
	signals_exit_codes(environment);
}

void	process_input(char *input, t_set **set, t_env *environment)
{
	if (input[0] != 0 && !whitespace_only(input))
	{
		if (!parse_error(input, environment))
		{
			signals_exit_codes(environment);
			*set = construct_parser_struct(input, environment);
			if (*set)
			{
				if (no_errors(*set))
					execute_sets(*set, environment);
				free_parser_struct(*set);
			}
			else
				write(2, "Malloc Error\n", 13);
		}
		add_history(input);
	}
	free(input);
}

// DESCRIPTION: MAIN
int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	*environment;
	t_set	*set;

	print_shekk();
	default_signals();
	set = NULL;
	environment = create_env_variables(envp, argc, argv);
	while (true)
	{
		input = readline(GREEN "Minishekk▸ " WHITE);
		if (!input)
			break ;
		process_input(input, &set, environment);
	}
	exit_builtin(NULL, environment, NULL);
}
