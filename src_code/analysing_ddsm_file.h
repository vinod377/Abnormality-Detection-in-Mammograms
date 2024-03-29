/*
 code to read directory containing .dcm file and convert to .png
 */


#ifndef analysing_ddsm_file_h
#define analysing_ddsm_file_h

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "boost/filesystem.hpp"
#include "boost/algorithm/string.hpp"
#include "opencv2/imgcodecs.hpp"

#include <iostream>

using namespace boost::filesystem;
using namespace std;
using namespace cv;

class ddsmImageConversion{
    path mammoSourcePath;
    string mammoCopyPath;
    
public:
    vector<path> path_list;
    vector<std::string> dcmImageName;
    void parse_file();
    void ddsmToPng();
    
    ddsmImageConversion(const path &dir_path,std::string &CopyPath){
        mammoSourcePath=dir_path;
        mammoCopyPath=CopyPath;
    }
};

void ddsmImageConversion::parse_file()
{
    /* function for parsing the directory and getting the
    .dcm file path and creating new image name for converted image*/
    recursive_directory_iterator end_itr;
    for(recursive_directory_iterator itr(mammoSourcePath);itr!=end_itr;++itr)
    {
        if(itr->path().extension()==".dcm")
        {
            int cnt = 0;
            std::vector<std::string> splited_full_roi;
            std::vector<std::string> splited_Calc_Mass;
            std::vector<std::string> end_name;
            for(auto &i:itr->path())
            {
                ++cnt;
                if (cnt==11)
                    boost::split(splited_full_roi,i.c_str(),boost::is_any_of("-, "));
                else if(cnt == 9)
                    boost::split(splited_Calc_Mass,i.c_str(),boost::is_any_of("_,-"));
                else if(cnt == 12)
                    boost::split(end_name,i.c_str(),boost::is_any_of("."));
            }
            std::string imageName = splited_Calc_Mass[0]+"_"+splited_Calc_Mass[1]+"_"
                                        +splited_full_roi[1]+"_"+splited_full_roi[4]+"_"+end_name[0];
            
            path_list.push_back(itr->path().string());
            dcmImageName.push_back(imageName);
        }
    }
}

void ddsmImageConversion::ddsmToPng(){
    /* Code to convert dcm file to .png file.
     the .dcm file have 16 depth.Dcmtll lib is used for conversion*/

    for(int i = 0;i<path_list.size();i++)
    {
        const char * mammoImagePath = path_list[i].c_str();
        DicomImage *image = new DicomImage(mammoImagePath);
        if (image == NULL)
        {
            std::cout<<"image is not nUll"<<std::endl;
        
        }
        //get the information .dcm image file
        unsigned long nRows = image->getHeight();
        unsigned int nCols = image->getWidth();
        unsigned int nImgs = image->getFrameCount();
        unsigned int depth = image->getDepth();
        std::cout<<"Rows number: "<<nRows<<" cols number "<<nCols<<" depth "<<depth<<std::endl;
        Mat mono = Mat(int(image->getHeight()), int(image->getWidth()), CV_16UC1, (Uint16*)(image->getOutputData(16/*bits per sample */)));
        std::string mammo_name = mammoCopyPath+dcmImageName[i]+".png";
        std::cout<<"wrote image"<<'\t'<<mammo_name<<std::endl;
        try{
            imwrite(mammo_name,mono);
        }
        catch(...) {};

    }
}
#endif /* analysing_ddsm_file_h */
