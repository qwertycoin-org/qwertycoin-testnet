// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2014 - 2017, XDN - project developers
// Copyright (c) 2018, The Karbo developers
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
//
// You should have received a copy of the GNU Lesser General Public License
// along with Qwertycoin.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <system_error>
#include <Logging/ILogger.h>
#include <Logging/LoggerRef.h>
#include <Rpc/HttpServer.h>
#include <System/Dispatcher.h>
#include <System/Event.h>

namespace Common {

class JsonValue;

} // namespace Common

namespace System {

class TcpConnection;

} // namespace System

namespace CryptoNote {

class HttpResponse;
class HttpRequest;

class JsonRpcServer : HttpServer
{
public:
    JsonRpcServer(System::Dispatcher &sys,
                  System::Event &stopEvent,
                  Logging::ILogger &loggerGroup);
    JsonRpcServer(const JsonRpcServer &) = delete;

    void setCerts(const std::string &chainFile,
                  const std::string &keyFile,
                  const std::string &dhFile);

    void start(const std::string &bindAddress,
               uint16_t bindPort,
               uint16_t bindPortSSL,
               bool serverSSLEnable,
               const std::string &m_rpcUser,
               const std::string &m_rpcPassword);


protected:
    static void makeErrorResponse(const std::error_code &ec, Common::JsonValue &resp);
    static void makeMethodNotFoundResponse(Common::JsonValue &resp);
    static void makeGenericErrorReponse(Common::JsonValue &resp,
                                        const char *what,
                                        int errorCode = -32001);
    static void fillJsonResponse(const Common::JsonValue &v, Common::JsonValue &resp);
    static void prepareJsonResponse(const Common::JsonValue &req, Common::JsonValue &resp);
    static void makeJsonParsingErrorResponse(Common::JsonValue &resp);

    virtual void processJsonRpcRequest(const Common::JsonValue &req, Common::JsonValue &resp) = 0;
private:
    void processRequest(const CryptoNote::HttpRequest &request,
                        CryptoNote::HttpResponse &response) override;

private:
    System::Dispatcher &system;
    System::Event &stopEvent;
    Logging::LoggerRef logger;
};

} // namespace CryptoNote
