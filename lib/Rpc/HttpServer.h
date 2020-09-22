// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2018-2020, The Qwertycoin Group.
//
// This file is part of Qwertycoin.
//
// Qwertycoin is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Qwertycoin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// Copyright (c) 2014-2016 XDN developers
//
// You should have received a copy of the GNU Lesser General Public License
// along with Qwertycoin.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <string.h>
#include <unordered_set>

#include <boost/asio.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/thread/thread.hpp>

#include <Http/HttpRequest.h>
#include <Http/HttpResponse.h>

#include <Logging/LoggerRef.h>

#include <System/ContextGroup.h>
#include <System/Dispatcher.h>
#include <System/Event.h>
#include <System/TcpConnection.h>
#include <System/TcpListener.h>

namespace CryptoNote {

class HttpServer
{
public:
    HttpServer(System::Dispatcher &dispatcher, Logging::ILogger &log);
    void setCerts(const std::string &chain_file, const std::string &key_file,
                  const std::string &dh_file);
    void start(const std::string &address, uint16_t port, uint16_t portSSL = 0,
               bool serverSSLEnable = false, const std::string &user = "",
               const std::string &password = "");
    void stop();

    virtual void processRequest(const HttpRequest &request, HttpResponse &response) = 0;
    virtual size_t get_connections_count() const;

protected:
    System::Dispatcher &m_dispatcher;

private:
    bool authenticate(const HttpRequest &request) const;
    void acceptLoop();
    void connectionHandler(System::TcpConnection &&conn);
    void sslServerUnitControl(boost::asio::ssl::stream<boost::asio::ip::tcp::socket &> &stream,
                              boost::system::error_code &ec, bool &unit_do, bool &unit_control_do,
                              size_t &stream_timeout_n);
    void sslServerUnit(boost::asio::ip::tcp::socket &socket, boost::asio::ssl::context &ctx);
    void sslServerControl(boost::asio::ip::tcp::acceptor &accept);
    void sslServer();

private:
    bool m_server_ssl_do;
    bool m_server_ssl_is_run;
    uint16_t m_server_ssl_port;
    unsigned int m_server_ssl_clients;
    std::string m_address;
    std::string m_chain_file;
    std::string m_dh_file;
    std::string m_key_file;
    std::string m_credentials;
    std::unordered_set<System::TcpConnection *> m_connections;
    boost::thread m_ssl_server_thread;
    System::ContextGroup workingContextGroup;
    System::TcpListener m_listener;
    Logging::LoggerRef logger;
};

} // namespace CryptoNote
