TARGET = bin/runner

#Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
LIB_DIR =

#Options
CC = g++
SRC_EXT = .cpp
RM = rm -rf

#List classes here
CLASS = main\
		entity/Background\
		entity/Eraser\
		entity/Laser\
		UICurses\
		entity/Minions\
		entity/Ship\
		Game\

#List interfaces here
INTERFACE = \
		IEntity\

#Auto var
SRC = $(addsuffix $(SRC_EXT), $(addprefix $(SRC_DIR)/, $(CLASS)))
OBJ = $(addsuffix .o, $(addprefix $(BUILD_DIR)/, $(CLASS)))
DEP = $(addsuffix .d, $(addprefix $(BUILD_DIR)/, $(CLASS)))
LIBS = $(addprefix -L,$(LIB_DIR))

#Flags
CFLAGS =-MMD -Wall -Wextra -Werror -O3 -g -std=c++98
LFLAGS =

#Libs
LIB_LOCAL = \

LIB_GLOBAL = \
			ncurses\

LIB_OTHER = \

LIBS += $(addsuffix /lib, $(addprefix -L, $(LIB_LOCAL)))
LIBS += $(addprefix -l,$(LIB_GLOBAL))
LIBS += $(LIB_OTHER)

#Includes
INC += $(addprefix -I,$(INC_DIR))
INC += $(addsuffix /include, $(addprefix -I, $(LIB_LOCAL)))

#RULES
all : dirbin $(TARGET)

clean :
	$(RM) $(BUILD_DIR)

fclean :
	$(RM) $(BUILD_DIR) $(TARGET)

re : fclean all

dirbin:
	mkdir -p bin

.PHONY: all clean fclean re

.SILENT: dirbuild dirbin

#Build rule
$(TARGET) : $(OBJ)
	@echo "\n\033[1;4;34mLNK:\033[0m\n"$^"\n\033[36mLinking objects ...\033[0m\n"
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

#Compilation rule
$(BUILD_DIR)/%.o: $(SRC_DIR)/%$(SRC_EXT)
	@mkdir -p $(dir $@)
	@echo "\n\033[1;4;34mCMP:\033[0m\n"$<"\n\033[36mCompiling src ...\033[0m"
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

-include $(DEP)
