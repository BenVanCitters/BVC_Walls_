  float[][] shape;
float[][] texCoords;
PImage tex1;
PImage tex2;

void setup()
{
  size(500,500,P3D);
  ortho();
  tex1 = loadImage("1.jpg");
  tex2 = loadImage("2.jpg");
  initShape(80,120,0);
}


float[][] initShape(float leg1Len, float leg2Len, float radOffs)
{
  texCoords= new float[][]{{0,0},{0,1},{1,1},{1,0}};
//  float radOffs = 2;
  float rad = 1;
  
  shape = new float[][]{{cos(radOffs+0),sin(radOffs+0)},
                          {sqrt(3)*cos(radOffs+PI/2),sqrt(3)*sin(radOffs+PI/2)},
                          {-cos(radOffs+0),-sin(radOffs+0)},
                          {sqrt(3)*cos(radOffs+PI*3.f/2),sqrt(3)*sin(radOffs+PI*3.f/2)}};  
                          
//  float leg1Len = 80;
//  float leg2Len = 120;

  float[] leg1Dir = new float[]{shape[0][0]-shape[3][0],
                                shape[0][1]-shape[3][1]};
  float leg1Dist = dist(0,0,leg1Dir[0],leg1Dir[1]); 
  leg1Dir[0] *= leg1Len/leg1Dist;
  leg1Dir[1] *= leg1Len/leg1Dist;  
  
  float[] leg2Dir = new float[]{shape[2][0]-shape[3][0],
                                shape[2][1]-shape[3][1]};
  float leg2Dist = dist(0,0,leg2Dir[0],leg2Dir[1]); 
  leg2Dir[0] *= leg2Len/leg2Dist;
  leg2Dir[1] *= leg2Len/leg2Dist;
  
  shape = new float[][]{{0,0},
                        {leg2Dir[0],leg2Dir[1]},
                        {leg1Dir[0]+leg2Dir[0],leg1Dir[1]+leg2Dir[1]},
                        {leg1Dir[0],leg1Dir[1]}};  

  for(int i = 0; i < shape.length; i++)
  {
    shape[i][0] -= (leg1Dir[0]+leg2Dir[0])/2;
    shape[i][1] -= (leg1Dir[1]+leg2Dir[1])/2;
  }
  return new float[][]{leg1Dir,leg2Dir};
}


void draw()
{
  lights();
  
  background(255,0,0);
  
  float tm = -(millis()/1000.f);
  
  if( (int)(tm/(PI/2)%2) == 0)
  {
    tm = -PI/2;
  }
  else
  {
     tm = tm % (PI/2);
  } 
//  stroke(0);
  noStroke();
  fill(200);
  strokeWeight(2);
  textureMode(NORMAL);
  float[][] offs = initShape(mouseX,mouseY,0);
  for(int k = -5; k < 5; k++)
  for(int j = -5; j < 5; j++)
  {
    
    pushMatrix();
    translate(width/2+offs[0][0]*j+offs[1][0]*k,height/2+offs[0][1]*j+offs[1][1]*k);
    rotateX(tm);
    beginShape();
    texture(tex1);
    for(int i = 0; i < shape.length; i++)
    {
      vertex(shape[i][0],shape[i][1]
      ,texCoords[i][0],texCoords[i][1]
      );
    }
    endShape(CLOSE);
    popMatrix();
    
    
    pushMatrix();
    translate(width/2+offs[0][0]*j+offs[1][0]*k,height/2+offs[0][1]*j+offs[1][1]*k);
    rotateX(tm+PI/2);
    beginShape();
    texture(tex2);
    for(int i = 0; i < shape.length; i++)
    {
      vertex(shape[i][0],shape[i][1]
      ,texCoords[i][0],texCoords[i][1]
      );
    }
    endShape(CLOSE);
    popMatrix();
  }
}
