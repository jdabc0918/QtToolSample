#ifndef GLVIEW_H
#define GLVIEW_H

#include "common.h"
#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <gl\GLU.h>

class GLView : public QGLWidget
{
	Q_OBJECT

private:
	int m_xRot;
	int m_yRot;
	int m_zRot;
	float m_xT;
	float m_yT;

	int m_point_size;
	QPoint m_lastPos;
	double m_scale;
	int m_selected_index;
	bool m_show_text_flag;

	std::vector<PointWithComment> m_points;
private:
	QSize minimumSizeHint() const;
	QSize sizeHint() const;
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);

	// Rotation
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);
	//	Zoom
	void setScale(int deg);
	//	Translation
	void setXTranslation(float t);
	void setYTranslation(float t);
	//	Draw
	void SetBackground();
	void DrawPoints(std::vector<PointWithComment> points, int selected_index = -1);

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);

signals:
	// signaling rotation from mouse movement
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);

public:
	GLView(QWidget *parent = 0);
	~GLView();
	void SetPointSize(int psize);
	void Set3DPointsData(std::vector<PointWithComment> points);
	cv::Mat GetImage();
	void SetImage(cv::Mat img);
	cv::Point2f Cvt3Dto2D(cv::Point3f p);

public slots:
	void s_PointSizeChanged(int psize);
	void s_ShowTextFlagChanged(int flag);
	void s_TableSelectionChanged(int rows, int cols);
};

#endif // GLVIEW_H
