
PImage imgs[]; 

ImgLayer imgLayers[];

void setup()
{
  size((1366+1920),768,P3D);
  loadImages();
}

void loadImages()
{
  
  File f = new File(dataPath(""));
  File[] children = f.listFiles();
  println(children);
  
  imgs = new PImage[children.length];
  for(int i = 0; i < children.length; i++)
  {
    imgs[i] = loadImage(children[i].getPath());
  }
  
  
  imgLayers = new ImgLayer[5];
  ImgTile imgTiles[][] = new ImgTile[imgLayers.length][children.length*10];
  
  for(int j = 0; j < imgLayers.length; j++)
  {
    for(int i = 0; i < imgTiles[0].length; i++)
    {
      int rndImgIndex = (int)(random(imgs.length));
      imgTiles[j][i] = new ImgTile(imgs[rndImgIndex],
                                new float[]{random(width),
                                            random(height)});
    }
    imgLayers[j] = new ImgLayer(imgTiles[j],getRandRadianDir());
  }
}

/////
float[] getRandQuantizedRadianDir()
{
  int piMult = (int)(random(2));
  piMult = random(1) > .5f ? piMult + 1 : -piMult-1;
  float rad = (piMult * PI/3.f);
  return new float[]{cos(rad),sin(rad)};
}
float[] getRandRadianDir()
{
  float rad = random(TWO_PI);
  return new float[]{cos(rad),sin(rad)};
}
/////

void draw()
{
  background(100);
  int randIndex = (int)(random(imgs.length));

  pushMatrix();
  for(int i = 0; i < imgLayers.length; i++)
  {
    translate(0,0,-1);
    imgLayers[i].update();
    imgLayers[i].draw();
  }
  popMatrix();
  textSize(32);
  fill(0,255,0);
//  translate(0,0,-10);
  text("FR: " + frameRate, 10, 30); 
}
