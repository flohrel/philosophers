###############
## Variables ##
###############

NAME		=	philo

VPATH		=	src
OBJDIR		=	obj
INCLDIR		=	incld

MAIN		=	main.c
UTILS		=
TEST		=
SRC			=	$(MAIN) $(UTILS) $(TEST)
OBJ			=	$(SRC:%.c=$(OBJDIR)/%.o)

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g3
INCFLAGS	=	-I./$(INCLDIR)
RM			=	/bin/rm -rf
UNAME		:=	$(shell uname -s)


###########
## Rules ##
###########

.PHONY:			all bonus clean fclean re

all:			$(NAME)

$(OBJDIR)/%.o:	%.c | $(OBJDIR)
				$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR):
				mkdir $(OBJDIR)

bonus:
				@make all

clean:
				$(RM) $(OBJ)

fclean:			clean
				$(RM) $(NAME) $(OBJDIR)

re:				fclean all
