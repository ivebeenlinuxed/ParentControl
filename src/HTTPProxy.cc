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

#include "HTTPProxy.h"
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/ServerSocket.h>

using namespace Poco::Net;

int HTTPProxy::main(const vector<string> &) {
	HTTPServer s(new HTTPProxyRequestHandlerFactory, ServerSocket(9090), new HTTPServerParams);

	s.start();
	waitForTerminationRequest();
	s.stop();
	return Application::EXIT_OK;
}
