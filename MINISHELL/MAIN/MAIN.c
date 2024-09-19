/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MAIN.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:31:50 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/07 10:39:55 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

int g_signal_triggered;

// LEGACY CODE -PRINT STRUCTURE
/*static void print_sets(t_set *cpy)
{
	t_pipe		*pipe;
	t_input		*input;
	t_output	*output;
	t_token		*hmm;
	t_token		*real_one;

	while (cpy)
	{
		printf("Pipeset Value: %d\nPipeset Rawtext: %s\n", cpy->exit_val, cpy->raw_text);
		pipe = cpy->pipe;
		while (pipe)
		{
			printf("\tPIPE %s\n", pipe->raw_text);
			input = pipe->in;
			while (input)
			{
				printf("\t\tIN:  %d\t%s \t%s \t%d\n", input->heredoc, input->filename, input->tmp, input->expand);
				input = input->next;
			}
			output = pipe->out;
			printf("\n");
			while (output)
			{
				printf("\t\tOUT: %d\t%s\n", output->append, output->filename);
				output = output->next;
			}
			printf("\n");
			printf("STRUCT\n");
			hmm = pipe->token;
			while (hmm)
			{
				printf("NEW STRUCT NEW STRUCT NEW STRUCT NEW STRUCT NEW STRUCT\n");
				printf("Token -> Token                  : %s\n", hmm->token);
				if (hmm->quoted_expanded)
					printf("Token -> Quoted_Expansion->Token: %s\n", hmm->quoted_expanded->token);
				real_one = hmm->real_tokens;
				while (real_one)
				{
					printf("Token -> Real_Token->Token   	: %s\n", real_one->token);
					real_one = real_one->next;
				}
				hmm = hmm->next;
			}
			int i = 0;
			//printf("ARG COUNT %d\n", ft_arrlen(pipe->args));
			if (pipe->args)
				while (i < ft_arrlen(pipe->args))
				{
					printf("TOKEN: %s\n", pipe->args[i]);   
					i++;
				}
			printf("\n");
			pipe = pipe->next;
		}
		cpy = cpy->next;
	}
}*/

static bool whitespace_only(char *str)
{
	int all_ws;

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

static void set_exit_val(int exit_val, t_env *environment)
{
	free(environment->value);
	environment->value = ft_itoa(exit_val % 256);
}

static void execute_sets(t_set *set, t_env *environment)
{
	int		val;
	t_pipe	*pipe;

	val = 0;
	while (set && g_signal_triggered == 0)
	{
		if (set->exit_val == 0 || (set->exit_val == 1 && ft_atoi(environment->value) != 0) || (set->exit_val == 2 && ft_atoi(environment->value) == 0))
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
	if (g_signal_triggered)
		set_exit_val(130, environment);
	g_signal_triggered = 0;
}

void process_input(char *input, t_set **set, t_env *environment, int *exit)
{
	if (input[0] != 0 && !whitespace_only(input))
	{
		if (!parse_error(input, environment))
		{
			*set = construct_parser_struct(input, environment);
			//print_sets(*set);
			if (*set)
			{
				if (no_errors(*set) )
					execute_sets(*set, environment);
				free_parser_struct(*set);
			}
			else
				write(2, "Malloc Error\n", 13);
		}
		else
			*exit = 2;
		add_history(input);
	}
	free(input);
}

// static void print_shekk()
// {
// 	printf("\
// 						\x1B[32m\n\
// 		⢀⡴⠑⡄⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ \n\
// 		⠸⡇⠀⠿⡀⠀⠀⠀⣀⡴⢿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀ \n\
// 		⠀⠀⠀⠀⠑⢄⣠⠾⠁⣀⣄⡈⠙⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀ \n\
// 		⠀⠀⠀⠀⢀⡀⠁⠀⠀⠈⠙⠛⠂⠈⣿⣿⣿⣿⣿⠿⡿⢿⣆⠀⠀⠀⠀⠀⠀⠀ \n\
// 		⠀⠀⠀⢀⡾⣁⣀⠀⠴⠂⠙⣗⡀⠀⢻⣿⣿⠭⢤⣴⣦⣤⣹⠀⠀⠀⢀⢴⣶⣆ \n\
// 		⠀⠀⢀⣾⣿⣿⣿⣷⣮⣽⣾⣿⣥⣴⣿⣿⡿⢂⠔⢚⡿⢿⣿⣦⣴⣾⠁⠸⣼⡿ \n\
// 		⠀⢀⡞⠁⠙⠻⠿⠟⠉⠀⠛⢹⣿⣿⣿⣿⣿⣌⢤⣼⣿⣾⣿⡟⠉⠀⠀⠀⠀⠀ \n\
// 		      \x1B[37m⠚⣦⣤⠤⠤⣤⡴⠗⠃ \x1B[32m			\n\
// 	.  .._..  .._.\x1B[37m⢰⣿⣿⣤⣀⡈⠃⣶⡆⠐⣶⡶⡶⠲⣦⢰⣶⡆⣰⡶⢰⣶⡆⣰⡶\x1B[32m\n\
// 	|\\/| | |\\ | | \x1B[37m⣉⠛⠻⠿⣿⣷⣼⣿⡷⠶⣿⣿⡗⠒⠛⢹⣿⣿⣯⡀⣿⣿⣯⡀\x1B[32m\n\
// 	|  |_|_| \\|_|_\x1B[37m⢿⣦⣀⣠⣿⠟⠼⠿⠇⠠⠿⠧⠻⠟⠋⠸⠿⠇⠹⣷⠸⠿⠇⠹⣷⡄\x1B[32m\n");
// 	//usleep(1000000);
// 	printf("\
// 	  		Behind every shell is a \x1B[37mshekk\x1B[32m...\n\
// \x1B[32m\n\n\n");
// 	//usleep(2000000);
// }

// DESCRIPTION: MAIN
int main(int argc, char **argv, char **envp)
{
	char *input;
	int exit_code;
	t_env *environment;
	t_set *set;

	g_signal_triggered = 0;
	//print_shekk();
	default_signals();
	set = NULL;
	environment = create_env_variables(envp, argc, argv);
	while (true)
	{
		input = readline(GREEN "Minishekk▸ " WHITE);
		if (!input)
			break;
		process_input(input, &set, environment, &exit_code);
	}
	exit_builtin(NULL, environment, NULL);
}
