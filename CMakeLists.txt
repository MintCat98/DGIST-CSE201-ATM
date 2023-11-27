cmake_minimum_required(VERSION 3.26)
project(DGIST_CSE201_ATM)

set(CMAKE_CXX_STANDARD 14)

include_directories(Src)

add_executable(DGIST_CSE201_ATM
        Src/Account.cpp
        Src/Account.h
        Src/ATM.cpp
        Src/ATM.h
        Src/Bank.cpp
        Src/Bank.h
        Src/Card.cpp
        Src/Card.h
        Src/Customer.cpp
        Src/Customer.h
        Src/Feeinitialize.cpp
        Src/Feeinitialize.h
        Src/main.cpp
        Src/Transaction.cpp
        Src/Transaction.h)
