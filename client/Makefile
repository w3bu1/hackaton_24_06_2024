# directories
MLX_DIR   = mlx
OBJS_DIR  = obj
SRCS_DIR  = src
INCS_DIR  = inc

# build
NAME = fanorona

# files
SRCS_FILES = main.c

# objects
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS_FILES:.c=.o))

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CLINKS = -L./$(MLX_DIR) -lmlx -lX11 -lXext -lm  -I $(INCS_DIR)

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ $(CLINKS)

$(NAME) : $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(CLINKS)

all : $(NAME)

clean :
	@rm -f $(OBJS)
	@rm -rf $(OBJS_DIR)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : re fclean clean all