#include <iostream>
#include<stdio.h>
#include <malloc.h>
using namespace std;
int image_height=64,image_width=64;

static void create_image(){
    FILE *fp = fopen("image.raw","w+");
for(int i=0; i<64; i++){
    for(int j = 0; j<64; j++){
        if(i%2 ==0)
        fprintf(fp,"%d",1);
        else
        fprintf(fp,"%d",0);

    }
    }
    fclose(fp);
}


static void read_raw_image(const char* image_file_path, void* image_buffer, size_t image_width, size_t image_height) {
        const size_t expected_file_size = image_width * image_height; // Grayscale, 16 bits per pixel, LSB

        FILE* image_file = fopen(image_file_path, "r");
        if (image_file != 0) {
                const size_t image_bytes_read = fread(image_buffer, 1, expected_file_size, image_file);
                if (image_bytes_read == expected_file_size) {
                        fclose(image_file);
                } else {
                        fprintf(stderr, "Could only read %u out of %u expected bytes from image %s\n",
                                unsigned(image_bytes_read), unsigned(expected_file_size), image_file_path);
//                        exit(-1);
                }
        } else {
                fprintf(stderr, "Failed to open the input file %s\n", image_file_path);
  //              exit(-1);
        }
}

char* consensus(int i, int j,char* image, int image_height, int image_width)
{
    char* result = (char*)malloc(sizeof(char)*(image_height-i)*(image_width-j));
    char* ptr = result;
    for(int row=i;row<image_height;row++)
    {
        for(int col=j;col<image_width;col++)
        {
            if(image[row*image_width+col] == image[(row-i)*image_width+col-j])
            {
                if(image[row*image_width+col] == '1')
                    *result='1';
                else if(image[row*image_width+col] == '0')
                    *result='0';
            }
                else
                    *result='o';
            result++;
        }
    }


    return ptr;
}
int main()
{
    char *image = (char*)malloc(sizeof(char)*64*64);
    char* result[64*64];
    read_raw_image("image.raw",image,64,64);
    FILE *fp = fopen("image2.raw","w+");
    for(int i=0; i<image_height; i++){
        for(int j = 0; j<image_width; j++){
            result[i*image_width+j]=consensus(i, j, image,image_height,image_width);
    }
    }
    for(int x=0;x<image_height*image_width;x++)
    {
        fprintf(fp,"%c",*result[0]);
        result[0]++;
    }

    fclose(fp);

}
