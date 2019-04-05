#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkBinaryThresholdImageFilter.h"
#include "cstdlib"

/**                                                                            
 * use ITK i/o to implement a thresholding program                  
 * input a raw 3D image .img or .hdr                           
 * give a thresholding parameter                                   
 * output a thresholded image                                       
 * use the input parameters on a command line                  
 */

int main (int argc, char * argv[])
{
  //return fail message if incorrect number of arguments
  if (argc < 7)
    {
      std::cerr << "Usage: " << std::endl;
      std::cerr << argv[0] << std::endl;
      std::cerr << "InputImageFile OutputImageFile";
      std::cerr << "lowerThreshold upperThreshold";
      std::cerr << "outsideValue insideValue" << std::endl;
      return EXIT_FAILURE;
    }//if

  //pixel type                                        
  using PixelType = unsigned char;
  //three dimensional x, y and z
  constexpr unsigned int Dimension = 3;

  //load image into memory                     
  const char * InputImage = argv[1];
  //make place and name for output image in memory                  
  const char * OutputImage = argv[2];

  //declare lower and upper thresholds                                       
  const auto lowerT = static_cast<PixelType>(atoi(argv[3]));
  const auto upperT = static_cast<PixelType>(atoi(argv[4]));

  //declare outside and inside values                                          
  const auto outsideV = static_cast<PixelType>(atoi(argv[5]));
  const auto insideV = static_cast<PixelType>(atoi(argv[6]));

  //image type constructor
  using ImageType = itk::Image<PixelType, Dimension>;

  //instantiation of an image file reader                           
  using ReaderType = itk::ImageFileReader<ImageType>;
  //creating a reader object                                       
  ReaderType::Pointer reader = ReaderType::New();
  //name image
  reader->SetFileName(InputImage);

  //instantiate threshold image filter
  using FilterType = itk::BinaryThresholdImageFilter<ImageType, ImageType>;
  //create filter object                                                   
  FilterType::Pointer binaryFilter = FilterType::New();

  //set input from reader output                               
  binaryFilter->SetInput(reader->GetOutput());
  //set lower threshold                                                  
  binaryFilter->SetLowerThreshold(lowerT);
  //set upper threshold                                                 
  binaryFilter->SetUpperThreshold(upperT);
  //set outside value                                                   
  binaryFilter->SetOutsideValue(outsideV);
  //set inside value                                                     
  binaryFilter->SetInsideValue(insideV);

  //instantiate writer                                                  
  using WriterType=itk::ImageFileWriter<ImageType>;
  //create writer object                                        
  WriterType::Pointer writer = WriterType::New();
  //name output file                                                        
  writer->SetFileName(OutputImage);
  //put the output of the filter into the writer
  writer->SetInput(binaryFilter->GetOutput());

  //try to write file
  try {                                                 
  writer->Update();
  }catch(itk::ExceptionObject & error){
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }//catch

  return EXIT_SUCCESS;
}//main                                                          

