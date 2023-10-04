#include "lib.h"

//---- which sensor to use ----
// TSu06down
float s1_slope [3] = { -0.020384642, -0.014101966, 0.999692753 };
float s2_slope [3] = { -0.004195275,  0.019316927, 0.999804609 };
float s3_slope [3] = { -0.002633071,  0.012574805, 0.999917467 };

float s1_origin[3] = { -328.9982437,  39103.62781, -9682.028961 };
float s2_origin[3] = {  34601.69288, -19825.60025, -9223.299579 };
float s3_origin[3] = { -35141.85037, -19264.36232, -9643.635368 };

float vector_axis[3] = { 1, 1, 1 };
float axis_origin[3] = {0};
//---- inputs ----

//---- calculated values ----
float s1_point[3]     = {0};
float s2_point[3]     = {0};
float s3_point[3]     = {0};

float vector_a[3]     = {0};
float vector_b[3]     = {0};
float vector_norm[3]  = {0};
float unitlength      =  0;

float plane_eqn[4]    = {0};
float plate_center[3] = {0};

//float coldmass[3]     = {0};
//---- calculated values ----

struct position{
    float coldmass[3] = {0};
};


struct position GetColdMass( float s1_reading, float s2_reading, float s3_reading, float rodlength ){ 
    struct position position_coldmass;
// -----------------------------------------------------------------------------------------------------
// -----------------       STEP 1: Locations of the 3 points on the plate         ----------------------
// -----------------------------------------------------------------------------------------------------
// - Inputs: 3 distances from each sensor - "DSDf09upS1" (ID6), "DSDf09upS2" (ID13), "DSDf09upS3" (ID20)
//           origins & slopes of lasers (from the survey group)
// - Calculate the actual length from sensor head to a point, multiplys by that laser's unit vector
//   and then adds that to the origin of the laser head to determine point location
// -----------------------------------------------------------------------------------------------------
    for (int i = 0; i < 3; i++){
        s1_point[i] = s1_origin[i] + s1_slope[i] + (65000 - s1_reading);
        s2_point[i] = s2_origin[i] + s2_slope[i] + (65000 - s2_reading);
        s3_point[i] = s3_origin[i] + s3_slope[i] + (65000 - s3_reading);
    }

// -----------------------------------------------------------------------------------------
// ------------------        STEP 2: Normal vector of the plate        ---------------------
// -----------------------------------------------------------------------------------------
// - Data from above: points one and two for vector a, and points one and three for vector b
// - Cross two vectors in the plane of the plate
// -----------------------------------------------------------------------------------------
    for (int i = 0; i < 3; i++){
        vector_a[i] = s2_point[i] - s1_point[i];
        vector_b[i] = s3_point[i] - s1_point[i];
    }

    vector_norm[0] = vector_b[1] * vector_a[2] - vector_a[1] * vector_b[2];
    vector_norm[1] = vector_b[2] * vector_a[0] - vector_a[2] * vector_b[0];
    vector_norm[2] = vector_b[0] * vector_a[1] - vector_a[0] * vector_b[1];
    unitlength = std::sqrt( std::pow(vector_norm[0], 2) + std::pow(vector_norm[1], 2) + std::pow(vector_norm[2], 2) );

    for (int i = 0; i < 3; i++){    
        vector_norm[i] /= unitlength;
    }

// ----------------------------------------------------------------------------------------------
// ----------------      STEP 3: the plane equation for the plate        ------------------------
// ----------------------------------------------------------------------------------------------
// - Inputs: The normal unit vector - to get the product
//           Half the thickness of the plate
//           (are added to point one)
// - Determine the x1,y1, z1 to be used in the plane equation, which are just a coordinate set 
//   that lies on the plane you want to find the equation of the plane that will be solved for is 
//   the plane that bisects the plate, since the center point of the plate is what stays on the 
//   port tube axis
// ----------------------------------------------------------------------------------------------
    for (int i = 0; i < 3; i++){
        plane_eqn[i] = s1_point[i]; 
    }

// - #plane_eqn_DS09up[3]: finding the value of d in the plane eqn
    float plate_t    = 0;
    float normFactor = 0;
    for (int i = 0; i < 3; i++){
        plane_eqn[3] += vector_norm[i] * s1_point[i];
        
        plate_t += vector_norm[i] * (axis_origin[i] - s1_point[i]);
        normFactor += vector_norm[i] * vector_axis[i];
    }

    plate_t /= (-1) * normFactor;

    for (int i = 0; i < 3; i++){
        plate_center[i] = axis_origin[i] + vector_axis[i] * plate_t;
    }

// -----------------------------------------------------------------------------------------
// --------------------          STEP 4: Cold Mass position        -------------------------
// -----------------------------------------------------------------------------------------
// - Inputs: the normal unit vector
//           the length of rod and plate (adding it to the point at the center of the plate)
// -----------------------------------------------------------------------------------------
    for (int i = 0; i < 3; i++){
        position_coldmass.coldmass[i] = plate_center[i] + vector_norm[i] * rodlength;
    }

    return position_coldmass;
}

void installationTest(){
    struct position coldmass1;
    coldmass1 = GetColdMass( 20018, 17242, 22614, 258166 );    
    for (int i = 0; i < 3; i++){
        std::cout << "coldmass1[" << i << "] = " << coldmass1.coldmass[i] << std::endl;
    }

    struct position coldmass2;
    coldmass2 = GetColdMass( 20072, 17871, 22534, 258166 );
    for (int i = 0; i < 3; i++){
        std::cout << "coldmass2[" << i << "] = " << coldmass2.coldmass[i] << std::endl;
    } 

    float dx = (coldmass2.coldmass[0] - coldmass1.coldmass[0]) / 1000;
    float dy = (coldmass2.coldmass[2] - coldmass1.coldmass[2]) / 1000;
    float dz = (coldmass2.coldmass[1] - coldmass1.coldmass[1]) / 1000;
    std::cout << "dx = " << dx << "mm, dy = " << dy << "mm, dz = " << dz << "mm"<< std::endl;
    std::cout << "total movement = " << std::sqrt( dx*dx + dy*dy + dz*dz ) << "mm" << std::endl;
}
