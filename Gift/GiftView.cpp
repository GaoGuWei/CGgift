
// GiftView.cpp: CGiftView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Gift.h"
#endif

#include "GiftDoc.h"
#include "GiftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
constexpr auto PI = 3.1415926;


// CGiftView

IMPLEMENT_DYNCREATE(CGiftView, CView)

BEGIN_MESSAGE_MAP(CGiftView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CGiftView 构造/析构

CGiftView::CGiftView() noexcept
{
	// TODO: 在此处添加构造代码
	arrayX[1] = 0; arrayY[1] = 200;
	arrayX[2] = 173; arrayY[2] = -100;
	arrayX[3] = -173; arrayY[3] = -100;
	arrayX[4] = 100; arrayY[4] = 100;
	arrayX[5] = 36; arrayY[5] = -136;
	arrayX[6] = -136; arrayY[6] = 36;
	arrayX[7] = 0; arrayY[7] = 0;
}

CGiftView::~CGiftView()
{
}

BOOL CGiftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGiftView 绘图

void CGiftView::OnDraw(CDC* pDC)
{
	CGiftDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CRect rect;
	GetClientRect(&rect);
	int nClientWidth = rect.Width();
	int nClientHeight = rect.Height();

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);//创建用于缓冲的内存DC

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC, nClientWidth, nClientHeight);//创建兼容位图
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);//把兼容位图选入用于缓冲的内存DC
	CBrush* pBrush = new CBrush(RGB(255, 255, 255));
	memDC.FillRect(rect, pBrush);//刷掉原来绘制的DC内容
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *pOldPen = memDC.SelectObject(&pen);
	memDC.Ellipse(100, 100, 500, 500);//绘制外接圆
	memDC.SelectObject(pOldPen);
	pen.DeleteObject();

	DrawWing(&memDC, arrayX, arrayY);//绘制风车叶片

	pDC->BitBlt(0, 0, nClientWidth, nClientHeight, &memDC, 0, 0, SRCCOPY);//将缓冲DC中的数据拷贝到窗口DC中
	memDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	
}


// CGiftView 打印

BOOL CGiftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGiftView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGiftView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CGiftView 诊断

#ifdef _DEBUG
void CGiftView::AssertValid() const
{
	CView::AssertValid();
}

void CGiftView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGiftDoc* CGiftView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGiftDoc)));
	return (CGiftDoc*)m_pDocument;
}
#endif //_DEBUG


// CGiftView 消息处理程序


int CGiftView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetTimer(1, 150, NULL);

	return 0;
}


void CGiftView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	KillTimer(1);
}


void CGiftView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	calculate();
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}

void CGiftView::DrawWing(CDC * pDC, array arrayXT, array arrayYT)
{
	Wing wing;
	wing.Draw(pDC,arrayXT,arrayYT);
}

void CGiftView::calculate()
{
	for (int i = 1; i <= 6; ++i) {
		double Xt = arrayX[i] * cos(PI / 60) + arrayY[i] * sin(PI / 60);
		double Yt = arrayX[i] * (-sin(PI / 60)) + arrayY[i] * cos(PI / 60);
		arrayX[i] = Xt;
		arrayY[i] = Yt;
	}
}
