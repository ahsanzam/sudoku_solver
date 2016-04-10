#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include "sudoku_solver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void solve_puzzle(); //call solve functions in sudokuSolver
    void displayGrid(); //displays grid
    void exit(); //exits program
    void hideError(); //hides errro window

private:
    Ui::MainWindow *ui;

    int grid[9][9];

    QWidget* centralWidget;
    QHBoxLayout* centralLayout;
    QVBoxLayout* buttonsLayout;
    QPushButton* solveButton;
    QPushButton* exitButton;
    QWidget* buttonsWidget;
    QTextEdit* textEdit;
    QWidget* errorWidget;
    QVBoxLayout* errorLayout;
    QPushButton* okButton;
    QLabel* outputLabel;
    Sudoku* solver;

    void error(std::string message);
};

#endif // MAINWINDOW_H
