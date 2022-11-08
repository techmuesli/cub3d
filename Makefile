NAME := cub3D
SRCFILES := main.c src/init.c src/cleanup.c src/run.c src/hooks.c src/input.c \
src/utils.c src/raycast.c src/keys.c src/input_check.c src/input_info.c src/input_map.c \
src/textures.c src/minimap.c src/raycast_utils.c src/minimap_utils.c src/startscreen.c \
src/network.c src/result.c src/create_map_files.c

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
