include $(config_dir)rel.mk

# this_lint_cmd :=
this_lint_cmd = $(prorab_lint_cmd_clang_tidy)

this_cxxflags += -fsanitize=address
this_ldflags += -fsanitize=address
