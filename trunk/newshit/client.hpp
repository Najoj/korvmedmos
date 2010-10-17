/**
 * client.hpp
 * 
 * Client to enable communication with server so we can get a board to solve,
 * and to send out solution to it.
 */
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <unistd.h>

using boost::asio::ip::tcp;

tcp::socket * open(std::string lHost, std::string lPort)
{
	try
	{
		// All programs that use asio need to have at least 1 io_service object
		boost::asio::io_service io_service;
		// We need to turn the server name that was specified as a parameter to
		// the appication, into a TCP endpoint using an ip::tcp::resolver object
		tcp::resolver resolver(io_service);
		// A resolver takes a query object and turns it into a list of endpoints
		// We construct a query using the name of the server, lHost, and the
		// port number, lPort
		tcp::resolver::query query(lHost, lPort);
		// The list of endpoints is returned using an iterator
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		// A defualt constructed iterator is used as the end iterator
		tcp::resolver::iterator end;
		// Now we create and connect the socket
		tcp::socket * socket = new tcp::socket(io_service);

		// We iterate through the set of endpoints until we find one that works
		boost::system::error_code error = boost::asio::error::host_not_found;
		while (error && endpoint_iterator != end)
		{
			socket->close();
			socket->connect(*endpoint_iterator++, error);
		}
		if (error)
			throw boost::system::system_error(error);

		// The connection is now open
		return socket;
	}
	// Finally, handle any exceptions that may have been thrown
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return NULL;
}

std::string read(tcp::socket& socket, std::string lBoard)
{
	try
	{
		boost::system::error_code ignored_error;
		// Send information that we want board lBoard
		boost::asio::write(socket, boost::asio::buffer(lBoard),
		boost::asio::transfer_all(), ignored_error);
		
		for (;;)
		{
			// We use a boost::array to hold the received data
			boost::array<char, 10000> buf;
			boost::system::error_code error;
			// The buffer() function automatically determines the size of the
			// array to help prevent buffer overruns
			size_t len = socket.read_some(boost::asio::buffer(buf), error);
			// When the server closes the connection, the read_some() function
			// will exit with the error::eof error which is how we exit the loop
			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

			std::string board(buf.data(), len);
			return board;
		}
	}
	// Finally, handle any exceptions that may have been thrown
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return std::string();
}

int send(tcp::socket& socket, std::string solution)
{
	try
	{
		boost::system::error_code ignored_error;
		for (;;)
		{
			boost::asio::write(socket, boost::asio::buffer(solution),
			boost::asio::transfer_all(), ignored_error);

			boost::array<char, 1024> buf;
			boost::system::error_code error;
			size_t len = socket.read_some(boost::asio::buffer(buf), error);
			std::cout.write(buf.data(), len);

			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
