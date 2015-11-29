#include "stdafx.h"
#include <regex>

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "ccBoostWebServerSession.h"

VOID ccBoostWebServerSession::HttpSessionStart()
{
	ReadHeader();
}

VOID ccBoostWebServerSession::ReadHeader()
{
	// ������Ʈ ����� �񵿱� ���Ź޴´�.
	// ����� �ٵ�� '\r\n\r\n'���� ���еȴ�.
	boost::asio::async_read_until(
		m_socket, 
		m_request_buffer,
		"\r\n\r\n",
		boost::bind(&ccBoostWebServerSession::ReadHeaderComplete, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

VOID ccBoostWebServerSession::ReadHeaderComplete(CONST boost::system::error_code& e, std::size_t nBytesTransferred)
{
	if (!e)
	{
		// ��Ʈ������ ��Ʈ������
		size_t currentSize = m_request_buffer.size();
		m_requestHeader.assign(
			boost::asio::buffers_begin(m_request_buffer.data()),
			boost::asio::buffers_begin(m_request_buffer.data()) + currentSize
			);

		// ������� ������������ ���Ѵ�.
		std::regex rgxContentLength(".*Content-Length: (\\w+).*");
		std::smatch matchContentLength;
		if (!std::regex_search(m_requestHeader, matchContentLength, rgxContentLength)) {
			// ������������ �������� ������ �ٷ� Handle�� �̵�
			Handle();
		}
		else {
			// ������������ �����ϸ� ReadBody�� �̵�
			size_t contentSize = boost::lexical_cast<size_t>(matchContentLength[1]);
			ReadBody(contentSize);
		}
	}
	else
	{
		Disconnect();
	}
}

VOID ccBoostWebServerSession::ReadBody(size_t contentSize)
{
	// ������Ʈ �ٵ� �񵿱� ���Ź޴´�.
	// �ٵ� ������� �˰� �ִ�.
	boost::asio::async_read(
		m_socket,
		m_request_buffer,
		boost::bind(&ccBoostWebServerSession::ReadBodyComplete, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

VOID ccBoostWebServerSession::ReadBodyComplete(CONST boost::system::error_code& e, std::size_t nBytesTransferred)
{
	if (!e)
	{
		// ��Ʈ������ ��Ʈ������
		size_t currentSize = m_request_buffer.size();
		m_requestBody.assign(
			boost::asio::buffers_begin(m_request_buffer.data()),
			boost::asio::buffers_begin(m_request_buffer.data()) + currentSize
			);

		// Handle�� �̵�
		Handle();
	}
	else
	{
		Disconnect();
	}
}

VOID ccBoostWebServerSession::Handle()
{
	ccBoostWebServerRequest req(m_requestHeader, m_requestBody);
	ccBoostWebServerResponse res;

	// ��û�� ó���Ѵ�.
	bool bIsBuiltinProcess = m_eventListener->OnWebServerRequest(&req, &res);
	if (!bIsBuiltinProcess) {
		std::string data =
			"<html>"
			"<head><title>Hello?</title></head>"
			"<body><h1>I am boost web server</h1></body>"
			"</html>";
		res.SetResponseString(data);
	}

	// ó�� ����� ������.
	Write(res);
}

VOID ccBoostWebServerSession::Write(ccBoostWebServerResponse& response)
{
	m_response_buffer.assign(response.GetResponseString().begin(), response.GetResponseString().end());

	boost::asio::async_write(
		m_socket,
		boost::asio::buffer(m_response_buffer),
		boost::bind(&ccBoostWebServerSession::WriteComplete, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

VOID ccBoostWebServerSession::WriteComplete(CONST boost::system::error_code& e, std::size_t nBytesTransferred)
{
	Disconnect();
}

VOID ccBoostWebServerSession::Disconnect()
{
	if (!m_socket.is_open())
	{
		boost::system::error_code ecIgnore;
		m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ecIgnore);
	}
}
