#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>


using namespace cv;
using namespace std;

struct vars{
    int num = 0;
    int width = 0;
    int height = 1;
} img;

Mat1f generateGrayCode(int n){
    Mat1f result(Size(n, pow(2,n)));

    vector<string> arr;

    arr.push_back("0");
    arr.push_back("1");


    for (int i = 2; i < (1<<n); i = i<<1) {
        for (int j = i-1; j >= 0; j--) {
            arr.push_back(arr[j]);
        }
        for (int j = 0; j < i; j++) {
            arr[j] = "0" + arr[j];
        }
        for (int j = i; j < 2*i; j++) {
            arr[j] = "1" + arr[j];
        }
    }

    for(int i = 0; i < result.rows; i++){
        for(int j = 0; j < result.cols; j++){
            result(i,j) = (int)arr[i][j] - 48; //because of ASCII codes
        }
    }


    return result;
}

void generateGrayImages(Mat1f* hor, Mat1f* vert, Mat1f gray, vars img){
    //vertical fill

    for(int k = 0; k < img.num; k++) {
        for (int i = 0; i < img.height; i++) {
            for (int j = 0; j < img.width; j++) {
                vert[k](i, j) = gray(j, k);
            }
        }
    }

    //horizontal fill
    for(int k = 0; k < img.num; k++) {
        for (int i = 0; i < img.width; i++) { 	//TODO Richtig eingefuegt nicht vertauscht???
            for (int j = 0; j < img.height; j++) {
                hor[k](j, i) = gray(j, k);
            }
        }
    }
}



int getNumImgs(vars img){
    int val = 1;
    int i = 0;
    while (max(img.width, img.height) > val){
        i++;
        val *= 2;
    }
    return i;
}

int main(int argc, char **argv) {

    img.width = 1920;
    img.height = 1080;
    img.num = getNumImgs(img);

    std::cout << "Generating " << img.num << " Images ";
    std::cout << "with resolution: " << img.width << "x" << img.height << std::endl;

    Mat1f grayCodeVer[img.num];
    Mat1f grayCodeHor[img.num];
    for (int i = 0; i < img.num; i++) {
        grayCodeVer[i] = Mat1f(Size(img.width, img.height));
        grayCodeHor[i] = Mat1f(Size(img.width, img.height));
    }

    Mat1f grayValues = generateGrayCode(img.num);
    generateGrayImages(grayCodeHor, grayCodeVer, grayValues, img);

    std::cout << "Gray Images generated" << endl;

    namedWindow( "w", WINDOW_NORMAL );
    setWindowProperty("w",WND_PROP_FULLSCREEN,WINDOW_FULLSCREEN);

    std::cout << "Delete old imgs and save new ones in grays/" << endl;

    mkdir("grays", 0777);
    mkdir("grays/verts", 0777);
    mkdir("grays/hors", 0777);

    for (int i = 0; i < img.num; i++) {
        string v = "grays/verts/" + to_string(i) + ".png";
        string h = "grays/hors/" + to_string(i) + ".png";
        grayCodeVer[i] *= 255.f;
        grayCodeHor[i] *= 255.f;
        imwrite(v, grayCodeVer[i]);
        imwrite(h, grayCodeHor[i]);
        imshow("w", grayCodeVer[i]);
        waitKey(0);
        imshow("w", grayCodeHor[i]);
        waitKey(0);
    }

    destroyAllWindows();

    return 0;
}