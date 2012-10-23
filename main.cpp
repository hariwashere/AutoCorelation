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

    struct ConsensusGrid {   // Declare PERSON struct type
       char *result;   // Declare member types
       int height;
       int width;
    };

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
                    }
            } else {
                    fprintf(stderr, "Failed to open the input file %s\n", image_file_path);
            }
    }

    ConsensusGrid consensus(int i, int j,char* image, int image_height, int image_width)
    {
        cout<< "I am in here for "<< i << "and"<<j<<endl;
        ConsensusGrid consensus_grid;
        //consensus_grid.result = (char*)malloc(sizeof(char)*(image_height-i)*(image_width-j));
        char *result = (char*)malloc(sizeof(char)*(image_height-i)*(image_width-j));
        char* ptr = result;
     /*   for(int row=i;row<image_height;row++)
        {
            for(int col=j;col<image_width;col++)
            {
                *(consensus_grid.result)= (image[row*image_width+col] == image[(row-i)*image_width+col-j]) ? image[row*image_width+col] : 'o';
                (consensus_grid.result)++;
            }
        }
    */

        int* row_flag=(int*)calloc(sizeof(int),(image_height-i));
        int* col_flag=(int*)calloc(sizeof(int),(image_width-j));
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

                    row_flag[row-i]=1;
                    col_flag[col-j]=1;
                }
                    else
                        *result='o';
                result++;
            }
        }
            int row_start,row_end;
            int col_start,col_end;
        for(row_start=0;row_start<(image_height-i);row_start++)
            {
                    if(row_flag[row_start]==1)
                            break;
            }
        for(row_end=(image_height-i-1);row_end>=0;row_end--)
            {
                    if(row_flag[row_end]==1)
                            break;
            }
        for(col_start=0;col_start<(image_width-j);col_start++)
            {
                    if(col_flag[col_start]==1)
                            break;
            }
        for(col_end=(image_width-j-1);col_end>=0;col_end--)
            {
                    if(col_flag[col_end]==1)
                            break;
    }
    cout << row_start << " " << row_end << " " << col_start << " " << col_end << endl;
    if((row_start > row_end) || (col_start > col_end) ){
        consensus_grid.result = NULL;
        consensus_grid.height = 0;
        consensus_grid.width = 0;
        return consensus_grid;
    }
    //consensus_grid.result = (char*)malloc(sizeof(char)*(row_end-row_start)*(col_end-col_start));
    char *result2 = (char*)malloc(sizeof(char)*(row_end-row_start+1)*(col_end-col_start+1));
    consensus_grid.result = result2;
        for(int row=row_start;row<=row_end;row++)
        {
            for(int col=col_start;col<=col_end;col++)
            {
                *result2 = ptr[row*(image_width-j) + col];
                result2++;
            }
        }
        cout<<"Done with the meet creation for "<< i << " and "<< j<<endl;
        consensus_grid.height = row_end - row_start + 1;
        consensus_grid.width = col_end - col_start + 1;
        free(ptr);
        //free(result);
        free(row_flag);
        free(col_flag);
        /*consensus_grid.result = ptr;
        consensus_grid.height = image_height;
        consensus_grid.width = image_width;*/
        return consensus_grid;
    }
    int main()
    {
        char *image = (char*)malloc(sizeof(char)*image_height*image_width);
        //char* result[image_height*image_width];
        ConsensusGrid meet[image_height*image_width];
        read_raw_image("image.raw",image,64,64);
        FILE *fp = fopen("image2.txt","w+");
        for(int i=0; i<image_height; i++){
            for(int j = 0; j<image_width; j++){
                meet[i*image_width+j]=consensus(i, j, image,image_height,image_width);
                if(i==1)
                 cout<< "the height is"<< meet[i*image_width+j].height<<endl;
        }
        }
        for(int x=0;x<meet[63].height*meet[63].width;x++)
        {
            fprintf(fp,"%c",meet[63].result[x]);
        }

        fclose(fp);
    }
