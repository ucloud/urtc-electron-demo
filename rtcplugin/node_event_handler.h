#ifndef URTC_NODE_EVENT_HANDLER_H_
#define URTC_NODE_EVENT_HANDLER_H_

#include <unordered_map>
#include <string>
#include <uv.h>
#include "node_napi_api.h"
namespace ucloud {
    namespace rtc {
#define RTC_ONEVENT_NOTIFY "onevent"
#define RTC_ONAUDIOVOL_NOTIFY "onaudiovol"

        class NodeRtcEngine;
        class NodeEventHandler
        {
        public:
            struct NodeEventCallback
            {
                Persistent<Function> callback;
                Persistent<Object> js_this;
            };
        public:
            NodeEventHandler();
            ~NodeEventHandler();
			void onEventNotify(int eventid, const char* msg);
			void onAudioVolNotify(int audiovol);
            void addEventHandler(const std::string& eventName, Persistent<Object>& obj, Persistent<Function>& callback);
			void removeEventHandler(const std::string& eventName);
			void clearEventHandler();

        private:
            void onEventNotify_node(int eventid, const char* msg) ;
			void onAudioVolNotify_node(int audiovol);
        private:
            std::unordered_map<std::string, NodeEventCallback*> m_callbacks;
        };
    }
}

#endif
