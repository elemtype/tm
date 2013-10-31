#ifndef DEBUGGER_H  
#define DEBUGGER_H
  
#include <QString>  
#include <vector>  
#include <iostream>  
#include <string> 
#include <QtGui/QWidget>
#include "ui_debugger.h" 
#include "../common/util.h"
#include "../crypter/crypter.h"

    
namespace Ui
{
  class Ui_MainWindow{};
}


class MainWindow : public QWidget
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent=0);
    ~MainWindow();

 private:
    Ui::MainWindow *ui;
    

 private slots:
    void handle_pushButton_encrypt_onClick();
    void handle_pushButton_decrypt_onClick();
};
  
     
#endif 
