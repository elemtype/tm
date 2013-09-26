#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>

int main ( int argc, int argv[] )
{
  try
    {

      ClientSocket client_socket ( "localhost", 6666 );

      std::string reply;
      unsigned char key[] = {0x61,0x61};//,0x6E,0x17,0xEF,0xDF,0xD6,0x0D,0xC2,0x87,0xBC,0x03,0x29,0xB4,0x4E,0x3C,'\0'};
      std::string ss(reinterpret_cast<char*>(key));
      //std::string ss(key);
      try
	{
	  client_socket << ss;//"Test message.";
	  client_socket >> reply;
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
