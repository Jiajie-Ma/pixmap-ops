#include "ppm_image.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace agl;
using namespace std;

int int_min(int a, int b){
   if (a <= b){
      return a;
   }
   else{
      return b;
   }
}

ppm_image::ppm_image() 
{
   // default constructor
   format = "P3";
   w = 1;
   h = 1;
   m = 255;
   p = new int** [h];
   for (int i = 0; i < h; i++)
   {
      p[i] = new int* [w];
      for (int j = 0; j < w; j++)
      {
         p[i][j] = new int [3];
         for (int k = 0; k < 3; k++)
         {
            p[i][j][k] = 0;
         }
      }
   }
}

ppm_image::ppm_image(int width, int height) 
{
   try{
      if (width <= 0 || height <= 0){
          throw "WARNING: width and height a image is supposed to be positive!";
      }
   } catch (const char* msg) {
      std::cout << msg << std::endl;
      std::cout << width << ", " << height << "are given to initialize a ppm image." << std::endl;
   }
   // set all member variables except w and h by default
   format = "P3";
   w = width;
   h = height;
   m = 255;
   p = new int** [h];
   for (int i = 0; i < h; i++)
   {
      p[i] = new int* [w];
      for (int j = 0; j < w; j++)
      {
         p[i][j] = new int [3];
         for (int k = 0; k < 3; k++)
         {
            p[i][j][k] = 0;
         }
      }
   }
}

ppm_image::ppm_image(const ppm_image& orig)
{
   format = orig.format;
   w = orig.w;
   h = orig.h;
   m = orig.m;
   p = new int** [h];
   for (int i = 0; i < h; i++)
   {
      p[i] = new int* [w];
      for (int j = 0; j < w; j++)
      {
         p[i][j] = new int [3];
         for (int k = 0; k < 3; k++)
         {
            p[i][j][k] = orig.p[i][j][k];
         }
      }
   }
}

ppm_image& ppm_image::operator=(const ppm_image& orig)
{
   if (&orig == this) // protect against self-assignment
   {
      return *this;
   }

   cleanup();
   format = orig.format;
   w = orig.w;
   h = orig.h;
   m = orig.m;
   p = new int** [h];
   for (int i = 0; i < h; i++)
   {
      p[i] = new int* [w];
      for (int j = 0; j < w; j++)
      {
         p[i][j] = new int [3];
         for (int k = 0; k < 3; k++)
         {
            p[i][j][k] = orig.p[i][j][k];
         }
      }
   }

   return *this;   
}

ppm_image::~ppm_image()
{
   // clean up the memory
   cleanup();
}

bool ppm_image::load(const std::string& filename)
{
   ifstream file(filename);
   if (!file)
   {
      cout << "Cannot load file: " << filename << endl;
      return false;
   }
   
   cleanup();
   // read the format, width, height, and maximum color value of the image
   file >> format;
   file >> w;
   file >> h;
   file >> m;
   
   p = new int** [h];
   // read the pixels of the image
   for (int i = 0; i < h; i++)
   {
      p[i] = new int* [w];
      for (int j = 0; j < w; j++)
      {
         p[i][j] = new int [3];
         for (int k = 0; k < 3; k++)
         {
            file >> p[i][j][k];
         }
      }
   }
   file.close();

   return true;
}

bool ppm_image::save(const std::string& filename) const
{
   ofstream file(filename);

   // write the format, width, height, and maximum color value of the image
   file << format << std::endl;;
   file << w << " ";
   file << h << std::endl;
   file << m << std::endl;
   
   // write the pixels of the image
   for (int i = 0; i < h; i++)
   {
      for (int j = 0; j < w; j++)
      {
         for (int k = 0; k < 3; k++)
         {
            file << p[i][j][k];
            // format the file for human understanding
            if (k == 2 && j == w - 1)
            {
               file << std::endl;
            }
            else{
               file << " ";
            }
         }
      }
   }
   file.close();

   return true;
}

 ppm_image ppm_image::resize(int width, int height) const
{
   // Return the original image if the inputs are not legal
   try{
      if (width <= 0 || height <= 0){
          throw "WARNING: width and height a image is supposed to be positive!";
      }
   } catch (const char* msg) {
      std::cout << msg << std::endl;
      std::cout << width << ", " << height << " are given to resize a image." << std::endl;
      return *this;
   }

    ppm_image result(width, height);

    // for each pixel in the new image, find its corresponding pixel in the original image
    int u, v;
    for (int i = 0; i < height; i++)
    {
       if (height == 1)
       {
          u = 0;
       }
       else{
          u = floor((static_cast<double>(i)/static_cast<double>(height - 1)) * static_cast<double>(h - 1));
       }

       for (int j = 0; j < width; j++)
       {
          if (width == 1)
          {
             v = 0;
          }
          else{
             v = floor((static_cast<double>(j)/static_cast<double>(width - 1)) * static_cast<double>(w - 1));
          }

          for (int k = 0; k < 3; k++)
          {
             result.p[i][j][k] = this->p[u][v][k];
          }
       }
    }

    return result;
}

ppm_image ppm_image::flip_horizontal() const
{
   ppm_image result(w, h);

   // set the RGB value of pixel (i, j) to that of (h - i - 1, j)
   for (int i = 0; i < h; i++)
   {
      for (int j = 0; j < w; j++)
      {
         for (int k = 0; k < 3; k++)
         {
            result.p[i][j][k] = this->p[h-i-1][j][k];
         }
      }
   }

    return result;
}

ppm_image ppm_image::subimage(int startx, int starty, int width, int height) const
{
   // Return the original image if the inputs are not legal
   try{
      if (startx < 0 || starty < 0 || startx > h-1 || starty > w-1){
          throw "WARNING: the top left corner of the specified subimage is out of range!";
      }
   } catch (const char* msg) {
      std::cout << msg << std::endl;
      std::cout << startx << ", " << starty << " are given as the top left corner for a subimage." << std::endl;
      return *this;
   }

   // take the whole image to the right of startx if width is out of range
   if (width < 0 || width > w - startx){
      width = w - starty;
   }
   // take the whole image below starty if height is out of range
   if (height < 0 || height > h - starty){
      height = h - startx;
   }
   
   ppm_image result(width, height);

   for (int i = 0; i < height; i++)
   {
      for (int j = 0; j < width; j++)
      {
         for (int k = 0; k < 3; k++)
         {
            result.p[i][j][k] = this->p[startx + i][starty + j][k];
         }
      }
   }

    return result;
}

void ppm_image::replace(const ppm_image& image, int startx, int starty)
{
   // Return the original image if the inputs are not legal
   try{
      if (startx < 0 || starty < 0 || startx > h-1 || starty > w-1){
          throw "WARNING: the specified coordinate of the image is out of range!";
      }
   } catch (const char* msg) {
      std::cout << msg << std::endl;
      std::cout << startx << ", " << starty << " are given as coordinate for an image with (width, height) = " << w << ", " << h << "." << std::endl;
      return ;
   }

   // determine the fraction of the image that gets replaced. If the given @image does not fit on @this, it replaces as much fraction of @this as possible
   int width, height;
   if (image.w > this->w - starty){
      width = this->w - starty;
   }
   else{
      width = image.w;
   }

   if (image.h > this->h - startx){
      height = this->h - startx;
   }
   else{
      height = image.h;
   }

   // If the given @image does not fit on @this, then only a fraction of @image replaces @this
   for (int i = 0; i < height; i++)
   {
      for (int j = 0; j < width; j++)
      {
         for (int k = 0; k < 3; k++)
         {
            p[startx + i][starty + j][k] = image.p[i][j][k];
         }
      }
   }
}

ppm_image ppm_image::alpha_blend(const ppm_image& other, float alpha) const
{
   // assume that the given image @other have the same dimension as @this
   // Return the original image if the inputs are not legal
   try{
      if (alpha < 0 || alpha > 1){
          throw "WARNING: the given alpha for blending is out of range!";
      }
   } catch (const char* msg) {
      std::cout << msg << std::endl;
      std::cout << alpha << " is given as for blend." << std::endl;
      return *this;
   }

   ppm_image result(w,h);

   for (int i = 0; i < h; i++)
   {
      for (int j = 0; j < w; j++)
      {
         for (int k = 0; k < 3; k++)
         {
            result.p[i][j][k] = int_min(m, floor(static_cast<double>(this->p[i][j][k]) * static_cast<double>(1-alpha) + static_cast<double>(other.p[i][j][k])*static_cast<double>(alpha)));
         }
      }
   }

   return result;
}

ppm_image ppm_image::gammaCorrect(float gamma) const
{
   ppm_image result(w, h);

   // Return a image of maximum color if gamma is 0
   if (gamma == 0){
      for (int i = 0; i < h; i++)
      {
         for (int j = 0; j < w; j++)
         {
            for (int k = 0; k < 3; k++)
            {
               result.p[i][j][k] = m;
            }
         }
      }
   }
   else{
      // otherwise, for each pixel, raise its RGB value to the power of 1/gamma (with a cap of m)
      for (int i = 0; i < h; i++)
      {
         for (int j = 0; j < w; j++)
         {
            for (int k = 0; k < 3; k++)
            {
               result.p[i][j][k] = int_min(m, floor(static_cast<double>(m) * pow(static_cast<double>(this->p[i][j][k])/static_cast<double>(m), static_cast<double>(1)/static_cast<double>(gamma))));
            }
         }
      }
   }
   
   return result;
}

ppm_image ppm_image::grayscale() const
{
   ppm_image result(w, h);

   // set each pixel to the average (R+G+B)/3
   int average;
   for (int i = 0; i < h; i++)
   {
      for (int j = 0; j < w; j++)
      {
         average = floor(static_cast<double>(this->p[i][j][0] + this->p[i][j][1] + this->p[i][j][2])/static_cast<double>(3));
         for (int k = 0; k < 3; k++)
         {
            result.p[i][j][k] = average;
         }
      }
   }

   return result;
}

ppm_pixel ppm_image::get(int row, int col) const
{
   // create and fill in the contents of a pixel from p
   ppm_pixel pixel;
   pixel.r = p[row][col][0];
   pixel.g = p[row][col][1];
   pixel.b = p[row][col][2];
   return pixel;
}

void ppm_image::set(int row, int col, const ppm_pixel& c)
{
   // test the legality of the inputs
   try{
      if (c.r < 0 || c.g < 0 || c.b < 0){
          throw "WARNING: an RGB value is supposed to be positive!";
      }
   } catch (const char* msg) {
      std::cout << msg << std::endl;
      std::cout << c.r << ", " << c.g << ", " << c.b << " is given to set a pixel." << std::endl;
   }

   // cap the RGB value with the maximum color value
   p[row][col][0] = int_min(m, c.r);
   p[row][col][1] = int_min(m, c.g);
   p[row][col][2] = int_min(m, c.b);
}

int ppm_image::height() const
{
   return h;
}

int ppm_image::width() const
{
   return w;
}

void ppm_image::cleanup()
{
   // clean up the memory
   for (int i = 0; i < h; i++)
   {
      for (int j = 0; j < w; j++)
      {
         delete[] p[i][j];
      }
      delete[] p[i];
   }
   delete[] p;
}
