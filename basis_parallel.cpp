ConsensusGrid consensus_parallel(int i, int j,char* image, int image_height, int image_width)
        {
            ConsensusGrid consensus_grid;
            char *result = (char*)malloc(sizeof(char)*(image_height-i)*(image_width-j));
            char* ptr = result;

            int* row_flag=(int*)calloc(sizeof(int),(image_height-i));
            int* col_flag=(int*)calloc(sizeof(int),(image_width-j));
            _Cilk_for(int row=i;row<image_height;row++)
            {
                _Cilk_for(int col=j;col<image_width;col++)
                {
                    if(image[row*image_width+col] == image[(row-i)*image_width+col-j])
                    {
                        if(image[row*image_width+col] == '1')
                            result[(row-i)*(image_width-j)+ (col-j)]='1';

                        else if(image[row*image_width+col] == '0')
                            result[(row-i)*(image_width-j)+ (col-j)]='0';

                        row_flag[row-i]=1;
                        col_flag[col-j]=1;
                    }
                        else
                            result[(row-i)*(image_width-j)+ (col-j)]='o';
                    //result++;
                }
            }
            _Cilk_sync;
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

        if((row_start > row_end) || (col_start > col_end) ){
            consensus_grid.result = NULL;
            consensus_grid.height = 0;
            consensus_grid.width = 0;
            return consensus_grid;
        }

        char *result2 = (char*)malloc(sizeof(char)*(row_end-row_start+1)*(col_end-col_start+1));
        consensus_grid.result = result2;
            _Cilk_for(int row=row_start;row<=row_end;row++) //_Cilk_
            {
                _Cilk_for(int col=col_start;col<=col_end;col++) //_Cilk_
                {
                    result2[(row - row_start) * (col_end - col_start + 1) + (col - col_start)] = ptr[row*(image_width-j) + col];
                }
            }
            _Cilk_sync;

            consensus_grid.height = row_end - row_start + 1;
            consensus_grid.width = col_end - col_start + 1;
            consensus_grid.occurance = NULL;
            consensus_grid.occurance_count = 0;

            free(ptr);
            free(row_flag);
            free(col_flag);
            return consensus_grid;
        }
