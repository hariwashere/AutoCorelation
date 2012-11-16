# include "basis.cpp"
# include "basis_parallel.cpp"
        int main()
        {
            //create_image();
            //image = (char*)malloc(sizeof(char)*image_height*image_width);
            //char* result[image_height*image_width];
            meet=(ConsensusGrid*)malloc(sizeof(ConsensusGrid)*image_height*image_width);
            basis = (int*)malloc(sizeof(int)*image_height*image_width);

            read_raw_image("image.raw",image,image_height,image_width);
            //image = {'0','0','1','1','1','1','0','0','1','1','0','1'};
            FILE *fp = fopen("image2.txt","w+");
            for(int i=0; i<image_height; i++){
                for(int j = 0; j<image_width; j++){
                    meet[i*image_width+j]=consensus_parallel(i, j, image,image_height,image_width);
            }
            }

           printf("Calculating list\n");
            calculate_list();

          /*  for(int x=0;x<meet[63].height*meet[63].width;x++)
            {
                fprintf(fp,"%c",meet[63].result[x]);
                //fprintf(fp,"count = %d",meet[0].occurance_count);
            }
                for(int i=0; i<meet[63].occurance_count; i++)
                    fprintf(fp,"List\n%d %d\n",meet[63].occurance[i].i,meet[63].occurance[i].j);
*/
            fclose(fp);
            printf("Calculating basis\n");
            calculate_basis();

        }
