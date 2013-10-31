/****************************************************************************
** Form implementation generated from reading ui file 'debugger.ui'
**
** Created by User Interface Compiler
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "debugger.h"


MainWindow::MainWindow(QWidget *parent) : QWidget(parent),ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->pushButton_encrypt, SIGNAL(clicked()), this, SLOT(handle_pushButton_encrypt_onClick()));
  connect(ui->pushButton_decrypt, SIGNAL(clicked()), this, SLOT(handle_pushButton_decrypt_onClick()));
  //QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(OnClick()));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::handle_pushButton_encrypt_onClick()
{
  int size = 0;
  QString q_key = ui->textEdit_key->toPlainText();
  string s_key = string((const char *)q_key.toLocal8Bit()); 
  size = formatString(s_key);
  byte key[size];
  hexStringToBytes(s_key,key);
  //pnt_byte(key,16);

  QString q_in = ui->textEdit_input->toPlainText();
  string s_in = string((const char *)q_in.toLocal8Bit()); 
  size = formatString(s_in);
  byte in[size];
  hexStringToBytes(s_in,in);
  //pnt_byte(in,70);

  byte *out = NULL;
  CRYPTER *crypter = new CRYPTER(key);	
  int len = crypter->encrypt(in,size,out);
  //pnt_byte(out,len);

  string s_out = bytesToHexString(out,len);
  QString q_out = QString(QString::fromLocal8Bit(s_out.c_str()));
  ui->textEdit_output->setPlainText(q_out);
  //std::cout << "handle_pushButton_encrypt_onClick" << std::endl;

  delete out;
  delete crypter;
}
 
void MainWindow::handle_pushButton_decrypt_onClick()
{
  int size = 0;
  QString q_key = ui->textEdit_key->toPlainText();
  string s_key = string((const char *)q_key.toLocal8Bit()); 
  size = formatString(s_key);
  byte key[size];
  hexStringToBytes(s_key,key);
  //pnt_byte(key,16);

  QString q_in = ui->textEdit_input->toPlainText();
  string s_in = string((const char *)q_in.toLocal8Bit()); 
  size = formatString(s_in);
  byte in[size];
  hexStringToBytes(s_in,in);
  //pnt_byte(in,70);

  byte *out = NULL;
  CRYPTER *crypter = new CRYPTER(key);	
  int len = crypter->decrypt(in,size,out);
  //pnt_byte(out,len);

  string s_out = bytesToHexString(out,len);
  QString q_out = QString(QString::fromLocal8Bit(s_out.c_str()));
  ui->textEdit_output->setPlainText(q_out);
  //std::cout << "handle_pushButton_decrypt_onClick" << std::endl;

  delete out;
  delete crypter;
}


