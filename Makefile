ANALEXSINC	=	src_analexsin/

CUADRUPLEC	=	src_cuadruples/

all:
				make -C $(ANALEXSINC)
				make -C $(CUADRUPLEC)

clean:
				make clean -C $(ANALEXSINC)
				make clean -C $(CUADRUPLEC)

fclean:
				make fclean -C $(ANALEXSINC)
				make distclean -C $(CUADRUPLEC)

re:				fclean all

.PHONY:			all clean fclean re
