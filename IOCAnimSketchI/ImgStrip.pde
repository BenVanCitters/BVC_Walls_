//image tile angles are 60 & 120
class ImgStrip
{
  float[] pos;
  float[] vel;
  float[] direction;
  float[] maxOffset;
  ImgTile[] imgTiles;
  private float totalLength = -1.f;
  
  float[] getRandRadianDir()
  {
    int piMult = (int)(random(2));
    piMult = random(1) > .5f ? piMult + 1 : -piMult-1;
    float rad = (piMult * PI/3.f);
    return new float[]{cos(rad),sin(rad)};
  }
  
  public ImgStrip(ImgTile[] tiles, float[] dir)
  {
    imgTiles = tiles;    
    direction = dir;
    
    float spd = .1 + random(.8);
    vel = new float[]{direction[0]*spd,direction[1]*spd};
    setStripLen();
  }

//  public ImgStrip(ImgTile[] tiles)
//  {
//    this (tiles,getRandRadianDir());
////    imgTiles = tiles;
////    float rad = getRandRadianDir();
////    
////    direction = new float[]{cos(rad),sin(rad)};
////    
////    float spd = .51f;
////    vel = new float[]{direction[0]*spd,direction[1]*spd};
////    setStripLen();
//  }
  
  private void setStripLen()
  {
    totalLength = 0.f;
    for(int i = 0; i < imgTiles.length; i++)
    {
      totalLength += imgTiles[i].getEdgeLength();
    }
    maxOffset = new float[]{direction[0]*totalLength,
                            direction[1]*totalLength};
//    totalLength /= dist(0,0,vel[0],vel[1]);
//    totalLength /=100.f;
    
  }
  
  void update()
  {
    
  }
  
  void draw()
  {
    float tm = millis()/1000.f;
    pushMatrix();
    float stripLen = 0.f;
    for(int i = 0; i < imgTiles.length; i++)
    {
      pushMatrix();
      float t = tm;// % (totalLength);
      float mvMtVec[] = new float[]{direction[0]*stripLen+vel[0]*t,
                                    direction[1]*stripLen+vel[1]*t};
      
      translate(mvMtVec[0]%maxOffset[0],
      mvMtVec[1]%maxOffset[1]);
      imgTiles[i].draw();
      stripLen += imgTiles[i].getEdgeLength();
      popMatrix();
    }
    popMatrix();
  }
}
