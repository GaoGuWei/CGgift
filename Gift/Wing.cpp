#include "pch.h"
#include "Wing.h"

Wing::Wing()
{
	colBlue = RGB(100, 149, 237);
	colRed = RGB(255, 99, 71);
	colYellow = RGB(218, 165, 32);
}

Wing::~Wing()
{
}

void Wing::Draw(CDC * pDC, array arrayXT, array arrayYT)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0,0,0));
	CPen *pOldPen = pDC->SelectObject(&pen);
	pDC->MoveTo(300 + arrayXT[7], 300 + arrayYT[7]);
	pDC->LineTo(300 + arrayXT[1], 300 + arrayYT[1]);
	pDC->LineTo(300 + arrayXT[4], 300 + arrayYT[4]);
	pDC->LineTo(300 + arrayXT[7], 300 + arrayYT[7]);
	pDC->LineTo(300 + arrayXT[2], 300 + arrayYT[2]);
	pDC->LineTo(300 + arrayXT[5], 300 + arrayYT[5]);
	pDC->LineTo(300 + arrayXT[7], 300 + arrayYT[7]);
	pDC->LineTo(300 + arrayXT[3], 300 + arrayYT[3]);
	pDC->LineTo(300 + arrayXT[6], 300 + arrayYT[6]);
	pDC->LineTo(300 + arrayXT[7], 300 + arrayYT[7]);

	pDC->SelectObject(pOldPen);
	pen.DeleteObject();

	for (int i = 0; i < 4; i++) {
		spt[i] = CPoint(0, 0);
	}
	spt[0] = CPoint(300 + arrayXT[7], 300 + arrayYT[7]);
	spt[1] = CPoint(300 + arrayXT[1], 300 + arrayYT[1]);
	spt[2] = CPoint(300 + arrayXT[4], 300 + arrayYT[4]);
	spt[3] = CPoint(300 + arrayXT[7], 300 + arrayYT[7]);
	for (int i = 0; i < 4; i++) {//获取最大和最小点
		maxY = maxY > spt[i].y ? maxY : spt[i].y;
		minY = minY < spt[i].y ? minY : spt[i].y;
	}
	ScanFill(pDC,spt,colBlue);

	for (int i = 0; i < 4; i++) {
		spt[i] = CPoint(0, 0);
	}
	spt[0] = CPoint(300 + arrayXT[7], 300 + arrayYT[7]);
	spt[1] = CPoint(300 + arrayXT[2], 300 + arrayYT[2]);
	spt[2] = CPoint(300 + arrayXT[5], 300 + arrayYT[5]);
	spt[3] = CPoint(300 + arrayXT[7], 300 + arrayYT[7]);
	for (int i = 0; i < 4; i++) {//获取最大和最小点
		maxY = maxY > spt[i].y ? maxY : spt[i].y;
		minY = minY < spt[i].y ? minY : spt[i].y;
	}
	ScanFill(pDC, spt, colRed);

	for (int i = 0; i < 4; i++) {
		spt[i] = CPoint(0, 0);
	}
	spt[0] = CPoint(300 + arrayXT[7], 300 + arrayYT[7]);
	spt[1] = CPoint(300 + arrayXT[3], 300 + arrayYT[3]);
	spt[2] = CPoint(300 + arrayXT[6], 300 + arrayYT[6]);
	spt[3] = CPoint(300 + arrayXT[7], 300 + arrayYT[7]);
	for (int i = 0; i < 4; i++) {//获取最大和最小点
		maxY = maxY > spt[i].y ? maxY : spt[i].y;
		minY = minY < spt[i].y ? minY : spt[i].y;
	}
	ScanFill(pDC, spt, colYellow);
}

void Wing::ScanFill(CDC* pDC, arrayspt spt, COLORREF color)
{
	int crossPointCount = 0;
	CPtrArray ptrPoint;
	for (int y = minY; y < maxY; y ++ ) {//对每隔三行的线进行填充
		crossPointCount = 0;//将交点数归零
		ptrPoint.RemoveAll();
		//获取与各边的交点
		for (int i = 1; i < 4; i++) {//对每个点进行检查
			if (i < 4) {//前count-2个点
				if (y < spt[i - 1].y&&y > spt[i].y || y > spt[i - 1].y&&y < spt[i].y) {
					crossPointCount++;
					CPoint p = getCrossPoint(spt[i - 1], spt[i], y);//获得扫描线与多边形的交点
					//存储点
					ptrPoint.Add(new CPoint(p.x, p.y));
				}
			}
		}
		if (crossPointCount >= 2) {//填充
			for (int i = 1; i <= crossPointCount; i += 2) {//每两点内为要填充区域
				int x = ((CPoint*)ptrPoint.GetAt(i - 1))->x;
				int y = ((CPoint*)ptrPoint.GetAt(i - 1))->y;
				CPoint p0(x, y);
				x = ((CPoint*)ptrPoint.GetAt(i))->x;
				y = ((CPoint*)ptrPoint.GetAt(i))->y;
				CPoint p1(x, y);
				fill(pDC,p0, p1,color);
			}
		}
	}
}

void Wing::fill(CDC* pDC, CPoint point_0, CPoint point_1, COLORREF color)
{
	CPen pen(PS_SOLID, 1, color);
	pDC->SelectObject(pen);
	pDC->MoveTo(point_0);
	pDC->LineTo(point_1);
	pen.DeleteObject();
}

CPoint Wing::getCrossPoint(CPoint point_0, CPoint point_1, int y)
{
	if (y == point_0.y)
		return point_0;
	else if (y == point_1.y)
		return point_1;
	else if (point_0.y == point_1.y)
		return point_0;
	else {
		int x = 0;
		x = ((point_0.x - point_1.x)*(y - point_1.y)) / (point_0.y - point_1.y);
		x += point_1.x;
		return CPoint(x, y);
	}
	return CPoint();
}
