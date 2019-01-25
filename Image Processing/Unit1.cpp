//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
float r[1024][1024];
float g[1024][1024];
float b[1024][1024];
float mGris[1024][1024];

int M=3;
float r2[1024][1024];
float g2[1024][1024];
float b2[1024][1024];
float mGris2[1024][1024];

float mGris3[1024][1024];//pour Iy
float mGris4[1024][1024];//temporel pour calculer G=racin(gx²+gy²)
float mGris5[1024][1024];//l'image de contour

float tanv[256];//pour l'histogramme en niveau de gris
bool nv=true;

//---------------------------------------------------------------------------
float middleInTri(float m[1024][1024],int M,int debutI,int debutJ)
{
float t[7*7];
int i2=0;
for(int i=debutI;i<debutI+M;i++){
        for(int j=debutJ;j<debutJ+M;j++){
                t[i2]=m[i][j];
                i2++;
                }
        }
for(int i=0;i<M*M-1;i++)
        for(int j=i+1;j<M*M;j++)
                if(t[i]>t[j])
                {
                        float l=t[i];
                        t[i]=t[j];
                        t[j]=l;
                }
return t[(M*M)/2];
}

float produitDeConvolutionH(int debutI,int debutJ)
{
float m[3][3]={-1,-2,-1,0,0,0,1,2,1};
float x[3][3];
float s=0;
for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
                x[i][j]=mGris[debutI+i][debutJ+j];
        }
}
for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
                s+=m[i][j]*x[i][j];
        }
}
return s;
}
float produitDeConvolutionV(int debutI,int debutJ)
{
float m[3][3]={-1,0,1,-2,0,2,-1,0,1};
float x[3][3];
float s=0;
for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
                x[i][j]=mGris[debutI+i][debutJ+j];
        }
}
for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
                s+=m[i][j]*x[i][j];
        }
}
return s;
}
//verifier si un point de contour faible est relier avec point de contourt fort
bool veriferSiRelier(float mGris4[1024][1024],int ii,int jj,int seuilMax)
{
for(int i=ii-1;i<ii+1;i++)
for(int j=jj-1;j<jj+1;j++)
if(mGris4[i][j]>seuilMax) return 1;
return 0;
}

float calculMin(float m[1024][1024],int debutI,int debutJ)
{
float t[7*7];
int i2=0;
for(int i=debutI;i<debutI+M;i++){
        for(int j=debutJ;j<debutJ+M;j++){
                t[i2]=m[i][j];
                i2++;
                }
        }
for(int i=0;i<M*M-1;i++)
        for(int j=i+1;j<M*M;j++)
                if(t[i]>t[j])
                {
                        float l=t[i];
                        t[i]=t[j];
                        t[j]=l;
                }
return t[0];
}
float calculMax(float m[1024][1024],int debutI,int debutJ)
{
float t[7*7];
int i2=0;
for(int i=debutI;i<debutI+M;i++){
        for(int j=debutJ;j<debutJ+M;j++){
                t[i2]=m[i][j];
                i2++;
                }
        }
for(int i=0;i<M*M-1;i++)
        for(int j=i+1;j<M*M;j++)
                if(t[i]>t[j])
                {
                        float l=t[i];
                        t[i]=t[j];
                        t[j]=l;
                }
return t[(M*M)-1];
}
float somme(float p[255],int fin)
{
float s=0;
for(int i=0;i<fin;i++)  s+=p[i];
return s;
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button1Click(TObject *Sender)
{
Image1->Width = Image1->Picture->Width;
Image1->Height=Image1->Picture->Height;
Image2->Width = Image1->Picture->Width;
Image2->Height=Image1->Picture->Height;
for(int i=0;i<Image2->Width;i++){
        for(int j = 0; j< Image2->Height; j++){
                r[i][j]=GetRValue(GetPixel(Image1->Canvas->Handle,i,j));
                g[i][j]=GetGValue(GetPixel(Image1->Canvas->Handle,i,j));
                b[i][j]=GetBValue(GetPixel(Image1->Canvas->Handle,i,j));
                //niveau de gris
                mGris[i][j]=(r[i][j]+g[i][j]+b[i][j])/3;
}
}
if(nv)
for(int i=0;i<Image1->Width;i++){
        for(int j = 0; j< Image1->Height; j++){
                Image2->Canvas->Pixels[i][j]=TColor(RGB(mGris[i][j],mGris[i][j],mGris[i][j]));
        }
}
else
for(int i=0;i<Image1->Width;i++){
        for(int j = 0; j< Image1->Height; j++){
                Image1->Canvas->Pixels[i][j]=TColor(RGB(mGris[i][j],mGris[i][j],mGris[i][j]));
        }
}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
Image1->Width = Image1->Picture->Width;
Image1->Height=Image1->Picture->Height;
Image2->Width = Image1->Picture->Width;
Image2->Height=Image1->Picture->Height;
for(int i=0;i<Image2->Width;i++){
        for(int j = 0; j< Image2->Height; j++){
                r[i][j]=GetRValue(GetPixel(Image1->Canvas->Handle,i,j));
                g[i][j]=GetGValue(GetPixel(Image1->Canvas->Handle,i,j));
                b[i][j]=GetBValue(GetPixel(Image1->Canvas->Handle,i,j));
                //niveau de gris
                mGris[i][j]=(r[i][j]+g[i][j]+b[i][j])/3;
}
}
int Seuil=Edit1->Text.ToInt();
if(nv)
for(int i=0;i<Image2->Width;i++){
        for(int j=0;j<Image2->Height;j++){
                if(mGris[i][j]>Seuil)mGris[i][j]=255;
                else mGris[i][j]=0;
                Image2->Canvas->Pixels[i][j]=TColor(RGB(mGris[i][j],mGris[i][j],mGris[i][j]));
                }
        }
else
for(int i=0;i<Image2->Width;i++){
        for(int j=0;j<Image2->Height;j++){
                if(mGris[i][j]>Seuil)mGris[i][j]=255;
                else mGris[i][j]=0;
                Image1->Canvas->Pixels[i][j]=TColor(RGB(mGris[i][j],mGris[i][j],mGris[i][j]));
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
Image1->Width = Image1->Picture->Width;
Image1->Height=Image1->Picture->Height;
Image2->Width = Image1->Picture->Width;
Image2->Height=Image1->Picture->Height;
for(int i=0;i<Image2->Width;i++){
        for(int j = 0; j< Image2->Height; j++){
                r[i][j]=GetRValue(GetPixel(Image1->Canvas->Handle,i,j));
                g[i][j]=GetGValue(GetPixel(Image1->Canvas->Handle,i,j));
                b[i][j]=GetBValue(GetPixel(Image1->Canvas->Handle,i,j));

                r2[i][j]=r[i][j];
                g2[i][j]=g[i][j];
                b2[i][j]=b[i][j];
}
}
for(int i=0;i<Image2->Width-M;i++){
        for(int j=0;j<Image2->Height-M;j++){
                r2[i+M/2][j+M/2]=middleInTri(r,M,i,j);
                g2[i+M/2][j+M/2]=middleInTri(g,M,i,j);
                b2[i+M/2][j+M/2]=middleInTri(b,M,i,j);
                }
        }
if(nv)
for(int i=0;i<Image2->Width;i++){
        for(int j=0;j<Image2->Height;j++){
                Image2->Canvas->Pixels[i][j]=TColor(RGB(r2[i][j],g2[i][j],b2[i][j]));
                }
        }
else
for(int i=0;i<Image2->Width;i++){
        for(int j=0;j<Image2->Height;j++){
                Image1->Canvas->Pixels[i][j]=TColor(RGB(r2[i][j],g2[i][j],b2[i][j]));
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
RadioButton2->Checked=false;
RadioButton3->Checked=false;
RadioButton1->Checked=true;
M=3;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
RadioButton2->Checked=true;
RadioButton3->Checked=false;
RadioButton1->Checked=false;
M=5;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton3Click(TObject *Sender)
{
RadioButton2->Checked=false;
RadioButton3->Checked=true;
RadioButton1->Checked=false;
M=7;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button8Click(TObject *Sender)
{
Image1->Width = Image1->Picture->Width;
Image1->Height=Image1->Picture->Height;
Image2->Width = Image1->Picture->Width;
Image2->Height=Image1->Picture->Height;
for(int i=0;i<Image2->Width;i++){
        for(int j = 0; j< Image2->Height; j++){
                r[i][j]=GetRValue(GetPixel(Image1->Canvas->Handle,i,j));
                g[i][j]=GetGValue(GetPixel(Image1->Canvas->Handle,i,j));
                b[i][j]=GetBValue(GetPixel(Image1->Canvas->Handle,i,j));
                mGris[i][j]=(r[i][j]+g[i][j]+b[i][j])/3;
}
}

for(int i=0;i<Image2->Width;i++){
        for(int j=0;j<Image2->Height;j++){
                mGris2[i][j]=produitDeConvolutionH(i,j);
                }
        }

for(int i=0;i<Image2->Width;i++){
        for(int j=0;j<Image2->Height;j++){
                mGris3[i][j]=produitDeConvolutionV(i,j);
                mGris4[i][j]=sqrt((mGris2[i][j]*mGris2[i][j])+(mGris3[i][j]*mGris3[i][j]));
                }
        }

        //maximum seuil
int seuilMax=Edit2->Text.ToInt();
//minimum seuil
int seuilMin=Edit3->Text.ToInt();
//calcul le max entre Ix Iy
for(int i=0;i<Image2->Width;i++){
        for(int j=0;j<Image2->Height;j++){
                if(mGris4[i][j]<seuilMin)mGris5[i][j]=0;
                else if(mGris4[i][j]>seuilMax)mGris5[i][j]=255;
                }
        }
for(int i=0;i<Image2->Width;i++){
        for(int j=0;j<Image2->Height;j++){
        if(seuilMin<mGris5[i][j]<seuilMax){
                if(veriferSiRelier(mGris4,i,j,seuilMax))mGris5[i][j]=255;
                else mGris5[i][j]=0;
                }
        }
}
if(nv)
for(int i=0;i<Image2->Width;i++){
        for(int j=0;j<Image2->Height;j++){
                Image2->Canvas->Pixels[i][j]=TColor(RGB(mGris5[i][j],mGris5[i][j],mGris5[i][j]));
                }
        }
else
for(int i=0;i<Image2->Width;i++){
        for(int j=0;j<Image2->Height;j++){
                Image1->Canvas->Pixels[i][j]=TColor(RGB(mGris5[i][j],mGris5[i][j],mGris5[i][j]));
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton4Click(TObject *Sender)
{
RadioButton5->Checked=false;
RadioButton6->Checked=false;
RadioButton4->Checked=true;
M=3;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{
Image1->Width = Image1->Picture->Width;
Image1->Height=Image1->Picture->Height;
Image2->Width = Image1->Picture->Width;
Image2->Height=Image1->Picture->Height;
for(int i=0;i<Image2->Width;i++){
        for(int j = 0; j< Image2->Height; j++){
                r[i][j]=GetRValue(GetPixel(Image1->Canvas->Handle,i,j));
                g[i][j]=GetGValue(GetPixel(Image1->Canvas->Handle,i,j));
                b[i][j]=GetBValue(GetPixel(Image1->Canvas->Handle,i,j));
                mGris[i][j]=(r[i][j]+g[i][j]+b[i][j])/3;
}
}

for(int i=0;i<Image2->Width-M;i++){
        for(int j=0;j<Image2->Height-M;j++){
                mGris2[i+M/2][j+M/2]=calculMin(mGris,i,j);
                }
        }
for(int i=0;i<Image2->Width-M;i++){
        for(int j=0;j<Image2->Height-M;j++){
                mGris3[i+M/2][j+M/2]=calculMax(mGris,i,j);
                }
        }
int seuil=Edit4->Text.ToInt();
for(int i=0;i<Image2->Width;i++){
        for(int j=0;j<Image2->Height;j++){
                float m=(mGris3[i][j]-mGris2[i][j])/2;
                if(m>seuil)mGris5[i][j]=255;
                else mGris5[i][j]=0;
                }
        }
if(nv)
for(int i=0;i<Image2->Width;i++){
        for(int j=0;j<Image2->Height;j++){
                Image2->Canvas->Pixels[i][j]=TColor(RGB(mGris5[i][j],mGris5[i][j],mGris5[i][j]));
                }
        }
else
for(int i=0;i<Image2->Width;i++){
        for(int j=0;j<Image2->Height;j++){
                Image1->Canvas->Pixels[i][j]=TColor(RGB(mGris5[i][j],mGris5[i][j],mGris5[i][j]));
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton5Click(TObject *Sender)
{
RadioButton4->Checked=false;
RadioButton6->Checked=false;
RadioButton5->Checked=true;
M=5;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton6Click(TObject *Sender)
{
RadioButton4->Checked=false;
RadioButton5->Checked=false;
RadioButton6->Checked=true;
M=7;
}
//---------------------------------------------------------------------------
int maxH=0;
void __fastcall TForm1::Button4Click(TObject *Sender)
{
Image1->Width=Image1->Picture->Width;
Image1->Height=Image1->Picture->Height;
Image2->Width = Image1->Picture->Width;
Image2->Height=Image1->Picture->Height;
for(int i=0;i<Image1->Width;i++)
        for(int j=0;j<Image1->Height;j++){
                r[i][j]=GetRValue(GetPixel(Image1->Canvas->Handle,i,j));
                g[i][j]=GetGValue(GetPixel(Image1->Canvas->Handle,i,j));
                b[i][j]=GetBValue(GetPixel(Image1->Canvas->Handle,i,j));
                mGris[i][j]=(int)(r[i][j]+g[i][j]+b[i][j])/3;
                }
for(int i=0;i<Image1->Width;i++){
        for(int j=0;j<Image1->Height;j++){
        tanv[int(mGris[i][j])]++;
        }
}
for(int i=0;i<255;i++){
        Series1->AddXY(i,tanv[i],"",1);
        if(tanv[i]>maxH)maxH=tanv[i];
}
Button6->Enabled=true;
Button5->Enabled=true;
Button4->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
if(nv)
for(int i=0;i<Image2->Width;i++){
        for(int j = 0; j< Image2->Height; j++){
                Image2->Canvas->Pixels[i][j]=TColor(RGB(mGris[i][j],mGris[i][j],mGris[i][j]));
        }
}
else
for(int i=0;i<Image2->Width;i++){
        for(int j = 0; j< Image2->Height; j++){
                Image1->Canvas->Pixels[i][j]=TColor(RGB(mGris[i][j],mGris[i][j],mGris[i][j]));
        }
}
Button6->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
float p[255];
for(int i=0;i<255;i++){
        p[i]=(float)tanv[i]/(Image1->Picture->Width*Image1->Picture->Height);
}
for(int i=0;i<255;i++){
        tanv[i]=(int)255*somme(p,i);
}


for(int i=0;i<255;i++){
        Series3->AddXY(i,tanv[i],"",2);
}
Series4->AddXY(0,maxH,"",2);
Button7->Enabled=true;
Button5->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
if(nv)
for(int i=0;i<Image2->Width;i++){
        for(int j = 0; j< Image2->Height; j++){
                Image2->Canvas->Pixels[i][j]=TColor(RGB(tanv[(int)mGris[i][j]],tanv[(int)mGris[i][j]],tanv[(int)mGris[i][j]]));
        }
}
else
for(int i=0;i<Image2->Width;i++){
        for(int j = 0; j< Image2->Height; j++){
                Image1->Canvas->Pixels[i][j]=TColor(RGB(tanv[(int)mGris[i][j]],tanv[(int)mGris[i][j]],tanv[(int)mGris[i][j]]));
        }
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{
if(OpenPictureDialog1->Execute()){
Image1->Picture->LoadFromFile(OpenPictureDialog1->FileName);
Button4->Enabled=true;
Button5->Enabled=false;
Button6->Enabled=false;
Button7->Enabled=false;
Image1->Width=Image1->Picture->Width;
Image1->Height=Image1->Picture->Height;
Image2->Width = Image1->Picture->Width;
Image2->Height=Image1->Picture->Height;
for(int i=0;i<Image2->Width;i++){
        for(int j = 0; j< Image2->Height; j++){
                Image2->Picture=NULL;
        }
}
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton8Click(TObject *Sender)
{
RadioButton8->Checked=true;
RadioButton7->Checked=false;
nv=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton7Click(TObject *Sender)
{
RadioButton8->Checked=false;
RadioButton7->Checked=true;
nv=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button11Click(TObject *Sender)
{
Image1->Width=Image1->Picture->Width;
Image1->Height=Image1->Picture->Height;
Image2->Width = Image1->Picture->Width;
Image2->Height=Image1->Picture->Height;
for(int i=0;i<Image1->Width;i++)
        for(int j=0;j<Image1->Height;j++){
                r[i][j]=GetRValue(GetPixel(Image1->Canvas->Handle,i,j));
                g[i][j]=GetGValue(GetPixel(Image1->Canvas->Handle,i,j));
                b[i][j]=GetBValue(GetPixel(Image1->Canvas->Handle,i,j));
                }
//pour l'histogramme en couleur
float tanvr[256]={0};
float tanvg[256]={0};
float tanvb[256]={0};
for(int i=0;i<Image1->Width;i++){
        for(int j=0;j<Image1->Height;j++){
        int indice=(int)r[i][j];
        tanvr[indice]++;
        indice=(int)g[i][j];
        tanvg[indice]++;
        indice=(int)b[i][j];
        tanvb[indice]++;
        }
}

float pr[256]={0};
float pb[256]={0};
float pg[256]={0};
for(int i=0;i<256;i++){
        pr[i]=(float)tanvr[i]/(Image1->Picture->Width*Image1->Picture->Height);
        pg[i]=(float)tanvg[i]/(Image1->Picture->Width*Image1->Picture->Height);
        pb[i]=(float)tanvb[i]/(Image1->Picture->Width*Image1->Picture->Height);
}

for(int i=0;i<255;i++){
        tanvr[i]=(int)255*somme(pr,i);
        tanvg[i]=(int)255*somme(pg,i);
        tanvb[i]=(int)255*somme(pb,i);
}
if(nv)
for(int i=0;i<Image2->Width;i++){
        for(int j=0;j<Image2->Height;j++){
                Image2->Canvas->Pixels[i][j]=TColor(RGB(tanvr[(int)r[i][j]],tanvg[(int)g[i][j]],tanvb[(int)b[i][j]]));
                }
        }
else
for(int i=0;i<Image2->Width;i++){
        for(int j=0;j<Image2->Height;j++){
                Image1->Canvas->Pixels[i][j]=TColor(RGB(tanvr[(int)r[i][j]],tanvg[(int)g[i][j]],tanvb[(int)b[i][j]]));
                }
        }
}
//---------------------------------------------------------------------------

