/*
 * ccRESTfulChattingApi.h
 *
 *  Created on: 2015. 11. 28.
 *      Author: kmansoo
 */

#ifndef CCPRODUCTLIBRARY_CCRESTFULCHATTINGAPI_CCRESTFULCHATTING_H_
#define CCPRODUCTLIBRARY_CCRESTFULCHATTINGAPI_CCRESTFULCHATTING_H_

#include <vector>

#include "ccWebServer/ccRESTfulApi.h"
#include "ccWebServer/ccWebsocketManager.h"

class ccRESTfulChattingUserInfo
{
public:
    std::string     _strID;
    std::string     _strName;
};

class ccRESTfulChattingMessageInfo
{
public:
    std::string     _strDateTime;
    std::string     _strFromID;
    std::string     _strMessage;
};

class ccRESTfulChattingSessionInfo
{
public:
    ccRESTfulChattingSessionInfo(const std::string& strSessionName, const std::string& strOwnerID);
    ~ccRESTfulChattingSessionInfo() {}

public:
    bool    join(const std::string& strUserID);
    bool    leave(const std::string& strUserID);
    bool    getMemberList(std::vector<std::string>& aUserIDs);

    bool    newMessage(const std::string& strUserID, const std::string& strMessage);

public:
    std::string     _strName;
    std::string     _strOwnerID;

private:
    std::vector<std::string>    _aMembers;
    std::vector<std::shared_ptr<ccRESTfulChattingMessageInfo>>  _aMessages;
};

class ccRESTfulChattingSessionManager
{
public:
    ccRESTfulChattingSessionManager() {}

public:
    bool    createID(const std::string& strID, const std::string& strName);
    bool    deleteID(const std::string& strID);
    bool    getUserInfo(const std::string& strID, ccRESTfulChattingUserInfo& oUserInfo);
    bool    getUserList(std::vector<std::string>& aUserIDs);

    bool    createSession(const std::string& strName, const std::string& strOwnerID);
    bool    deleteSession(const std::string& strName, const std::string& strRequestID);

    bool    joinSession(const std::string& strSessionName, const std::string& strUserID);
    bool    leaveSession(const std::string& strSessionName, const std::string& strUserID);

    bool    getSessionList(std::vector<std::string>& aSessionNames, std::vector<std::string>& aOwnerIDs);
    bool    getSessionInfo(const std::string& strSessionName, std::vector<std::string>& aMembers);

    bool    broadcastMessage(const std::string& strSessionName, const std::string& strUserID, const std::string& strMessage);

protected:
    std::shared_ptr<ccRESTfulChattingSessionInfo> DoFindSession(const std::string& strName);

private:
    std::vector< std::shared_ptr<ccRESTfulChattingUserInfo>>    _aUserInfos;
    std::vector< std::shared_ptr<ccRESTfulChattingSessionInfo>> _aSessionInfos;
};

class ccRESTfulChatting : 
    public Luna::ccRESTfulApi,
    public Luna::ccWebsocketManager
{
public:
    ccRESTfulChatting();
    virtual ~ccRESTfulChatting();

protected:
    bool    user(std::shared_ptr<Luna::ccWebServerRequest> pRequest, std::shared_ptr<Luna::ccWebServerResponse> pResponse);
    bool    session(std::shared_ptr<Luna::ccWebServerRequest> pRequest, std::shared_ptr<Luna::ccWebServerResponse> pResponse);
    bool    session_member(std::shared_ptr<Luna::ccWebServerRequest> pRequest, std::shared_ptr<Luna::ccWebServerResponse> pResponse);
    bool    session_member_id(std::shared_ptr<Luna::ccWebServerRequest> pRequest, std::shared_ptr<Luna::ccWebServerResponse> pResponse);
    bool    session_message(std::shared_ptr<Luna::ccWebServerRequest> pRequest, std::shared_ptr<Luna::ccWebServerResponse> pResponse);

protected:
    bool    ws_chat(Luna::ccWebsocket::ccWebSocketEvent eEvent, std::shared_ptr<Luna::ccWebsocket> pWS, const std::string& strData);

private:
    ccRESTfulChattingSessionManager     _oSessionManager;    
};


#endif /* CCLIBRARY_CCWEBSERVERAPI_CCWEBSERVER_H_ */
