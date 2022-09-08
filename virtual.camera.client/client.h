#pragma once

#include "../psyai.virtual.camera/shared_memory_queue.h"

#define INTERVAL 10000000ULL / 30

typedef struct
{
	size_t width;
	size_t height;
	uint8_t* data[2];
	uint32_t linesize[2];
} Frame;

typedef struct 
{
	video_queue_t* queue;
	Frame frame;
	bool runing;
} VCam;

typedef struct
{
	size_t size;
	size_t y_size;
	size_t uv_size;
} NV12Layout;

extern "C" __declspec(dllexport) VCam* vcam_open();
extern "C" __declspec(dllexport) int vcam_start(VCam* vcam, uint32_t width, uint32_t height);
extern "C" __declspec(dllexport) int vcam_write_frame(VCam* vcam, uint8_t* data);
extern "C" __declspec(dllexport) void vcam_stop(VCam* vcam);
extern "C" __declspec(dllexport) NV12Layout get_nv12_layout(size_t width, size_t height);
extern "C" __declspec(dllexport) uint8_t* i420_to_nv12(size_t width, size_t height, uint8_t* i420);