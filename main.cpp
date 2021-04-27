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
    
    const path mypath("/path to downloaded ddsm folder.");
    std::string  mammoCopyPath = "/path to write the converted .dcm file.";
    ddsmImageConversion ddsm_obj(mypath,mammoCopyPath);
    ddsm_obj.parse_file();
    ddsm_obj.ddsmToPng();

    
}
