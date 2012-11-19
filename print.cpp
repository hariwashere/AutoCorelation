void print_meet()
{
    cout<< "Getting all the meets";
    for(int i=0; i< image_height* image_width; i++)
    {
        cout<<" For meet "<<i<<endl;
        for(int j=0; j< meet[i].height * meet[i].width; j++)
        {
            cout<< meet[i].result[j]<< ", ";
        }
        cout<<endl;

    }
}

void print_occurances()
{
    for(int i=0; i< basis_count; i++)
    {
        cout<<" The occurances of meet "<< i<< "with the occurance count"<<meet[basis[i]].occurance_count<< endl;
        for(int j=0; j< meet[basis[i]].occurance_count; j++)
            cout<<"i = "<< meet[basis[i]].occurance[j].i<< " j= "<< meet[basis[i]].occurance[j].j<<endl;
    }
}

void print_basis()
{
    cout << "The basis count is "<< basis_count<<endl;
    cout<<"The basis has"<< endl;
    for(int i=0; i< basis_count; i++ )
    {
        cout<< basis[i]<< endl;
    }
}

