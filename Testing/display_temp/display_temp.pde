//Program by Jeremy Blum
//www.jeremyblum.com
//Give you the temperature
import processing.serial.*;   //communication over serial port
Serial port;
String data = "";   //string read from serial port
int[] reads = new int[200]; //array to holf 192 values, bigger for outofbounds errors
int r=0,g=0,b=0;    //integers representing R,G,B colors of square

void setup()
{
  size(1000,800);   //window size
  //port = new Serial(this, "COM4", 115200);   //serial port and baud rate
  //if(port.available() >0)
  //{
  //if(port.lastChar() == '~')
  //{
  //port.bufferUntil('.');    //read string until '.' read
  //}
  //}
}

void draw()
{
  background(0,0,0);    //black background
  for(int i = 0; i < 192; i++){
    if(i == 12 || i == 13 || i == 14 || i == 29 || i == 30 || i == 28 || i == 45 || i == 46 || i == 44){
     reads[i] = (int)random(150,400);
    }
    else if(i == 83 || i == 84 || i == 85 || i == 99 || i == 100 || i == 101 || i == 115 || i == 116 || i == 117){
     reads[i] = (int)random(150,400);
    }
    else if(i == 149 || i == 150 || i == 151 || i == 165 || i == 166 || i == 167 || i == 181 || i == 182 || i == 183){
     reads[i] = (int)random(150,400);
    }
    else{
      reads[i] = (int)random(0,200); 
    }
  }
  for(int i = 0; i<192; i++)    //iterate through array for each temperature
  {
    r = int((reads[i]/600.0*255.0));    //red increases as temp increases
    g = 0;//int(((1-(reads[i]/600.0))*255/2));
    b = int(((1-(reads[i]/600.0))*255.0));    //blue decreases as temp increases
    fill(r,g,b);    //set color of square to rgb value
    print(r);
    print(" ");
    print(g);
    print(" ");
    println(b);  
  rect(50*(i%16)+30,50*(i/16)+20, 50, 50);    
  }
}
  
//void serialEvent (Serial port)
//{
//  data = port.readStringUntil('.');
//  data = data.substring(0, data.length() - 1);
//  reads = int(split(data,' '));
//}