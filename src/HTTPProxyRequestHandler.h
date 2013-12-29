/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * parentcontrol
 * Copyright (C) Will Tinsdeall 2013 <ivebeenlinuxed@googlemail.com>
 * 
parentcontrol is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * parentcontrol is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _HTTPPROXYREQUESTHANDLER_H_
#define _HTTPPROXYREQUESTHANDLER_H_

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPRequestHandler.h>

using namespace Poco::Net;

class HTTPProxyRequestHandler: public Poco::Net::HTTPRequestHandler 
{
public:
	void handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp);
protected:

private:

};

#endif // _HTTPPROXYREQUESTHANDLER_H_
