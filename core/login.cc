#include "login.h"

byte *g_id  = new byte[4];
byte *g_0825_data = new byte[29];
byte *g_key = rand_nbyte(16);
byte *g_0825_token = new byte[0x38];
byte *g_0826_token = new byte[0x38];
byte *g_0826_key = new byte[4];
byte *g_0828_key_0 = new byte[4];
byte *g_0828_key_1 = new byte[4];
byte *g_local_ip = new byte[4];
int g_sequence = 0x01;

int main(int argc,char **argv)
{

  byte redirect_flag = 0xEF;    //需要重定向
  try
    {
      unsigned long id = 365063521;
      
      ulong2byte(id,g_id);
      //pnt_byte(g_id,4);

      //ClientSocket client_socket ( "183.60.48.174", 8000 );
      Socket *socket = new Socket();
      socket->create();
      socket->bind(0);
      socket->connect("183.60.48.174", 8000);

      byte sequence[] = {0x00,0x01};

      unsigned char *reply = NULL;
      unsigned char *key   = NULL;

      int reply_len = 0;

      while(redirect_flag == 0xEF)
      {
        TouchPacketOut *out = new TouchPacketOut(sequence);
        out->gen_packet();
            
        key = out->get_data();

        try
	{
          socket->send(key,115);
          reply_len = socket->recv(reply);
	}
        catch ( SocketException& ) {}

        pnt_byte(reply,reply_len);

        Parse *parse = new Parse();
        parse->set_packet(reply,reply_len);
        
        if(parse->event_command[0] == 0xEF)
        {
          RedirectPacketIn *rpin = new RedirectPacketIn(reply,reply_len);
          pnt_byte(rpin->time,4);
          pnt_byte(rpin->server_ip,4);
          pnt_byte(rpin->local_ip,4);

          string redirect_ip = byte2ipaddr(rpin->server_ip);
          socket->connect(redirect_ip, 8000);
        }else
	{
          redirect_flag = 0x00;
	}  

        delete parse;
        delete out;
      }
      /*
        sequence[1] = 0x02;
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
      pnt_byte(parse->event_command,1);
      */
      
      TouchPacketIn *tpin = new TouchPacketIn(reply,reply_len);
      pnt_byte(tpin->token,(int)tpin->token_size[1]);
      pnt_byte(tpin->time,4);

      memcpy(g_0825_token,tpin->token,(int)tpin->token_size[1]);
      memcpy(g_local_ip,tpin->local_ip,4 * sizeof(byte));

      //delete parse;
      //delete out;

      sequence[0] = 0x0B;
      sequence[1] = 0x01;
      LogonPacketOut *lpout = new LogonPacketOut(sequence);
      lpout->gen_packet();

      key = lpout->get_data();
      reply_len = 0;
      try
	{
	  socket->send(key,499);
          reply_len = socket->recv(reply);
        }  
      catch ( SocketException& ) {}
      LogonPacketIn *lpin = new LogonPacketIn(reply,reply_len);
    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\n";
    }

  return 0;
}
