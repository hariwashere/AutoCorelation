# include "basis.cpp"
        int main()
        {
            meet=(ConsensusGrid*)malloc(sizeof(ConsensusGrid)*image_height*image_width);
            basis = (int*)malloc(sizeof(int)*image_height*image_width);

            FILE *fp = fopen("image2.txt","w+");
            for(int i=0; i<image_height; i++){
                for(int j = 0; j<image_width; j++){
                    meet[i*image_width+j]=consensus(i, j, image,image_height,image_width);
                    meet[i*image_width+j].occurance = new tuple[image_height*image_width];
            }
            }

           printf("Caclulating list\n");
            calculate_list();
            printf("Calculating basis\n");
            calculate_basis();

        }

