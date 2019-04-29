#pragma once
#include <fbxsdk.h>
struct fbx_parse_context
{
      private:
        fbx_parse_context(){};
        static fbx_parse_context *singleton;

      public:
        static fbx_parse_context *get() { return singleton; }
};
fbx_parse_context *fbx_parse_context::singleton = new fbx_parse_context();
