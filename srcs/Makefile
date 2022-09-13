NAME = containers

V_SRCS	= ./vector/main.cpp
S_SRCS	= ./stack/main.cpp
M_SRCS	= ./map/test.cpp

V_INCLUDES = -I./vector
S_INCLUDES = -I./stack
M_INCLUDES = -I./map

V_OBJS = $(V_SRCS:.cpp=.o)
S_OBJS = $(S_SRCS:.cpp=.o)
M_OBJS = $(M_SRCS:.cpp=.o)

CXX = clang++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

all: ${NAME}

${NAME}: vector stack map

vector: $(V_OBJS)
		$(CXX) $(CXXFLAGS) $(V_INCLUDES) -o ft_vector $(V_OBJS)

stack:	$(S_OBJS)
		$(CXX) $(CXXFLAGS) $(S_INCLUDES) -o ft_stack $(S_OBJS)

map: 	$(M_OBJS)
		$(CXX) $(CXXFLAGS) $(M_INCLUDES) -o ft_map $(M_OBJS)
		
clean:
		rm -f $(V_OBJS) $(S_OBJS) $(M_OBJS)

fclean: clean
		rm ft_vector ft_stack ft_map

re: fclean all

.PHONY: all clean fclean re