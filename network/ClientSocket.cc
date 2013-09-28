// Implementation of the ClientSocket class

#include "ClientSocket.h"
#include "SocketException.h"


ClientSocket::ClientSocket ( std::string host, int port )
{
  if ( ! Socket::create() )
    {
      throw SocketException ( "Could not create client socket." );
    }

  if ( ! Socket::bind(0) )
    {
      throw SocketException ( "Could not bind to port");
    }

  if ( ! Socket::connect ( host, port ) )
    {
      throw SocketException ( "Could not connect to port." );
    }

}

/*
const ClientSocket& ClientSocket::operator << ( const unsigned char* c ) const
{
  if ( ! Socket::send ( c,115 ) )
    {
      throw SocketException ( "Could not write to socket." );
    }

  return *this;

}


const ClientSocket& ClientSocket::operator >> ( std::string& s ) const
{
  if ( ! Socket::recv ( s ) )
    {
      throw SocketException ( "Could not read from socket." );
    }

  return *this;
}
*/
