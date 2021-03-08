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
    // Resize the cat image (750 * 1000) to 600 * 650
    ppm_image fatcat = cat.resize(600, 650);
    fatcat.save("../results/fatcat.ppm");

    // Flip the Iowa firework image
    ppm_image flipfire = fire.flip_horizontal();
    flipfire.save("../results/flipfire.ppm");

    // Extract the Shanghai metro icon from the shanghai image
    ppm_image metro = shanghai.subimage(210, 110, 120, 120);
    metro.save("../results/metro.ppm");

    // Gamma correct the haverford evening image with gamma = 0.6
    ppm_image ghceve = hceve.gammaCorrect(0.6);
    ghceve.save("../results/gamma-hceve.ppm");
    
    // Return the grayscaled image of haverford spring
    ppm_image grayhcspring = hcspring.grayscale();
    grayhcspring.save("../results/gray-hcspring.ppm");

    // Return the alpha blended image of Haverford evening scene with Iowa fireworks
    ppm_image hcfirework = ghceve.alpha_blend(fire, 0.2);
    hcfirework.save("../results/hcfirework.ppm");

    // Combine the Iowa fireworks and the disney scene with lightest
    ppm_image lightfirework = disney.lightest(fire);
    lightfirework.save("../results/lightfirework.ppm");

    // Combine the Iowa fireworks and the Haverford evening scene with darkest
    ppm_image darkfirework = disney.darkest(fire);
    darkfirework.save("../results/darkfirework.ppm");

    // Return a robot with swirl colors
    ppm_image swirlrobot = robot.swirlcolor();
    swirlrobot.save("../results/swirlrobot.ppm");

    // Return a robot with inverted colors and alpha = 1
    ppm_image invertdraw = robot.invert(1);
    invertdraw.save("../results/invertdraw.ppm");

    // Detect the edges of shanghai scene with sobel kernel (threshold = 120, reverse = false)
    ppm_image shsobel = shanghai.sobel(120, false);
    shsobel.save("../results/shsobel.ppm");

    // Blur hc spring image with gaussian blur kernel
    ppm_image blurhcspring = hcspring.gaussianblur();
    blurhcspring.save("../results/blurhcspring.ppm");

    // Sharpen drawing image with sharpen kernel
    ppm_image sharpenfire = draw.sharpen();
    sharpenfire.save("../results/sharpenfire.ppm");
    
    // Replace a fraction of sky in the shanghai image with fireworks (after resizing and alpha blended)
    ppm_image shnight = shanghai.subimage(0, 0, 280, 210);
    ppm_image smallfirework = firework.resize(280, 215);
    ppm_image shfirework = shnight.alpha_blend(smallfirework, 0.25);
    shanghai.replace(shfirework, 0, 0);
    shanghai.save("../results/shfirework.ppm");

    // Restore shanghai image
    shanghai.load("../images/shanghai.ppm");

    // Artworks!
    // disney sobel
    ppm_image gdisney = disney.gammaCorrect(2.0);
    ppm_image blurdisney = gdisney.gaussianblur();
    ppm_image disneysobel = blurdisney.sobel(80, false);
    disneysobel.save("../results/disneysobel.ppm");

    // drawing on blackboard
    ppm_image gdraw = draw.gammaCorrect(0.6);
    ppm_image boarddraw = gdraw.invert(1);
    boarddraw.save("../results/boarddraw.ppm");

    // robot sobel
    ppm_image grobot = robot.gammaCorrect(2.0);
    ppm_image grayrobot = grobot.grayscale();
    ppm_image blurrobot = grayrobot.gaussianblur();
    ppm_image robotsobel = blurrobot.sobel(23, true);
    robotsobel.save("../results/robotsobel.ppm");
}