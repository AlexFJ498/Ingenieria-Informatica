NAME=main

#
OBJECTS = $(NAME).o funcionesAuxiliares.o Graph.o Edge.o Vertex.o Point2D.o

#
CPPFLAGS = -c -g -Wall -ansi -O2

INCLUDES = funcionesAuxiliares.hpp Graph.hpp Edge.hpp Vertex.hpp macros.hpp Point2D.hpp

# Macros predefinidas
#
# $@: nombre del objetivo
# $^: todas las dependencias
# $<: primera dependencia
#

objetivo: $(NAME).exe

#Opciones para NO depurar los asertos
ndebug: CPPFLAGS += -DNDEBUG 
ndebug: objetivo

# Primer objetivo 
$(NAME).exe: $(OBJECTS)
			@echo "Generando " $@
			@g++ $^ -o $@
#
$(NAME).o: $(NAME).cpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

#
funcionesAuxiliares.o: funcionesAuxiliares.cpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

#
Graph.o: Graph.cpp Graph.hpp \
		  Edge.hpp Vertex.hpp \
		  Vertex.hpp Point2D.hpp
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

#
Edge.o: Edge.cpp Edge.hpp   
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<


#
Vertex.o:  Vertex.cpp Vertex.hpp
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

#
Point2D.o:  Point2D.cpp Point2D.hpp
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<





# Generación de la documentación
doc: Doxyfile 
	@echo "Generando la documentación con doxygen"
	@doxygen
  
# Borrado
.PHONY: clean  
clean:
	@echo "Borrando los ficheros superfluos"
	@rm -f $(OBJECTS) *~ 

