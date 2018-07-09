#include "cvstamp.h"

using namespace std;

int cvStamp::orientationMap(const cv::Mat& img, int c)
{
    //cout << "depth: " << image.depth() << endl;
    //cout << "channels: " << image.channels() << endl;

    Mat gray;

    cvtColor(img, gray, CV_BGR2GRAY);

    double thresh = 1.0;

    Mat Sx;
    Sobel(gray, Sx, CV_32F, 1, 0, 3);

    Mat Sy;
    Sobel(gray, Sy, CV_32F, 0, 1, 3);

    Mat mag, ori;
    magnitude(Sx, Sy, mag);

    phase(Sx, Sy, ori, true);

    Mat oriMap = Mat::zeros(ori.size(), CV_8UC3);

    Vec3b red(0, 0, 255);
    Vec3b cyan(255, 255, 0);
    Vec3b green(0, 255, 0);
    Vec3b yellow(0, 255, 255);

    int i1 = 0,
        i2 = 0,
        i3 = 0,
        i4 = 0;

    int point = 0;

	for(int i = 0; i < oriMap.rows*oriMap.cols; i++)
	{
		float* magPixel = reinterpret_cast<float*>(mag.data + i*sizeof(float));
		if(*magPixel > thresh)
		{
			float* oriPixel = reinterpret_cast<float*>(ori.data + i*sizeof(float));
			Vec3b* mapPixel = reinterpret_cast<Vec3b*>(oriMap.data + i*3*sizeof(char));
			if(*oriPixel < 90.0)
			{
				i1++;
				*mapPixel = red;
			}
			else if(*oriPixel >= 90.0 && *oriPixel < 180.0)
			{
				i2++;
				*mapPixel = cyan;
			}

			else if(*oriPixel >= 180.0 && *oriPixel < 270.0)
			{
				i3++;
				*mapPixel = green;
			}

			else if(*oriPixel >= 270.0 && *oriPixel < 360.0)
			{
				i4++;
				*mapPixel = yellow;
			}

		}
	}

    //imshow("orimap", oriMap);
    //waitKey();

    /*cout << "1: " << i1 << "  2: " << i2 << endl;
    cout << "3: " << i3 << "  4: " << i4 << endl << endl;*/

    switch (c)
    {
        case 1:
        {
            if( i1>i2 ) point++;
            if( i3>i4 ) point++;
            break;
        }
        case 2:
        {
            if( i1<i2 ) point++;
            if( i3<i4 ) point++;
            break;
        }
        case 3:
        {
            if( i1<i2 ) point++;
            if( i3<i4 ) point++;
            break;
        }
        case 4:
        {
            if( i1>i2 ) point++;
            if( i3>i4 ) point++;
            break;
        }
        default:
        {
            return 0;
            break;
        }
    }
    if( point != 0 )
        return point;
    else
        return 0;
}

cvStamp::cvStamp()
{
    //получаем картинку
	image = imread("apple.jpg", 1);
	if(image.cols == 0)	throw -1;
}

cvStamp::cvStamp(string path)
{
    pathImage = path;
    //получаем картинку
	image = imread(pathImage, 1);
	if(image.cols == 0)	throw -1;

}

cvStamp::~cvStamp()
{
	//освобождаем ресурсы, окна
	/*if(!image.empty()) delete &image;
	if(!imageBlue.empty()) delete &imageBlue;
	if(!imageCircles.empty()) delete &imageCircles;
	if(!imageRoi.empty()) delete &imageRoi;
	if(!imageClasters.empty()) delete &imageClasters;*/
	destroyAllWindows();
}

Mat cvStamp::getImage()
{
	return image;
}

void cvStamp::setSizeRotate(float sz)
{
	//Коэфы масштаба
	float ky =  sz / image.cols;
	float kx =  sz / image.rows;

	//Наибольшее значение
	float k =  (kx > ky ? ky : kx);

	//cout << k << endl;

	Size s(round(k*image.cols), round(k*image.rows));

	resize(image, image, Size(), k, k);

	//Поворот
	if(image.cols < image.rows)
		rotate(image, image, 0);

	//imshow("resize", tempImage);
	//waitKey();

}

void cvStamp::showImage(string im_path)
{
	Mat temp = imread(im_path, 1);

	//cout << temp.cols << " " << temp.rows << endl;

	imshow(im_path, temp);

	waitKey();
}

void cvStamp::showImageAll()
{
	//imshow("image", image);
	//imshow("imageBlue", imageBlue);
	imshow("imageCircles", imageCircles);
	//imshow("imageRoi", imageRoi);
    waitKey();
}

void cvStamp::saveImage(string _pathImage, Mat img)
{
	imwrite(_pathImage, img);
}

bool cvStamp::setRoi(Mat& img)
{
    //Шаг разбиения на кластеры
    int shag = 2;

    //Рисум кластеры
    //img = setClasters(img, shag);

    //Вычисляем размеры кластеров
    Rect r1(0, 0, (img.rows)/shag, (img.cols)/shag );
    Rect r2((img.rows)/shag, 0, (img.rows)/shag, (img.cols)/shag );
    Rect r3(0, (img.cols)/shag, (img.rows)/shag, (img.cols)/shag );
    Rect r4((img.rows)/shag, (img.cols)/shag, (img.rows)/shag, (img.cols)/shag );

    Mat subRoi[4];

    //Создаем subROI
    img(r1).copyTo( subRoi[0] );
    img(r2).copyTo( subRoi[1] );
    img(r3).copyTo( subRoi[2] );
    img(r4).copyTo( subRoi[3] );

/*
    imshow("1", subRoi[0]);
    waitKey();
    imshow("2", subRoi[1]);
    waitKey();
    imshow("3", subRoi[2]);
    waitKey();
    imshow("4", subRoi[3]);
    waitKey();


    cout << orientationMap(subRoi[0], 1) << " + "
                    << orientationMap(subRoi[1], 2) << " + "
                    << orientationMap(subRoi[2], 3) << " + "
                    << orientationMap(subRoi[3], 4)
                    << endl;

    cout << "points: " << orientationMap(subRoi[0], 1)
                + orientationMap(subRoi[1], 2)
                + orientationMap(subRoi[2], 3)
                + orientationMap(subRoi[3], 4)
                << endl << endl;
*/
    if(orientationMap(subRoi[0], 1)
    + orientationMap(subRoi[1], 2)
    + orientationMap(subRoi[2], 3)
    + orientationMap(subRoi[3], 4)
    > 6)
    {
        return true;
    }
    else
        return false;
}


void cvStamp::setImageToCircle()
{
    imageCircles = imageBlue.clone();
    imageRoi = image.clone();
    std::vector<Vec3f> circles;

    //Расчет допустимых радиусов окружностей
	const float dopusk = 1.075;//7.5%
	unsigned r_min = (imageCircles.rows)/(2*7.78*dopusk);
	unsigned r_max = (imageCircles.rows*dopusk)/(2*5);

    //cout << "r_min: " << r_min << endl;
    //cout << "r_max: " << r_max << endl;

    //В серый
    Mat gray;
    cvtColor(imageCircles, gray, COLOR_BGR2GRAY);

    //Размытие
    medianBlur(gray, gray, 5);//???
    medianBlur(gray, gray, 5);//???

	//Поиск окружностей
	HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
				 2*r_min, // расстояние между центрами
				 100, 30, r_min, r_max
				 );

    //Выделение памяти под ROI
    rois = new Rect[circles.size()];
    img = new Mat[circles.size()];

    //Счетчик правильного обнаружния
    unsigned int true_sr = 0;

    //Накладываем окружности и ROI на изображение
    for( size_t i = 0; i < circles.size(); i++ )
    {
        //буфер
        Vec3i c = circles[i];
/*
        cout << "rois[i].x = " << (c[0] - c[2] - c[2]*0.1) << endl
             << "rois[i].y = " << (c[1] - c[2] - c[2]*0.1) << endl
             << "rois[i].width = " << 2.2*c[2] << endl
             << "rois[i].height = " << 2.2*c[2] << endl;
*/
        //сохраняем roi
        rois[i].x = c[0] - c[2]; //((c[0] - c[2] - c[2]*0.1) > 0) ? (c[0] - c[2] - c[2]*0.1) : 0;
        rois[i].y = c[1] - c[2]; //((c[1] - c[2] - c[2]*0.1) > 0) ? (c[1] - c[2] - c[2]*0.1) : 0;
        rois[i].width = 2*c[2];  //2.2
        rois[i].height = 2*c[2]; //2.2
/*
        //Обработка исключений выхода за пределы изображения
        if((rois[i].x + rois[i].width) > image.cols)
        {
            cout <<  image.cols - rois[i].x << " vooodox! " << endl;
            rois[i].width = 10;
        }
        if((rois[i].y + rois[i].height) > image.rows)
        {
            cout << image.rows - rois[i].y << " vooodoy! " << endl;
            rois[i].height = 10;
        }
*/

        //рисуем все roi
        rectangle(imageRoi, Point(c[0] - c[2], c[1] - c[2]), Point(c[0] + c[2], c[1] + c[2]), Scalar(0, 255, 0), 2);

        // Копирование региона в отдельное изображение
		imageBlue(rois[i]).copyTo( img[i] );

        //отбор ROI
        if( this->setRoi(img[i]) )
        {

			//Рисуем окружности
			circle( imageCircles, Point(c[0], c[1]), c[2], Scalar(0,0,255), 2, LINE_AA); //Окружность
			circle( imageCircles, Point(c[0], c[1]), 2, Scalar(0,255,0), 2, LINE_AA); //Точка
            //cout << true_sr << endl;

            //Для пути без расширения
            string pathImage_;

            //Храним размер пути изображения
            int sizePathImage = pathImage.size();

            //Перепечатываем путь до точки
			for ( int l = 0; l < 13 /*sizePathImage*/ ; l++ )
			{
                pathImage_ += pathImage[l];
			}

            //Формируем названия печатей
			pathImage_ += "/signet/file_" + to_string(true_sr) + ".jpg";

            //Для сохранинеия печати из исходного изображения
			image(rois[i]).copyTo(img[i]);

			cout << pathImage_ << endl;
			saveImage(pathImage_, img[i]);

			//Номер картинки
            true_sr = true_sr + 1;

			//showImage(pathImage);

			//showImage(pathImage_);
        }
    }
}


void cvStamp::setImageToBlue()
{
	//поворот
	unsigned o_size = 1000;
	if(image.rows > o_size || image.cols > o_size)
	{
		//setSizeRotate(o_size);

		rotate(image, image, 0);
	}

	else
		//Поворот
		if(image.cols < image.rows)
			rotate(image, image, 0);

	cout << endl << "image_size" << image.cols << "x" << image.rows << endl;
	imageBlue = image.clone();

    //Расчет допустимых цветов
    const int GREEN_MIN = 0;
    const int GREEN_MAX = 360;

    //Переводим в формат HSV
    Mat hsv = Mat(imageBlue.cols, imageBlue.rows, 8, 3);
    vector<Mat> splitedHsv = vector<Mat>();
    cvtColor(imageBlue, hsv, CV_BGR2HSV);
    split(hsv, splitedHsv);

    //Удаляем фон
    for (int y = 0; y < hsv.cols; y++)
    {
        for (int x = 0; x < hsv.rows; x++)
        {
            // получаем HSV-компоненты пикселя
            int H = static_cast<int>(splitedHsv[0].at<uchar>(x, y));        // Тон
            int S = static_cast<int>(splitedHsv[1].at<uchar>(x, y));        // Интенсивность
            int V = static_cast<int>(splitedHsv[2].at<uchar>(x, y));        // Яркость

            //Если яркость слишком низкая либо Тон не попадает у заданный диапазон, то закрашиваем белым
            if ((S < 20) ||(V < 80) || (H < GREEN_MIN) || (H > GREEN_MAX))
            {
                imageBlue.at<Vec3b>(x, y)[0] = 255;
                imageBlue.at<Vec3b>(x, y)[1] = 255;
                imageBlue.at<Vec3b>(x, y)[2] = 255;
            }
        }
    }
}

Mat cvStamp::setClasters(Mat& img, int _shag)
{
    imageClasters = img.clone();

    //Сетка 2x2
    int sh_rows, sh_cols, shag = _shag;

    //Размер ROI
    sh_rows = int(imageClasters.rows/shag);
    sh_cols = int(imageClasters.cols/shag);

    //Рисуем белую сетку
    for(int i = 0; i < imageClasters.rows; i++)
    {
        for(int j = 0; j < imageClasters.cols; j++)
        {
            if((i%(sh_rows+1) == sh_rows && j%2 == 1) || (j%(sh_cols+1) == sh_cols && i%2 == 1))
            {
                imageClasters.at<Vec3b>(i, j)[0] = 255;
                imageClasters.at<Vec3b>(i, j)[1] = 255;
                imageClasters.at<Vec3b>(i, j)[2] = 255;
            }
        }
    }

    return imageClasters;
}

/* Распознавание букв
std::vector<cv::Rect> detectLetters(const char *pcv::Mat img)
{
    Mat img = imread(p);
    std::vector<cv::Rect> boundRect;
    cv::Mat img_gray, img_sobel, img_threshold, element;
    cvtColor(img, img_gray, CV_BGR2GRAY);
    cv::Sobel(img_gray, img_sobel, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
    cv::threshold(img_sobel, img_threshold, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
    element = getStructuringElement(cv::MORPH_RECT, cv::Size(17, 3) );
    cv::morphologyEx(img_threshold, img_threshold, CV_MOP_CLOSE, element); //Does the trick
    std::vector< std::vector< cv::Point> > contours;
    cv::findContours(img_threshold, contours, 0, 1);
    std::vector<std::vector<cv::Point> > contours_poly( contours.size() );
    for( int i = 0; i < contours.size(); i++ )
        if (contours[i].size()>100)
        {
            cv::approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 3, true );
            cv::Rect appRect( boundingRect( cv::Mat(contours_poly[i]) ));
            if (appRect.width>appRect.height)
                boundRect.push_back(appRect);
        }
    //boundRect = boundRect.boundingRect();
    //rectangle(img, boundRect, Scalar(255,0,0));
    return boundRect;
}
*/
