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

#include "HTTPProxyRequestHandler.h"
#include <Poco/Net/SocketAddress.h>
#include <iostream>
#include <linux/netfilter_ipv4.h>
#include <linux/socket.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/StreamSocketImpl.h>
#include <Poco/Net/HTTPServerRequestImpl.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/StreamCopier.h>

using namespace std;

void HTTPProxyRequestHandler::handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp) {
	resp.setStatus(HTTPResponse::HTTP_OK);
    resp.setContentType("text/plain");

	//Some debug for the time being
    ostream& out = resp.send();
    out << "Hello world!" << "\r\n";
    out << "URI: " << req.getURI() << "\r\n";
    out << "Host: " << req.getHost() << "\r\n";
    out << "Server Address: " << req.clientAddress().toString() << "\r\n";
    out << "Client Address: " << req.serverAddress().toString() << "\r\n";

	//Get the StreamSocketImpl through lots of casting
	StreamSocket socket = static_cast<HTTPServerRequestImpl&>(req).socket();
	StreamSocketImpl* socketimpl = static_cast<StreamSocketImpl*>(socket.impl());

	//Get where the packet was originally for before interception
	struct sockaddr_in addr;
	bzero((char *) &addr, sizeof(addr));
	//addr.sin_family = AF_NET;
	socklen_t addr_sr = sizeof(addr);
	int iaddr;
	getsockopt(socketimpl->sockfd(), SOL_IP, SO_ORIGINAL_DST, &addr, &addr_sr );

	SocketAddress s((sockaddr*)&addr, addr_sr);
	
    out << "Original Address: " << s.toString() << "\r\n";

	return;

	//Start forwarding the request
	HTTPClientSession forward_session(s);	
	HTTPRequest forward_request(req.getMethod(), req.getURI());

	//Put all the headers on the ongoing request
	string name;
    string value;
	NameValueCollection::ConstIterator i = req.begin();
	while(i!=req.end()){

		name=i->first;
		value=i->second;
		forward_request.set(name, value);
		++i;
	}
	forward_session.sendRequest(forward_request);
	HTTPResponse forward_response;
	std::istream& forward_response_stream = forward_session.receiveResponse(forward_response); 
	Poco::StreamCopier::copyStream(forward_response_stream, out);
	
}