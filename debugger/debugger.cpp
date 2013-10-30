/****************************************************************************
** Form implementation generated from reading ui file 'debugger.ui'
**
** Created by User Interface Compiler
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "debugger.h"
#include "ui_debugger.h"

MainWindow::MainWindow(QWidget *parent)
  : QWidget(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  //QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(OnClick()));
}

MainWindow::~MainWindow()
{
  delete ui;
}
