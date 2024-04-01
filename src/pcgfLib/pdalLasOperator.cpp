#include<pcgfLib\pdalLasOperator.h>

namespace pcgf{
	PointCloud pdalLasOperator::pc_read()
{
	pdal::Option las_opt("filename", lasFileName);
	pdal::Options las_opts;
	las_opts.add(las_opt);

	pdal::PointTable table;
	pdal::LasReader las_reader;


	las_reader.addOptions(las_opts);
	las_reader.prepare(table);

	pdal::PointViewSet point_view_set = las_reader.execute(table);
	pdal::PointViewPtr point_view = *point_view_set.begin();
	pdal::Dimension::IdList dims = point_view->dims();
	pdal::LasHeader las_header = las_reader.header();




	las_header_fresh.scale[0] = las_header.scaleX();
	las_header_fresh.scale[1] = las_header.scaleY();
	las_header_fresh.scale[2] = las_header.scaleZ();
	las_header_fresh.offset[0] = las_header.offsetX();
	las_header_fresh.offset[1] = las_header.offsetY();
	las_header_fresh.offset[2] = las_header.offsetZ();


	//double xmin = las_header.minX();
	//double xmax = las_header.maxX();
	//double ymin = las_header.minY();
	//double ymax = las_header.maxY();
	//double zmin = las_header.minZ();
	//double zmax = las_header.maxZ();
	//unsigned int n_features = las_header.pointCount();

	PointCloud point_cloud;
	point_cloud.points = Eigen::MatrixXf::Zero(las_header.pointCount(), 3);
	point_cloud.intensities = Eigen::RowVectorXf::Zero(las_header.pointCount());
	for (pdal::PointId idx = 0; idx < las_header.pointCount(); ++idx)
	{

		point_cloud.points(idx, 0) = point_view->getFieldAs<double>(pdal::Dimension::Id::X, idx);
		point_cloud.points(idx, 1) = point_view->getFieldAs<double>(pdal::Dimension::Id::Y, idx);
		point_cloud.points(idx, 2) = point_view->getFieldAs<double>(pdal::Dimension::Id::Z, idx);

		point_cloud.classifications.push_back(point_view->getFieldAs<int>(pdal::Dimension::Id::Classification, idx));
		point_cloud.intensities(idx) = (point_view->getFieldAs<float>(pdal::Dimension::Id::Intensity, idx));

	}
	std::cout << las_header.pointCount() << std::endl;
	return point_cloud;
}

void pdalLasOperator::pc_save(const std::string& path,std::vector<int> clc, int NoiseLabel)
{
	pdal::Options xiOptions, xjOptions;
	xjOptions.add("filename", path);
	xjOptions.add("offset_x", las_header_fresh.offset[0]);
	xjOptions.add("offset_y", las_header_fresh.offset[1]);
	xjOptions.add("offset_z", las_header_fresh.offset[2]);
	xjOptions.add("scale_x", las_header_fresh.scale[0]);
	xjOptions.add("scale_y", las_header_fresh.scale[1]);
	xjOptions.add("scale_z", las_header_fresh.scale[2]);

	pdal::PointTable table;
	table.layout()->registerDim(pdal::Dimension::Id::X);
	table.layout()->registerDim(pdal::Dimension::Id::Y);
	table.layout()->registerDim(pdal::Dimension::Id::Z);
	table.layout()->registerDim(pdal::Dimension::Id::Intensity);
	table.layout()->registerDim(pdal::Dimension::Id::Red);
	table.layout()->registerDim(pdal::Dimension::Id::Green);
	table.layout()->registerDim(pdal::Dimension::Id::Blue);
	table.layout()->registerDim(pdal::Dimension::Id::Classification);

	//首先读取原始文件
	xiOptions.add("filename", lasFileName);

	pdal::LasReader las_reader;
	las_reader.addOptions(xiOptions);
	las_reader.prepare(table);

	//下面两个专门用于读取
	pdal::PointViewSet point_view_set = las_reader.execute(table);
	pdal::PointViewPtr point_view = *point_view_set.begin();

	//下面用于输出
	pdal::PointViewPtr view(new pdal::PointView(table));

	//0   1  

	for (int i = 0; i < las_reader.header().pointCount(); ++i)
	{
		view->setField(pdal::Dimension::Id::X, i, point_view->getFieldAs<double>(pdal::Dimension::Id::X, i));
		view->setField(pdal::Dimension::Id::Y, i, point_view->getFieldAs<double>(pdal::Dimension::Id::Y, i));
		view->setField(pdal::Dimension::Id::Z, i, point_view->getFieldAs<double>(pdal::Dimension::Id::Z, i));
		view->setField(pdal::Dimension::Id::Intensity, i, point_view->getFieldAs<double>(pdal::Dimension::Id::Intensity, i));
		if (clc[i] == 1 ) {
			view->setField(pdal::Dimension::Id::Classification, i, NoiseLabel);
		}
		else {
			view->setField(pdal::Dimension::Id::Classification, i, point_view->getFieldAs<double>(pdal::Dimension::Id::Classification, i));
		}

		view->setField(pdal::Dimension::Id::Red, i, point_view->getFieldAs<double>(pdal::Dimension::Id::Red, i));
		view->setField(pdal::Dimension::Id::Green, i, point_view->getFieldAs<double>(pdal::Dimension::Id::Green, i));
		view->setField(pdal::Dimension::Id::Blue, i, point_view->getFieldAs<double>(pdal::Dimension::Id::Blue, i));
	}

	pdal::BufferReader xjBufferReader;
	xjBufferReader.addView(view);

	pdal::StageFactory factory;
	std::string w_drivername = factory.inferWriterDriver(path);
	pdal::Stage* writer = factory.createStage(w_drivername);
	//pdal::Stage* writer = factory.createStage("writers.las");

	writer->addOptions(xjOptions);

	writer->setInput(xjBufferReader);
	writer->setOptions(xjOptions);
	writer->prepare(table);

	writer->execute(table);

}

}

