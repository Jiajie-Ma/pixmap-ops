#include <iostream>
#include "ppm_image.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
    // Load a collection of original images
    ppm_image cat;
    ppm_image disney;
    ppm_image draw;
    ppm_image fire;
    ppm_image firework;
    ppm_image hcspring;
    ppm_image shanghai;
    ppm_image robot;
    ppm_image hceve;
    cat.load("../images/cat.ppm");
    disney.load("../images/disney.ppm");
    draw.load("../images/draw.ppm");
    fire.load("../images/fire.ppm");
    firework.load("../images/firework.ppm");
    hcspring.load("../images/hcspring.ppm");
    shanghai.load("../images/shanghai.ppm");
    robot.load("../images/robot.ppm");
    hceve.load("../images/hceve.ppm");


    // Provide examples for each image operator in ppm_image class
    // Resize a cat image (750 * 1000) to 1000 * 750
    ppm_image fatcat = cat.resize(550, 610);
    fatcat.save("../results/fatcat.ppm");
    
}