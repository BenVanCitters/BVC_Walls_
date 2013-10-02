//image tile angles are 60 & 120
class ImgTile
{
  float pos[];
  float yRotDelta = 0;
  float yRotOffset = 0;
  PImage texture;
  float[][] texCoords;
  float[][] posCoords;
  float [] extDir;
long tmStart = 0;
  float sclDelta;
  public ImgTile(PImage pImg, float[] position)
  {
    extDir = new float[]{cos(PI/3),sin(PI/3)};
    tmStart = millis();
    pos = position;
    texture = pImg;
    //come up with a length/height ratio...
    texCoords = new float[][]{{.5,0},
                              {.5+.5/sqrt(3),.5},
                              {.5,1},
                              {.5-.5/sqrt(3),.5}};
                             
    posCoords = new float[][]{{0,0},
                              {.5/sqrt(3),.5},
                              {0,1},
                              {-.5/sqrt(3),.5}};
              sclDelta = random(.1);                
    yRotOffset = random(TWO_PI);
                     yRotDelta = random(1)/100;         
    for(int i = 0; i < posCoords.length; i++)
    {
      posCoords[i][0] *= 300;
      posCoords[i][1] *= 300;
    }
//    .5+1/sqrt(3)
  }
  
  public void update()
  {
//    szScle *= (2+sclDelta);
  }
  public void draw()
  {
    float len = (millis()-tmStart)/100.f;
    
    float bottomEdge[][] = new float[][]{{posCoords[1][0]+extDir[0]*len,
                                                posCoords[1][1]+extDir[1]*len},
                                               {posCoords[2][0]+extDir[0]*len,
                                                posCoords[2][1]+extDir[1]*len}};
    float yRot = .2*sin(yRotOffset+millis()*yRotDelta);
    float xRot = .1*sin(yRotOffset*1.5+millis()*yRotDelta);
    pushMatrix();
//    rotateY(yRot);
//    rotateX(xRot);
    noStroke();
    textureMode(NORMAL);
    beginShape();
    texture(texture);
    
    vertex(posCoords[0][0],posCoords[0][1]
          ,texCoords[0][0],texCoords[0][1]
      );
    vertex(bottomEdge[0][0],bottomEdge[0][1]
          ,texCoords[1][0],texCoords[1][1]
      );
    vertex(bottomEdge[1][0],bottomEdge[1][1]
          ,texCoords[2][0],texCoords[2][1]
      );
    vertex(posCoords[3][0],posCoords[3][1]
          ,texCoords[3][0],texCoords[3][1]
      );
      
    endShape();
    popMatrix();
  }
  
  public float getEdgeLength()
  {
    return dist(texCoords[0][0],texCoords[0][1], 
                   texCoords[1][0],texCoords[1][1]);
  }
}
