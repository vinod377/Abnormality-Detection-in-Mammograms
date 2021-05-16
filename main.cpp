/*The code converts .dcm images of DDSM to png format, so that it can be used with
image processing and Ml algorithms,The main function take two file path
mypath:downloaded DDSM root folder
mammoCopyPath:folder path to write the converted images.
The converted images are named following the same rules as in original data.
 {mass/calc}_{train/tets}_{full/roi}_{patient_id}_{1/2}
*/


#include <iostream>
#include "analysing_ddsm_file.h"

int main(int argc, const char * argv[]) {
    
    const path mypath("/Users/tangerine/PycharmProjects/dataset/ddsm/");
    std::string  mammoCopyPath = "/Users/tangerine/PycharmProjects/dataset/ddsm_images_only/";
    ddsmImageConversion ddsm_obj(mypath,mammoCopyPath);
    ddsm_obj.parse_file();
    ddsm_obj.ddsmToPng();
    
}
