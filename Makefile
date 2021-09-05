CC = gcc

NAME_SERVER	= server
NAME_CLIENT	= client


HEADERS =	minitalk.h

FLAGS	= 	

SRC_SERVER  = server.c 
SRC_CLIENT  = client.c


OBJ_SERVER		=	$(patsubst %.c, %.o, $(SRC_SERVER))
OBJ_CLIENT		=	$(patsubst %.c, %.o, $(SRC_CLIENT))


all		:	$(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER)	:	$(SRC_SERVER)
	gcc $(FLAGS) -c $(SRC_SERVER)
	gcc $(FLAGS) $(OBJ_SERVER) -o $(NAME_SERVER)

$(NAME_CLIENT) : $(SRC_CLIENT)
	gcc $(FLAGS) -c $(SRC_CLIENT)
	gcc $(FLAGS) $(OBJ_CLIENT) -o $(NAME_CLIENT) 


clean	:
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)

fclean	:	clean
	rm -f $(NAME) 
	rm -f $(NAME_BONUS) 

re:	fclean all

.PHONY	:	all clean fclean re