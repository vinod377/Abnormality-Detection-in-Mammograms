//
//  main.cpp
//  Breast_cancer_det
//
//  Created by Tangerine on 15/04/21.
//  Copyright © 2021 vinod. All rights reserved.
//

#include <iostream>
#include "analysing_ddsm_file.h"

int main(int argc, const char * argv[]) {
    
    const path mypath("/Users/tangerine/PycharmProjects/dataset/ddsm/");
    std::string  mammoCopyPath = "/Users/tangerine/PycharmProjects/dataset/ddsm_images_only/";
    ddsmImageConversion ddsm_obj(mypath,mammoCopyPath);
    ddsm_obj.parse_file();
    ddsm_obj.ddsmToPng();

    
}
