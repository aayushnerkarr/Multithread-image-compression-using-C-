# Multi Threaded Real-Time Image Compression using OpenCV

This project demonstrates real-time image and video compression using OpenCV in C++. It provides an interactive application that allows the user to choose between image or video compression, specify the compression level, and visualize the results.

## Features

- **Image Compression:**
  - Allows the user to select an image file for compression.
  - Supports multi-threading for efficient compression.
  - Calculates the compression percentage and displays it on the compressed image.
  - Displays the original and compressed images side by side.

## Usage

1. Ensure that OpenCV is properly installed and configured.

2. Compile the project using a C++ compiler with the OpenCV library linked. For example, using g++:

3. Run the compiled executable.

4. The program will prompt you to choose between image.

5. If you selected **image compression**:
- Enter the compression level as a percentage (e.g., 50 for 50% compression).
- The program will display the original and compressed images side by side, along with the compression percentage.

## Notes

- **Image Compression:**
- The input image file should be in a supported format (e.g., JPEG, PNG).
- Adjust the compression level to balance between image quality and file size.
