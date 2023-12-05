cmake_minimum_required(VERSION 3.21)
project(Meta2POO)

set(CMAKE_CXX_STANDARD 23)

add_executable(Meta2POO main.cpp Objetos/Animal.cpp Objetos/Animal.h Objetos/Animal.h Objetos/Alimento.h Objetos/Alimento.cpp Visual/Terminal.cpp Visual/Terminal.h Objetos/Especificacao/Comida.h Objetos/Especificacao/Comida.cpp Visual/Reserva.cpp Visual/Reserva.h Visual/curses.h Objetos/Especificacao/Especie.cpp Objetos/Especificacao/Especie.h Objetos/Especificacao/Categoria.cpp Objetos/Especificacao/Categoria.h helpers.cpp helpers.h)

target_link_libraries(${PROJECT_NAME} c:/PDCurses-3.9/wincon/pdcurses.a)
