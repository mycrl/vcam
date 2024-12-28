{
    "targets": [
        {
            "target_name": "vcam-napi",
            "cflags!": [ 
                "-fno-exceptions" 
            ],
            "cflags_cc!": [ 
                "-fno-exceptions" 
            ],
            "sources": [ 
                "./src/lib.cpp",
                "./src/lib.h",
                "../driver/vcam.h",
                "../driver/vcam.cpp",
                "../service/shared_memory_queue.h",
                "../service/shared_memory_queue.cpp",
                "../service/nv12_scale.h",
                "../service/nv12_scale.cpp"
            ],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")",
                "../driver/",
                "../service/"
            ],
            'defines': [ 
                'NAPI_DISABLE_CPP_EXCEPTIONS',
                'NODE_ADDON_API_ENABLE_MAYBE'
            ]
        }
    ]
}
