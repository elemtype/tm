// Implementation of the Socket class.


#include "Socket.h"
#include "string.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>



Socket::Socket() :
  m_sock ( -1 )
{

  memset ( &m_addr_from,
	   0,
	   sizeof ( m_addr_from ));

  memset ( &m_addr_to,
           0,
	   sizeof ( m_addr_to));

}

Socket::~Socket()
{
  if ( is_valid() )
    ::close ( m_sock );
}

bool Socket::create()
{
  m_sock = socket ( AF_INET,
		    SOCK_DGRAM,
		    0 );

  if ( ! is_valid() )
    return false;


  // TIME_WAIT - argh
  //int on = 1;
  //if ( setsockopt ( m_sock, SOL_SOCKET, SO_REUSEADDR, ( const char* ) &on, sizeof ( on ) ) == -1 )
  //return false;


  return true;

}



bool Socket::bind ( const int port )
{
   m_addr_from.sin_family=AF_INET;
   m_addr_from.sin_port=htons(4000);//获得任意空闲端口
   m_addr_from.sin_addr.s_addr=htons(INADDR_ANY);//获得本机地址
   int r=::bind(m_sock,(struct sockaddr*)&m_addr_from,sizeof(m_addr_from));

   if(r==-1)
   {
     return false;
   }
  return true;
}


bool Socket::listen() const
{
  return true;
}


bool Socket::accept ( Socket& new_socket ) const
{
  return true;
}


bool Socket::send ( const unsigned char* c,int len ) const
{
 int status = ::send ( m_sock, c, len, MSG_NOSIGNAL);
  if ( status == -1 )
    {
      return false;
    }
  else
    {
      return true;
    }
}


int Socket::recv ( unsigned char*& s ) const
{
  char buf [ MAXRECV + 1 ];   //本来+1是为了存放‘\0’，实际基本用不上，同时返回字符串长度

  memset ( buf, 0, MAXRECV + 1 );

  int len = ::recv ( m_sock, buf, MAXRECV, 0);

  if ( len == -1 )
    {
      std::cout << "status == -1   errno == " << errno << "  in Socket::recv\n";
      return 0;
    }
  else if ( len == 0 )
    {
      return 0;
    }
  else
    { 
      buf[len] = 0;     //‘\0’
      s = reinterpret_cast<unsigned char*>(buf);
      return len;
    }
}



bool Socket::connect ( const std::string host, const int port )
{

  if ( ! is_valid() ) return false;  

  m_addr_to.sin_family = AF_INET;
  m_addr_to.sin_port = htons ( port );
  m_addr_to.sin_addr.s_addr=inet_addr(host.c_str());
  //  int status = inet_pton ( AF_INET, host.c_str(), &m_addr_to.sin_addr );
  if(::connect(m_sock,(struct sockaddr*)&m_addr_to,sizeof(struct sockaddr_in))<0)
    {
     return false;
    }
  else
    {
    return true;
    }
}

void Socket::set_non_blocking ( const bool b )
{

  int opts;

  opts = fcntl ( m_sock,
		 F_GETFL );

  if ( opts < 0 )
    {
      return;
    }

  if ( b )
    opts = ( opts | O_NONBLOCK );
  else
    opts = ( opts & ~O_NONBLOCK );

  fcntl ( m_sock,
	  F_SETFL,opts );

}
