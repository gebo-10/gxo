#ifndef MPEG_MODULE
#define MPEG_MODULE
#include "module.h"
extern "C"{
#include <libavutil/log.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
}
using namespace std;

#define LOGE info

class MpegModule :public Module
{
public:

	AVFormatContext* pFormatCtx;
	int i, videoindex;
	AVCodecContext* pCodecCtx;
	AVCodec* pCodec;

	AVPacket* avPacket;
	AVFrame* avFrameIn;
	SwsContext* swsContext;
	AVFrame* pAVFrameYUV420P;
	int currentIndex;
	FILE* fileYUV420P;
	uint8_t* outBuffer;

	AVFrame* pFrame, * pFrameYUV;
	uint8_t* out_buffer;
	AVPacket* pPacket;
	int y_size;
	int ret, got_picture;
	struct SwsContext* img_convert_ctx;
	FILE* fp_yuv;
	int frame_cnt;
	clock_t time_start, time_finish;
	double  time_duration = 0.0;

	const char* input_str = "a.mp4";
	const char* output_str = "a2.mp4";



	CameraPtr camera;
	PlaneModelPtr plane;
	TexturePtr t;
	MpegModule()
	{
	}

	~MpegModule()
	{
	}

	virtual void init() {
		glClearColor(1.0, 0.5, 0.2, 1.0);

		auto video_mat = std::make_shared<VideoMaterial>(1280, 720);
		plane = std::make_shared<PlaneModel>(video_mat);
		t = video_mat->get_texture();
		camera = std::make_shared<Camera>();
		camera->set_type(Camera::PERSPECTIVE);
		camera->set_ortho(-400, 400, -400, 400);
		camera->lookat(vec3(0, 0, 2), vec3(0, 0, 0), vec3(0, 1, 0));

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glClearColor(1.0, 0.5, 0.2, 1.0);




		pFormatCtx = avformat_alloc_context();

		//打开输入的视频文件
		if (avformat_open_input(&pFormatCtx, input_str, NULL, NULL) != 0) {
			LOGE("Couldn't open input stream.\n");
			return ;
		}
	

		//获取视频文件信息
		if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
			LOGE("Couldn't find stream information.\n");
			return ;
		}


		videoindex = -1;
		///遍历视音频流的个数
		for (int i = 0; i < pFormatCtx->nb_streams; i++) {
			if (pFormatCtx->streams[i]/*视音频流*/->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
				videoindex = i;
				break;
			}
		}

		if (videoindex == -1) {
			LOGE("Couldn't find a video stream.\n");
			return;
		}

		/*
	* 2.根据视频流索引，获取解码器上下文
	* 旧的接口，拿到上下文，pFormatContext->streams[i]->codec
	* 4.0.0以后新加入的类型代替codec
	* codec-codecpar 此处的新接口不需要上下文
   */
		AVCodecParameters* avcodecParameters = pFormatCtx->streams[videoindex]->codecpar;
		enum AVCodecID codecId = avcodecParameters->codec_id;

		//指向AVCodecContext的指针
		//pCodecCtx = pFormatCtx->streams[videoindex]->codecpar;
		//指向AVCodec的指针.查找解码器
		pCodec = avcodec_find_decoder(pFormatCtx->streams[videoindex]->codecpar->codec_id);
		if (pCodec == NULL)
		{
			LOGE("Couldn't find Codec.\n");
			return;
		}


		pCodecCtx = avcodec_alloc_context3(NULL);
		if (pCodecCtx == NULL)
		{
			//创建解码器上下文失败
			LOGE("create condectext failed ");
			return;
		}
		//pCodecCtx = avcodec_alloc_context3(pCodec);
		//pCodecCtx->width = 1280;
		//pCodecCtx->height = 720;
		

		//打开解码器
		avcodec_parameters_to_context(pCodecCtx, avcodecParameters);
		if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
			LOGE("Couldn't open codec.\n");
			return ;
		}

		////用来保存数据缓存的对像
		//pFrame = av_frame_alloc();
		//pFrameYUV = av_frame_alloc();

		//out_buffer = (unsigned char*)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height, 1));
		//av_image_fill_arrays(pFrameYUV->data, pFrameYUV->linesize, out_buffer,
		//	AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height, 1);

		//pPacket = (AVPacket*)av_malloc(sizeof(AVPacket));

		//img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
		//	pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);

		////sprintf(info, "[Input     ]%s\n", input_str);
		////sprintf(info, "%s[Output    ]%s\n", info, output_str);
		////sprintf(info, "%s[Format    ]%s\n", info, pFormatCtx->iformat->name);
		////sprintf(info, "%s[Codec     ]%s\n", info, pCodecCtx->codec->name);
		////sprintf(info, "%s[Resolution]%dx%d\n", info, pCodecCtx->width, pCodecCtx->height);

		//fp_yuv = fopen(output_str, "wb+");
		//if (fp_yuv == NULL) {
		//	printf("Cannot open output file.\n");
		//	return ;
		//}

		//frame_cnt = 0;
		//time_start = clock();



		/*
	 * 第六步：读取视频压缩数据->循环读取
	 * av_read_frame(AVFoematContext *s, AVPacket *packet)
	 * s: 封装格式上下文
	 * packet:一帧的压缩数据
	*/
		avPacket = (AVPacket*)av_mallocz(sizeof(AVPacket));
		avFrameIn = av_frame_alloc();  //用于存放解码之后的像素数据
		// sws_getContext(int srcW, int srcH, enum AVPixelFormat srcFormat, int dstW, int dstH, enum AVPixelFormat dstFormat, int flags, SwsFilter *srcFilter, SwsFilter *dstFilter, const double *param)
		// 原始数据
		// scrW: 原始格式宽度
		// scrH: 原始格式高度
		// scrFormat: 原始数据格式
		// 目标数据
		// dstW: 目标格式宽度
		// dstH: 目标格式高度
		// dstFormat: 目标数据格式
		// 当遇到Assertion desc failed at src/libswscale/swscale_internal.h:668
		// 这个问题就是获取元数据的高度有问题
		swsContext = sws_getContext(avcodecParameters->width,
			avcodecParameters->height,
			pCodecCtx->pix_fmt,
			avcodecParameters->width,
			avcodecParameters->height,
			AV_PIX_FMT_RGBA,
			SWS_BITEXACT, NULL, NULL, NULL);
		//创建缓冲区
		//创建一个YUV420视频像素数据格式缓冲区（一帧数据）
		pAVFrameYUV420P = av_frame_alloc();
		//给缓冲区设置类型->yuv420类型
		 //得到YUV420P缓冲区大小
		 // av_image_get_buffer_size(enum AVPixelFormat pix_fmt, int width, int height, int align)
		 //pix_fmt: 视频像素数据格式类型->YUV420P格式
		 //width: 一帧视频像素数据宽 = 视频宽
		 //height: 一帧视频像素数据高 = 视频高
		 //align: 字节对齐方式->默认是1
		int bufferSize = av_image_get_buffer_size(AV_PIX_FMT_RGBA,
			pCodecCtx->width,
			pCodecCtx->height,
			1);
		cout << "size:" << bufferSize << endl;
		//开辟一块内存空间
		outBuffer = (uint8_t*)av_malloc(bufferSize);
		//向pAVFrameYUV420P->填充数据
		// av_image_fill_arrays(uint8_t **dst_data, int *dst_linesize, const uint8_t *src, enum AVPixelFormat pix_fmt, int width, int height, int align)
		//dst_data: 目标->填充数据(pAVFrameYUV420P)
		//dst_linesize: 目标->每一行大小
		//src: 原始数据
		//pix_fmt: 目标->格式类型
		//width: 宽
		//height: 高
		//align: 字节对齐方式
		av_image_fill_arrays(pAVFrameYUV420P->data,
			pAVFrameYUV420P->linesize,
			outBuffer,
			AV_PIX_FMT_RGBA,
			pCodecCtx->width,
			pCodecCtx->height,
			1);
		fileYUV420P = fopen("out.yuv", "wb+");
		currentIndex = 0;

		
		

	}
	virtual void render() {
		/* Render here */

		if (av_read_frame(pFormatCtx, avPacket) >= 0)
		{
			//判断是不是视频
			if (avPacket->stream_index == videoindex)
			{
				//读取每一帧数据，立马解码一帧数据
				//解码之后得到视频的像素数据->YUV
				// avcodec_send_packet(AVCodecContext *avctx, AVPacket *pkt)
				// avctx: 解码器上下文
				// pkt: 获取到数据包
				// 获取一帧数据
				avcodec_send_packet(pCodecCtx, avPacket);

				//解码
				ret = avcodec_receive_frame(pCodecCtx, avFrameIn);
				if (ret == 0)  //解码成功
				{
					currentIndex++;
					cout << "当前解码 " << currentIndex << "帧" << endl;

					

					//此处无法保证视频的像素格式一定是YUV格式
					 //将解码出来的这一帧数据，统一转类型为YUV
					 // sws_scale(struct SwsContext *c, const uint8_t *const *srcSlice, const int *srcStride, int srcSliceY, int srcSliceH, uint8_t *const *dst, const int *dstStride)
					  // SwsContext *c: 视频像素格式的上下文
					  // srcSlice: 原始视频输入数据
					  // srcStride: 原数据每一行的大小
					  // srcSliceY: 输入画面的开始位置，一般从0开始
					  // srcSliceH: 原始数据的长度
					  // dst: 输出的视频格式
					  // dstStride: 输出的画面大小
					//sws_scale(sws_ctx, _std_frame->data, _std_frame->linesize, 0, _codec_context_video->height, _rgb_frame->data, _rgb_frame->linesize);

					sws_scale(swsContext, (const uint8_t* const*)avFrameIn->data,
						avFrameIn->linesize,
						0,
						pCodecCtx->height,
						pAVFrameYUV420P->data,
						pAVFrameYUV420P->linesize);

					t->update(pAVFrameYUV420P->data[0]);
					

					//方式二：写入yuv文件格式
					//5、将yuv420p数据写入.yuv文件中
					//5.1 计算YUV大小
					//分析一下原理?
					//Y表示：亮度
					//UV表示：色度
					//有规律
					//YUV420P格式规范一：Y结构表示一个像素(一个像素对应一个Y)
					//YUV420P格式规范二：4个像素点对应一个(U和V: 4Y = U = V)
					/*
					int ySize, uSize, vSize;
					ySize = pCodecCtx->width * pCodecCtx->height;
					uSize = ySize / 4;
					vSize = ySize / 4;
					fwrite(pAVFrameYUV420P->data[0], 1, ySize, fileYUV420P);
					fwrite(pAVFrameYUV420P->data[1], 1, uSize, fileYUV420P);
					fwrite(pAVFrameYUV420P->data[2], 1, vSize, fileYUV420P);
					
					
					*/
				}
			}
		}
		av_packet_unref(avPacket);

		cout << "当前解码 " << currentIndex << "帧" << endl;


		//static int i = 0;
		//plane->transform.rotate = vec3(0, 0, 180);
		//i++;
		plane->transform.scale = vec3(1.5, 1, 1);
		glClearColor(0.0, 0.5, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		plane->render(camera);

	}


	virtual void quit() {
		/*
		 * 关闭解码器
		 *
		*/
		/*av_packet_free(&avPacket);
		fclose(fileYUV420P);
		av_frame_free(&avFrameIn);
		av_frame_free(&pAVFrameYUV420P);
		free(outBuffer);
		avcodec_close(pCodecCtx);
		avformat_free_context(pFormatCtx);*/
	}
	virtual void key(int key) {}

	virtual void mouse(int button, int x, int y) {}

private:

};

#endif