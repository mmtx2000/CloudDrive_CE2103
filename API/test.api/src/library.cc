#include <node.h>
#include <iostream>

void prapra(const v8::FunctionCallBackInfo<v8::Value>& args){
    v8::Isolate*isolate = args.GetIsolate();

    //std::cout<<"prapra"<<std::endln;
    args.GetReturnValue().Set("prapra");
}

void Initialize(v8::Local<v8::Object> exports){
    NODE_SET_METHOD(exports,"prapra",prapra);

}
NODE_MODULUE(library, Initialize)