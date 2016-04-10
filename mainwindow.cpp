#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sstream>
#include <string>
#include "sudoku_solver.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowTitle("Sudoku Solver");
    centralWidget = new QWidget();
    centralLayout = new QHBoxLayout( centralWidget );
    setCentralWidget( centralWidget );

    textEdit = new QTextEdit();
    QFont font("monospace", 20);
    textEdit->setFont(font);
    solver = new Sudoku();
    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++)
            solver->setval(i,j, 0);
    displayGrid();
    centralLayout->addWidget(textEdit);
    textEdit->setFixedWidth(270);
    textEdit->setFixedHeight(330);

    buttonsWidget = new QWidget();
    buttonsLayout = new QVBoxLayout( buttonsWidget );
    centralLayout->addWidget( buttonsWidget );

    solveButton = new QPushButton("Solve");
    buttonsLayout->addWidget(solveButton);
    connect(solveButton, SIGNAL(clicked()), this, SLOT(solve_puzzle()));

    exitButton = new QPushButton("Exit");
    buttonsLayout->addWidget( exitButton );
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exit()));

    errorWidget = new QWidget();
    errorWidget->setWindowTitle("Error");
    errorLayout = new QVBoxLayout();
    errorWidget->setLayout(errorLayout);
    outputLabel = new QLabel();
    errorLayout->addWidget(outputLabel);
    okButton = new QPushButton("Ok");
    errorLayout->addWidget(okButton);
    connect(okButton, SIGNAL(clicked()), this, SLOT(hideError()));
    errorWidget->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete exitButton;
    delete solveButton;
    delete buttonsLayout;
    delete buttonsWidget;
    delete textEdit;
    delete centralLayout;
    delete centralWidget;
    delete okButton;
    delete outputLabel;
    delete errorLayout;
    delete errorWidget;
    delete solver;
}

void MainWindow::displayGrid(){
    std::stringstream ss;
    for(int i=0; i<9; i++){
        if (i % 3 == 0) ss << "----------------------\n";
        for(int j=0; j<9; j++){
            if(j%3 == 0) ss << "|";
            ss << " " << solver->printval(i, j) << " " ;
        }
        ss << "\n" ;
    }
    ss << "----------------------";
    textEdit->setText(QString::fromStdString(ss.str()));
}

void MainWindow::solve_puzzle(){
    std::string s = textEdit->toPlainText().toStdString();
    std::stringstream ss(s);
    bool quit = false;
    char x;
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            ss >> x;
            while(x == '-') ss >> x;
            if(x == '|') ss >> x;
            solver->setval(i, j, x-'0');
        }
    }
    displayGrid();
    if(!quit && solver->solve()){
        displayGrid();
    }
    else error("Bad Puzzle");
}

void MainWindow::exit(){
    errorWidget->hide();
    close();
}

void MainWindow::error(std::string message)
{
    outputLabel->setText(QString::fromStdString(message));
    errorWidget->show();
    okButton->setFocus();
}

void MainWindow::hideError(){
    errorWidget->hide();
}
