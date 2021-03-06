// An empty test as a placeholder

#include "gtest/gtest.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

#include "AprilTags/TagDetector.h"
#include "AprilTags/Tag36h11.h"
using namespace AprilTags;

#include "../test_common.h"
#include "test_data.h"

static Mat load36H11GreyscaleImage( void )
{
  Mat inputImage( imread(  TEST_36H11_GREYSCALE_JPG, CV_LOAD_IMAGE_GRAYSCALE ));
  EXPECT_FALSE( inputImage.empty() );
  return inputImage;
}

static Mat load36H11ObliqueGreyscaleImage( void )
{
  Mat inputImage( imread(  TEST_36H11_OBLIQUE_GREYSCALE_JPG, CV_LOAD_IMAGE_GRAYSCALE ));
  EXPECT_FALSE( inputImage.empty() );
  return inputImage;
}


static void validate_36h11_tags( const std::vector<TagDetection> &tags )
{
  EXPECT_EQ( 80, tags.size() );
}

// This isn't a unit test per se, but tests that the tag TagDetector
// Is in fact still working against test data.
TEST( TagDetectorTest, DefaultConfiguration ) {
  TagDetector detector( tagCodes36h11 );

  Mat inputImage( load36H11GreyscaleImage() );

  std::vector<TagDetection> tags = detector.extractTags( inputImage );

  validate_36h11_tags( tags );
}



TEST( TagDetectorTest, DebugConfiguration ) {
  TagDetector detector( tagCodes36h11 );
  detector.SaveDebugImages(true);

  Mat inputImage( load36H11GreyscaleImage() );

  std::vector<TagDetection> tags = detector.extractTags( inputImage );

  EXPECT_EQ( detector.debugImage(TagDetector::OriginalImage).size(), inputImage.size() );
  EXPECT_EQ( detector.debugImage(TagDetector::BlurredImage).size(), inputImage.size() );
  EXPECT_EQ( detector.debugImage(TagDetector::MagnitudeImage).size(), inputImage.size() );
  EXPECT_EQ( detector.debugImage(TagDetector::LineSegmentsImage).size(), inputImage.size() );
  EXPECT_EQ( detector.debugImage(TagDetector::QuadImage).size(), inputImage.size() );

  write32FC1("/tmp/original.jpg", detector.debugImage(TagDetector::OriginalImage) );
  write32FC1("/tmp/low_pass_image.jpg", detector.debugImage(TagDetector::BlurredImage) );
  write32FC1("/tmp/magnitude.jpg", detector.debugImage(TagDetector::MagnitudeImage) );
  write32FC3("/tmp/line_segment_image.jpg", detector.debugImage(TagDetector::LineSegmentsImage) );
  write32FC1("/tmp/quad_image.jpg", detector.debugImage(TagDetector::QuadImage) );

  validate_36h11_tags( tags );
}

TEST( TagDetectorTest, ObliqueImage ) {
  TagDetector detector( tagCodes36h11 );

  Mat inputImage( load36H11ObliqueGreyscaleImage() );

  std::vector<TagDetection> tags = detector.extractTags( inputImage );

  cout << "Got " << tags.size() << " tags from oblique image: ";
  for( unsigned int i = 0; i < tags.size(); ++i ) cout << tags[i].id << " ";
  cout << endl;

  cout << "Areas: ";
  for( unsigned int i = 0; i < tags.size(); ++i ) cout << tags[i].totalArea() << " ";
  cout << endl;


  Mat tagImage;
  cv::cvtColor( inputImage, tagImage, CV_GRAY2BGR );
  for( unsigned int i = 0; i < tags.size(); ++i ) tags[i].draw( tagImage );
  cv::imwrite( "oblique_tags.jpg", tagImage );

}
