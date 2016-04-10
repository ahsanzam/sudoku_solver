#-------------------------------------------------
#
# Project created by QtCreator 2016-04-08T13:06:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SudokuQT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        sudoku_solver.cpp

HEADERS  += mainwindow.h\
			sudoku_solver.h

FORMS    += mainwindow.ui
