
// ImageScrollViewerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ImageScrollViewer.h"
#include "ImageScrollViewerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageScrollViewerDlg 대화 상자



CImageScrollViewerDlg::CImageScrollViewerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMAGESCROLLVIEWER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageScrollViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CImageScrollViewerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SELECT, &CImageScrollViewerDlg::OnBnClickedBtnSelect)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CImageScrollViewerDlg 메시지 처리기

BOOL CImageScrollViewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	GetClientRect(m_rect);
	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CImageScrollViewerDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if (!m_image.IsNull())
		{
			int scroll_x_pos = GetScrollPos(SB_HORZ);
			int scroll_y_pos = GetScrollPos(SB_VERT);
			/*m_image.Draw(dc, -scroll_x_pos, -scroll_y_pos);*/
			m_image.Draw(dc, 0, 0, m_rect.Width(), m_rect.Height(),
				scroll_x_pos, scroll_y_pos, m_rect.Width(), m_rect.Height());
		}
		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CImageScrollViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CImageScrollViewerDlg::OnBnClickedBtnSelect()
{
	wchar_t name_filter[] = L"모든 파일 (*.*)|*.*|Jpeg 파일 (*.jpg)|*.jpg|PNG 파일 (*.png)|*.png||";
	CFileDialog ins_dlg(TRUE, L"jpg", L"*.jpg", OFN_HIDEREADONLY | OFN_NOCHANGEDIR, name_filter);
	ins_dlg.m_ofn.nFilterIndex = 2;

	if (IDOK == ins_dlg.DoModal())
	{
		if (!m_image.IsNull()) m_image.Destroy();

		m_image.Load(ins_dlg.GetPathName());

		SetScrollRange(SB_HORZ, 0, m_image.GetWidth() - m_rect.Width(), 0);
		SetScrollRange(SB_VERT, 0, m_image.GetHeight() - m_rect.Height(), 0);
		Invalidate(FALSE);
	}
}

void CImageScrollViewerDlg::ProcessScroll(UINT nSBCode, UINT nPos, int a_scroll_type)
{
	if (nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK)
	{
		SetScrollPos(a_scroll_type, nPos);
	}

	else
	{
		int scroll_pos = GetScrollPos(a_scroll_type), min = 0, max = 0;
		GetScrollRange(a_scroll_type, &min, &max);
		switch (nSBCode)
		{
		case SB_LINEDOWN:
			if (scroll_pos < max) SetScrollPos(a_scroll_type, ++scroll_pos);
			break;
		case SB_LINEUP:
			if (scroll_pos > min) SetScrollPos(a_scroll_type, --scroll_pos);
			break;
		case SB_PAGEDOWN:
			if (scroll_pos + 24 < max) SetScrollPos(a_scroll_type, scroll_pos + 24);
			break;
		case SB_PAGEUP:
			if (scroll_pos - 24 > min) SetScrollPos(a_scroll_type, scroll_pos - 24);
			break;
		}
	}
	Invalidate(FALSE);
}


void CImageScrollViewerDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == NULL) ProcessScroll(nSBCode, nPos, SB_VERT);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CImageScrollViewerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == NULL) ProcessScroll(nSBCode, nPos, SB_HORZ);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CImageScrollViewerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	m_rect.right = cx;
	m_rect.bottom = cy;
	
	if (!m_image.IsNull())
	{
		SetScrollRange(SB_HORZ, 0, m_image.GetWidth() - m_rect.Width(), 0);
		SetScrollRange(SB_VERT, 0, m_image.GetHeight() - m_rect.Height(), 0);
	}

	Invalidate(FALSE);
}
