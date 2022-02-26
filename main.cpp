#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


int main()
{
    std::string fname = "/home/code/Documents/training/train-annotations-bbox.csv";


    std::vector<std::vector<std::string>> content;
    std::vector<std::string> row;
    std::string line, word;
    std::fstream file (fname, std::ios::in);

    if(file.is_open())
    {
        while(getline(file, line))
        {
            row.clear();

            std::stringstream str(line);

            int classFlag = 0;
            while(getline(str, word, ','))
            {
                row.push_back(word);

                if(word == "/m/02hj4")
                {
                    classFlag = 1;
                }
            }

            if(classFlag)
                content.push_back(row);
        }
    }
    else
        std::cout<<"Could not open the file\n";

    for(int i=0;i<(int)content.size();i++)
    {



        std::cout<<content[i][0]<<" "<<content[i][2]<<" "<<content[i][4]<<" "<<content[i][5]<<" "<<content[i][6]<<" "<<content[i][7]<<std::endl;


        std::string temp = ".jpg /home/code/Documents/training/images/";
        std::string temp2 = "aws s3 --no-sign-request cp s3://open-images-dataset/train/";
        std::string temp3 = content[i][0];

        std::ofstream labelTxt;
        std::string labelFile = "/home/code/Documents/training/labels/" + temp3 + ".txt";

        labelTxt.open(labelFile, std::ios::app);

        double midX = (std::stod(content[i][4]) + std::stod(content[i][5]))/2;
        double midY = (std::stod(content[i][6]) + std::stod(content[i][7]))/2;
        double widthImg = std::stod(content[i][5]) -     std::stod(content[i][4]);
        double heightImg = std::stod(content[i][7]) - std::stod(content[i][6]);

        labelTxt << "0 " << std::to_string(midX) <<" " << std::to_string(midY) <<" " << std::to_string(widthImg) <<" " << std::to_string(heightImg)<< "\n";
        labelTxt.close();


        std::string strCommand = temp2 + temp3 + temp;
r



        const char *command = strCommand.c_str();

        std::cout<<command<<std::endl;

        system(command);

    }

    std::cout<<content.size()<<std::endl;

    return 0;
}
