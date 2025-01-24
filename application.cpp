#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <mutex>
#include <iomanip>

using namespace std;
using namespace cv;

// Function to compress the image
void compressImage(Mat& image, int compression_level)
{
    vector<uchar> buf;
    vector<int> params;
    params.push_back(IMWRITE_JPEG_QUALITY);
    params.push_back(compression_level);

    imencode(".jpg", image, buf, params);
    image = imdecode(buf, IMREAD_COLOR);
}

// Function to compress the frame
void compressFrame(Mat& frame, Mat& compressed_frame, mutex& mtx, int compression_level)
{
    vector<uchar> buf;
    vector<int> params;
    params.push_back(IMWRITE_JPEG_QUALITY);
    params.push_back(compression_level);

    while (true)
    {
        // Compress the frame
        Mat local_frame;
        mtx.lock();
        frame.copyTo(local_frame);
        mtx.unlock();

        imencode(".jpg", local_frame, buf, params);
        mtx.lock();
        compressed_frame = imdecode(buf, IMREAD_COLOR);
        mtx.unlock();
    }
}

int main()
{
    // Prompt user for compression type
    cout << "Enter the compression type (image): ";
    string compression_type;
    cin >> compression_type;

    // Check the compression type
    if (compression_type == "image")
    {
        // Read the image
        Mat image = imread("flower.jpg", IMREAD_COLOR);
        if (image.empty())
        {
            cout << "Failed to read image." << endl;
            return -1;
        }

        // Prompt user for compression level
        cout << "Enter the compression level (0-100): ";
        int compression_level;
        cin >> compression_level;

        // Create a copy of the image for compression
        Mat compressed_image = image.clone();

        // Perform image compression using multithreading
        thread compression_thread(compressImage, ref(compressed_image), compression_level);
        compression_thread.join();

        // Calculate the original and compressed image file sizes
        vector<uchar> original_buf, compressed_buf;
        imencode(".jpg", image, original_buf);
        imencode(".jpg", compressed_image, compressed_buf);
        size_t original_size = original_buf.size();
        size_t compressed_size = compressed_buf.size();

        // Calculate the compression percentage
        double compression_percentage = 100.0 - (compressed_size / (double)original_size * 100.0);

        // Convert the compression percentage to a string
        stringstream ss;
        ss << fixed << setprecision(2) << "Compression: " << compression_percentage << "%";
        string compression_text = ss.str();

        // Display the original and compressed images
        namedWindow("Compressed Image", WINDOW_NORMAL);
        putText(compressed_image, "Original Size: " + to_string(image.cols) + "x" + to_string(image.rows), Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2, LINE_AA);
        putText(compressed_image, "Compressed Size: " + to_string(compressed_image.cols) + "x" + to_string(compressed_image.rows), Point(10, 70), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2, LINE_AA);
        putText(compressed_image, compression_text, Point(10, 110), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2, LINE_AA);
        imshow("Compressed Image", compressed_image);
        waitKey(0);
    }
    
    else
    {
        cout << "Invalid compression type. Please choose either 'image'." << endl;
    }

    // Destroy any OpenCV windows
    destroyAllWindows();

    return 0;
}