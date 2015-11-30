
// WebApiTestDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "WebApiTest.h"
#include "WebApiTestDlg.h"
#include "afxdialogex.h"

#include <afxinet.h>  

#include "ccWin32API/ccWin32WebApiHelper.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // ��ȭ ���� �������Դϴ�.
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

    // �����Դϴ�.
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWebApiTestDlg ��ȭ ����




CWebApiTestDlg::CWebApiTestDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CWebApiTestDlg::IDD, pParent)
    , _strRequestData(_T(""))
    , _strResponseData(_T(""))
    , _strServerIP(_T(""))
    , _uServerPort(0)
    , _strWebAPI(_T(""))
    , _strMethod(_T(""))
    , _uStatusCode(0)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWebApiTestDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_REQUEST_DATA, _strRequestData);
    DDX_Text(pDX, IDC_RESPONSE_DATA, _strResponseData);

    DDX_Text(pDX, IDC_SERVER_IP, _strServerIP);
    DDX_Text(pDX, IDC_SERVER_PORT, _uServerPort);
    DDX_Text(pDX, IDC_WEB_API, _strWebAPI);
    DDX_CBString(pDX, IDC_METHOD, _strMethod);
    DDX_Text(pDX, IDC_STATUS_CODE, _uStatusCode);
}

BEGIN_MESSAGE_MAP(CWebApiTestDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_REQUEST_API, &CWebApiTestDlg::OnBnClickedRequestAPI)
    //  ON_BN_CLICKED(IDC_VERIFY, &CWebApiTestDlg::OnBnClickedVerify)
    ON_EN_CHANGE(IDC_REQUEST_DATA, &CWebApiTestDlg::OnEnChangeRequestData)
END_MESSAGE_MAP()


// CWebApiTestDlg �޽��� ó����

BOOL CWebApiTestDlg::OnInitDialog()
{
    _strServerIP    =   AfxGetApp()->GetProfileString(_T("Config"), _T("ServerIP"), _T("localhost"));
    _uServerPort    =   AfxGetApp()->GetProfileInt(_T("Config"), _T("ServerPort"), 8000);

    _strRequestData =   AfxGetApp()->GetProfileString(_T("Config"), _T("RequestData"), _T(""));
    _strMethod      =   AfxGetApp()->GetProfileString(_T("Config"), _T("Method"), _T("GET"));
    _strWebAPI      = AfxGetApp()->GetProfileString(_T("Config"), _T("WebAPI"), _T(""));

    CDialogEx::OnInitDialog();

    // �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

    // IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
    //  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
    SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
    SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

    // TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

    return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CWebApiTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CWebApiTestDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // �������� �׸��ϴ�.
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CWebApiTestDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CWebApiTestDlg::DoUpdateConfiguration()
{
    UpdateData();

    AfxGetApp()->WriteProfileString(_T("Config"), _T("ServerIP"), _strServerIP);
    AfxGetApp()->WriteProfileInt(_T("Config"), _T("ServerPort"), _uServerPort);

    AfxGetApp()->WriteProfileString(_T("Config"), _T("RequestData"),   _strRequestData);
    AfxGetApp()->WriteProfileString(_T("Config"), _T("Method"),   _strMethod);
    AfxGetApp()->WriteProfileString(_T("Config"), _T("WebAPI"),  _strWebAPI);

    ccWin32WebApiHelper::getInstance()->SetConnectionInfo((LPCTSTR)_strServerIP, _uServerPort);
}

void CWebApiTestDlg::OnTransactionRecveResponse(std::uint16_t uStatusCode, const std::string& strResponse)
{
    if (!IsWindow(m_hWnd))
        return;

    Json::Value     oValue;
    Json::Reader    oReader;

    std::string strData = strResponse;

    if (oReader.parse(strData, oValue) == false)
        OnTransactionRequestTimeout();
}

void CWebApiTestDlg::OnTransactionRequestTimeout()
{
    if (!IsWindow(m_hWnd))
        return;
}

BOOL CWebApiTestDlg::DoRequestAPI()
{
    UpdateData();

    _strResponseData = "";

    std::string     strResponse;

    ccWebServerRequest::HttpMethod eMethod;

    if (_strMethod == "GET")
        eMethod = ccWebServerRequest::HttpMethod_Get;

    if (_strMethod == "POST")
        eMethod = ccWebServerRequest::HttpMethod_Post;

    if (_strMethod == "PUT")
        eMethod = ccWebServerRequest::HttpMethod_Put;

    if (_strMethod == "DELETE")
        eMethod = ccWebServerRequest::HttpMethod_Delete;


    if (_strResponseData.GetLength())
    {
        Json::Value     oParams;
        Json::Reader    oRequestReader;

        if (oRequestReader.parse((const char *)_strRequestData, oParams) == false)
        {
            MessageBox("JCON Parser Error!", "Warring", MB_ICONWARNING);
            UpdateData(FALSE);
            return FALSE;
        }

        if ((_uStatusCode = ccWin32WebApiHelper::getInstance()->RequestAPI(eMethod, (LPCTSTR)_strWebAPI, oParams, strResponse)))
        {
            _strResponseData = strResponse.c_str();
            _strResponseData.Replace("\n", "\r\n");
        }
        else
            MessageBox("Could not connect to Web API Server!", "Warring", MB_ICONWARNING);
    }
    else
    {
        if ((_uStatusCode = ccWin32WebApiHelper::getInstance()->RequestAPI(eMethod, (LPCTSTR)_strWebAPI, strResponse)))
        {
            _strResponseData = strResponse.c_str();
            _strResponseData.Replace("\n", "\r\n");
        }
        else
            MessageBox("Could not connect to Web API Server!", "Warring", MB_ICONWARNING);
    }

    UpdateData(FALSE);

    return TRUE;
}

void CWebApiTestDlg::OnBnClickedRequestAPI()
{
    DoUpdateConfiguration();

    DoRequestAPI();
}


void CWebApiTestDlg::OnEnChangeRequestData()
{
    // TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
    // __super::OnInitDialog() �Լ��� ������ 
    //�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
    // �� �˸� �޽����� ������ �ʽ��ϴ�.

    // TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
