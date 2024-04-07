cmake_minimum_required(VERSION 3.5)




# Registra los componentes de tu proyecto
idf_component_register(SRCS "main.c"
                       INCLUDE_DIRS  "."
                       REQUIRES moduloA driver )
