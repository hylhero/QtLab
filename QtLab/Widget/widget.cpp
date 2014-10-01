#include "widget.h"
#include <QDebug>
#include <QPainter>
#include <QFontMetrics>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
	resize(402, 322);
}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);

	/*!
	 * Draw the border
	 */
	QRect rect = this->geometry();
	rect.moveTopLeft(QPoint(0, 0));
	rect.adjust(10, 10, -11, -11); /**< set aside for edge. */
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(Qt::white));
	painter.drawRoundRect(rect, 10, 10);

	/*!
	 * Draw the Title
	 */
	painter.setPen(Qt::SolidLine);
	painter.setFont(QFont("Microsoft YaHei UI", 12)); /**< Use YaHei Font */
	painter.drawText(QRect(rect.left(), rect.top(), rect.width(), 50), Qt::AlignCenter, "Simple barchart example");

	/*!
	 * Set data for test
	 */
	QStringList monthList;
	monthList << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";

	QStringList valueList;
	valueList << "0.0" << "3.2" << "6.5" << "9.8" << "13.0";

	/*!
	 * Calculate the Font's pixel.
	 */
	QFontMetrics metrics = painter.fontMetrics();

	int leftBearing = metrics.width("100.0") + 35; /**< 5 is the scale width. */
	const int topBearing = 15;
	int coordWidth	= rect.width() - 2*leftBearing;
	int coordHeight = rect.height() - topBearing - 4*metrics.height();

	painter.translate(leftBearing, rect.bottom() - 2*metrics.height()); /**< move center to left bottom */
	float deltaX = static_cast<float>(coordWidth)/monthList.size();
	float deltaY = static_cast<float>(coordHeight)/(valueList.size()-1);

	/*!
	 * Draw the coordinate
	 */
	painter.drawLine(0, 0, coordWidth, 0);
	for (int i = 0; i != monthList.size(); ++i)
	{
		int strLen = metrics.width(monthList.at(i));
		// scale
		painter.drawLine(deltaX*(i+1), 0, deltaX*(i+1), 4);
		// text
		painter.drawText(deltaX*i + (deltaX-strLen)/2 ,metrics.height(), monthList.at(i));
	}

	painter.drawLine(0, 0, 0, -coordHeight);
	for (int i = 0; i != valueList.size(); ++i)
	{
		int deviation = metrics.height()/2 - metrics.descent();
		painter.drawLine(-4, -deltaY*i, 0, -deltaY*i);
		painter.drawText(-metrics.width(valueList.at(i))-4, -deltaY*i+deviation, valueList.at(i));
	}
}
