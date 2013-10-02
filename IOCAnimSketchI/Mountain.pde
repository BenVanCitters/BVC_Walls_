class Mountain
{
  float[] pos;
  float[] vel;
  ImgStrip imgStrip;
  public Mountain()
  {
    
  }
  
  float[] getRandRadianDir()
  {
    int piMult = (int)(random(2));
    piMult = random(1) > .5f ? piMult + 1 : -piMult-1;
    float rad = (piMult * PI/3.f);
    return new float[]{cos(rad),sin(rad)};
  }
  
  public void update()
  {
    pos[0]+=vel[0];
  }
  
  public void draw()
  {
      imgStrip.draw();
  }
}
