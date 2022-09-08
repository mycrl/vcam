{
    "targets": [
        {
            "target_name": "vcam",
            "cflags!": [ 
                "-fno-exceptions" 
            ],
            "cflags_cc!": [ 
                "-fno-exceptions" 
            ],
            "sources": [ 
                "./src/wrapper.cc",
                "./src/wrapper.h",
                "../psyai.virtual.camera.client/client.h",
                "../psyai.virtual.camera.client/client.cpp",
                "../psyai.virtual.camera/shared_memory_queue.h",
                "../psyai.virtual.camera/shared_memory_queue.cpp",
                "../psyai.virtual.camera/nv12_scale.h",
                "../psyai.virtual.camera/nv12_scale.cpp"
            ],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")",
                "../psyai.virtual.camera.client/",
                "../psyai.virtual.camera/"
            ],
            'defines': [ 
                'NAPI_DISABLE_CPP_EXCEPTIONS',
                'NODE_ADDON_API_ENABLE_MAYBE'
            ]
        }
    ]
}
