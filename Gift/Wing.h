#pragma once

#include <afxwin.h>
typedef float array[8];
typedef POINT arrayspt[4];

class Wing
{
public:
	Wing();
	virtual ~Wing();

public:
	void Draw(CDC* pDC, array arrayXT, array arrayYT);

private:
	COLORREF colBlue,colRed,colYellow;

	int maxY = 0, minY = 30000;
	arrayspt spt;

	void ScanFill(CDC* pDC, arrayspt spt, COLORREF color);
	void fill(CDC* pDC, CPoint p0, CPoint p1,COLORREF color);
	CPoint getCrossPoint(CPoint point_0, CPoint point_1, int y);
};

