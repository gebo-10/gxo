#ifndef FBX_MODEL_H
#define FBX_MODEL_H
#include "model.h"
#include <fbxsdk.h>
class FbxModel :public Model
{
public:
	FbxManager* lSdkManager;
	FbxScene* lScene;
	FbxModel(string_view file):Model(nullptr,nullptr)
	{
		lSdkManager = FbxManager::Create();
		FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
		lSdkManager->SetIOSettings(ios);
		FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

		if (!lImporter->Initialize(file.data(), -1, lSdkManager->GetIOSettings())) {
			printf("Call to FbxImporter::Initialize() failed.\n");
			printf("Error returned: %s\n\n", lImporter->GetStatus().GetErrorString());
			exit(-1);
		}
		lScene = FbxScene::Create(lSdkManager, "myScene");
		lImporter->Import(lScene);


		lImporter->Destroy();

	}

	~FbxModel()
	{
		lSdkManager->Destroy();
	}


};


#endif