#pragma once

#include "HSCoreAPI/HSObject.h"

class IHSWin32RgWebApiTransactionNotifier 
{
public:
    virtual void    OnTransactionRecveResponse(const CString& strResponse) = 0;
    virtual void    OnTransactionRequestTimeout() = 0;
};

/* ====================================================================
 *  File: IHSWin32RgWebApiTransactionNotifier.h
 *
 *  Desc:
 *      Win32��� Multimedia Timer
 *
 *  Author:
 *      �踸��(kmansoo@humaxdigital.com)
 *
 *  Date:
 *      2014.11.29
 */
