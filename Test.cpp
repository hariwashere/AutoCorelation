# include "basis.cpp"

    void construct_image(){
        image[0] = '0';
        image[0] = '0';
        image[0] = '1';
        image[0] = '1';
        image[0] = '1';
        image[0] = '1';
        image[0] = '0';
        image[0] = '0';
        image[0] = '1';
        image[0] = '1';
        image[0] = '0';
        image[0] = '1';
    }

        int main()
        {
            image_height=4;
            image_width=3;
            image = (char*)malloc(sizeof(char)*image_height*image_width);
            construct_image();

            meet=(ConsensusGrid*)malloc(sizeof(ConsensusGrid)*image_height*image_width);
            basis = (int*)malloc(sizeof(int)*image_height*image_width);

            FILE *fp = fopen("image2.txt","w+");
            for(int i=0; i<image_height; i++){
                for(int j = 0; j<image_width; j++){
                    meet[i*image_width+j]=consensus(i, j, image,image_height,image_width);
                    meet[i*image_width+j].occurance = new tuple[image_height*image_width];
                }
            }

            cout<< "Getting all the meets";
            for(int i=0; i< 12; i++){
                cout<<" For meet "<<i<<endl;
                for(int j=0; j< sizeof(meet[i].result); j++){
                    cout<< meet[i].result[j]<< ", ";
                }
                cout<<endl;

            }

           printf("Caclulating list\n");
            calculate_list();
            printf("Calculating basis\n");
            calculate_basis();

            cout<<"The basis has"<< endl;
            for(int i=0; i< image_height; i++){
                for(int j=0; j< image_width; j++){
                   // cout<< meet[i*image_width + j].occurance[0].i;
                    //cout<< "and the j is"<< meet[i*image_width + j].occurance[0].j<<endl;
                }
            }
        }

