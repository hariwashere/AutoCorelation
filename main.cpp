        #include <iostream>
        #include <stdio.h>
        #include <malloc.h>

        using namespace std;
        int image_height=4,image_width=3;
        char image[] ={'0','0','1','1','1','1','0','0','1','1','0','1'};

        int *basis;
        int basis_count = 0;

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

        struct tuple
        {
            int i,j;
        };

        struct ConsensusGrid {   // Declare PERSON struct type
           char *result;   // Declare member types
           int height;
           int width;
           tuple *occurance;
           int occurance_count;
        };

        ConsensusGrid *meet;

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
        //    cout<< "I am in here for "<< i << "and"<<j<<endl;
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
        //cout << row_start << " " << row_end << " " << col_start << " " << col_end << endl;
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

            //cout<<"Done with the meet creation for "<< i << " and "<< j<<endl;
            consensus_grid.height = row_end - row_start + 1;
            consensus_grid.width = col_end - col_start + 1;
            consensus_grid.occurance = NULL;
            consensus_grid.occurance_count = 0;

            free(ptr);
            //free(result);
            free(row_flag);
            free(col_flag);
            /*consensus_grid.result = ptr;
            consensus_grid.height = image_height;
            consensus_grid.width = image_width;*/
            return consensus_grid;
        }

        void calculate_list()
        {
            for(int i=0; i<image_height*image_width; i++)
            {
                if((meet[i].height != 0) && (meet[i].width != 0))
                {

                for(int row_offset=0; row_offset<=image_height - meet[i].height; row_offset++)
                {
                    for(int col_offset=0; col_offset<=image_width - meet[i].width; col_offset++)
                    {

                        int count = 0;
                        for(int row = 0; row<meet[i].height; row++)
                        {
                            for(int col = 0; col<meet[i].width; col++)
                            {
                                if(meet[i].result[row*meet[i].width + col] == 'o' )
                                    count++;
                                else
                                {
                                    if(meet[i].result[row*meet[i].width + col] == image[(row+row_offset)*image_width + (col+col_offset)])
                                        count++;
                                    else
                                        break;
                                }
                            }
                        }
                        //if(i == 64)
                        //printf("count = %d",count);
                        if(count == meet[i].width*meet[i].height)
                        {
                                //if(i == 64)
                                  //  printf("entered");
                                tuple t;
                                t.i = row_offset;
                                t.j = col_offset;
                               meet[i].occurance[meet[i].occurance_count++] = t;
                        }
                    }
                }
                }
                cout << "For meet " << i << endl;
                for(int g=0;g<meet[i].occurance_count; g++)
                    cout << meet[i].occurance[g].i << " " << meet[i].occurance[g].j << endl;
            }

        }

        void calculate_basis()
        {
                for(int i=0; i<image_height*image_width;i++)
                {
                    int max = -1;
                    int index = i;
                    for(int j=i;j<image_height*image_width;j++)
                    {
                        if(max < meet[j].occurance_count)
                        {
                             max = meet[j].occurance_count;
                             index = j;
                        }
                    }

                    ConsensusGrid temp = meet[i];
                    meet[i] = meet[index];
                    meet[index] = temp;
                }

                for(int n = 0;n<image_height*image_width;n++)
                {
                    cout << "for " << n << endl;
                    for(int m =0;m<meet[n].occurance_count;m++)
                            cout << meet[n].occurance[m].i << " " << meet[n].occurance[m].j << endl;
                        cout << endl;
                }

                for(int i=0; i<image_height*image_width; i++)
                {
                    /// For every meet make count = 0
                    int count = 0;

                    /// Loop over every element in occurance list
                    for(int j = 0; j<meet[i].occurance_count; j++)
                    {
                        int flag = 0;

                        /// Compare the occurance list of every meet with current meet
                        for(int k=0; k<image_height*image_width; k++)
                        {
                            if( (k!=i) && (meet[k].occurance != NULL))
                               {
                                   /// Loop through all occurances
                                   for(int l=0; l<meet[k].occurance_count; l++)
                                   {
                                       if((meet[k].occurance[l].i == meet[i].occurance[j].i) && (meet[k].occurance[l].j == meet[i].occurance[j].j))
                                        {
                                                printf("found! i = %d  j = %d %d\n",i,meet[i].occurance[j].i, meet[i].occurance[j].j);
                                                flag = 1;
                                        }
                                   }
                                   if(flag == 1)
                                    break;
                               }
                               if(flag == 1)
                                break;
                        }
                        if(flag != 1)
                            break;
                        else
                            count++;


                    }
                    if(count != meet[i].occurance_count)
                    {
                        basis[basis_count++] = i;
                        cout << i << endl;
                        for(int m =0;m<meet[i].occurance_count;m++)
                            cout << meet[i].occurance[m].i << " " << meet[i].occurance[m].j << endl;

                        cout << endl;
                    }

                    else
                        meet[i].occurance_count = 0;
                }
        }

        int main()
        {
            //image = (char*)malloc(sizeof(char)*image_height*image_width);
            //char* result[image_height*image_width];
            meet=(ConsensusGrid*)malloc(sizeof(ConsensusGrid)*image_height*image_width);
            basis = (int*)malloc(sizeof(int)*image_height*image_width);

            //read_raw_image("image.raw",image,image_height,image_width);
            //image = {'0','0','1','1','1','1','0','0','1','1','0','1'};
            FILE *fp = fopen("image2.txt","w+");
            for(int i=0; i<image_height; i++){
                for(int j = 0; j<image_width; j++){
                    meet[i*image_width+j]=consensus(i, j, image,image_height,image_width);
                    meet[i*image_width+j].occurance = new tuple[image_height*image_width];
            //        if(i==1)
          //           cout<< "the height is"<< meet[i*image_width+j].height<<endl;
            }
            }

           printf("Caclulating list\n");
            calculate_list();

          /*  for(int x=0;x<meet[63].height*meet[63].width;x++)
            {
                fprintf(fp,"%c",meet[63].result[x]);
                //fprintf(fp,"count = %d",meet[0].occurance_count);
            }
                for(int i=0; i<meet[63].occurance_count; i++)
                    fprintf(fp,"List\n%d %d\n",meet[63].occurance[i].i,meet[63].occurance[i].j);

            fclose(fp);*/
            printf("Calculating basis\n");
            calculate_basis();

        }
