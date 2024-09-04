cmake_minimum_required(VERSION 3.15)

project(8080)

add_executable(emulator 8080_emulator.c 8080_disassembler.h 8080_disassembler.c)
