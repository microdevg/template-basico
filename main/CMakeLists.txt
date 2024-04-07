cmake_minimum_required(VERSION 3.5)




# Registra el componente principal
idf_component_register(SRCS "main.c"
                       INCLUDE_DIRS  "."
                       REQUIRES moduloA driver )
