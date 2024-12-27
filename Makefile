# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/27 14:25:10 by meferraz          #+#    #+#              #
#    Updated: 2024/12/27 17:30:41 by meferraz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                MINITALK PROJECT                              #
#==============================================================================#

# Main target names
NAME_SERVER = server
NAME_CLIENT = client
NAME_BONUS = minitalk_bonus

#------------------------------------------------------------------------------#
#                                COLORS & STYLES                               #
#------------------------------------------------------------------------------#

# ANSI color codes for prettier output
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

# Text style codes
BOLD = \033[1m
DIM = \033[2m
ITALIC = \033[3m
UNDERLINE = \033[4m

# Emojis for visual feedback
CHECK = ✓
CLEAN = 🧹
BUILD = 🔨
ROCKET = 🚀
BOOK = 📚
SPARKLES = ✨

#------------------------------------------------------------------------------#
#                            	  NAMES AND PATHS                              #
#------------------------------------------------------------------------------#

# Directory structure
BUILD_PATH = .build
SRC_PATH = src
BONUS_PATH = src_bonus
INC_PATH = inc
HEADERS = ${INC_PATH}/minitalk.h

LIBFT_PATH = libs/libft
LIBFT_ARC = ${LIBFT_PATH}/libft.a

# Source files for server and client
SRCS_SERVER = ${addprefix ${SRC_PATH}/, server.c}
SRCS_CLIENT = ${addprefix ${SRC_PATH}/, client.c}

# Object files derived from source files
OBJS_SERVER = ${addprefix ${BUILD_PATH}/, ${notdir ${SRCS_SERVER:.c=.o}}}
OBJS_CLIENT = ${addprefix ${BUILD_PATH}/, ${notdir ${SRCS_CLIENT:.c=.o}}}
OBJS_BONUS = ${addprefix ${BUILD_PATH}/, ${notdir ${SRCS_BONUS:.c=.o}}}

#------------------------------------------------------------------------------#
#                            	   FLAGS & COMMANDS                            #
#------------------------------------------------------------------------------#

CC = cc                           # Compiler to use
CFLAGS = -Wall -Wextra -Werror -g # Compiler flags for warnings/errors/debugging
LDFLAGS = -L${LIBFT_PATH} -lft

AR = ar rcs                       # Archive command to create static libraries
RM = rm -fr                       # Command to remove files/directories forcefully
MKDIR_P = mkdir -p                # Command to create directories (with parent)
INC = -I ${INC_PATH}              # Include path for header file
MAKE = make --no-print-directory -C
MAKE_EXTRA = make extra --no-print-directory -C

VALGRIND = valgrind
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

#------------------------------------------------------------------------------#
#                                    RULES                                     #
#------------------------------------------------------------------------------#

##  Compilation Rules for minitalk  ##

all: ${BUILD_PATH} deps ${NAME_SERVER} ${NAME_CLIENT}	## Compile minitalk

bonus: all			## Compile minitalk with bonus features
	@echo "[${CYAN}Compiled minitalk${RESET} ${YELLOW}with bonus!${RESET}] $(CHECK) ${YELLOW}🖔${RESET}"

${BUILD_PATH}/%.o: ${SRC_PATH}/%.c
	@${CC} ${CFLAGS} -c $< -o $@

${BUILD_PATH}:
	@${MKDIR_P} ${BUILD_PATH}
	@echo "* ${YELLOW}Creating ${BUILD_PATH} folder:${RESET} $(CHECK)"

${NAME_SERVER}: ${LIBFT_ARC} ${OBJS_SERVER}
	@echo "\n${CYAN}${BOLD}${DIM} Compiling minitalk Server...${RESET}"
	@${CC} ${CFLAGS} ${OBJS_SERVER} ${LIBFT_ARC} -o ${NAME_SERVER}
	@echo "${GREEN}Server compiled!${RESET} ${YELLOW}🎉${RESET}"

${NAME_CLIENT}: ${LIBFT_ARC} ${OBJS_CLIENT}
	@echo "\n${CYAN}${BOLD}${DIM} Compiling minitalk Client...${RESET}"
	@${CC} ${CFLAGS} ${OBJS_CLIENT} ${LIBFT_ARC} -o ${NAME_CLIENT}
	@echo "${GREEN}Client compiled!${RESET} ${YELLOW}🎉${RESET}"


${LIBFT_ARC}: deps
	@printf "${CYAN}${BOLD}${DIM} Compiling Libft...${RESET}\n"
	@${MAKE_EXTRA} ${LIBFT_PATH}
	@printf "${BLUE}${BOLD}${BUILD} ${WHITE}${LIBFT_ARC}${GREEN} compiled! ${RESET}\n"

deps:
	@if test ! -d "${LIBFT_PATH}"; then make get_libft; \
		else printf "${GREEN}${BOLD}${ROCKET} ${WHITE}${LIBFT_ARC}${GREEN} folder found!${RESET}\n"; fi

get_libft:
	@printf "${CYAN}${BOLD}${BOOK} Getting Libft...${RESET}\n"
	@git clone git@github.com:melaniereis/libft.git ${LIBFT_PATH}
	@printf "${GREEN}${BOLD}${ROCKET} ${WHITE}${LIBFT_ARC}${GREEN} successfully downloaded!${RESET}\n"

##  Norm Rules  ##

norm:                # Check norms for mandatory sources 
	@printf "\n${BLUE}${BOLD}${DIM} Checking Norminette...${RESET}\n"
	@norminette_output=$$(norminette *.c *.h | grep -v "OK!" || true); \
	if [ -z "$$norminette_output" ]; then \
		printf "${GREEN}${BOLD}${CHECK} No norminette errors found!${RESET}\n"; \
	else \
		printf "$$norminette_output\n"; \
		printf "${RED}${BOLD}❌ Norminette errors found.${RESET}\n"; \
	fi
	@printf "${GREEN}${BOLD}${CHECK} Norminette check completed!${RESET}\n"

##   Check for external functions  ##
check_external_functions: all               # Check norms for mandatory sources 
	@printf "\n${BLUE}${BOLD}${DIM} Checking External Functions...${RESET}\n"
	nm ./${NAME_SERVER} | grep "U" | grep -v "__"
	nm ./${NAME_CLIENT} | grep "U" | grep -v "__"
	@printf "${GREEN}${BOLD}${CHECK} External functions check completed!${RESET}\n"

##  Cleaning Rules  ##

clean:                       # Clean up object files and temporary build files 
	@printf "\n${YELLOW}${BOLD}${CLEAN} Cleaning object files...${RESET}\n"
	@${RM} ${OBJS_SERVER} ${OBJS_CLIENT}
	@printf "${GREEN}${BOLD}${CHECK} Object files cleaned!${RESET}\n"

fclean: clean               # Fully clean up by removing executables and build directories 
	@printf "${YELLOW}${BOLD}${CLEAN} Removing executable, libft.a and build files...${RESET}\n"
	@${RM} ${NAME_SERVER} ${NAME_CLIENT}
	@${RM} ${BUILD_PATH}
#@${RM} ${LIBFT_PATH}
	@printf "${GREEN}${BOLD}${CHECK} All files cleaned!${RESET}\n"

re: fclean all          # Rebuild everything from scratch

.PHONY: all clean fclean re norm get_libft deps check_external_functions
