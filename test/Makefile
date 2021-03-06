#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/29 13:16:03 by mcanal            #+#    #+#              #
#    Updated: 2017/10/03 21:21:16 by mc               ###   ########.fr        #
#                                                                              #
#******************************************************************************#

##
## CUSTOM CONFIG
##

# name of the binary to make
NAME =		test_nibbler

# file-names of the sources
SRCS =      test_main.cpp			\
			test_parse_argv.cpp		\
			test_map.cpp			\
			test_player.cpp			\
			test_game.cpp

# folder-names of the sources (':' separated list)
VPATH =		src:src/argv_parser:src/game

# where is the tested project?
ROOT_DIR =	..

# # sdl
# SDL_DIR =	$(ROOT_DIR)/SDL
# SDL_INSTALL_DIR = $(shell pwd)/$(SDL_DIR)/install
# SDL_I_DIR =	`./$(SDL_DIR)/sdl2-config --cflags`
# SDL_LIB =	`./$(SDL_DIR)/sdl2-config --libs`
# SDL =		$(SDL_DIR)/build/libSDL2.la

# # libft
# LFT_DIR =	$(ROOT_DIR)/libft
# LFT_I_DIR = -I$(LFT_DIR)/inc
# LFT =		$(LFT_DIR)/libft.a
# LFT_LIB =	-L$(LFT_DIR) -lft

# minunit "framework"
MIN_DIR =	minunit
MIN_I_DIR = -I$(MIN_DIR)
MIN =		$(MIN_DIR)/minunit.h
MIN_LIB =

# folder-names containing headers files (prefix them with "-I")
I_DIR =		-Iinc	-I$(ROOT_DIR)/core/inc	-I$(ROOT_DIR)/core/inc/argv_parser	-I$(ROOT_DIR)/core/inc/game	$(MIN_I_DIR)	#$(SDL_I_DIR)	$(LFT_I_DIR)

# extra libraries needed for linking
LIBS =		$(MIN_LIB)	-ldl #$(SDL_LIB)		$(LFT_LIB)		-lm



##
## GLOBAL VARIABLES
##

# folder used to store all compilations sub-products (.o and .d mostly)
O_DIR =		obj
OBJS =		$(SRCS:%.cpp=$(O_DIR)/%.o)
DEPS =		$(OBJS:%.o=%.d)
TEST_OBJS =	$(shell find $(ROOT_DIR)/obj -name \*.o 2>/dev/null | grep -v main) #TODO

# specify flags for commands used in the following rules
RM =		rm -f
RMDIR =		rmdir -p
MKDIR =		mkdir -p
MAKE =		make
MAKEFLAGS =	-j
CXX =		$(shell clang --version &>/dev/null && echo clang++ || echo g++) -std=c++11
LD =		$(CXX)
CPPFLAGS =
CXXFLAGS =	-Wall -Wextra -Werror -O2
LDFLAGS =
LDLIBS =	$(LIBS)

# guess os and architecture
ifeq ($(OS), Windows_NT)
  CPPFLAGS += -D WIN32
  ifeq ($(PROCESSOR_ARCHITECTURE), AMD64)
    CPPFLAGS += -D AMD64
  else ifeq ($(PROCESSOR_ARCHITECTURE), x86)
    CPPFLAGS += -D IA32
  endif
else
  UNAME_S = $(shell uname -s)
  ifeq ($(UNAME_S), Linux)
    ECHO = echo -e
    CPPFLAGS += -D LINUX
    LDLIBS = -Wl,--whole-archive $(LIBS) -Wl,--no-whole-archive
  else ifeq ($(UNAME_S), Darwin)
    ECHO = echo
    CPPFLAGS += -D OSX
    LDLIBS = -Wl,-all_load $(LIBS) -Wl
  endif
  UNAME_P = $(shell uname -p)
  ifeq ($(UNAME_P), unknown)
    UNAME_P = $(shell uname -m)
  endif
  ifeq ($(UNAME_P), x86_64)
    CPPFLAGS += -D AMD64
  else ifneq ($(filter %86, $(UNAME_P)), )
    CPPFLAGS += -D IA32
  else ifneq ($(filter arm%, $(UNAME_P)), )
    CPPFLAGS += -D ARM
  endif
endif

# some colors for pretty printing
WHITE =		\033[37;01m
RED =		\033[31;01m
GREEN =		\033[32;01m
YELLOW =	\033[33;01m
BLUE =		\033[34;01m
BASIC =		\033[0m

# default to silent Makefile, but you can run ´VERBOSE=t make´
ifdef VERBOSE
CPPFLAGS += -D VERBOSE
else
.SILENT:
endif



##
## PUBLIC RULES
##

# just to avoid conflicts between rules and files/folders names
.PHONY: all debug sanitize me_cry re clean fclean mrproper

# classic build
all: $(O_DIR)
	$(MAKE) -C $(ROOT_DIR) $(FLAGS)
	$(MAKE) $(NAME) $(FLAGS)
	./$(NAME)

# build for gdb/valgrind debugging
debug: FLAGS = "CXXFLAGS = -g -ggdb"
debug: all

# build for clang runtime debugging (fsanitize)
sanitize: FLAGS = "CXXFLAGS = -g -ggdb -fsanitize=address,undefined -ferror-limit=5"
sanitize: all

# masochist build
me_cry: FLAGS = "CXXFLAGS = -Wall -Werror -Wextra -Wpedantic -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wcast-align -Wconversion -Wshadow -Weffc++ -Wredundant-decls -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Winline" #-Wcast-qual
me_cry: all

# clean build and recompile with previous flags
re: FLAGS = $(PREV_FLAGS)
re: fclean all

# remove all generated .o and .d
clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)

# remove the generated binary, and all .o and .d
fclean: clean
	$(RM) $(NAME)

# just clean everything this Makefile could have generated
mrproper: fclean $(O_DIR)
	$(RMDIR) $(O_DIR)
	$(MAKE) -C $(ROOT_DIR) fclean



##
## PRIVATE RULES
##

# read dependencies list generated by -MMD flag
-include $(DEPS)

# create binary (link)
$(NAME): $(OBJS)
	@$(ECHO) "$(BLUE)$(OBJS) $(TEST_OBJS) $(LDLIBS) $(WHITE)->$(RED) $@ $(BASIC)"
	$(CXX) $(CXXFLAGS) $(I_DIR) $(OBJS) $(TEST_OBJS) $(LDLIBS) -o $@ $(LDFLAGS)
	@$(ECHO) "$(WHITE)ldflags:$(BASIC) $(LDFLAGS)"
	@$(ECHO) "$(WHITE)cxxflags:$(BASIC) $(CXXFLAGS)"
	@$(ECHO) "$(WHITE)cppflags:$(BASIC) $(CPPFLAGS)"
	@$(ECHO) "$(WHITE)compi:$(BASIC) $(CXX)"

# create object files (compile)
$(O_DIR)/%.o: %.cpp
	@$(ECHO) "$(WHITE)$<\t->$(BLUE) $@ $(BASIC)"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(I_DIR) -MMD -c $< -o $@

# create directory for compilation sub-products
$(O_DIR):
	$(MKDIR) $(O_DIR)
