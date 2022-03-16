CC = c++
FLAGS = -std=c++98 -Wall -Wextra -Werror
SRCS = main.cpp
SRCS_FT = ft_main.cpp
SRCS_STD = std_main.cpp

OBJ = $(SRCS:.cpp=.o)
OBJ_FT = $(SRCS_FT:.cpp=.o)
OBJ_STD = $(SRCS_STD:.cpp=.o)
RM = rm -f
NAME = containers
NAME_FT = ft_containers
NAME_STD = std_containers


%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ) stack.hpp vector.hpp map.hpp utils.hpp ft_iterator_traits.hpp ft_iterator.hpp ft_reverse_iterator.hpp ft_map_iterator.hpp RBtree.hpp
	$(CC) -o $(NAME) $(OBJ)

$(NAME_FT): $(OBJ_FT) stack.hpp vector.hpp map.hpp utils.hpp ft_iterator_traits.hpp ft_iterator.hpp ft_reverse_iterator.hpp ft_map_iterator.hpp RBtree.hpp
	$(CC) -o $(NAME_FT) $(OBJ_FT)

$(NAME_STD): $(OBJ_STD) stack.hpp vector.hpp map.hpp utils.hpp ft_iterator_traits.hpp ft_iterator.hpp ft_reverse_iterator.hpp ft_map_iterator.hpp RBtree.hpp
	$(CC) -o $(NAME_STD) $(OBJ_STD)

all: $(NAME)

clean:
	$(RM) $(OBJ) $(OBJ_FT) $(OBJ_STD)

fclean:
	$(RM) $(NAME) $(NAME_FT) $(NAME_STD) $(OBJ) $(OBJ_FT) $(OBJ_STD)

re: fclean all

ft: $(NAME_FT)

std: $(NAME_STD)


