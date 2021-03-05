#include <iostream>
#include "ppm_image.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
    ppm_image image;
    image.load("../images/draw.ppm");
    
    ppm_image gamma = image.gammaCorrect(0.4);
    ppm_image gray = gamma.grayscale();
    ppm_image sobel = gray.sobel(30, true); 
    ppm_image blur = sobel;
    blur.save("draw_result.ppm"); 
}