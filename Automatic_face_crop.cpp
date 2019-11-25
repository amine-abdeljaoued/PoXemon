#include <opencv2/objdetect.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<stdlib.h>
#include <iostream>
#include <opencv2/core/types_c.h>
#include <stdio.h>
#include <string.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;





int main() {
	CascadeClassifier faceDetection;
	/* IMPORT FACIAL RECOGNITION LIBRARY */
	if (!faceDetection.load("C:/Users/unpol/Documents/Bachelor/CS201/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml")) {
		cout << "\n File not loaded properly ...";
		exit(0);
	}

	/* RETRIEVE THE FIRST IMAGE TO TAKE FACE FROM */
	char path[100] = "C:/Users/unpol/Documents/Bachelor/CS201/";
	char img_path[100];
	cout << "\n Image to take face : ";
	cin.getline(img_path, 100);
	strcat_s(path, img_path); //path is the full path to the first image

	/* RETRIEVE THE SECOND IMAGE TO PASTE FACE TO */
	char path2[100] = "C:/Users/unpol/Documents/Bachelor/CS201/";
	char img_path2[100];
	cout << "\n Image to replace face : ";
	cin.getline(img_path2, 100);
	strcat_s(path2, img_path2); //path is the full path to the second image

	Mat img = imread(path, IMREAD_UNCHANGED); //IMREAD_UNCHANGED needed to read color/alpha channels
	Mat img2 = imread(path2, IMREAD_UNCHANGED); //tranform both images to matrices opencv



	if (img.empty() or img2.empty()) {
		cout << "\n One image has not been loaded"; //error message
	}
	else {
		cout << "\n Images found"; //Style points
		cout << "\n Processing...";

		/* FACIAL RECOGNITION */

		vector<Rect> faces;
		faceDetection.detectMultiScale(img, faces); //stored in faces
		vector<Rect> faces2;
		faceDetection.detectMultiScale(img2, faces2);


		/*CUT AN ELLIPSE AROUND THE FACE*/


		int centerX = faces[0].width / 2 + faces[0].x, centerY = faces[0].height / 2 + faces[0].y, length_y = 0.8*((faces[0].width + faces[0].height) / 4), length_x = 0.75 * length_y;
		//coordinates and distances of the first face in the first image

		Mat bgr[3];   //3 dimension blue_green_red array in which we will put the different color channels
		split(img, bgr); //split source into the array

		/*================================*/

		
		Mat im2(bgr[0].rows, bgr[0].cols, CV_8UC1, Scalar(0, 0, 0)); // create empty mask of the same dimension as the original image
		ellipse(im2, Point(centerX, centerY), Size(length_x, length_y), 0, 0, 360, Scalar(255, 255, 255), -1, 8); //fill mask with a "negative" ellipse

		/*================================*/

		Mat blue_result; //matrix to save new face
		bitwise_and(bgr[0], im2, blue_result); //take only what is common to both
		//imwrite("C:/Users/unpol/Documents/Bachelor/CS201/blue_ellipse.png", blue_result);//save blue

		/*================================*/

		Mat green_result; //matrix to save new face
		bitwise_and(bgr[1], im2, green_result); //take only what is common to both
		//imwrite("C:/Users/unpol/Documents/Bachelor/CS201/green_ellipse.png", green_result);//save green

		/*================================*/

		Mat red_result; //matrix to save new face
		bitwise_and(bgr[2], im2, red_result); //take only what is common to both
		//imwrite("C:/Users/unpol/Documents/Bachelor/CS201/red_ellipse.png", red_result);//save red

		/*================================*/

		//recombine the 3 channels into a color image

		vector<Mat> chan;

		chan.push_back(blue_result);
		chan.push_back(green_result);
		chan.push_back(red_result);

		Mat color_image;
		merge(chan, color_image); //color_image the original picture with only an ellipse of the face

		/*CROP TO TAKE ONLY THE FACE OF IMAGE 1*/

		int startX = faces[0].x, startY = faces[0].y, width = faces[0].width, height = faces[0].height; //takes pos
		Mat ROI(color_image, Rect(startX, startY, width, height)); //creates region of interest around the face only
		Mat croppedImage;
		ROI.copyTo(croppedImage); //saves the region of interest
		//imwrite("C:/Users/unpol/Documents/Bachelor/CS201/cropped.png", croppedImage); //saves the cropped image

		int img2_x = faces2[0].x, img2_y = faces2[0].y, img2_width = faces2[0].width, img2_height = faces2[0].height;
		//coordinates of second face on the picture

		/*RESIZE TO FIT FACE OF IMAGE 2*/

		Mat resized;
		resize(croppedImage, resized, Size(img2_width, img2_height));
		//imwrite("C:/Users/unpol/Documents/Bachelor/CS201/cropped_resized.png", resized); //saves resized image


		/*ADD ALPHA CHANNEL AROUND THE ELLIPSE*/

		Mat with_alpha;
		Mat tmp, thr;

		cvtColor(resized, tmp, COLOR_BGR2GRAY);
		threshold(tmp, thr, 100, 255, THRESH_BINARY);

		vector< vector <Point> > contours; // Vector for storing contour
		vector< Vec4i > hierarchy;

		Mat alphabis(resized.size(), CV_8UC1, Scalar(0)); //makes "blank" copy

		findContours(tmp, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); // Find the contours in the image, here the ellipse

		drawContours(alphabis, contours, 0, Scalar(255), FILLED, 8, hierarchy);
		Mat rgb[3]; //split into 3 channels
		split(resized, rgb); //blue, green, red like above

		Mat rgba[4] = { rgb[0],rgb[1],rgb[2],alphabis }; 
		merge(rgba, 4, with_alpha); //merge adding the alpha channel
		imwrite("C:/Users/unpol/Documents/Bachelor/CS201/cropped_resized_transparent.png", with_alpha); //store the transparent version
		

		/* PASTE FACE ONTO SECOND PICTURE */

		//img2 = second picture
		//(img2_x, img2_y) top left corner of the the picture

		Mat4b abc = with_alpha;
		double alpha = 0.99;
		Mat3b roi = img2(Rect(img2_x, img2_y, abc.cols, abc.rows));

		for (int r = 0; r < roi.rows; ++r)
		{
			for (int c = 0; c < roi.cols; ++c)
			{
				const Vec4b& vf = abc(r, c);
				if (vf[3] > 0) // alpha channel > 0
				{
					// Blending
					Vec3b& vb = roi(r, c);
					vb[0] = alpha * vf[0] + (1 - alpha) * vb[0];
					vb[1] = alpha * vf[1] + (1 - alpha) * vb[1];
					vb[2] = alpha * vf[2] + (1 - alpha) * vb[2];
				}
			}
		}

		
		imwrite("C:/Users/unpol/Documents/Bachelor/CS201/final.png", img2);
		cout << "\n Final product ready!";
		imshow("Final Product", img2);
		waitKey();
	}

	return 0;
}
