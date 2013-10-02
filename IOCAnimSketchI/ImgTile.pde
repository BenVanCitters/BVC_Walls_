//image tile angles are 60 & 120
class ImgTile
{
  PImage texture;
  float[][] texCoords;
  
  public ImgTile(PImage pImg)
  {
    texture = pImg;
    //come up with a length/height ratio...
    texCoords = new float[][]{{.5,0},
                              {.5+.5/sqrt(3),.5},
                              {.5,1},
                              {.5-.5/sqrt(3),.5}};
//    for(int i = 0; i < texCoords.length; i++)
//    {
//      texCoords[i][0] *= 150;
//      texCoords[i][1] *= 150;
//    }
//    .5+1/sqrt(3)
  }
  public void draw()
  {
    noStroke();
    textureMode(NORMAL);
    beginShape();
    texture(texture);
    
    vertex(texCoords[0][0],texCoords[0][1]
//          ,0,0
          ,texCoords[0][0],texCoords[0][1]
      );
    vertex(texCoords[1][0],texCoords[1][1]
//    ,1,0
          ,texCoords[1][0],texCoords[1][1]
      );
    vertex(texCoords[2][0],texCoords[2][1]
//    ,1,1
          ,texCoords[2][0],texCoords[2][1]
      );
    vertex(texCoords[3][0],texCoords[3][1]
//            ,0,1
          ,texCoords[3][0],texCoords[3][1]
      );
      
    endShape();
  }
  
  public float getEdgeLength()
  {
    return dist(texCoords[0][0],texCoords[0][1], 
                   texCoords[1][0],texCoords[1][1]);
  }
}
