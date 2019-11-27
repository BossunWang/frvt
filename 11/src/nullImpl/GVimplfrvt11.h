/*
 * This software was developed at the National Institute of Standards and
 * Technology (NIST) by employees of the Federal Government in the course
 * of their official duties. Pursuant to title 17 Section 105 of the
 * United States Code, this software is not subject to copyright protection
 * and is in the public domain. NIST assumes no responsibility  whatsoever for
 * its use by other parties, and makes no guarantees, expressed or implied,
 * about its quality, reliability, or any other characteristic.
 */

#ifndef NULLIMPLFRVT11_H_
#define NULLIMPLFRVT11_H_

#include "frvt11.h"
#include <time.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <memory>
#include <string>
#include <string.h>
#include <sys/stat.h>
#include <string>

#include <inference_engine.hpp>

#include <samples/ocv_common.hpp>
#include <samples/slog.hpp>

//#include "interactive_face_detection.hpp"
#include "detectors.hpp"
#include "face.hpp"
#include "visualizer.hpp"

#include <ie_iextension.h>
#include <ext_list.hpp>

#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/geometry/rectangle.h>
#include <dlib/pixel.h>
#include <dlib/geometry/vector.h>
#include <dlib/pixel.h>
#include <dlib/opencv/to_open_cv.h>
#include <dlib/matrix/matrix.h>
#include <dlib/image_transforms/interpolation.h>
#include <dlib/image_transforms.h>
#include <dlib/opencv.h>
#include <dlib/image_processing/full_object_detection.h>
#include <dlib/image_transforms.h>

#define FR_IMAGE_HEIGHT 224
#define FR_IMAGE_PADDING 25
#define FR_EMBEDDING_SIZE 512



/*
 * Declare the implementation class of the FRVT 1:1 Interface
 */
namespace FRVT_11 {
    class NullImplFRVT11 : public FRVT_11::Interface {
public:

    NullImplFRVT11();
    ~NullImplFRVT11() override;

    FRVT::ReturnStatus
    initialize(const std::string &configDir) override;

    FRVT::ReturnStatus
    createTemplate(
            const FRVT::Multiface &faces,
            FRVT::TemplateRole role,
            std::vector<uint8_t> &templ,
            std::vector<FRVT::EyePair> &eyeCoordinates) override;

    FRVT::ReturnStatus
    matchTemplates(
            const std::vector<uint8_t> &verifTemplate,
            const std::vector<uint8_t> &enrollTemplate,
            double &similarity) override;

    static std::shared_ptr<FRVT_11::Interface>
    getImplementation();

private:
    std::string configDir;
    static const int featureVectorSize{FR_EMBEDDING_SIZE};
    // Some other members
    //unsigned char* input_image = NULL;
    // std::string input_name;
    // std::string output_name;
    std::string deviceName;
    FaceDetection *faceDetector = NULL;
    FacialLandmarksDetection *facialLandmarksDetector = NULL;
    // --------------------------- 1. Load inference engine instance -------------------------------------
    InferenceEngine::Core ie;
    bool bFaceDetectorIsLoaded;
    bool bFaceLandmarkIsLoaded;
    // -----------------------------------------------------------------------------------------------------
    // InferenceEngine::ExecutableNetwork executable_network;
    InferenceEngine::InferRequest infer_request;



    ////////////////////////////////////For FR/////////////////////////////////////
    // InferenceEngine::Core engine_ptr;
	// InferenceEngine::InferRequest infer_request;
    InferenceEngine::CNNNetwork network;
	std::string network_input_name;
    static InferenceEngine::ExecutableNetwork::Ptr exe_network;
	std::vector<std::string> network_OutputName;
	std::map<std::string, int> OutputName_vs_index;
	unsigned char* input_image = NULL;
	// int batch_size;
	double mean_values[3];
	double scale_values[3];
    float FR_emb[512];
    float gender[2];
    float age[7];
    // int imgCount;
	// std::vector<std::string> Device_List;
	// std::string Plugin_Device;
};
}

#endif /* NULLIMPLFRVT11_H_ */