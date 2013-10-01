Mountain m;
PImage imgs[]; 
void setup()
{
  size(700,700);
  loadImages();
}

void loadImages()
{
  File f = new File(dataPath(""));
  File[] children = f.listFiles();
  imgs = new PImage[children.length];
  println(children);
  for(int i = 0; i < children.length; i++)
  {
    imgs[i] = loadImage(children[i].getPath());
  }
}

void draw()
{
  int randIndex = (int)(random(imgs.length));
  image(imgs[randIndex],0,0);
}
