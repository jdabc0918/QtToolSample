#include "glview.h"

GLView::GLView(QWidget *parent)
	: QGLWidget(parent)
{
	m_xRot = 0;
	m_yRot = 0;
	m_zRot = 0;

	m_xT = 0;
	m_yT = 0;

	m_point_size = 10;
	m_scale = 1.0;
	m_show_text_flag = false;
}

GLView::~GLView()
{

}

QSize GLView::minimumSizeHint() const
{
	return QSize(50, 50);
}

QSize GLView::sizeHint() const
{
	return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
	while (angle < 0)
		angle += 360 * 16;
	while (angle > 360)
		angle -= 360 * 16;
}

void GLView::setXRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_xRot) {
		m_xRot = angle;
		emit xRotationChanged(angle);
		updateGL();
	}
}

void GLView::setYRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_yRot) {
		m_yRot = angle;
		emit yRotationChanged(angle);
		updateGL();
	}
}

void GLView::setZRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_zRot) {
		m_zRot = angle;
		emit zRotationChanged(angle);
		updateGL();
	}
}

void GLView::setScale(int deg)
{
	double s_step = 0.2;
	if (deg >= 0) m_scale *= (1.0 + s_step);
	else m_scale *= (1.0 - s_step);
	updateGL();
}

void GLView::setXTranslation(float t)
{
	m_xT = t;
	updateGL();
}

void GLView::setYTranslation(float t)
{
	m_yT = t;
	updateGL();
}

void GLView::initializeGL()
{
	qglClearColor(Qt::black);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);

	////	ライト
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void GLView::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(m_xT, m_yT, -10.0);
	glScalef(m_scale, m_scale, m_scale);
	glRotatef(m_xRot / 16.0, 1.0, 0.0, 0.0);
	glRotatef(m_yRot / 16.0, 0.0, 1.0, 0.0);
	glRotatef(m_zRot / 16.0, 0.0, 0.0, 1.0);
	
	DrawPoints(m_points, m_selected_index);
}

void GLView::resizeGL(int width, int height)
{
	//int side = qMin(width, height);
	//glViewport((width - side) / 2, (height - side) / 2, side, side);
	glViewport(0, 0, width, height);
	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
#ifdef QT_OPENGL_ES_1
	glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
	glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
	glMatrixMode(GL_MODELVIEW);
}

void GLView::mousePressEvent(QMouseEvent *event)
{
	m_lastPos = event->pos();
}

void GLView::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - m_lastPos.x();
	int dy = event->y() - m_lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(m_xRot + 8 * dy);
		setYRotation(m_yRot + 8 * dx);
	}
	else if (event->buttons() & Qt::RightButton) {
		setXRotation(m_xRot + 8 * dy);
		setZRotation(m_zRot + 8 * dx);
	}
	else if (event->buttons() & Qt::MiddleButton) {
		float xt = m_xT, yt = m_yT;
		float t_step = 0.05;
		if (dx >= 0) xt += t_step;
		else xt -= t_step;
		if (dy >= 0) yt += t_step;
		else yt -= t_step;
		setXTranslation(xt);
		setYTranslation(yt);
	}

	m_lastPos = event->pos();
}

void GLView::wheelEvent(QWheelEvent *event)
{
	
	int deg = event->angleDelta().y();
	qDebug() << __FUNCTION__ << " " << deg;
	setScale(deg);
}

void GLView::SetBackground()
{
	//	グラデーション色
	cv::Vec3b u(6, 3, 3);		//	upper
	cv::Vec3b b(230, 117, 117);	//	bottom

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLE_STRIP);
	//	右下
	glColor3f(b[2] / 255.f, b[1] / 255.f, b[0] / 255.f);
	glTexCoord2i(1, 0);
	glVertex3f(1, -1, 0.99999);
	//	右上
	glColor3f(u[2] / 255.f, u[1] / 255.f, u[0] / 255.f);
	glTexCoord2i(1, 1);
	glVertex3f(1, 1, 0.99999);
	//	左下
	glColor3f(b[2] / 255.f, b[1] / 255.f, b[0] / 255.f);
	glTexCoord2i(0, 0);
	glVertex3f(-1, -1, 0.99999);
	//	左上
	glColor3f(u[2] / 255.f, u[1] / 255.f, u[0] / 255.f);
	glTexCoord2i(0, 1);
	glVertex3f(-1, 1, 0.99999);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void GLView::DrawPoints(std::vector<PointWithComment> points, int selected_index)
{
	int pointSize = m_point_size;
	int pointNum = (int)points.size();

	//	背景セット
	SetBackground();
	
	//	色
	cv::Scalar gray(200, 200, 200);	//	default_color
	cv::Scalar red(0, 0, 255);		//	selected_color

	//	点描画
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	for (int i=0;i<pointNum;i++)
	{
		cv::Point3f *p = &points[i].first;
		if (i == selected_index)
		{
			glColor3f(red[2]/255.0f, red[1] / 255.0f, red[0] / 255.0f);
		}
		else
		{
			glColor3f(gray[2] / 255.0f, gray[1] / 255.0f, gray[0] / 255.0f);
		}
		glVertex3f(p->x, p->y, p->z);
	}
	glEnd();

	if (m_show_text_flag)
	{
		//	OpenCVでテキスト描画
		cv::Mat img = GetImage();
		for (int i = 0; i < pointNum; i++)
		{
			cv::Point3f p3 = points[i].first;
			cv::Point2f p2 = Cvt3Dto2D(p3);
			if (p2.x < 0 || p2.x > img.cols - 1 || p2.y < 0 || p2.y > img.rows - 1) continue;
			std::string text = (boost::format("[%d]") % (i+1)).str();
			cv::Scalar color = (i == selected_index) ? red : gray;
			cv::putText(img, text, p2, cv::FONT_HERSHEY_SIMPLEX, 0.5, color);
		}
		SetImage(img);
	}
}

void GLView::Set3DPointsData(std::vector<PointWithComment> points)
{
	m_points = points;
	return;
}

cv::Mat GLView::GetImage()
{
	int height = this->size().height();
	int width = this->size().width();

	cv::Mat img = cv::Mat::zeros(cv::Size(width, height), CV_8UC4);
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, img.data);	//	data = { r[0], g[0], b[0], a[0], r[1]...
	cv::flip(img, img, 0);	//	左下が(0,0)になっているので反転

	std::vector<cv::Mat> mat4;
	cv::split(img, mat4);
	std::vector<cv::Mat> mat3{ mat4[2], mat4[1], mat4[0] };
	cv::merge(mat3, img);

	return img;
}

void GLView::SetImage(cv::Mat img)
{
	int height = this->size().height();
	int width = this->size().width();

	std::vector<cv::Mat> mat3;
	cv::split(img, mat3);
	cv::Mat alpha(img.size(), CV_8UC1, cv::Scalar(255));
	std::vector<cv::Mat> mat4{ mat3[2], mat3[1], mat3[0], alpha };
	cv::Mat glImg;
	cv::merge(mat4, glImg);
	
	cv::flip(glImg, glImg, 0);

	glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, glImg.data);
}

cv::Point2f GLView::Cvt3Dto2D(cv::Point3f p)
{
	//	Projection Matrix
	GLfloat pmat[16];
	glGetFloatv(GL_PROJECTION_MATRIX, pmat);
	//	Modelview Matrix
	GLfloat mmat[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mmat);
	//	Viewport Matrix
	float h = this->size().height();
	float w = this->size().width();
	float x_off = 0.0, y_off = 0.0;
	GLfloat vmat[16] = {
		w / 2,0,0,(x_off + w / 2),
		0,h / 2,0,(y_off + h / 2),
		0,0,0,0,	//	0,0,(f-n)/2,(f+n)/2
		0,0,0,1
	};

	//	Convert
	cv::Mat src = (cv::Mat_<float>(4, 1) << p.x , p.y , p.z , 0.0f);
	cv::Mat dst;
	cv::Mat P(4, 4, CV_32FC1, pmat);
	cv::Mat M(4, 4, CV_32FC1, mmat);
	cv::Mat V(4, 4, CV_32FC1, vmat);

	//std::cout << "P = " << P << std::endl;
	//std::cout << "M = " << M << std::endl;
	//std::cout << "V = " << V << std::endl;
	//std::cout << "src = " << src << std::endl;

	dst = V * P.t() * M.t() * src;

	cv::Point2f ret(dst.at<float>(0), dst.at<float>(1));
	ret.x += w / 2;
	ret.y -= h / 2;
	ret.y *= -1;
	return ret;
}

void GLView::s_ShowTextFlagChanged(int flag)
{
	if (flag == 0) m_show_text_flag = false;
	else m_show_text_flag = true;
	updateGL();
}

void GLView::s_TableSelectionChanged(int rows, int cols)
{
	m_selected_index = rows;
	updateGL();
}

void GLView::SetPointSize(int psize)
{
	m_point_size = psize;
	updateGL();
}
void GLView::s_PointSizeChanged(int psize)
{
	SetPointSize(psize);
}
