
// ImageScrollViewerDlg.h: 헤더 파일
//

#pragma once


// CImageScrollViewerDlg 대화 상자
class CImageScrollViewerDlg : public CDialogEx
{
private:
	CImage	m_image;
	CRect	m_rect;
// 생성입니다.
public:
	CImageScrollViewerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	void ProcessScroll(UINT nSBCode, UINT nPos, int a_scroll_type);
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGESCROLLVIEWER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSelect();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
