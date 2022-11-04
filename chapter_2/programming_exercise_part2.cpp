/*
To make a friendly user interface, we wish to describe orientations in the planar
world by a single angle, Theta(th), instead of by a 2x2 rotation matrix. The user 
will always communicate in terms of angle theta, but internally we will need the
rotation-matrix form. So, we want to allow the user to specify a frame as a 3-tuple
(x, y, theta). 

Internally we wish to use a 2 x 1 position vector and 2 x 2 rotation matrix, so we need 
conversion routines. Write a subroutine whose pascal definition would begin 

Procedure UTOI(VAR uform: vec3; VAR iform: frame); 

where "UTOI stands for User form to internal form". The first argument is the 3-tuple (x, y, theta), 
and the second argument is  of type frame, consists of a (2 x 1) position vector and 
a 2 x 2 rotation matrix. If you wish, you may represent the frame with a 3 x 3 homogeneous 
transform in which the third row is [0 0 1]. 

The inverse routine will also be necessary : 

Procedure ITOU(VAR iform: frame, VAR uform: vec3); 



*/


#include <iostream>
#include <iomanip>
#include <math.h>
#include <array>

#define PI 3.141592

std::array<std::array<double, 4>, 4> multiply_transform(std::array<std::array<double, 4>, 4> t1, std::array<std::array<double, 4>, 4> t2)
{
    std::array<std::array<double, 4>, 4> transformed_matrix; 
    std::array<double, 3> relative_position_between_frames; 


    // when we multiply two transormation matrices, the format of matrix multiplication is as follows:
    
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            transformed_matrix.at(i).at(j) = 0.0; 
            

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 3; k++)
                transformed_matrix.at(i).at(j) += t1.at(i).at(k) * t2.at(k).at(j); 

        }

    }

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0;  j < 3; j++)
            {
                transformed_matrix.at(i).at(3) += t1.at(i).at(j) * t2.at(j).at(3);  

            }
        transformed_matrix.at(i).at(3) += t2.at(i).at(3); 


    }






    for(int i = 0; i < 3; i++)
        transformed_matrix.at(3).at(i) = 0.0; 

    transformed_matrix.at(3).at(3) = 1.0; 









return transformed_matrix; 


}




// we receive x and y coordinates and the degree as an angle 
std::array<std::array<double, 4>, 4> transform(std::array<int, 3> input_tuple, char frame)
{
    std::array<std::array<double, 4>, 4> transformation_matrix; 
    int location_1, location_2; 
    location_1 = input_tuple.at(0); 
    location_2 = input_tuple.at(1); 
    int angle = input_tuple.at(2); 
    


    if (frame == 'x')
    {
        transformation_matrix.at(0).at(0) = 1; 
        transformation_matrix.at(0).at(1) = 0; 
        transformation_matrix.at(0).at(2) = 0; 
        transformation_matrix.at(0).at(3) = 0; 
        transformation_matrix.at(1).at(0) = 0; 
        transformation_matrix.at(1).at(1) = cos(angle * PI / 180.0); 
        transformation_matrix.at(1).at(2) = -1* sin(angle * PI / 180.0); 
        transformation_matrix.at(1).at(3) = location_1; 
        transformation_matrix.at(2).at(0) = 0; 
        transformation_matrix.at(2).at(1) = sin(angle * PI / 180.0); 
        transformation_matrix.at(2).at(2) = cos(angle* PI / 180.0); 
        transformation_matrix.at(2).at(3) = location_2; 

        for(int i = 0; i < 3; i++)
            transformation_matrix.at(3).at(i) = 0; 
        transformation_matrix.at(3).at(3) = 1; 
        
    }
    else if (frame == 'y')
    {
        transformation_matrix.at(0).at(0) = cos(angle * PI / 180.0); 
        transformation_matrix.at(0).at(1) = 0; 
        transformation_matrix.at(0).at(2) = sin(angle * PI  / 180.0); 
        transformation_matrix.at(0).at(3) = location_1; 
        transformation_matrix.at(1).at(0) = 0; 
        transformation_matrix.at(1).at(1) = 1; 
        transformation_matrix.at(1).at(2) = 0; 
        transformation_matrix.at(1).at(3) = 0; 
        transformation_matrix.at(2).at(0) = -1 * sin(angle * PI / 180.0); 
        transformation_matrix.at(2).at(1) = 0; 
        transformation_matrix.at(2).at(2) = cos(angle * PI / 180.0); 
        transformation_matrix.at(2).at(3) = location_2; 
        
        for(int i = 0; i < 3; i++)
            transformation_matrix.at(3).at(i) = 0; 
        transformation_matrix.at(3).at(3) = 1; 
        


    }
    else if (frame == 'z')
    {
        transformation_matrix.at(0).at(0) = cos(angle * PI / 180.0); 
        transformation_matrix.at(0).at(1) = -1* sin(angle * PI / 180.0 ); 
        transformation_matrix.at(0).at(2) = 0; 
        transformation_matrix.at(0).at(3) = location_1; 

        transformation_matrix.at(1).at(0) = sin(angle * PI / 180.0); 
        transformation_matrix.at(1).at(1) = cos(angle * PI / 180.0); 
        transformation_matrix.at(1).at(2) = 0; 
        transformation_matrix.at(1).at(3) = location_2; 

        transformation_matrix.at(2).at(0) = 0; 
        transformation_matrix.at(2).at(1) = 0; 
        transformation_matrix.at(2).at(2) = 1; 
        transformation_matrix.at(2).at(3) = 0; 


        for(int i = 0; i < 3; i++)
            transformation_matrix.at(3).at(i) = 0; 
        transformation_matrix.at(3).at(3) = 1; 

    }
    else
    {
        std::cout << "please insert a proper frame for the rotation: "; 
    }


return  transformation_matrix; 

}






int main()
{

std::array<std::array<double, 4>, 4> transformation_matrix; 
std::array<std::array<double, 4>, 4> transformation_matrix_2; 
std::array<std::array<double, 4>, 4> multiplied_matrix; 

char frame; 
char frame2; 


std::array<int, 3> input_tuple; // input tuple with x, y and theta 
std::array<int, 3> input_tuple_2; // second tuple

std::cout << "insert the parameters of the transformation: (x, y, theta(in degrees))\n"; 


for(int i = 0; i < input_tuple.size(); i++)
    std::cin >> input_tuple.at(i); 

std::cout << "insert the rotation of the frame around the axis: (x, y, z): "; 
std::cin >> frame; 


transformation_matrix = transform(input_tuple, frame); 




for(int i = 0; i < 4; i++)
    {
       for(int j = 0; j < 4; j++)
        {
            std::cout << std::setw(7) << std::setprecision(3) <<  transformation_matrix[i][j] << " "; 
        }
            
    std::cout << std::endl; 
    }


std::cout << "insert the parameters of the second transformation: (x, y, theta)\n"; 


for(int i = 0; i < input_tuple_2.size(); i++)
    std::cin >> input_tuple_2.at(i); 

std::cout << "insert the rotation of the frame around the axis: (x, y, z): \n"; 
std::cin >> frame2;  

transformation_matrix_2 = transform(input_tuple_2, frame2); 


for(int i = 0; i < 4; i++)
    {
       for(int j = 0; j < 4; j++)
        {
            std::cout << std::setw(7) << std::setprecision(3) <<  transformation_matrix_2[i][j] << " "; 
        }
            
    std::cout << std::endl; 
    }

    std::cout << std::endl; 




multiplied_matrix = multiply_transform(transformation_matrix, transformation_matrix_2);





for(int i = 0; i < 4; i++)
    {
       for(int j = 0; j < 4; j++)
        {
            std::cout << std::setw(7) << std::setprecision(3) <<  multiplied_matrix[i][j] << " "; 
        }
            
    std::cout << std::endl; 
    }







    
}