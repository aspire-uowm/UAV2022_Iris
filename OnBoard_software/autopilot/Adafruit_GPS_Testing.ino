#include <math.h>

#define deg2rad(x) (x * PI / 180.0)
#define rad2deg(x) (x * 180.0 / PI)

// 40.27889225135205, 21.752731280931766
// 40.27912701008762, 21.753720765356963

float Border_Pin_1[1][2]= {{40.276271, 21.750355}};
float Border_Pin_2[1][2]= {{40.27694, 21.754913}};
float Border_Pin_3[1][2]= {{40.279405, 21.75615}};
float Border_Pin_4[1][2]= {{40.281533, 21.75396}};
float Border_Pin_5[1][2]= {{40.279833, 21.749441}};

float Estw_Apostash_Apo_lat= 40.277085; 
float Estw_Apostash_Apo_lon= 21.7531; 

float kathetos_lat = 40.276683;
float kathetos_lon = 21.753159;


float Previous_GPS[1][2] = {{40.27762859801926, 21.75134990464876}};
float Current_GPS[1][2] = {{40.277085, 21.7531}};
float Target_GPS[1][2] = {{40.27847681815135, 21.751944673977913}};

void setup(){
  Serial.begin(9600);
  Serial.println("");
  Serial.println("");
  Serial.println("");


  float distance,distance_to_border1,distance_to_border2,distance_to_border3,distance_to_border4,distance_to_border5;
  int status = 0;

  /*
  Serial.print("Current POS Lon:"); Serial.print(" "); Serial.println(Current_GPS[0][0],15);
  Serial.print("Current POS Lat:"); Serial.print(" "); Serial.println(Current_GPS[0][1],15);
  Serial.print("Target POS Lon:"); Serial.print(" "); Serial.println(Target_GPS[0][0],15);
  Serial.print("Target POS Lat:"); Serial.print(" "); Serial.println(Target_GPS[0][1],15);

  distance = distanceGPS(Current_GPS[0][0],Current_GPS[0][1],Target_GPS[0][0], Target_GPS[0][1]);
  Serial.print("Distance:"); Serial.print(" "); Serial.println(distance,4);
  delay(5000);

  distance = distanceGPS(Estw_Apostash_Apo_lat, Estw_Apostash_Apo_lon, kathetos_lat, kathetos_lon);
  Serial.print("Distance:"); Serial.print(" "); Serial.println(distance2,4);
  delay(5000);
  
  status = trajectoryCheckGPS(Previous_GPS[0][0], Previous_GPS[0][1], Current_GPS[0][0], Current_GPS[0][1], Target_GPS[0][0], Target_GPS[0][1]); */

  distance_to_border1 = distance_to_border(Current_GPS[0][0], Current_GPS[0][1], Border_Pin_1[0][0], Border_Pin_1[0][1], Border_Pin_2[0][0], Border_Pin_2[0][1]);
  Serial.print("Distance to Border 1:"); Serial.print(" "); Serial.println(distance_to_border1,5); 

  distance_to_border2 = distance_to_border(Current_GPS[0][0], Current_GPS[0][1], Border_Pin_2[0][0], Border_Pin_2[0][1], Border_Pin_3[0][0], Border_Pin_3[0][1]);
  Serial.print("Distance to Border 2:"); Serial.print(" "); Serial.println(distance_to_border2,5); 

  distance_to_border3 = distance_to_border(Current_GPS[0][0], Current_GPS[0][1], Border_Pin_3[0][0], Border_Pin_3[0][1], Border_Pin_4[0][0], Border_Pin_4[0][1]);
  Serial.print("Distance to Border 3:"); Serial.print(" "); Serial.println(distance_to_border3,5);

  distance_to_border4 = distance_to_border(Current_GPS[0][0], Current_GPS[0][1], Border_Pin_4[0][0], Border_Pin_4[0][1], Border_Pin_5[0][0], Border_Pin_5[0][1]);
  Serial.print("Distance to Border 4:"); Serial.print(" "); Serial.println(distance_to_border4,5);

  distance_to_border5 = distance_to_border(Current_GPS[0][0], Current_GPS[0][1], Border_Pin_5[0][0], Border_Pin_5[0][1], Border_Pin_1[0][0], Border_Pin_1[0][1]);
  Serial.print("Distance to Border 5:"); Serial.print(" "); Serial.println(distance_to_border5,5);

}

void loop(){


}

// This function calculates the distance from a current GPS location to a border defined by two points.
double distance_to_border(double Current_GPS_lat, double Current_GPS_lon, double Border_Point_1_lat, double Border_Point_1_lon, double Border_Point_2_lat, double Border_Point_2_lon){

  // Create arrays to store coordinates
  double CP[1][2] = {{Current_GPS_lat, Current_GPS_lon}};
  double BP1[1][2] = {{Border_Point_1_lat, Border_Point_1_lon}};
  double BP2[1][2] = {{Border_Point_2_lat, Border_Point_2_lon}};

  // Calculate the slope of the line passing through Border Point 1 and Border Point 2
  double l1 = (BP2[0][0]-BP1[0][0])/(BP2[0][1]-BP1[0][1]);

  // Calculate the y-intercept of the line passing through Border Point 1 and Border Point 2
  double b1 = BP1[0][0]-l1*BP1[0][1];

  // Calculate the slope of the line perpendicular to the line passing through Border Point 1 and Border Point 2
  double l2 = -1/l1;

  // Calculate the y-intercept of the line perpendicular to the line passing through Border Point 1 and Border Point 2
  double b2 = CP[0][0]-l2*CP[0][1];

  // Calculate the intersection point of the two lines
  double lat_KP = (b2-b1)/(l1-l2);
  double lon_KP = -(b1*l2-b2*l1)/(l1-l2);

  double KP[1][2] = {{lon_KP, lat_KP}}; // Intersection point coordinates

  // Calculate the distance from the current GPS location to the intersection point
  double distance_to_border = distanceGPS(CP[0][0], CP[0][1], KP[0][0], KP[0][1]);

  return distance_to_border;
}

double distanceGPS(double lat1, double lon1, double lat2, double lon2) {

  // Convert latitude and longitude values from degrees to radians
  lat1 = lat1 * M_PI / 180.0;
  lon1 = lon1 * M_PI / 180.0;
  lat2 = lat2 * M_PI / 180.0;
  lon2 = lon2 * M_PI / 180.0;

  // Calculate the angular distance between the two points in radians
  double deltaLat = lat2 - lat1;
  double deltaLon = lon2 - lon1;
  double a = pow(sin(deltaLat/2), 2) + cos(lat1) * cos(lat2) * pow(sin(deltaLon/2), 2);
  double c = 2 * atan2(sqrt(a), sqrt(1-a));

  // Convert the distance from radians to meters
  double distance = c * 6371000.0;

  return distance;
} 

double absolute_calc(double Ax, double Ay, double Bx, double By) {
    // Calculation of relative angle.
    double a = sqrt(pow((Bx - Ax), 2) + pow((By - Ay), 2));
    double b = abs(Bx - Ax);
    double relative_angle = asin(b / a);

    // Calculation of absolute angle.
    double absolute_angle = 0.0;
    if (Bx > Ax && By > Ay) {
        absolute_angle = relative_angle;
    } else if (Bx > Ax && By < Ay) {
        absolute_angle = PI - relative_angle;
    } else if (Bx < Ax && By < Ay) {
        absolute_angle = PI + relative_angle;
    } else if (Bx < Ax && By > Ay) {
        absolute_angle = 2 * PI - relative_angle;
    }

    // Convert to degrees.
    return (180.0 / PI) * absolute_angle;
}

double trajectoryCheckGPS(double lat1, double lon1, double lat2, double lon2, double lat3, double lon3) {

  // Convert GPS coordinates to Cartesian coordinates
  double prev_pos[1][2] = {{lon1, lat1}};
  double current_pos[1][2] = {{lon2, lat2}};
  double target_pos[1][2] = {{lon3, lat3}};
  double status;

  // Initialize variables
  int dest = 0;
  int div = 0;
  float r = 5;
  
  Serial.print("Current POS Lon:"); Serial.print(" "); Serial.println(current_pos[0][1],15);
  Serial.print("Current POS Lat:"); Serial.print(" "); Serial.println(current_pos[0][0],15);
  Serial.print("Target POS Lon:"); Serial.print(" "); Serial.println(target_pos[0][1],15);
  Serial.print("Target POS Lat:"); Serial.print(" "); Serial.println(target_pos[0][0],15);

  // Calculate distance to target
  double distanceToTarget = distanceGPS(current_pos[0][1], current_pos[0][0], target_pos[0][1], target_pos[0][0]);

  Serial.print("Distance:"); Serial.print(" "); Serial.println(distanceToTarget,4);
  delay(1000);

  // Check if target is reached
  if (distanceToTarget < r) {
    dest = 1;
    Serial.println("\nTarget Complete!");
    status = 0;
  }
  
  // Calculate deviation angle
  double theta = absolute_calc(prev_pos[0][0],prev_pos[0][1], current_pos[0][0], current_pos[0][1]) - absolute_calc(current_pos[0][0], current_pos[0][1], target_pos[0][0], target_pos[0][1]);
  double epsilon = asin(r/distanceToTarget) * 180 / PI;
  
  // Check if deviation is insignificant
  if (-epsilon < theta && theta < epsilon) {
    div = 1;
    Serial.println("\nInsignificant deviation - Continuing straight.");
    status = 1;
  }
  
  // Determine turn direction
  if (dest != 1 && div != 1) {
    if (0 < theta && theta <= 180 || theta < -180) {
      Serial.println("\nTurning left");
      status = 2;
    }
    else if (-180 < theta && theta <= 0 || theta > 180) {
      Serial.println("\nTurning right");
      status = 3;
    }
  }

  return status;
}

