SRC	=	src/noise.cpp	\
		src/utils3d.cpp	\
		src/main.cpp	\
		src/venom.cpp	\
		src/noise_map.cpp\

FLAGS = -Wall -Wextra

INSTALL_DIR = /usr/bin
NAME = -o noise

# OBJ	=	$(SRC:.cpp=.o)
# OBJ=$(subst .cpp,.o,$(SRCS))
# -lraylib -lbrcmGLESv2 -lbrcmEGL -lpthread -lrt -lm -lbcm_host -ldl -latomic
all:	$(SRC)
	g++ $(FLAGS) $(NAME) $(SRC) -I ./include/ -w -std=c++11 -I. -L. -lraylib -lGL -lopenal -lrt -lm -pthread -ldl -O3 -g -Wall -Wextra ./libglfw3.a
