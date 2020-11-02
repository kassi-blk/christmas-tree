cflags = -Wall -Wextra -Iinclude -g
ldeps  = -g -lncurses -lm

srcs_dir = src
objs_dir = obj
bin_dir  = bin

srcs = $(addprefix $(srcs_dir)/,main.c tree.c)
objs = $(srcs:$(srcs_dir)/%.c=$(objs_dir)/%.o)

.PHONY: all
all: $(bin_dir)/prog

$(bin_dir)/prog: $(objs) | $(bin_dir)
	@gcc $(ldeps) -o $@ $^

$(objs_dir)/%.o: $(srcs_dir)/%.c | $(objs_dir)
	@gcc $(cflags) -c $< -o $@

$(objs_dir):
	@[ -d $(objs_dir) ] || mkdir $(objs_dir)

$(bin_dir):
	@[ -d $(bin_dir) ] || mkdir $(bin_dir)

.PHONY: clean
clean:
	@rm -rf $(objs_dir) $(bin_dir)
