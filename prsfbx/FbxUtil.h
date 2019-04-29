#pragma once
#include "Common/Common.h"
#include <fbxsdk.h>
#include <string>
struct fbx_parse_context
{
      private:
        fbx_parse_context(){};
        static fbx_parse_context* singleton;

      public:
        FbxManager*               lSdkManager = NULL;
        FbxScene*                 lScene      = NULL;
        static fbx_parse_context* get()
        {
                return singleton;
        }
        void compile_animation(std::string filepath)
        {
                InitializeSdkObjects(lSdkManager, lScene);
                FbxString lFilePath(filepath.c_str());
                if (lFilePath.IsEmpty())
                        return;

                FBXSDK_printf("\n\nFile: %s\n\n", lFilePath.Buffer());
                bool lResult = LoadAnimationStacks(lSdkManager, lScene, lFilePath.Buffer());

                if (lResult == false)
                {
                        FBXSDK_printf("\n\nAn error occurred while loading the scene...");
                }
                else
                {
                        if (!lScene)
                        {
                                FBX_ASSERT_NOW("null scene");
                        }

                        // get root node of the fbx scene
                        FbxNode* lRootNode = lScene->GetRootNode();
                }
        }
};
fbx_parse_context* fbx_parse_context::singleton = new fbx_parse_context();
