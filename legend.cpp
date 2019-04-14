#include "legend.h"
#include <QPainter>
#include <fstream>


Legend::Legend(QWidget *parent) : QWidget(parent)
{
    image = new QImage(width(), height(), QImage::Format_ARGB32);
    bits = image->bits();
    viewModel = new LegendViewModel();
    readInput();
}

void Legend::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    image = new QImage(width(), height(), QImage::Format_ARGB32);
    bits = image->bits();

    for (int i = 0; i < sizeof(bits) / sizeof(bits[0]); i++) {
        bits[0] = 0;
    }
    start();
    painter.drawImage(0, 0, *image);
}

void Legend::readInput()
{
    std::ifstream file;
    file.open("/Users/savely/Downloads/Lab3/input.txt");
    if(!file.is_open()){
        exit(1);
    }
    int a,b,c,d,m,n;
    std::vector <QColor*> colors;
    file>>a>>b>>c>>d>>m>>n;
    while(!file.eof()){
        int r,g,b;
        file>>r>>g>>b;
        colors.push_back(new QColor(r,g,b));
    }
    this->viewModel = new LegendViewModel(a,b,c,d,m,n,colors);
    file.close();
}

void Legend::start(){
    viewModel->start(width(),height());
    int i=0;
    for(int u=0;u<width();u++){
        for(int v=0;v<height();v++){
            bits[u*4+v*width()*4+0]=viewModel->colors[viewModel->colInd[i]]->blue();
            bits[u*4+v*width()*4+1]=viewModel->colors[viewModel->colInd[i]]->green();
            bits[u*4+v*width()*4+2]=viewModel->colors[viewModel->colInd[i]]->red();
            bits[u*4+v*width()*4+3]=255;
            i++;
        }
    }
    if(viewModel->isSmoothed){
        smoothShading(viewModel->divide, viewModel->val, viewModel->colInd);
    }
}

void Legend::smoothShading(std::vector <LegendBoundaries> divide,std::vector <double> val,std::vector <int> colInd)
{
    std::vector <LegendNewColor> newColors;
        for(int i=0;i<val.size()-1;i++){
            LegendBoundaries cur(-1,0,0);
            LegendBoundaries next(-1,0,0);
                    foreach(LegendBoundaries j,divide){
                        if(j.color==colInd[i]){
                            cur=j;
                        }
                    }
                    foreach(LegendBoundaries j,divide){
                        if(cur.color>=0 && cur.color+1==j.color){
                            next=j;
                        }
                    }
            if(next.color>=0 && cur.color>=0){
                double k=(val.at(i)-cur.lower)/(cur.higher- cur.lower);
                int r = (1.0-k)*(double)viewModel->colors[cur.color]->red()+k*(double)viewModel->colors[next.color]->red();
                int g = (1.0-k)*(double)viewModel->colors[cur.color]->green()+k*(double)viewModel->colors[next.color]->green();
                int b = (1.0-k)*(double)viewModel->colors[cur.color]->blue()+k*(double)viewModel->colors[next.color]->blue();
                newColors.push_back(LegendNewColor(i,r,g,b));
            }
        }
        int i=0;
        for(int u=0;u<width();u++){
                for(int v=0;v<height();v++){
                    if(i<newColors.size()){
                    bits[u*4+v*width()*4+0]=newColors.at(i).b;
                    bits[u*4+v*width()*4+1]=newColors.at(i).g;
                    bits[u*4+v*width()*4+2]=newColors.at(i).r;
                    bits[u*4+v*width()*4+3]=255;}
                    i++;
                }
        }

}

