 #include <iostream>
        #include <stdio.h>
        #include <malloc.h>

        using namespace std;
        int image_height=64,image_width=64;
        char* image;//[] ={'0','0','1','1','1','1','0','0','1','1','0','1'};

        int *basis;
        int basis_count = 0;

        static void create_image(){
            FILE *fp = fopen("image.raw","w+");
        for(int i=0; i<image_height; i++){
            for(int j = 0; j<image_width; j++){
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
