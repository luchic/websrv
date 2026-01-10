
NAME = websrv

SRC_FOLDER = srcs
OBJ_FOLDER = out
INCLUDES = includes
INTERFACES = interfaces

SRC_FILES  = $(notdir $(wildcard $(SRC_FOLDER)/*.cpp))

OBJ_FILES = $(addprefix $(OBJ_FOLDER)/, $(SRC_FILES:.cpp=.o))

CXX = g++
# CXXFLAGS = -g -Wall -Wextra -Werror -std=c++17
CXXFLAGS = -g -std=c++17 -I$(INCLUDES) -I$(INTERFACES)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp | $(OBJ_FOLDER)
	$(CXX) $(CXXFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJ_FOLDER):
	mkdir $(OBJ_FOLDER)

clean:
	rm -fr $(OBJ_FOLDER)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re