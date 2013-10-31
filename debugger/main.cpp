#include <QtGui/QApplication>  
#include "debugger.h"  
     
int main(int argc,char *argv[])  
{  
    QApplication a(argc,argv);  
    MainWindow main;
    main.setFixedSize(800,700);  
    main.show();  
    return a.exec();  
 } 
