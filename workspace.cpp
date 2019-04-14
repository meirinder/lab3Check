#include "workspace.h"
#include <QPainter>
#include <cmath>
#include "settings.h"

WorkSpace::WorkSpace(QWidget *parent) : QWidget(parent) {
    image = new QImage(width(), height(), QImage::Format_ARGB32);
    bits = image->bits();

    readInput();
}

void WorkSpace::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    image = new QImage(width(), height(), QImage::Format_ARGB32);

    bits = image->bits();
    for (int i = 0; i < sizeof(bits) / sizeof(bits[0]); i++) {
        bits[0] = 0;
    }
    make(width(),height());
    painter.drawImage(0, 0, *image);
}

void WorkSpace::readInput()
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
    this->viewModel = new WorkspaceViewModel(a,b,c,d,m,n,colors);
    file.close();
}

void WorkSpace::smoothShading(std::vector <WorkBoundaries> divide,std::vector <double> val,std::vector <int> colInd)
{
    std::vector <NewColor> newColors;
        for(int i=0;i<val.size()-1;i++){
            WorkBoundaries cur(-1,0,0);
            WorkBoundaries next(-1,0,0);
                    foreach(WorkBoundaries j,divide){
                        if(j.color==colInd[i]){
                            cur=j;
                        }
                    }
                    foreach(WorkBoundaries j,divide){
                        if(cur.color>=0 && cur.color+1==j.color){
                            next=j;
                        }
                    }
            if(next.color>=0 && cur.color>=0){
                double k=(val.at(i)-cur.lower)/(cur.higher- cur.lower);
                int r = (1.0-k)*(double)viewModel->colors[cur.color]->red()+k*(double)viewModel->colors[next.color]->red();
                int g = (1.0-k)*(double)viewModel->colors[cur.color]->green()+k*(double)viewModel->colors[next.color]->green();
                int b = (1.0-k)*(double)viewModel->colors[cur.color]->blue()+k*(double)viewModel->colors[next.color]->blue();
                newColors.push_back(NewColor(i,r,g,b));
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



void WorkSpace::make(int width, int height){
    viewModel->start(width,height);
    int i=0;
    for(int u=0;u<width;u++){
        for(int v=0;v<height;v++){
            bits[u*4+v*width*4+0]=viewModel->colors[viewModel->colInd[i]]->blue();
            bits[u*4+v*width*4+1]=viewModel->colors[viewModel->colInd[i]]->green();
            bits[u*4+v*width*4+2]=viewModel->colors[viewModel->colInd[i]]->red();
            bits[u*4+v*width*4+3]=255;
            i++;
        }
    }
    viewModel->divideColor=viewModel->divide;
    if(viewModel->isSmoothed){
        smoothShading(viewModel->divide, viewModel->val, viewModel->colInd);
    }
    if(viewModel->isGrided){
        paintGdrid();
    }
    if(viewModel->isIsolined){
         isolines(viewModel->val, viewModel->colInd, viewModel->divide);
    }
}


void WorkSpace::isolines(std::vector <double> val,std::vector <int> colInd,std::vector <WorkBoundaries> divide)
{
    int stepX = (double)(width())/(double)(viewModel->m);
    int stepY = (double)(height())/(double)(viewModel->n);
    std::vector <WorkCoordinates> nodes;
    for(int i =0;i<width()-stepX;i+=stepX){
        for(int j =0;j<height()-stepY;j+=stepY){

            double col1 = val[j + i*height()];
            double col2 = val[j + (i + stepX - 1)*height()];
            double col3 = val[j + i*height() + stepY - 1];
            double col4 = val[j + (i + stepX - 1)*height() + stepY - 1];
           foreach(WorkBoundaries b,divide){
            if(!((col1<b.lower && col2<b.lower) || (col1>b.lower && col2>b.lower))){
                int x = (stepX)*abs((b.lower-col1))/abs((col2-col1))+i;
                nodes.push_back(WorkCoordinates(x,j));
            }
            if(!((col1<b.lower && col3<b.lower) || (col1>b.lower && col3>b.lower))){
               int y = (stepY)*abs((b.lower-col1))/abs((col3-col1))+j;
               nodes.push_back(WorkCoordinates(i,y));
            }
            if(!((col2<b.lower && col4<b.lower) || (col2>b.lower && col4>b.lower))){
                int y = (stepY)*abs((b.lower-col2))/abs((col4-col2))+j;
                nodes.push_back(WorkCoordinates(i+stepX,y));
            }
            if(!((col3<b.lower && col4<b.lower) || (col3>b.lower && col4>b.lower))){
                int x = (stepX)*abs((b.lower-col3))/abs((col4-col3))+i;
                nodes.push_back(WorkCoordinates(x,j+stepY));
            }
            if(nodes.size()==2){
                    drawLine(nodes[0].x,nodes[0].y,nodes[1].x,nodes[1].y);
            }
            if(nodes.size()==4){
                double col5 = (col1 + col2 + col3 + col4)/4.0;
                if(!((col1<b.lower && col5<b.lower) || (col5>b.lower && col5>b.lower))){
                    int x = (stepX)*abs((b.lower-col1))/abs((col5-col1))+i;
                    int y = (stepY)*abs((b.lower-col1))/abs((col5-col1))+j;
                    drawLine(x,y,nodes[0].x,nodes[0].y);
                    nodes.erase(nodes.begin());
                }
                if(!((col5<b.lower && col3<b.lower) || (col5>b.lower && col3>b.lower))){
                    int x = (stepX)*abs((b.lower-col3))/abs((col5-col3))+i;
                    int y = (stepY)*abs((b.lower-col3))/abs((col5-col3))+j;
                    drawLine(x,y,nodes[0].x,nodes[0].y);
                    nodes.erase(nodes.begin());

                }
                if(!((col2<b.lower && col5<b.lower) || (col2>b.lower && col5>b.lower))){
                    int x = (stepX)*abs((b.lower-col2))/abs((col5-col2))+i;
                    int y = (stepY)*abs((b.lower-col2))/abs((col5-col2))+j;
                    drawLine(x,y,nodes[0].x,nodes[0].y);
                    nodes.erase(nodes.begin());
                }
                if(!((col5<b.lower && col4<b.lower) || (col5>b.lower && col4>b.lower))){
                    int x = (stepX)*abs((b.lower-col4))/abs((col5-col4))+i;
                    int y = (stepY)*abs((b.lower-col4))/abs((col4-col5))+j;
                    drawLine(x,y,nodes[0].x,nodes[0].y);
                    nodes.erase(nodes.begin());
                }
            }
            nodes.clear();
        }
    }
}
}


void WorkSpace::recieveData(int a,int b,int c,int d,int m, int n){
    viewModel->a=a;
    viewModel->b=b;
    viewModel->c=c;
    viewModel->d=d;
    viewModel->m=m;
    viewModel->n=n;
    this->repaint();
}

void WorkSpace::drawLine(int x1, int y1, int x2, int y2) {
    int deltaX = abs(x2 - x1);
    int deltaY = abs(y2 - y1);

    int signX = x1 < x2 ? 1 : -1;
    int signY = y1 < y2 ? 1 : -1;

    int error = deltaX - deltaY;

    setPixel(x2, y2, QColor(255, 255, 255, 255));

    while (x1 != x2 || y1 != y2) {
        setPixel(x1, y1, QColor(255, 255, 255, 255));
        int error2 = error * 2;

        if (error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if (error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
}

void WorkSpace::setPixel(int x, int y, QColor color) {
    int i = (x + y * width()) * 4;
    bits[i] = color.blue();
    bits[i + 1] = color.green();
    bits[i + 2] = color.red();
    bits[i + 3] = color.alpha();
}

void WorkSpace::paintGdrid(){
    double stepX = (double)(width())/(double)(viewModel->m);
    double stepY = (double)(height())/(double)(viewModel->n);
    drawLine(width()-1,0,width()-1,height()-1);
    drawLine(0,height()-1,width()-1,height()-1);
    for(int i=0;i<viewModel->n;i++){
        drawLine(0,stepY*i,width()-1,stepY*i);
    }
    for(int i=0;i<viewModel->m;i++){
        drawLine(stepX*i,0,stepX*i,height()-1);
    }
 //   drawLine(width()-stepX,0,width()-stepX,height()-1);
}

