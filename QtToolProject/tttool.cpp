#include "tttool.h"

ttTool::ttTool(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//	2次元点データの読み込み
	std::string data2d = "2d.txt";
	Load2DPointsData(data2d);

	//	3次元点データの読み込み
	std::string data = "3d_points.csv";
	Load3DPointsData(data);

	//	GLViewへ点情報をセット
	ui.widget->Set3DPointsData(m_3Dpoints);

	//	2次元点データのリストアップ
	ListUp2DPoint();
}

ttTool::~ttTool()
{

}

void ttTool::Load2DPointsData(std::string pointDataStr2D)
{
	//	ファイルオープン
	std::ifstream ifs(pointDataStr2D, std::ios::in);
	if (!ifs.is_open())
	{
		std::cerr << __FUNCTION__ << " error : cannot open file." << std::endl;
		return;
	}

	//	クリア
	m_2Dpoints.clear();
	//	ロード＆プッシュ
	std::string line;
	std::getline(ifs, line);	//	1行飛ばし
	while (std::getline(ifs, line))
	{
		cv::Point p;

		std::replace(line.begin(), line.end(), ',', ' ');
		std::stringstream ss(line);
		int tmp;
		ss >> tmp >> p.x >> p.y;

		m_2Dpoints.push_back(p);
	}

}

void ttTool::Load3DPointsData(std::string pointDataStr3D)
{
	//	ファイルオープン
	std::ifstream ifs(pointDataStr3D, std::ios::in);
	if (!ifs.is_open())
	{
		std::cerr << __FUNCTION__ << " error : cannot open file." << std::endl;
		return;
	}

	//	クリア
	m_3Dpoints.clear();
	//	ロード＆プッシュ
	std::string line;
	while (std::getline(ifs, line))
	{
		PointWithComment tmp;
		cv::Point3f *p = &tmp.first;
		std::string *str = &tmp.second;

		std::replace(line.begin(), line.end(), ',', ' ');
		std::stringstream ss(line);
		ss >> p->x >> p->y >> p->z >> *str;
		m_3Dpoints.push_back(tmp);
	}

}

void ttTool::InitPairIndex()
{
	int pointNum = (int)m_2Dpoints.size();
	
	for (int i = 0; i < pointNum; i++)
	{
		m_2D3Dpairs.push_back(std::make_pair(i, -1));
	}
}

void ttTool::ListUp2DPoint()
{
	int pointNum = (int)m_2Dpoints.size();

	//	行数、列数
	ui.pairTable->setColumnCount(1);
	ui.pairTable->setRowCount(pointNum);

	//	タイトル行
	ui.pairTable->setHorizontalHeaderLabels(QStringList() << tr("Comment"));

	//	列ヘッダーを0～に変更
	QStringList VHeader;
	for (int i = 0; i < pointNum; i++)
	{
		std::string numStr = (boost::format("%d") % i).str();
		VHeader.push_back(QString::fromStdString(numStr));
	}
	ui.pairTable->setVerticalHeaderLabels(VHeader);

	//	一行選択モード
	ui.pairTable->setSelectionMode(QAbstractItemView::ContiguousSelection);
	ui.pairTable->setSelectionBehavior(QAbstractItemView::SelectRows);

	//	各列の設定
	ui.pairTable->setColumnWidth(0, 170);

	//	各行の設定
	for (int i = 0; i < pointNum; i++)
	{
		//	高さセット
		ui.pairTable->setRowHeight(i, 20);

		//	アイテム登録
		QComboBox *box = new QComboBox(ui.pairTable);
		box->insertItem(0,"");
		for (int j = 0; j < (int)m_3Dpoints.size(); j++)
		{
			std::string str = (boost::format("[%d]:") % j).str();
			box->insertItem(j+1, QString::fromStdString(str + m_3Dpoints[j].second));
		}
		
		ui.pairTable->setCellWidget(i, 0, box);

		
		//
	}

	//ui.pairTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
	//ui.pairTable->horizontalHeader()->setResizeMode(1, QHeaderView::ResizeToContents);
}

std::vector<ttTool::PairIndex> ttTool::GetPairs()
{
	std::vector<PairIndex> ret;

	int size = ui.pairTable->rowCount();
	
	for (int i = 0; i < size; i++)
	{
		QComboBox *b = (QComboBox *)ui.pairTable->cellWidget(i, 0);
		PairIndex pi = std::make_pair(i, b->currentIndex() - 1);	//	先頭の空行のため-1
		ret.push_back(pi);
	}

	return ret;
}

void ttTool::s_Save()
{
	std::string output = "CorrespondenceList.csv";
	std::ofstream ofs(output, std::ios::out);

	//	リスト取得
	m_2D3Dpairs.clear();
	m_2D3Dpairs = GetPairs();

	//	保存
	int size = (int)m_2D3Dpairs.size();
	for (int i = 0; i < size; i++)
	{
		PairIndex index = m_2D3Dpairs[i];
		cv::Point p2 = m_2Dpoints[index.first];
		ofs << p2.x << "," << p2.y;

		if (index.second >= 0)
		{
			cv::Point3f p3 = m_3Dpoints[index.second].first;
			ofs << "," << p3.x << "," << p3.y << "," << p3.z;
		}

		ofs << std::endl;
	}

	//	通知
	QMessageBox box;
	box.setText(QString::fromStdString("Saved following file.\n" + output));
	box.exec();
}