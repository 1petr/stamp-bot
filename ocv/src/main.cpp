#include "cvstamp.cpp"

int main(int argc, char* argv[])
{
		try
		{
			cvStamp* stamp = new cvStamp(argc == 2 ? argv[1] : "img/554555555/12.jpg");

			stamp->setImageToBlue();

			stamp->setImageToCircle();

			//stamp->showImageBlue();

			//stamp->showImageCircle();
			//stamp->showImageAll();

			delete stamp;
		}
		catch(int ex)
		{
			if(ex == -1)
				cout << "The broken path to the image. Check there is an image." << endl;
		}
 
        return 0;
}