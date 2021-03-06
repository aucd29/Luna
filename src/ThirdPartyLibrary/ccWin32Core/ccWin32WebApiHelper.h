#pragma once

#include <memory>
#include <mutex>
#include <thread>
#include <functional>

#include "ccJsonParser/json/json.h"
#include "ccWebServer/ccWebServerRequest.h"
#include "ccWin32RgWebApiTransactionNotifier.h"

namespace Luna {

class ccWin32WebApiHelper
{
protected:
    ccWin32WebApiHelper(void);

public:
    virtual ~ccWin32WebApiHelper(void);

public:
    static std::shared_ptr<ccWin32WebApiHelper> getInstance();

public:
    void    setConnectionInfo(const std::string& strIP, UINT uPort);

    std::uint16_t   requestAPI(ccWebServerRequest::HttpMethod eMethod, const std::string& strWebAPI, std::string& strResponse);
    std::uint16_t   requestAPI(ccWebServerRequest::HttpMethod eMethod, const std::string& strWebAPI, Json::Value& oParams, std::string& strResponse);

    bool            asyncRequestAPI(ccWebServerRequest::HttpMethod eMethod, const std::string& strWebAPI, ccWin32RgWebApiTransactionNotifier *pNotifier = NULL);
    bool            asyncRequestAPI(ccWebServerRequest::HttpMethod eMethod, const std::string& strWebAPI, Json::Value& oParams, ccWin32RgWebApiTransactionNotifier *pNotifier = NULL);

public:
    static bool get_value_string(Json::Value& oValue, const std::string& strName, std::string& strValue, std::string strDefaultValue = _T(""));
    static bool get_value_int(Json::Value& oValue, const std::string& strName, int& nValue, int nDefaultValue = 0);

private:
    std::uint16_t   doSendRequestAPI(ccWebServerRequest::HttpMethod eMethod, const std::string& strWebAPI, const std::string& strRequestData, std::string& strResponse);
    void            doRunThread();

private:
    class   XTransactionInfo
    {
    public:
        XTransactionInfo() {_pNotifier = NULL;}
        virtual ~XTransactionInfo() {}

    public:
        ccWebServerRequest::HttpMethod  _eMethod;
        std::string                     _strWebAPI;
        std::string                     _strRequestData;

        ccWin32RgWebApiTransactionNotifier* _pNotifier;
    };

private:
    std::string     _strDestIP;
    UINT            _uDestPort;
    std::mutex      _mutex;
    
    std::thread     _oPollThread;
    bool            _bIsStopThread;

    std::vector<std::shared_ptr<XTransactionInfo>>   _aTransactionInfos;
};

}
