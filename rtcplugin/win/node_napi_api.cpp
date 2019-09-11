#include "node_napi_api.h"
#include "node_async_queue.h"
#include <chrono>
#include <string>

#define NODE_SET_OBJ_PROP_UINT32(obj, name, val) \
    { \
        Local<Value> propName = String::NewFromUtf8(isolate, name, NewStringType::kInternalized).ToLocalChecked(); \
        Local<Value> propVal = v8::Uint32::New(isolate, val); \
        obj->Set(isolate->GetCurrentContext(), propName, propVal); \
    }
#define NODE_SET_OBJ_PROP_HEADER(obj, it) \
    { \
        Local<Value> propName = String::NewFromUtf8(isolate, "header", NewStringType::kInternalized).ToLocalChecked(); \
        Local<v8::ArrayBuffer> buff = v8::ArrayBuffer::New(isolate, (it)->buffer, (it)->length); \
        obj->Set(isolate->GetCurrentContext(), propName, buff); \
    }

#define NODE_SET_OBJ_PROP_DATA(obj, name, it) \
    { \
        Local<Value> propName = String::NewFromUtf8(isolate, name, NewStringType::kInternalized).ToLocalChecked(); \
        Local<v8::ArrayBuffer> buff = v8::ArrayBuffer::New(isolate, (it)->buffer, (it)->length); \
        Local<v8::Uint8Array> dataarray = v8::Uint8Array::New(buff, 0, it->length);\
        obj->Set(isolate->GetCurrentContext(), propName, dataarray); \
    }

int napi_get_value_string_utf8_(const Local<Value>& str, char *buffer, uint32_t len)
{
    if (!str->IsString())
        return 0;
    if (!buffer) {
        return str.As<String>()->Utf8Length();
    }
    else {
        int copied = str.As<String>()->WriteUtf8(buffer, len - 1, nullptr, String::REPLACE_INVALID_UTF8 | String::NO_NULL_TERMINATION);
        buffer[copied] = '\0';
        return copied;
    }
}

napi_status napi_get_value_uint32_(const Local<Value>& value, uint32_t& result)
{
    if (!value->IsUint32())
        return napi_invalid_arg;
    result = value->Uint32Value();
    return napi_ok;
}

napi_status napi_get_value_bool_(const Local<Value>& value, bool& result)
{
    if(!value->IsBoolean())
        return napi_invalid_arg;
    result = value->BooleanValue();
    return napi_ok;
}
	
napi_status napi_get_value_int32_(const Local<Value>& value, int32_t& result)
{
    if (!value->IsInt32())
        return napi_invalid_arg;
    result = value->Int32Value();
    return napi_ok;
}

napi_status napi_get_value_double_(const Local<Value>& value, double &result)
{
    if (!value->IsNumber())
        return napi_invalid_arg;

    result = value->NumberValue();
    return napi_ok;
}

napi_status napi_get_value_int64_(const Local<Value>& value, int64_t& result)
{
    int32_t tmp;
    napi_status status = napi_get_value_int32_(value, tmp);
    result = tmp;
    return status;
}
napi_status napi_get_value_nodestring_(const Local<Value>& str, NodeString& nodechar)
{
    napi_status status = napi_ok;
    do {
        int len = napi_get_value_string_utf8_(str, nullptr, 0);
        if (len == 0) {
            break;
        }
        char *outstr = NodeString::alloc_buf(len + 1);
        if (!outstr) {
            status = napi_generic_failure;
            break;
        }
        len = napi_get_value_string_utf8_(str, outstr, len + 1);

        if (status != napi_ok) {
            break;
        }
        nodechar.setBuf(outstr);
    } while (false);
    return status;
}

Local<Value> napi_create_uint32_(Isolate *isolate, const uint32_t& value)
{
    return v8::Number::New(isolate, value);
}

Local<Value> napi_create_bool_(Isolate *isolate, const bool& value)
{
    return v8::Boolean::New(isolate, value);
}

Local<Value> napi_create_string_(Isolate *isolate, const char* value)
{
    return String::NewFromUtf8(isolate, value ? value : "");
}

Local<Value> napi_create_double_(Isolate *isolate, const double &value)
{
    return v8::Number::New(isolate, value);
}

Local<Value> napi_create_uint64_(Isolate *isolate, const uint64_t& value)
{
    return v8::Number::New(isolate, (double)value);
}

Local<Value> napi_create_int32_(Isolate *isolate, const int32_t& value)
{
    return v8::Int32::New(isolate, value);
}

Local<Value> napi_create_uint16_(Isolate *isolate, const uint16_t& value)
{
    return v8::Uint32::New(isolate, value);
}

static Local<Value> napi_get_object_property_value(Isolate* isolate, const Local<Object>& obj, const std::string& propName)
{
    Local<Name> keyName = String::NewFromUtf8(isolate, propName.c_str(), NewStringType::kInternalized).ToLocalChecked();
    return obj->Get(isolate->GetCurrentContext(), keyName).ToLocalChecked();
}

/**
* get uint32 property from V8 object.
*/
napi_status napi_get_object_property_uint32_(Isolate* isolate, const Local<Object>& obj, const std::string& propName, uint32_t& result)
{
    Local<Value> value = napi_get_object_property_value(isolate, obj, propName);
    return napi_get_value_uint32_(value, result);
}

/**
* get bool property from V8 object.
*/
napi_status napi_get_object_property_bool_(Isolate* isolate, const Local<Object>& obj, const std::string& propName, bool& result)
{
    Local<Value> value = napi_get_object_property_value(isolate, obj, propName);
    return napi_get_value_bool_(value, result);
}

/**
* get int32 property from V8 object.
*/
napi_status napi_get_object_property_int32_(Isolate* isolate, const Local<Object>& obj, const std::string& propName, int32_t& result)
{
    Local<Value> value = napi_get_object_property_value(isolate, obj, propName);
    return napi_get_value_int32_(value, result);
}

/**
* get double property from V8 object.
*/
napi_status napi_get_object_property_double_(Isolate* isolate, const Local<Object>& obj, const std::string& propName, double &result)
{
    Local<Value> value = napi_get_object_property_value(isolate, obj, propName);
    return napi_get_value_double_(value, result);
}

/**
* get int64 property from V8 object.
*/
napi_status napi_get_object_property_int64_(Isolate* isolate, const Local<Object>& obj, const std::string& propName, int64_t& result)
{
    Local<Value> value = napi_get_object_property_value(isolate, obj, propName);
    return napi_get_value_int64_(value, result);
}

/**
* get nodestring property from V8 object.
*/
napi_status napi_get_object_property_nodestring_(Isolate* isolate, const Local<Object>& obj, const std::string& propName, NodeString& nodechar)
{
    Local<Value> value = napi_get_object_property_value(isolate, obj, propName);
    return napi_get_value_nodestring_(value, nodechar);
}

