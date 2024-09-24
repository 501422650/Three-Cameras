// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 YOLOV5SEGTRT_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// YOLOV5SEGTRT_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef YOLOV5SEGTRT_EXPORTS
#define YOLOV5SEGTRT_API __declspec(dllexport)
#else
#define YOLOV5SEGTRT_API __declspec(dllimport)
#endif

#include <fstream>
#include <iostream>
#include <sstream>
#include "NvInfer.h"
#include <opencv2/opencv.hpp>

using namespace nvinfer1;
using namespace cv;

struct DetectResult {
	int classId;
	float conf;
	cv::Rect box;
	int area;
};

// 此类是从 dll 导出的
class YOLOV5SEGTRT_API yolov5segtrt {
public:
	void readClassNames(std::string label_path);
	void initConfig(std::string enginefile, float conf_thresholod, float score_thresholod, std::string label_path);
	void detect(cv::Mat& frame, std::vector<DetectResult>& results);
	~yolov5segtrt();
private:
	std::vector<std::string> classNames;
	float sigmoid_function(float a);
	float conf_thresholod = 0.25;
	float score_thresholod = 0.25;
	int input_h = 512;
	int input_w = 512;
	int output_h;
	int output_w;
	int output_m_c;
	int output_m_len;
	int input_index;
	int output_index;
	int mask_index;
	IRuntime* runtime{ nullptr };
	ICudaEngine* engine{ nullptr };
	IExecutionContext* context{ nullptr };
	void* buffers[3] = { NULL, NULL , NULL };
	std::vector<float> prob; // detect
	std::vector<float> mprob; // mask
	cudaStream_t stream;
};

