CC = g++
CFLAGS = -Wall - Wextra - std = c++11  #Включаем все предупреждения и используем стандарт C++11
SRCS = filework.cpp main.cpp
HEADER = filework.h
OBJS = $(SRCS:.cpp = .o)
EXEC = VideoLibrary

all:    $(EXEC)

$(EXEC):    $(OBJS)
    $(CC) $(CFLAGS) $(OBJS) -o $(EXEC)


%.o: %.cpp $(HEADER)
    $(CC) $(CFLAGS) - c $ < -o $@
clean:
    rm - f $(OBJS) $(EXEC)
