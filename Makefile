# Nom de sortie
NAME = ft_select 

# Détection de l'OS
OS = $(shell uname -s)

# Options de compilation
CC = @gcc
CFLAGS = -Wall -Werror -Wextra
ifeq ($(OS), Linux)
	CFLAGSUP = -Wno-sign-compare -Wno-empty-body #-fsanitize=address
else
	CFLAGSUP = -Wno-sign-compare #-fsanitize=address
endif
CPPFLAGS = -I $(INC_PATH) -I $(LIB_INC)
CLIB = -L $(LIBFT) -lft -ltermcap

# Headers
INC_PATH = includes/
INC_FILE = ft_select.h 

# Fichiers sources
SRC_PATH = src/
SRC_FILE = main.c error.c error_init.c error_term.c get_term.c key.c launch.c list.c list_move.c list_move2.c signal.c struct.c struct_is.c struct_member.c window.c

# Variables
PROJET = ft_select
LIBFT = libft/
LIB_INC = $(LIBFT)includes/
OBJ = $(SRC:.c=.o)
LIB = $(LIBFT)libft.a

INC = $(addprefix $(INC_PATH), $(INC_FILE))
SRC = $(addprefix $(SRC_PATH), $(SRC_FILE))

# Règles globales
all: libft $(NAME)

$(OBJ): $(INC)

$(NAME): Makefile $(OBJ) $(LIB)
	@echo "$(CYAN)Compilation de $(NAME)$(RESET)"
	@$(CC) $(CFLAGS) $(CFLAGSUP) $(CPPFLAGS) $(OBJ) $(CLIB) -o $(NAME)

clean: del cleanlib

fclean: delall fcleanlib

re: fclean all

# Règles pour le projet
del:
	@echo "Suppression des fichiers objets de $(NAME)"
	@rm -f $(OBJ)

delall: del
	@echo "Suppression de l'exécutable $(NAME)"
	@rm -f $(NAME)

reproj: delall all

# Règles pour libft
libft:
	@echo "$(VERT)Compilation...$(RESET)"
	@make -C $(LIBFT) all

cleanlib:
	@make -C $(LIBFT) clean

fcleanlib:
	@make -C $(LIBFT) fclean

relib:
	@make -C $(LIBFT) re

# Règles supplémentaires
normeinc:
	@echo "$(MAGEN)Norme des headers$(RESET)"
	@norminette includes/*.h

normesrc:
	@echo "$(MAGEN)Norme des sources$(RESET)"
	@norminette src/

msg:
	@echo "$(MAGEN)Norme pour $(NAME) :$(RESET)"

norme: delall msg normeinc normesrc

normeall: norme
	@echo
	@make -C $(LIBFT) norme

doxygen:
	@echo "$(CYAN)Génération de la documentation de $(PROJET)$(RESET)"
	@mkdir -p Docs
	@$(DOXYGEN) $(PROJET).doxyconf > Docs/$(PROJET).log

cleandoxy:
	@echo "Suppression de la documentation de $(PROJET)"
	@rm -rf Docs/

fcleanall: cleandoxy fclean

# Couleurs
RESET = \033[0m
BLANC = \033[37m
BLEU  = \033[34m
CYAN  = \033[36m
JAUNE = \033[33m
MAGEN = \033[35m
NOIR  = \033[30m
ROUGE = \033[31m
ROUGEC = \033[1;31m
VERT  = \033[32m

# Variables
DOXYGEN = doxygen

.PHONY: all clean fclean re del delall libft cleanlib fcleanlib relib norme normeall
