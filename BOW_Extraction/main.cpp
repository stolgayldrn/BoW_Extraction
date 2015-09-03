//////////////////////////////////////////////////////////////////////////
/// This code creates features from frames		
//////////////////////////////////////////////////////////////////////////
#include "TVoctreeVLFeat.h"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc.hpp"
//#include "helpers.h"
#include <string>
#include "helpers2.h"
#include "TFeatureExtractor.h"



using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	vector<string> fileList;
	get_directory_images(argv[1],fileList);//@param argv[1] is directory of frames' folder
	
	int BoW_Hist_prev[1000000] = {};
	
	for(int i = 0; i < fileList.size(); i++)
	{

		
		t_feat_init();// initialization of TFeatureExtractor
		TSignature mySig;
		t_feat_init_sig(mySig);
		unsigned char * MySiftu;

		string fileName = argv[1];
		fileName = fileName + "\\" + fileList[i];
		string writeName = fileName + ".sig";
		Mat im = imread(fileName,IMREAD_GRAYSCALE);
		TByte * IM = im.data;
		//t_feat_extract_buffer(TByte* imageData, TUInt dataSize, TUInt maxFeaturesPerImage, TFeatureMode featMode = T_FEAT_CV_SIFT, TFeatDistMode distMode = T_FEAT_DIST_EUC, TFeatCompressMode compressMode = T_FEAT_CMPRS_NONE);
		mySig = t_feat_extract(IM, 640, 640,640,1, 2000,T_FEAT_EZ_SIFT,T_FEAT_DIST_HELL,T_FEAT_CMPRS_NONE);
		MySiftu = new unsigned char[mySig.numKeypts*128];
		memcpy(MySiftu, mySig.keyPoints,(mySig.numKeypts)*128*sizeof(unsigned char));

		TVoctreeVLFeat VT;
		unsigned int *vwi = new unsigned int[mySig.numKeypts]();		
		VT.init_read("D:/Data/VT_Middle_Tree_100MSig2s_SIFT_HELL_ZSTD_SIFT.dat");
		VT.quantize_multi(vwi,MySiftu,mySig.numKeypts);
		
		t_feat_release_signature(&mySig);

		//////////////////////////////////////////////////////////////////////////
		// WRITE AND READ // TEST //
		//////////////////////////////////////////////////////////////////////////

		//TInt wr = t_feat_write_sig_v2(mySig, writeName.c_str());
		//
		//TSignature mySigRead;
		//t_feat_init_sig(mySigRead);
		////string tempRead = "D:\\ImageSearchEngine\\Dumps\\Temporary_100MSig2s_SIFT_HELL_ZSTD\\00000F94-A0DD-44ED-A15B-89AB227E53DA.sig";
		//if(file_exist(writeName.c_str()))
		//{
		//	if(is_sig_file(writeName.c_str()))
		//	{
		//		
		//		TSignature mySigRead = t_feat_read_sig_v2(writeName.c_str());				
		//		t_feat_decompress(mySigRead);
		//	}
		//}

		//////////////////////////////////////////////////////////////////////////
	}
	

	//{
	//	//
	//	string fn = fileList[i].substr(0,fileList[i].length()-4);
	//	//TChar *FileName = (TChar)fn.c_str();
	//	TSignature signature;
	//	t_feat_init_sig(signature);
	//	//t_feat_extract(image, 480, 360, 20, 3, 200);
	//	//t_feat_write_sig_v2(signature,FileName);

	//}
	

	return 0;
}