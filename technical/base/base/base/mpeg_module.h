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

		//���������Ƶ�ļ�
		if (avformat_open_input(&pFormatCtx, input_str, NULL, NULL) != 0) {
			LOGE("Couldn't open input stream.\n");
			return ;
		}
	

		//��ȡ��Ƶ�ļ���Ϣ
		if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
			LOGE("Couldn't find stream information.\n");
			return ;
		}


		videoindex = -1;
		///��������Ƶ���ĸ���
		for (int i = 0; i < pFormatCtx->nb_streams; i++) {
			if (pFormatCtx->streams[i]/*����Ƶ��*/->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
				videoindex = i;
				break;
			}
		}

		if (videoindex == -1) {
			LOGE("Couldn't find a video stream.\n");
			return;
		}

		/*
	* 2.������Ƶ����������ȡ������������
	* �ɵĽӿڣ��õ������ģ�pFormatContext->streams[i]->codec
	* 4.0.0�Ժ��¼�������ʹ���codec
	* codec-codecpar �˴����½ӿڲ���Ҫ������
   */
		AVCodecParameters* avcodecParameters = pFormatCtx->streams[videoindex]->codecpar;
		enum AVCodecID codecId = avcodecParameters->codec_id;

		//ָ��AVCodecContext��ָ��
		//pCodecCtx = pFormatCtx->streams[videoindex]->codecpar;
		//ָ��AVCodec��ָ��.���ҽ�����
		pCodec = avcodec_find_decoder(pFormatCtx->streams[videoindex]->codecpar->codec_id);
		if (pCodec == NULL)
		{
			LOGE("Couldn't find Codec.\n");
			return;
		}


		pCodecCtx = avcodec_alloc_context3(NULL);
		if (pCodecCtx == NULL)
		{
			//����������������ʧ��
			LOGE("create condectext failed ");
			return;
		}


		//�򿪽�����
		avcodec_parameters_to_context(pCodecCtx, avcodecParameters);
		if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
			LOGE("Couldn't open codec.\n");
			return ;
		}


		/*
	 * ����������ȡ��Ƶѹ������->ѭ����ȡ
	 * av_read_frame(AVFoematContext *s, AVPacket *packet)
	 * s: ��װ��ʽ������
	 * packet:һ֡��ѹ������
	*/
		avPacket = (AVPacket*)av_mallocz(sizeof(AVPacket));
		avFrameIn = av_frame_alloc();  //���ڴ�Ž���֮�����������
		// sws_getContext(int srcW, int srcH, enum AVPixelFormat srcFormat, int dstW, int dstH, enum AVPixelFormat dstFormat, int flags, SwsFilter *srcFilter, SwsFilter *dstFilter, const double *param)
		// ԭʼ����
		// scrW: ԭʼ��ʽ���
		// scrH: ԭʼ��ʽ�߶�
		// scrFormat: ԭʼ���ݸ�ʽ
		// Ŀ������
		// dstW: Ŀ���ʽ���
		// dstH: Ŀ���ʽ�߶�
		// dstFormat: Ŀ�����ݸ�ʽ
		// ������Assertion desc failed at src/libswscale/swscale_internal.h:668
		// ���������ǻ�ȡԪ���ݵĸ߶�������
		swsContext = sws_getContext(avcodecParameters->width,
			avcodecParameters->height,
			pCodecCtx->pix_fmt,
			avcodecParameters->width,
			avcodecParameters->height,
			AV_PIX_FMT_RGBA,
			SWS_BITEXACT, NULL, NULL, NULL);
		//����������
		//����һ��YUV420��Ƶ�������ݸ�ʽ��������һ֡���ݣ�
		pAVFrameYUV420P = av_frame_alloc();
		//����������������->yuv420����
		 //�õ�YUV420P��������С
		 // av_image_get_buffer_size(enum AVPixelFormat pix_fmt, int width, int height, int align)
		 //pix_fmt: ��Ƶ�������ݸ�ʽ����->YUV420P��ʽ
		 //width: һ֡��Ƶ�������ݿ� = ��Ƶ��
		 //height: һ֡��Ƶ�������ݸ� = ��Ƶ��
		 //align: �ֽڶ��뷽ʽ->Ĭ����1
		int bufferSize = av_image_get_buffer_size(AV_PIX_FMT_RGBA,
			pCodecCtx->width,
			pCodecCtx->height,
			1);
		cout << "size:" << bufferSize << endl;
		//����һ���ڴ�ռ�
		outBuffer = (uint8_t*)av_malloc(bufferSize);
		//��pAVFrameYUV420P->�������
		// av_image_fill_arrays(uint8_t **dst_data, int *dst_linesize, const uint8_t *src, enum AVPixelFormat pix_fmt, int width, int height, int align)
		//dst_data: Ŀ��->�������(pAVFrameYUV420P)
		//dst_linesize: Ŀ��->ÿһ�д�С
		//src: ԭʼ����
		//pix_fmt: Ŀ��->��ʽ����
		//width: ��
		//height: ��
		//align: �ֽڶ��뷽ʽ
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
			//�ж��ǲ�����Ƶ
			if (avPacket->stream_index == videoindex)
			{
				//��ȡÿһ֡���ݣ��������һ֡����
				//����֮��õ���Ƶ����������->YUV
				// avcodec_send_packet(AVCodecContext *avctx, AVPacket *pkt)
				// avctx: ������������
				// pkt: ��ȡ�����ݰ�
				// ��ȡһ֡����
				avcodec_send_packet(pCodecCtx, avPacket);

				//����
				int ret = avcodec_receive_frame(pCodecCtx, avFrameIn);
				if (ret == 0)  //����ɹ�
				{
					currentIndex++;
					cout << "��ǰ���� " << currentIndex << "֡" << endl;

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

		//cout << "��ǰ���� " << currentIndex << "֡" << endl;


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
		 * �رս�����
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