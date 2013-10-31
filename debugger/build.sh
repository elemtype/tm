#! /bin/sh

/usr/lib/qt4/bin/uic debugger.ui -o ui_debugger.h
/usr/lib/qt4/bin/qmake -project
/usr/lib/qt4/bin/qmake
make