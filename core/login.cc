#include "login.h"



int main(int argc,char **argv)
{
  try
    {
      unsigned long id = 86079725;
      byte *byte_id = new byte[4];
      ulong2byte(id,byte_id);
      //pnt_byte(byte_id,4);

      //ClientSocket client_socket ( "183.60.48.174", 8000 );
      Socket *socket = new Socket();
      socket->create();
      socket->bind(0);
      socket->connect("183.60.48.174", 8000);

      byte sequence[] = {0x00,0x01};

      TouchPacketIn *in = new TouchPacketIn(sequence);
      in->gen_packet();
            
      int reply_len = 0;
      unsigned char *reply;
      unsigned char *key = in->get_data();

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

      pnt_byte(reply,reply_len);

      std::cout << "We received this response from the server:\n\"" << reply << "\"\n";;

    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\n";
    }

  return 0;
}
