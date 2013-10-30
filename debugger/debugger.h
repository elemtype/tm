#ifndef DEBUGGER_H  
#define DEBUGGER_H  
#include <QtGui/QWidget> 

    
namespace Ui
{
  class MainWindow{};
}

class MainWindow : public QWidget
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

 private:
    Ui::MainWindow *ui;
};
  
     
#endif 
