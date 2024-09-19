# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: razamora <razamora@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/13 15:53:30 by bmatos-d          #+#    #+#              #
#    Updated: 2024/09/11 18:14:12 by razamora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

REMOVE	  = rm -rf
CC	  	  = cc
CFLAGS	  =-Wall -Werror -Wextra -g3
EXTRAFLAG = -lreadline -fsanitize=leak -fsanitize=address
NAME	  = minishell
MAKEFLAGS = --no-print-directory

LIBFT		= LIBFT/libft.a
LIBFT_PATH  = LIBFT

BLTN_PATH = ./BUILTINS
BLTN_SRCS = Builtin_cd.c							\
			Builtin_echo.c							\
			Builtin_env.c							\
			Builtin_exit.c							\
			Builtin_export.c						\
			Builtin_pwd.c							\
			Builtin_unset.c

ENVR_PATH = ./ENVIRONMENT
ENVR_SRCS = Initialise.c

LIBR_PATH = ./LIBERATION
LIBR_SRCS = Liberation.c							\

PARS_PATH = ./PARSING
PARS_SRCS = 0_Parse_Error.c							\
			1_Split_Lists.c							\
			2_Split_Pipes.c							\
			3_Tokenise.c							\
			4_Quote_Split.c							\
			5_Word_Splitting.c						\
			6_Empty_Tokens.c						\
			7_Make_Struct.c							\
			8_Heredoc_Expand.c

SIGN_PATH = ./SIGNALS
SIGN_SRCS = Signal_Handling.c 						\
			Signal_Bash.c

UTIL_PATH = ./UTILS
UTIL_SRCS = Builtin_Utils.c							\
			Struct_Alloc_Utils.c					\
			Var_Exp_Utils.c							\
			Env_Utils.c								\
			Here_Doc_Var_Patch.c					\
			Errors_Utils.c							\
			String_Utils.c							\
			Tokenise_Utils.c						\
			Ambiguous_Redirect.c					\
			Execution_Utils_1.c 					\
			Execution_Utils_2.c 					\
			Execution_Utils_3.c						\
			Liberation_Utils.c
			
EXEC_PATH = ./EXECUTION
EXEC_SRCS =  Multi_Exec.c							\
			Redirects.c 							\
			Handle_File.c 							\
			Single_Exec.c
					
MAIN_PATH = ./MAIN
MAIN_SRCS = Main.c \
			Shekk.c

SOURCES  := $(addprefix $(BLTN_PATH)/,$(BLTN_SRCS)) \
			$(addprefix $(ENVR_PATH)/,$(ENVR_SRCS)) \
			$(addprefix $(LIBR_PATH)/,$(LIBR_SRCS)) \
			$(addprefix $(PARS_PATH)/,$(PARS_SRCS)) \
			$(addprefix $(SIGN_PATH)/,$(SIGN_SRCS)) \
			$(addprefix $(EXEC_PATH)/,$(EXEC_SRCS)) \
			$(addprefix $(UTIL_PATH)/,$(UTIL_SRCS)) \
			$(addprefix $(MAIN_PATH)/,$(MAIN_SRCS))

OBJECTS	  = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT) 
	@ $(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(EXTRAFLAG) -o $(NAME)
	@ echo "Compiled"
	
$(LIBFT):
	@make re -C $(LIBFT_PATH) $(MAKEFLAGS)

clean:
	@ $(REMOVE) $(OBJECTS)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@ $(REMOVE) $(NAME)
	@$(RM) $(LIBFT)
	

re: fclean $(NAME)

.PHONY : clean re fclean all
