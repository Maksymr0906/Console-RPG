NAME = ConsoleRPG

SRC =   main.cpp Armor.cpp Enemy.cpp Entity.cpp Event.cpp Functions.cpp Game.cpp GameOption.cpp I_Printable.cpp Inventory.cpp Item.cpp Player.cpp Product.cpp Puzzle.cpp Weapon.cpp

SRCDIR = source/

OBJDIR = objects/


OBJ = $(addprefix $(OBJDIR), $(SRC:.cpp=.o))

FLAGS = -Wall -Werror -Wextra 

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) ./header/*.hpp
	g++ $(CXXFLAGS) $(OBJ) -o $(NAME)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJ) : $(OBJDIR)%.o : $(SRCDIR)%.cpp ./header/*.hpp
	g++ -std=c++17 $(FLAGS) -o $@ -c $< -I ./header

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)