//
// This program takes ASCII-encoded strings
// from the serial port at 9600 baud and graphs them. It expects values in the
// range 0 to 1023, followed by a newline


import processing.serial.*;

Serial myPort;        // The serial port
int nt = 500;         // number of time points
ArrayList acc_x, acc_y, acc_z;    // data to plot
ArrayList vel_x, vel_y, vel_z;    // data to plot
ArrayList pos_x, pos_y, pos_z;    // data to plot
ArrayList pitch, roll;

void setup () {
  // set the window size:
  size(800, 600);        

  // initialize acceleration variables
  acc_x = new ArrayList(nt);
  acc_y = new ArrayList(nt);
  acc_z = new ArrayList(nt);
  vel_x = new ArrayList(nt);
  vel_y = new ArrayList(nt);
  vel_z = new ArrayList(nt);
  pos_x = new ArrayList(nt);
  pos_y = new ArrayList(nt);
  pos_z = new ArrayList(nt);
  pitch = new ArrayList(nt);
  roll = new ArrayList(nt);
  for (int i=0; i < nt; i++) {
    acc_x.add(0.);
    acc_y.add(0.);
    acc_z.add(0.);

    vel_x.add(0.);
    vel_y.add(0.);
    vel_z.add(0.);
    
    pos_x.add(0.);
    pos_y.add(0.);
    pos_z.add(0.);
    
    pitch.add(0.);
    roll.add(0.);
  }


  // List all the available serial ports
  println(Serial.list());
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[17], 9600);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  // set inital background:
  background(0);
}

void draw () {
  background(0);
  fill(0);

  // draw the legend
  textSize(20);
  fill(100, 100, 255);
  text("x-axis", width-70, 20); 
  fill(255, 100, 100);
  text("y-axis", width-70, 40); 
  fill(100, 255, 100);
  text("z-axis", width-70, 60); 

  
  // draw the lines
  int np;
  float pt0, pt1, pv0, pv1;

  int center_v = height/2;
  float scale_v = (1 / sens) * center_v * scaling;
  
  strokeWeight(2);
  np = acc_x.size()-1;
  for (int i=0; i < np-1; i++) {
    pt0 = (float(i) / np) * width;
    pt1 = (float(i+1) / np) * width;
    
    // plot the x-axis data
    stroke(100, 100, 255);
    pv0 = (Float)acc_x.get(i) * scale_v;
    pv1 = (Float)acc_x.get(i+1) * scale_v;
    line(pt0, center_v + pv0, pt1, center_v + pv1);
        
    // plot the y-axis data
    stroke(255, 100, 100);
    pv0 = (Float)acc_y.get(i) * scale_v;
    pv1 = (Float)acc_y.get(i+1) * scale_v;
    line(pt0, center_v + pv0, pt1, center_v + pv1);
    
    // plot the z-axis data
    stroke(100, 255, 100);
    pv0 = (Float)acc_z.get(i) * scale_v;
    pv1 = (Float)acc_z.get(i+1) * scale_v;
    line(pt0, center_v + pv0, pt1, center_v + pv1);
  }


  // plot roll/pitch
  for (int i=0; i < np; i++) {
    stroke(255, 255, 255, 255*(float(i)/float(np)));
    noFill();
    float px = map((Float)roll.get(i), -PI, PI, 0, width);
    float py = map((Float)pitch.get(i), -PI, PI, 0, height);
    //ellipse(px, py, 10, 10);
  }
}

float rquad, yquad;
float r_conv = 180/3.141519256;
void calc_rpy (float Rx, float Ry, float Rz) {      
  float R =  sqrt(pow(Rx, 2)+pow(Ry, 2)+pow(Rz, 2));
  //  float Arx = acos(Rx/R)*r_conv;
  //  float Ary = acos(Ry/R)*r_conv;
  //  float Arz = acos(Rz/R)*r_conv;

  rquad = -atan2(Rx/R, Rz/R);
  yquad = -atan2(Ry/R, Rz/R);

  roll.add(rquad);
  if (roll.size() > nt) {
    roll.remove(0);
  }
  pitch.add(yquad);
  if (pitch.size() > nt) {
    pitch.remove(0);
  }
}

float alpha = 0.2;
float calc_expAvg(float curAvg, float newVal) {
  float newAvg = alpha * newVal + (1 - alpha) * curAvg;
  return newAvg;
}


float aref = 5.0;
float nv = 1024;
float vpg = 0.8; 
float sens = 1.5;
float off = 1.65;
float scaling = 0.5;
void saveData(float ax, float ay, float az) {

  float off_v = (off/aref) * nv;
  float g_conv = (aref / nv) / vpg;

  // save new x-axis data
  ax = (ax - off_v) * g_conv;
  Float axAvg = calc_expAvg((Float)acc_x.get(acc_x.size()-1), ax);
  acc_x.add(axAvg);
  Float vx = (Float)acc_x.get(acc_x.size()-1) + (Float)vel_x.get(vel_x.size()-1);
  vel_x.add(vx);
  if (acc_x.size() > nt) {
    acc_x.remove(0);
    vel_x.remove(0);
  }

  
  // save new y-axis data
  ay = (ay - off_v) * g_conv;
  Float ayAvg = calc_expAvg((Float)acc_y.get(acc_y.size()-1), ay);
  acc_y.add(ayAvg);
  if (acc_y.size() > nt) {
    acc_y.remove(0);
  }
  
  // save new z-axis data
  az = (az - off_v) * g_conv;
  Float azAvg = calc_expAvg((Float)acc_z.get(acc_z.size()-1), az);
  acc_z.add(azAvg);
  if (acc_z.size() > nt) {
    acc_z.remove(0);
  }

  // calculate roll/pitch
  //calc_rpy(axAvg, ayAvg, azAvg);
}

void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  // ensure data is present
  if (inString == null) { 
    return;
  }
  // trim off any whitespace:
  inString = trim(inString);
  // breakup data values (return if not enough)
  String[] inVals = split(inString, ',');
  if (inVals.length < 3) { 
    return;
  }

  saveData(float(inVals[0]), float(inVals[1]), float(inVals[2]));
}

