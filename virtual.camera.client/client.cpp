#include "client.h"

static bool HAVE_CLOCKFREQ = false;
static LARGE_INTEGER CLOCKFREQ;

static inline uint64_t get_clockfreq(void)
{
	if (!HAVE_CLOCKFREQ)
	{
		QueryPerformanceFrequency(&CLOCKFREQ);
		HAVE_CLOCKFREQ = true;
	}

	return CLOCKFREQ.QuadPart;
}

uint64_t gettime_100ns(void)
{
	LARGE_INTEGER current_time;
	double time_val;

	QueryPerformanceCounter(&current_time);
	time_val = (double)current_time.QuadPart;
	time_val *= 10000000.0;
	time_val /= (double)get_clockfreq();

	return (uint64_t)time_val;
}

NV12Layout get_nv12_layout(size_t width, size_t height)
{
	NV12Layout layout;
	layout.size = width * height * 1.5;
	layout.y_size = width * height;
	layout.uv_size = width * height / 2;
	return layout;
}

uint8_t* i420_to_nv12(size_t width, size_t height, uint8_t* i420)
{
	NV12Layout layout = get_nv12_layout(width, height);
	uint8_t* nv12 = (uint8_t*)malloc(sizeof(uint8_t) * layout.size);
	if (nv12 == NULL)
	{
		return NULL;
	}

	// copy y
	memcpy(nv12, i420, layout.y_size);

	// uv
	uint8_t* nv12_uv = nv12 + layout.y_size;
	uint8_t* i420_u = i420 + layout.y_size;
	uint8_t* i420_v = i420_u + (layout.uv_size / 2);
	for (int i = 0; i < layout.uv_size / 2; i ++)
	{
		nv12_uv[i * 2] = i420_u[i];
		nv12_uv[i * 2 + 1] = i420_v[i];
	}

	return nv12;
}

VCam* vcam_open()
{
	VCam* vcam = (VCam*)malloc(sizeof(VCam));
	if (!vcam)
	{
		return NULL;
	}

	vcam->runing = false;
	return vcam;
}

int vcam_start(VCam* vcam, uint32_t width, uint32_t height)
{
	if (vcam->runing)
	{
		return -2;
	}

	vcam->queue = video_queue_create(width, height, INTERVAL);
	if (!vcam->queue)
	{
		return -1;
	}

	vcam->runing = true;
	vcam->frame.width = width;
	vcam->frame.height = height;
	vcam->frame.linesize[0] = width;

	return 0;
}

void vcam_stop(VCam* vcam)
{
	video_queue_close(vcam->queue);
	vcam->runing = false;
}

int vcam_write_frame(VCam* vcam, uint8_t* frame)
{
	if (!vcam->runing)
	{
		return -2;
	}

	vcam->frame.data[0] = frame;
	vcam->frame.data[1] = frame + (vcam->frame.width * vcam->frame.height);

	uint8_t** data = vcam->frame.data;
	uint32_t* linesize = vcam->frame.linesize;
	video_queue_write(vcam->queue, data, linesize, gettime_100ns());

	return 0;
}