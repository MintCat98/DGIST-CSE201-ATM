cmake_minimum_required(VERSION 3.26)
project(Src)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Src
        Account.cpp
        Account.h
        ATM.cpp
        ATM.h
        Bank.cpp
        Bank.h
        Card.cpp
        Card.h
        Customer.cpp
        Customer.h
        main.cpp
        Transaction.cpp
        Transaction.h)
