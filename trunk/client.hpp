//
// client.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <unistd.h>

using boost::asio::ip::tcp;

int send(std::string lHost, std::string lPort, std::string lBoard,
        std::string solution)
{
    try
    {
        boost::asio::io_service io_service;

        tcp::resolver resolver(io_service);

		tcp::resolver::query query(lHost,lPort);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::resolver::iterator end;

        tcp::socket socket(io_service);
        boost::system::error_code error = boost::asio::error::host_not_found;
        while (error && endpoint_iterator != end)
        {
            socket.close();
            socket.connect(*endpoint_iterator++, error);
        }
        if (error)
            throw boost::system::system_error(error);

        boost::system::error_code ignored_error;
        boost::asio::write(socket, boost::asio::buffer(lBoard),
                boost::asio::transfer_all(), ignored_error);
        for (;;)
        {
            boost::array<char, 1024> buf;
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);
           	if(!strcmp(buf.data(),"Wrong ID\n"))
			{
				std::cout.write(buf.data(), len);
				break;
			}
            if (error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.

            std::cout << "Solving " << std::endl;
            std::cout.write(buf.data(), len);
            std::string lBoardAsString(buf.data(),len);

            boost::asio::write(socket,boost::asio::buffer(solution),boost::asio::transfer_all(),ignored_error);

            len = socket.read_some(boost::asio::buffer(buf),error);
            std::cout.write(buf.data(), len);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

