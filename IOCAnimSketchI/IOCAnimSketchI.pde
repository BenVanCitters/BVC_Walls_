Mountain m;
PImage imgs[]; 
ImgTile imgTiles[];
ImgStrip imgStrip;
ImgStrip imgStrip2;

void setup()
{
  size(700,700,P2D);
  loadImages();
}

void loadImages()
{
  File f = new File(dataPath(""));
  File[] children = f.listFiles();
  imgs = new PImage[children.length];
  imgTiles = new ImgTile[children.length];
  println(children);
  for(int i = 0; i < children.length; i++)
  {
    imgs[i] = loadImage(children[i].getPath());
    imgTiles[i] = new ImgTile(imgs[i]);
  }
  imgStrip = new ImgStrip(imgTiles,getRandRadianDir());
  imgStrip2 = new ImgStrip(imgTiles,getRandRadianDir());
}

/////
float[] getRandRadianDir()
  {
    int piMult = (int)(random(2));
    piMult = -2;// random(1) > .5f ? piMult + 1 : -piMult-1;
    float rad = (piMult * PI/3.f);
    return new float[]{cos(rad),sin(rad)};
  }
/////

void draw()
{
  int randIndex = (int)(random(imgs.length));
//  image(imgs[randIndex],0,0);
  translate(width/2,height/2);
  scale(300);
  imgStrip2.draw();
  translate(0,-1);
  imgStrip.draw();
}
