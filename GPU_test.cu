__global__ void compute_Dontcares(char* image,int* row_flag,int* col_flag,char* result, int i, int j, int image_width)
{
	int row = (blockIdx.x + i);
	int col = threadIdx.x + j;
	if(image[row*image_width+col] == image[(row-i)*image_width+col-j])
	{
		if(image[row*image_width+col] == '1')
			result[(row-i)*(image_width-j)+ (col-j)]='1';

		else//(image[row*image_width+col] == '0')
			result[(row-i)*(image_width-j)+ (col-j)]='0';

		row_flag[row-i]=1;
		col_flag[col-j]=1;
	}
	else
		result[(row-i)*(image_width-j)+ (col-j)]='o';
	//result++;
}


__global__ void compute_Result(char* ptr_ptr ,int image_height, int image_width, int row_start,int col_start, int col_end, char* result2_ptr, int j)    {
	int row = blockIdx.x + row_start;
	int col = threadIdx.x + col_start;
	result2_ptr[(row - row_start) * (col_end - col_start + 1) + (col - col_start)] = ptr_ptr[row*(image_width-j) + col];
}



ConsensusGrid consensus_parallel(int i, int j,char* image, int image_height, int image_width)
{
	ConsensusGrid consensus_grid;
	char* image_ptr;
	int* row_flag_ptr;
	int*  col_flag_ptr;
	char * ptr_ptr;
	char*  result2_ptr;
	char* result_ptr;

	char *result = (char*)malloc(sizeof(char)*(image_height-i)*(image_width-j));
	char* ptr = result;

	int* row_flag=(int*)calloc(sizeof(int),(image_height-i));
	int* col_flag=(int*)calloc(sizeof(int),(image_width-j));
	//copy result and image to gpu
	//compute the result array
	//copy result back to cpu
	cudaMalloc((void**)&image_ptr, sizeof(char)*(image_height*image_width));
	cudaMemcpy(image_ptr, image, sizeof(char)*(image_height*image_width) ,  cudaMemcpyHostToDevice);
	cudaMalloc((void**)&row_flag_ptr, sizeof(int)*(image_height-i));
	cudaMemcpy(row_flag_ptr, row_flag, sizeof(int)*(image_height-i) ,  cudaMemcpyHostToDevice);
	cudaMalloc((void**)&col_flag_ptr, sizeof(int)*(image_width-j));
	cudaMemcpy(col_flag_ptr, col_flag, sizeof(int)*(image_width-j) ,  cudaMemcpyHostToDevice);
	cudaMalloc((void**)&result_ptr, sizeof(char)*(image_width-j)*(image_height-i));


	// __global__ functions are called:  Func<<< Dg, Db, Ns  >>>(parameter);
	compute_Dontcares<<<(image_height-i),(image_width-j)>>>(image_ptr,row_flag_ptr, col_flag_ptr, result_ptr,i,j, image_width);

	cudaDeviceSynchronize();
	cudaMemcpy(result, result_ptr, sizeof(char)*(image_height-i)*(image_width-j),  cudaMemcpyDeviceToHost);
	cudaMemcpy(row_flag, row_flag_ptr, sizeof(int)*(image_height-i),  cudaMemcpyDeviceToHost);
	cudaMemcpy(col_flag, col_flag_ptr, sizeof(int)*(image_width-j),  cudaMemcpyDeviceToHost);
	cudaMemcpy(image, image_ptr, sizeof(char)*(image_height)*(image_width),  cudaMemcpyDeviceToHost);
	//////Printing
	//if(i ==0 &&j == 0)
/*	cout << "i = " << i << " j = " << j << endl;
	{

		/*for(int ii=0;ii<image_height-i;ii++)
		{
			cout << "rf " << row_flag[ii] << endl;
		}*/
/*		for(int ii=0; ii<(image_height-i)*(image_width-j); ii++)
		{
			cout <<"p " << ptr[ii] << ", " ;
		}
	}
	cout<< endl << endl;
*/	int row_start,row_end;
	int col_start,col_end;
	for(row_start=0; row_start<(image_height-i); row_start++)
	{
		if(row_flag[row_start]==1)
			break;
	}
	for(row_end=(image_height-i-1); row_end>=0; row_end--)
	{
		if(row_flag[row_end]==1)
			break;
	}
	for(col_start=0; col_start<(image_width-j); col_start++)
	{
		if(col_flag[col_start]==1)
			break;
	}
	for(col_end=(image_width-j-1); col_end>=0; col_end--)
	{
		if(col_flag[col_end]==1)
			break;
	}

	if((row_start > row_end) || (col_start > col_end) )
	{
		consensus_grid.result = NULL;
		consensus_grid.height = 0;
		consensus_grid.width = 0;
		return consensus_grid;
	}

	char* result2 = (char*)malloc(sizeof(char)*(row_end-row_start+1)*(col_end-col_start+1));
	cudaMalloc((void**)&result2_ptr, sizeof(char)*(row_end-row_start+1)*(col_end-col_start+1));
	//cudaMemcpy(col_flag_ptr, col_flag, sizeof(image_width-j) ,  cudaMemcpyHostToDevice);
	cudaMalloc((void**)&ptr_ptr, sizeof(char)*(image_height-i)*(image_width-j));
	cudaMemcpy(ptr_ptr, ptr, sizeof(char)*(image_height-i)*(image_width-j) ,  cudaMemcpyHostToDevice);

	consensus_grid.result = result2;

	compute_Result<<<(row_end-row_start+1),(col_end-col_start+1)>>>(ptr_ptr , image_height, image_width, row_start,col_start, col_end, result2_ptr, j);

	cudaDeviceSynchronize();
	cudaMemcpy(result2, result2_ptr, sizeof(char)*(row_end-row_start+1)*(col_end-col_start+1),  cudaMemcpyDeviceToHost);
	 

	consensus_grid.height = row_end - row_start + 1;
	consensus_grid.width = col_end - col_start + 1;
	consensus_grid.occurance = NULL;
	consensus_grid.occurance_count = 0;

	free(ptr);
	free(row_flag);
	free(col_flag);
	return consensus_grid;
}
