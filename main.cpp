# include "basis.cpp"
#include "print.cpp"
//# include "basis_parallel.cpp"
        int main()
        {
            image_height=16;
            image_width=16;
            //create_image();
            image = (char*)malloc(sizeof(char)*image_height*image_width);
            meet=(ConsensusGrid*)malloc(sizeof(ConsensusGrid)*image_height*image_width);
            basis = (int*)malloc(sizeof(int)*image_height*image_width);

            read_raw_image("image.raw",image,image_height,image_width);
            for(int i=0; i<image_height; i++){
                for(int j = 0; j<image_width; j++){
                    meet[i*image_width+j]=consensus(i, j, image,image_height,image_width);
            }
            }

           printf("Calculating list\n");
            calculate_list();

            printf("Calculating basis\n");
            calculate_basis();
            print_basis();
            print_occurances();
        }
