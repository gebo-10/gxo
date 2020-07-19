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
	uint8_t* outBuffer;



	const char* input_str = "a.mp4";



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


		//打开解码器
		avcodec_parameters_to_context(pCodecCtx, avcodecParameters);
		if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
			LOGE("Couldn't open codec.\n");
			return ;
		}


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
				int ret = avcodec_receive_frame(pCodecCtx, avFrameIn);
				if (ret == 0)  //解码成功
				{
					currentIndex++;
					cout << "当前解码 " << currentIndex << "帧" << endl;

					sws_scale(swsContext, (const uint8_t* const*)avFrameIn->data,
						avFrameIn->linesize,
						0,
						pCodecCtx->height,
						pAVFrameYUV420P->data,
						pAVFrameYUV420P->linesize);

					t->update(pAVFrameYUV420P->data[0]);
				}
			}
		}
		av_packet_unref(avPacket);

		//cout << "当前解码 " << currentIndex << "帧" << endl;


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