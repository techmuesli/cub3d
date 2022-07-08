NAME := cub3D
SRCFILES := main.c init.c cleanup.c run.c hooks.c input.c utils.c raycast.c keys.c \
input_check.c input_info.c input_map.c textures.c minimap.c raycast_utils.c \
minimap_utils.c startscreen.c network.c result.c create_map_files.c

CC ?= cc
LD ?= cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft/
LIBFT = libft.a
UNAME_S := $(shell uname -s)
MINILBX_DIR = minilibx/
ifeq ($(UNAME_S), Darwin)
	MINILBX = libmlx.a
endif
ifeq ($(UNAME_S), Linux)
	MINILBX = libmlx_Linux.a
endif

$(NAME):
	$(MAKE) all -C $(LIBFT_DIR)
	$(MAKE) -C $(MINILBX_DIR)
	$(CC) $(CFLAGS) $(SRCFILES) $(LIBFT_DIR)$(LIBFT) $(MINILBX_DIR)$(MINILBX) \
		-L/usr/X11/include/../lib -lXext -lX11 -lm -lz -o $(NAME)

.PHONY: all bonus debug clean fclean re

all: $(NAME)

bonus: $(NAME)

debug: CFLAGS += -g3
debug:
	$(MAKE) debug -C $(LIBFT_DIR)
	$(MAKE) -C $(MINILBX_DIR)
	$(CC) $(CFLAGS) $(SRCFILES) $(LIBFT_DIR)$(LIBFT) $(MINILBX_DIR)$(MINILBX) \
		-L/usr/X11/include/../lib -lXext -lX11 -lm -lz -o $(NAME)

clean:
	$(MAKE) clean -C $(MINILBX_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all
