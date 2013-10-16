#include "login.h"

byte *g_id  = new byte[4];
//byte *g_key = new byte[16];
byte *g_key = rand_nbyte(16);
int g_sequence = 0x01;

int main(int argc,char **argv)
{
  try
    {
      unsigned long id = 365063521;
      
      ulong2byte(id,g_id);
      //pnt_byte(byte_id,4);

      //ClientSocket client_socket ( "183.60.48.174", 8000 );
      Socket *socket = new Socket();
      socket->create();
      socket->bind(0);
      socket->connect("183.60.48.174", 8000);

      byte sequence[] = {0x00,0x01};

      TouchPacketOut *out = new TouchPacketOut(sequence);
      out->gen_packet();
            
      int reply_len = 0;
      unsigned char *reply;
      unsigned char *key = out->get_data();

      //reinterpret_cast<char*>(key);
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

      Parse *parse = new Parse();
      parse->set_packet(reply,reply_len);
      
      RedirectPacketIn *rpin = new RedirectPacketIn(reply,reply_len);
      pnt_byte(rpin->time,4);
      pnt_byte(rpin->server_ip,4);
      pnt_byte(rpin->local_ip,4);

      string redirect_ip = byte2ipaddr(rpin->server_ip);
      socket->connect(redirect_ip, 8000);
      
      //std::cout << std::hex << parse->event_command;
      delete parse;
      delete out;

      
      out = new TouchPacketOut(sequence);
      out->gen_packet();
            
      reply_len = 0;
      key = out->get_data();

      //reinterpret_cast<char*>(key);
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
      parse = new Parse();
      parse->set_packet(reply,reply_len);
      
      TouchPacketIn *tpin = new TouchPacketIn(reply,reply_len);
      pnt_byte(tpin->token,(int)tpin->token_size[1]);
      pnt_byte(tpin->time,4);

      delete parse;
      //std::cout << "We received this response from the server:\n\"" << reply << "\"\n";;

    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\n";
    }

  return 0;
}
