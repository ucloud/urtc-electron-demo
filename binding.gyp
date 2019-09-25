{
  "targets": [
    {
      "target_name": "UCloudRtcElectronEngine",
	   'defines': [
           "_UNICODE",
		   "UNICODE"
       ],
	  'conditions': [
            [
				'OS=="win"',
				{
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
						"rtcplugin/win/UCloudRtcElectronPlugin.cc",
						"rtcplugin/win/node_async_queue.cpp",
						"rtcplugin/win/node_async_queue.h",
						"rtcplugin/win/node_event_handler.cpp",
						"rtcplugin/win/node_event_handler.h",
						"rtcplugin/win/node_napi_api.cpp",
						"rtcplugin/win/node_napi_api.h",
						"rtcplugin/win/UCloudRtcElectronEngine.cc",
						"rtcplugin/win/UCloudRtcElectronEngine.h",
						"rtcplugin/win/UCloudRtcElectronDefine.h",
						"rtcplugin/win/node_log.cpp",
						"rtcplugin/win/node_log.h",
						"rtcplugin/win/VideoPackageQueue.cpp",
						"rtcplugin/win/BufferQueue.cpp"
					],
					'include_dirs':[
						'rtcplugin',
						'rtcplugin/win/urtcsdkc/urtcsdk/include',
						'rtcplugin/win/urtcsdkc/third_party/jsoncpp/include',
						'rtcplugin/win/urtcsdkc/third_party/beauty',
						'rtcplugin/win/urtcsdkc/third_party/beauty/include'
						
					],
					'library_dirs': [
						'rtcplugin/win/urtcsdkc/urtcsdk/sdk',
						'rtcplugin/win/urtcsdkc/third_party/jsoncpp/lib/release',
						'rtcplugin/win/urtcsdkc/third_party/beauty/lib'
					],
					'link_settings': {
						'libraries': [
							'-ljsoncpp.lib',
							'-lUCloudRtcMediaEngine.lib',
							'-lbeautymoudle.lib'
						]
					},
				}
			],
			[
				 'OS=="mac"', {
					 'mac_framework_dirs': [
						'rtcplugin/mac/urtcsdkc/lib'
					 ],
					 'link_settings': {
						'libraries': [
							'libresolv.9.dylib',
							'Accelerate.framework',
							'UCloudRtcSdk_mac.framework',
							'CoreWLAN.framework',
							'Cocoa.framework',
							'VideoToolbox.framework',
							'SystemConfiguration.framework',
							'IOKit.framework',
							'CoreVideo.framework',
							'CoreMedia.framework',
							'OpenGL.framework',
							'CoreGraphics.framework',
							'CFNetwork.framework',
							'AudioToolbox.framework',
							'CoreAudio.framework',
							'Foundation.framework',
							'AVFoundation.framework',
						]
					},
					"sources": [
						"rtcplugin/mac/UCloudRtcElectronPlugin.cc",
						"rtcplugin/mac/node_async_queue.cpp",
						"rtcplugin/mac/node_async_queue.h",
						"rtcplugin/mac/node_event_handler.cpp",
						"rtcplugin/mac/node_event_handler.h",
						"rtcplugin/mac/node_napi_api.cpp",
						"rtcplugin/mac/node_napi_api.h",
						"rtcplugin/mac/UCloudRtcElectronEngine.cc",
						"rtcplugin/mac/UCloudRtcElectronEngine.h",
						"rtcplugin/mac/UCloudRtcElectronDefine.h",
						"rtcplugin/mac/node_log.cpp",
						"rtcplugin/mac/node_log.h"
					],
					'include_dirs': [
						'./sdk/lib/mac/AgoraRtcEngineKit.framework/Headers'
					],
					'defines!': [
                		'_HAS_EXCEPTIONS=0',
                		'-std=gnu++14'
                	],
                	'xcode_settings': {
                    	'MACOSX_DEPLOYMENT_TARGET': '10.10',
                    	'FRAMEWORK_SEARCH_PATHS': [
                    		'./sdk/lib/mac'
                    	]
                	},
				 }
			]
	  ]
	}
  ]
}