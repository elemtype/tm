#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>

int main ( int argc, char** argv )
{
  try
    {

      //ClientSocket client_socket ( "183.60.48.174", 8000 );
      Socket *socket = new Socket();
      socket->create();
      socket->bind(0);
      socket->connect("183.60.48.174", 8000);
      
      int reply_len = 0;
      unsigned char *reply;
      unsigned char key[] = {
	0x02,0x30,0x18,0x08,0x25,0x01,0x4c,0x05,0x21,0x78,0xed,0x03,0x00,0x00,0x00,0x01,
        0x01,0x01,0x00,0x00,0x66,0x07,0x00,0x00,0x00,0x00,0xf5,0x9a,0x7f,0xc1,0xda,0xe4,
	0xf4,0xaa,0x86,0xeb,0xfe,0x6d,0xda,0x5c,0xa7,0xbc,0x4f,0x49,0x90,0xec,0x3c,0x3b,
	0xa7,0xe0,0xfb,0x22,0x40,0x97,0xfd,0xa9,0xd6,0x38,0x60,0x06,0xa3,0xc6,0x4a,0x0a,
	0x98,0x4b,0x34,0x56,0xb1,0x15,0x83,0x4f,0x6b,0x48,0x6f,0x6a,0x96,0x6f,0xfc,0xdd,
	0xd5,0x0e,0xce,0xff,0x64,0x03,0x91,0x48,0x43,0x69,0x00,0xc5,0xa8,0x7c,0xf2,0x37,
	0x02,0xca,0x4a,0x37,0x27,0xf5,0x18,0xb5,0x75,0x4b,0x3e,0x15,0xbf,0xc4,0x48,0xde,
	0x71,0x75,0x03
      };
      reinterpret_cast<char*>(key);
      //std::string ss(key);
      try
	{
	  //socket << key;//"Test message.";
	  //socket >> reply;
          socket->send(key,115);
          reply_len = socket->recv(reply);
	}
      catch ( SocketException& ) {}

      std::cout << "We received this response from the server:\n\"" << reply << "\"\n";;

    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\n";
    }

  return 0;
}
