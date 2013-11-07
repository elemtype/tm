#include "login.h"

byte *g_id           = new byte[4];
string g_password ;
byte *g_0825_data    = new byte[29];
byte *g_key          = rand_nbyte(16);
byte *g_0825_token   = new byte[0x38];
byte *g_0826_token   = new byte[0x38];
byte *g_0826_token_1 = new byte[0x78];
byte *g_0826_key     = new byte[4];
byte *g_0828_key_0   = new byte[4];
byte *g_0828_key_1   = new byte[4];
byte *g_local_ip     = new byte[4];
byte *g_server_ip    = new byte[4];
byte *g_crc32        = new byte[52];
byte *g_session_key  = new byte[16];
int g_sequence       = 0x01;

int main(int argc,char **argv)
{

  //int _0825_index = 0;
  byte redirect_flag = 0xFE;    //需要重定向
  try
    {
      unsigned long id = 544264186;
      g_password = "bbsxml";
 
      string server_ip = "183.60.48.174";
      
      ulong2byte(id,g_id);
      //pnt_byte(g_id,4);

      //ClientSocket client_socket ( "183.60.48.174", 8000 );
      Socket *socket = new Socket();
      socket->create();
      socket->bind(0);
      socket->connect(server_ip, 8000);
      
      //ipaddr2byte(server_ip,g_server_ip);
      //pnt_byte(g_server_ip,4);

      byte sequence[] = {0x00,0x01};

      unsigned char *reply = NULL;
      unsigned char *key   = NULL;

      int reply_len = 0;

      while(redirect_flag == 0xFE)
      {
        TouchPacketOut *tpout = new TouchPacketOut(sequence);
        tpout->gen_packet();
            
        key = tpout->get_data();

        try
	{
          socket->send(key,115);
          reply_len = socket->recv(reply);
	}
        catch ( SocketException& ) {}

        pnt_byte(reply,reply_len);

        Parse *parse = new Parse();
        parse->set_packet(reply,reply_len);
        
	//std::cout  << "xxxxxxxxxxxxxxxxx";
	//pnt_byte(parse->event_command,1);
        if(parse->event_command[0] == 0xFE)
        { 
          RedirectPacketIn *rpin = new RedirectPacketIn(reply,reply_len);
          pnt_byte(rpin->time,4);
          pnt_byte(rpin->server_ip,4);
          pnt_byte(rpin->local_ip,4);

          string redirect_ip = byte2ipaddr(rpin->server_ip);
          socket->connect(redirect_ip, 8000);
        }else if(parse->event_command[0] == 0x00)
	{
          TouchPacketIn *tpin = new TouchPacketIn(reply,reply_len);
          pnt_byte(tpin->token,(int)tpin->token_size[1]);
          pnt_byte(tpin->time,4);

          redirect_flag = parse->event_command[0];
	}else
	{
	  ;
	}
        delete parse;
        //delete out;
      }
       


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


      sequence[0] = 0x0B;
      sequence[1] = 0x02;
      
      /*
      byte a[4];
      ulong2byte(8000,a);
      pnt_byte(a,4);
      */

      LoginPacketOut *lipout = new LoginPacketOut(sequence);
      lipout->gen_packet();

      key = lipout->get_data();
      reply_len = 0;
      try
	{
	  socket->send(key,lipout->get_data_size());
          reply_len = socket->recv(reply);
        }  
      catch ( SocketException& ) {}
      LoginPacketIn *lipin = new LoginPacketIn(reply,reply_len);
    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\n";
    }

  return 0;
}
