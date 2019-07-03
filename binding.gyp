{
  "targets": [
    {
      "target_name": "UCloudRtcElectronEngine",
	  'configurations': {
            'Debug': {
                'msvs_settings': {
					'VCCLCompilerTool': {
						'RuntimeLibrary': '2' # /MD
					},
                },
            },
            'Release': {
                'msvs_settings': {
					'VCCLCompilerTool': {
						'RuntimeLibrary': '2' # /MD
					},
                },
            },
        },
      "sources": [
					"rtcplugin/UCloudRtcElectronPlugin.cc",
					"rtcplugin/node_async_queue.cpp",
					"rtcplugin/node_async_queue.h",
					"rtcplugin/node_event_handler.cpp",
					"rtcplugin/node_event_handler.h",
					"rtcplugin/node_napi_api.cpp",
					"rtcplugin/node_napi_api.h",
					"rtcplugin/UCloudRtcElectronEngine.cc",
					"rtcplugin/UCloudRtcElectronEngine.h",
					"rtcplugin/UCloudRtcElectronDefine.h",
					"rtcplugin/node_log.cpp",
					"rtcplugin/node_log.h"
			],
	  'include_dirs':[
					'rtcplugin',
					'rtcplugin/urtcsdkc/urtcsdk/include',
					'rtcplugin/urtcsdkc/third_party/jsoncpp/include'
    ],
	  'library_dirs': [
         'rtcplugin/urtcsdkc/urtcsdk/sdk',
		 'rtcplugin/urtcsdkc/third_party/jsoncpp/lib/release'
      ],
	  'link_settings': {
		'libraries': [
			'-ljsoncpp.lib',
			'-lUCloudRtcMediaEngine.lib'
		]
      },
    }
  ]
}