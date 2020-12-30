
// GiftView.h: CGiftView 类的接口
//

#pragma once
#include "Wing.h"
typedef float array[8];

class CGiftView : public CView
{
protected: // 仅从序列化创建
	CGiftView() noexcept;
	DECLARE_DYNCREATE(CGiftView)

// 特性
public:
	CGiftDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CGiftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void DrawWing(CDC* pDC, array arrayXT, array arrayYT);
	void calculate();

private:
	array arrayX, arrayY;
};

#ifndef _DEBUG  // GiftView.cpp 中的调试版本
inline CGiftDoc* CGiftView::GetDocument() const
   { return reinterpret_cast<CGiftDoc*>(m_pDocument); }
#endif

