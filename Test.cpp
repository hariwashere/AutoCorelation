# include "basis.cpp"
#include "print.cpp"
#include "expected_results.cpp"
#include<string.h>
void construct_image()
{
    image[0] = '0';
    image[1] = '0';
    image[2] = '1';
    image[3] = '1';
    image[4] = '1';
    image[5] = '1';
    image[6] = '0';
    image[7] = '0';
    image[8] = '1';
    image[9] = '1';
    image[10] = '0';
    image[11] = '1';
}

void assert_meet()
{
    cout<< "Asserting meet..."<<endl;
    for(int i=0; i< image_height * image_width; i++)
    {
        for(int j = 0; j< strlen(expected_meet[i]); j++)
        {
            if(meet[i].result[j] != expected_meet[i][j])
            {
                cout<<"Error in meet. Expected "<<expected_meet[i][j]<<" at meet "<<i<<" and at position "<<j<<" but got "<<meet[i].result[j];
                exit(-1);
            }
        }
    }
    cout<<"Meet is correct"<<endl;
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
    for(int i=0; i<image_height; i++)
    {
        for(int j = 0; j<image_width; j++)
        {
            meet[i*image_width+j]=consensus(i, j, image,image_height,image_width);
            meet[i*image_width+j].occurance = new tuple[image_height*image_width];
        }
    }
    assert_meet();
    printf("Caclulating list\n");
    calculate_list();
    printf("Calculating basis\n");
    calculate_basis();
    print_basis();
}

